#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <cstring>
#include <optional>
#include <Memory/IManager.hpp>
#include <Memory/MemoryElement.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>

namespace MemoryNameSpace{

/**
 * @class Manager
 * @brief Main memory manager implementation with fixed capacity
 * 
 * The Manager class implements the IManager interface and provides
 * complete memory management functionality including allocation,
 * deallocation, error tracking, program management, and memory defragmentation.
 * 
 * @tparam capacity_ Fixed capacity of the memory buffer in bytes
 */
template <size_t capacity_>
class Manager final : public IManager {
private:
    std::unique_ptr<IBuffer> buffer_;                              ///< Memory buffer implementation
    std::unordered_map<std::string, std::unique_ptr<IMemoryElement>> memory_elements_; ///< All memory elements
    std::vector<Error> error_log_;                                 ///< Error log
    std::unordered_map<std::string, std::unique_ptr<Program>> programs_; ///< Registered programs

private:
    /**
     * @brief Validates and performs memory allocation
     * 
     * @param size Size to allocate in bytes
     * @param program Program requesting allocation
     * @return std::optional<size_t> Offset of allocated block, or nullopt on failure
     */
    std::optional<size_t> valid_allocate(size_t size, const Program& program) override {
        size_t offset = 0;
        try{ offset = buffer_->allocate_block(size); }
        catch(const std::runtime_error& e){
            record_error(SIZE_ERROR, e.what(), program.get_name());
            return std::nullopt;
        }
        return offset;
    }

    /**
     * @brief Validates and performs memory destruction
     * 
     * @param offset Offset of block to destroy
     * @param size Size of block to destroy
     * @param program Program requesting destruction
     * @return true if destruction was successful
     * @return false if destruction failed
     */
    bool valid_destroy(size_t offset, size_t size, const Program& program) override {
        try{ buffer_->destroy_block(offset, size); }
        catch(const std::out_of_range& e){
            record_error(SIZE_ERROR, e.what(), program.get_name());
            return false;
        }
        catch(const std::runtime_error& e){
            record_error(DOUBLE_FREE, e.what(), program.get_name());
            return false;
        }
        return true;
    }

    /**
     * @brief Checks if element exists and records allocation error if it does
     * 
     * @param name Name of element to check
     * @param program Program making the request
     * @return true if element exists (error recorded)
     * @return false if element doesn't exist
     */
    bool check_exist_with_allocate_error(const std::string& name, const Program& program) override {
        auto it = memory_elements_.find(name);
        if(it != memory_elements_.end()){
            record_error(MEMORY_LEAK, "Invalid write. The memory for variable '" + name + "' has already been allocated.", program.get_name());
            return true;
        }
        return false;
    }

    /**
     * @brief Checks if element exists and records destruction error if it doesn't
     * 
     * @param name Name of element to check
     * @param program Program making the request
     * @return true if element doesn't exist (error recorded)
     * @return false if element exists
     */
    bool check_exist_with_destroy_error(const std::string& name, const Program& program) override {
        auto it = memory_elements_.find(name);
        if(it == memory_elements_.end()){
            record_error(MEMORY_LEAK, "Invalid free. The memory for variable '" + name + "' has already been free.", program.get_name());
            return true;
        }
        return false;
    }

    /**
     * @brief Validates shared segment access with error recording
     * 
     * @param prog_name Name of program requesting access
     * @param segment_name Name of shared segment
     * @return true if access is valid
     * @return false if access is invalid (error recorded)
     */
    bool is_correct_shared_with_error(const std::string& prog_name, const std::string& segment_name){
        auto prog_it = programs_.find(prog_name);
        if(prog_it == programs_.end()){
            record_error(ACCESS_ERROR, "The program does not exist.", prog_name);
            return false;
        }
        auto segment_it = memory_elements_.find(segment_name);
        if(segment_it == memory_elements_.end()){
            record_error(ACCESS_ERROR, "The variable '" + segment_name + "' does not exist.", prog_name);
            return false;
        }
        SharedSegmentDescriptor* segment = dynamic_cast<SharedSegmentDescriptor*>(segment_it->second.get());
        if(!segment){
            record_error(ACCESS_ERROR, "The variable '" + segment_name + "' is not shared segment.", prog_name);
            return false;
        }
        return true;
    }

public:
    /**
     * @brief Constructs a new Manager object
     */
    Manager() : IManager(), buffer_(std::unique_ptr<IBuffer>{new Buffer<capacity_>{}}) {};

    /**
     * @brief Inserts a memory element into the manager
     * 
     * @param element Pointer to the memory element to insert
     */
    void insert_element(IMemoryElement* element) override {
        memory_elements_.try_emplace(element->get_name(), std::unique_ptr<IMemoryElement>(element));
    }

    /**
     * @brief Erases a memory element from the manager
     * 
     * @param element Pointer to the memory element to erase
     */
    void erase_element(IMemoryElement* element) override {
        memory_elements_.erase(element->get_name());
    }

    /**
     * @brief Creates a reference to another memory element
     * 
     * @param name Name of the new reference
     * @param target_name Name of the target memory element
     * @param program Program creating the reference
     * @return ReferenceDescriptor* Pointer to created reference, or nullptr on failure
     */
    ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name, const Program& program) override {
        if(check_exist_with_allocate_error(name, program)) return nullptr;
        auto it = memory_elements_.find(target_name);
        if(it == memory_elements_.end()){
            record_error(ACCESS_ERROR, "The variable named '" + target_name + "' does not exist.", program.get_name());
            return nullptr;
        }
        MemoryElement* element = dynamic_cast<MemoryElement*>(it->second.get());
        if(!element){
            record_error(ACCESS_ERROR, "You can't create a link to a link.", program.get_name());
            return nullptr;
        }
        ReferenceDescriptor* reference = new ReferenceDescriptor{element->make_reference(name)};
        memory_elements_.try_emplace(name, std::unique_ptr<IMemoryElement>(reference));
        return reference;
    }

    /**
     * @brief Destroys a memory element by name
     * 
     * @param name Name of element to destroy
     * @param program Program requesting destruction
     * @return true if destruction successful
     * @return false if destruction failed
     */
    bool destroy_element(const std::string& name, const Program& program) override {
        if(check_exist_with_destroy_error(name, program)) return false;
        auto it = memory_elements_.find(name);
        if(!valid_destroy(it->second->get_offset(), it->second->get_size(), program)) return false;
        memory_elements_.erase(name);
        return true;
    }

    /**
     * @brief Gets a memory element by name
     * 
     * @param target_name Name of element to retrieve
     * @return IMemoryElement* Pointer to memory element, or nullptr if not found
     */
    IMemoryElement* get_element(const std::string& target_name) const override {
        auto it = memory_elements_.find(target_name);
        if(it == memory_elements_.end()) return nullptr;
        return it->second.get();
    }

    /**
     * @brief Records an error in the error log
     * 
     * @param type Error type identifier
     * @param description Error description
     * @param program Name of program where error occurred
     */
    void record_error(size_t type, const std::string& description, const std::string& program) override {
        error_log_.push_back(Error{type, description, program});
    }

    /**
     * @brief Adds a new program to the manager
     * 
     * @param name Name of the program
     * @param file_path Path to program file
     * @param memory_limit Memory limit for the program
     * @return Program* Pointer to created program, or nullptr on failure
     */
    Program* add_program(const std::string& name, const std::string& file_path, size_t memory_limit) override {
        auto it = programs_.find(name);
        if(it != programs_.end()){
            record_error(ACCESS_ERROR, "The program has already been created.", it->second->get_name());
            return nullptr;
        }
        auto program = std::make_unique<Program>(name, file_path, memory_limit, *this);
        Program* program_ptr = program.get();
        programs_.insert({name, std::move(program)});
        return program_ptr;
    }

    /**
     * @brief Deletes a program from the manager
     * 
     * @param name Name of program to delete
     */
    void delete_program(const std::string& name) override {
        programs_.erase(name);
    }

    /**
     * @brief Grants access to a shared segment for a program
     * 
     * @param prog_name Name of program requesting access
     * @param segment_name Name of shared segment
     * @return true if access granted successfully
     * @return false if access denied
     */
    bool get_access_to_shared(const std::string& prog_name, const std::string& segment_name) override {
        if(is_correct_shared_with_error(prog_name, segment_name) == false) return false;
        Program* prog = programs_.find(prog_name)->second.get();
        SharedSegmentDescriptor* segment = dynamic_cast<SharedSegmentDescriptor*>(memory_elements_.find(segment_name)->second.get());
        if(prog->possible_for_expansion(segment->get_size()) == false){
            record_error(SIZE_ERROR, "The memory limit in the '" + segment->get_name() + "' program has been exceeded.", prog_name);
            return false;
        }
        prog->insert_element(segment);
        segment->insert_program(prog);
        return true;
    }
    
    /**
     * @brief Revokes access to a shared segment for a program
     * 
     * @param prog_name Name of program to revoke access from
     * @param segment_name Name of shared segment
     * @return true if access revoked successfully
     * @return false if revocation failed
     */
    bool revoke_access_to_shared(const std::string& prog_name, const std::string& segment_name) override {
        if(is_correct_shared_with_error(prog_name, segment_name) == false) return false;
        Program* prog = programs_.find(prog_name)->second.get();
        SharedSegmentDescriptor* segment = dynamic_cast<SharedSegmentDescriptor*>(memory_elements_.find(segment_name)->second.get());
        if(segment->is_last()){
            record_error(MEMORY_LEAK, "This is the last program that owns the segment '" + segment->get_name() + "'.", prog_name);
            return false;
        }
        prog->erase_element(segment);
        segment->erase_program(prog);
        return true;
    }

    /**
     * @brief Gets all registered programs
     * 
     * @return std::unordered_map<std::string, Program*> Map of program names to pointers
     */
    std::unordered_map<std::string, Program*> get_programs() const override {
        std::unordered_map<std::string, Program*> programs;
        for(auto&& [name, ptr] : programs_)
            programs.insert({name, ptr.get()});
        return programs;
    }

    /**
     * @brief Gets raw data buffer pointer
     * 
     * @return std::byte* Pointer to raw memory buffer
     */
    std::byte* get_data() noexcept override {
        return buffer_->get_data();
    }

    /**
     * @brief Gets raw data buffer pointer (const version)
     * 
     * @return const std::byte* Const pointer to raw memory buffer
     */
    const std::byte* get_data() const noexcept override {
        return buffer_->get_data();
    }

    /**
     * @brief Gets the capacity of the memory buffer
     * 
     * @return constexpr size_t Buffer capacity in bytes
     */
    constexpr size_t get_capacity() const noexcept override {
        return capacity_;
    }

    /**
     * @brief Gets all errors from the error log
     * 
     * @return std::vector<Error> Vector of all recorded errors
     */
    std::vector<Error> all_errors() const override {
        return error_log_;
    }

    /**
     * @brief Gets errors for a specific program
     * 
     * @param program_name Name of program to get errors for
     * @return std::vector<Error> Vector of errors for the specified program
     */
    std::vector<Error> program_errors(const std::string& program_name) const override {
        std::vector<Error> errors;
        for(auto&& error : error_log_){
            if(error.get_program() == program_name)
                errors.push_back(error);
        }
        return errors;
    }

    /**
     * @brief Finds all dangling references
     * 
     * @return std::vector<ReferenceDescriptor*> Vector of dangling reference pointers
     */
    std::vector<ReferenceDescriptor*> dungling_reference() const override {
        std::vector<ReferenceDescriptor*> dungling_refs;
        for(auto&& [name, ptr] : memory_elements_){
            ReferenceDescriptor* ref = dynamic_cast<ReferenceDescriptor*>(ptr.get());
            if(ref && (ref->is_valid() == false))
                dungling_refs.push_back(ref);
        }
        return dungling_refs;
    }

    /**
     * @brief Gets memory usage statistics for all programs
     * 
     * @return std::unordered_map<std::string, double> Map of program names to memory usage ratio
     */
    std::unordered_map<std::string, double> statistics() const override {
        std::unordered_map<std::string, double> table;
        for(auto&& [name, ptr] : programs_){
            table.insert({name, static_cast<double>(ptr->get_used_memory()) / static_cast<double>(capacity_)});
        }
        return table;
    }

    /**
     * @brief Gets all memory elements managed by this manager
     * 
     * @return std::unordered_map<std::string, IMemoryElement*> Map of memory element names to pointers
     */
    std::unordered_map<std::string, IMemoryElement*> get_memory_elements() const override {
        std::unordered_map<std::string, IMemoryElement*> result;
        result.reserve(memory_elements_.size());
        for (auto& [name, ptr] : memory_elements_)
            result.emplace(name, ptr.get());
        return result;
    }

    /**
     * @brief Defragments memory by compacting allocated blocks
     * 
     * This method moves all allocated memory blocks to the beginning of the buffer,
     * eliminating fragmentation and creating a single large free block at the end.
     */
    void defragment_memory() override {
        std::vector<IMemoryElement*> elems;
        for(auto& [name, ptr] : memory_elements_)
            elems.push_back(ptr.get());

        std::sort(elems.begin(), elems.end(), [](IMemoryElement* a, IMemoryElement* b){
                return a->get_offset() < b->get_offset();
        });

        size_t new_offset = 0;
        for (IMemoryElement* elem : elems) {
            size_t old_offset = elem->get_offset();
            size_t size = elem->get_size();

            if (old_offset != new_offset) {
                std::memmove(buffer_->get_data() + new_offset, buffer_->get_data() + old_offset, size);
                elem->set_offset(new_offset);
            }
            new_offset += size;
        }

        auto& blocks = buffer_->get_blocks();
        blocks.clear();
        if (new_offset < capacity_)
            blocks.push_back(Block{new_offset, capacity_ - new_offset});
    }
};

}

#endif