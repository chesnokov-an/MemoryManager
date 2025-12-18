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

template <size_t capacity_>
class Manager final : public IManager {
private:
    std::unique_ptr<IBuffer> buffer_;
    std::unordered_map<std::string, std::unique_ptr<IMemoryElement>> memory_elements_;
    std::vector<Error> error_log_;
    std::unordered_map<std::string, std::unique_ptr<Program>> programs_;

private:
    std::optional<size_t> valid_allocate(size_t size, const Program& program) override {
        size_t offset = 0;
        try{ offset = buffer_->allocate_block(size); }
        catch(const std::runtime_error& e){
            record_error(SIZE_ERROR, e.what(), program.get_name());
            return std::nullopt;
        }
        return offset;
    }

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

    bool check_exist_with_allocate_error(const std::string& name, const Program& program) override {
        auto it = memory_elements_.find(name);
        if(it != memory_elements_.end()){
            record_error(MEMORY_LEAK, "Invalid write. The memory for variable '" + name + "' has already been allocated.", program.get_name());
            return true;
        }
        return false;
    }

    bool check_exist_with_destroy_error(const std::string& name, const Program& program) override {
        auto it = memory_elements_.find(name);
        if(it == memory_elements_.end()){
            record_error(MEMORY_LEAK, "Invalid free. The memory for variable '" + name + "' has already been free.", program.get_name());
            return true;
        }
        return false;
    }

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
    Manager() : IManager(), buffer_(std::unique_ptr<IBuffer>{new Buffer<capacity_>{}}) {};

    void insert_element(IMemoryElement* element) override {
        memory_elements_.try_emplace(element->get_name(), std::unique_ptr<IMemoryElement>(element));
    }

    void erase_element(IMemoryElement* element) override {
        memory_elements_.erase(element->get_name());
    }

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

    bool destroy_element(const std::string& name, const Program& program) override {
        if(check_exist_with_destroy_error(name, program)) return false;
        auto it = memory_elements_.find(name);
        if(!valid_destroy(it->second->get_offset(), it->second->get_size(), program)) return false;
        memory_elements_.erase(name);
        return true;
    }

    IMemoryElement* get_element(const std::string& target_name) const override {
        auto it = memory_elements_.find(target_name);
        if(it == memory_elements_.end()) return nullptr;
        return it->second.get();
    }

    void record_error(size_t type, const std::string& description, const std::string& program) override {
        error_log_.push_back(Error{type, description, program});
    }

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

    void delete_program(const std::string& name) override {
        programs_.erase(name);
    }

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

    std::unordered_map<std::string, Program*> get_programs() const override {
        std::unordered_map<std::string, Program*> programs;
        for(auto&& [name, ptr] : programs_)
            programs.insert({name, ptr.get()});
        return programs;
    }

    std::byte* get_data() noexcept override {
        return buffer_->get_data();
    }

    const std::byte* get_data() const noexcept override {
        return buffer_->get_data();
    }

    constexpr size_t get_capacity() const noexcept override {
        return capacity_;
    }

    std::vector<Error> all_errors() const override {
        return error_log_;
    }

    std::vector<Error> program_errors(const std::string& program_name) const override {
        std::vector<Error> errors;
        for(auto&& error : error_log_){
            if(error.get_program() == program_name)
                errors.push_back(error);
        }
        return errors;
    }

    std::vector<ReferenceDescriptor*> dungling_reference() const override {
        std::vector<ReferenceDescriptor*> dungling_refs;
        for(auto&& [name, ptr] : memory_elements_){
            ReferenceDescriptor* ref = dynamic_cast<ReferenceDescriptor*>(ptr.get());
            if(ref && (ref->is_valid() == false))
                dungling_refs.push_back(ref);
        }
        return dungling_refs;
    }

    std::unordered_map<std::string, double> statistics() const override {
        std::unordered_map<std::string, double> table;
        for(auto&& [name, ptr] : programs_){
            table.insert({name, static_cast<double>(ptr->get_used_memory()) / static_cast<double>(capacity_)});
        }
        return table;
    }


    std::unordered_map<std::string, IMemoryElement*> get_memory_elements() const override {
        std::unordered_map<std::string, IMemoryElement*> result;
        result.reserve(memory_elements_.size());
        for (auto& [name, ptr] : memory_elements_)
            result.emplace(name, ptr.get());
        return result;
    }

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