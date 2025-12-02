#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <optional>
#include <Memory/IManager.hpp>
#include <Memory/MemoryElement.hpp>

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
            error_log_.push_back(Error{SIZE_ERROR, e.what(), program});
            return std::nullopt;
        }
        return offset;
    }

    bool valid_destroy(size_t offset, size_t size, const Program& program) override {
        try{ buffer_->destroy_block(offset, size); }
        catch(const std::out_of_range& e){
            error_log_.push_back(Error{SIZE_ERROR, e.what(), program});
            return false;
        }
        catch(const std::runtime_error& e){
            error_log_.push_back(Error{DOUBLE_FREE, e.what(), program});
            return false;
        }
        return true;
    }

    bool check_exist_with_error(const std::string& name, const Program& program, const std::string& error_description) override {
        auto it = memory_elements_.find(name);
        if(it != memory_elements_.end()){
            error_log_.push_back(Error{MEMORY_LEAK, error_description, program});
            return true;
        }
        return false;
    }

    bool check_exist_with_allocate_error(const std::string& name, const Program& program) override {
        return check_exist_with_error(name, program, "Invalid write. The memory for variable '" + name + "' has already been allocated");
    }

    bool check_exist_with_destroy_error(const std::string& name, const Program& program) override {
        return check_exist_with_error(name, program, "Invalid free. The memory for variable '" + name + "' has already been free");
    }

public:
    Manager() : buffer_(std::unique_ptr<IBuffer>{new Buffer<capacity_>{}}) {};

    void insert_element(IMemoryElement* element) override {
        memory_elements_.insert({element->get_name(), std::unique_ptr<IMemoryElement>{element}});
    }

    void erase_element(IMemoryElement* element) override {
        memory_elements_.erase(element->get_name());
    }

    ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name, const Program& program) override {
        if(check_exist_with_allocate_error(name, program)) return nullptr;
        auto it = memory_elements_.find(target_name);
        if(it == memory_elements_.end())
            error_log_.push_back(Error{ACCESS_ERROR, "The variable named '" + target_name + "' does not exist", program});
        MemoryElement* element = dynamic_cast<MemoryElement*>(it->second.get());
        if(!element){
            error_log_.push_back(Error{ACCESS_ERROR, "You can't create a link to a link.", program});
        }
        ReferenceDescriptor* reference = new ReferenceDescriptor{element->make_reference(name, *this)};
        memory_elements_.insert({name, std::unique_ptr<IMemoryElement>{reference}});
        return reference;
    }

    void destroy_element(const std::string& name, const Program& program) override {
        if(check_exist_with_destroy_error(name, program)) return;
        auto it = memory_elements_.find(name);
        if(!valid_destroy(it->second->get_offset(), it->second->get_size(), program)) return;
        memory_elements_.erase(name);
    }

    IMemoryElement* get_element(const std::string& target_name) const override {
        auto it = memory_elements_.find(target_name);
        if(it == memory_elements_.end()) return nullptr;
        return it->second.get();
    }

    void record_error(size_t type, std::string description, const Program& program) override {
        error_log_.push_back(Error{type, description, program});
    }

    Program* add_program(const std::string& name, const std::string& file_path, size_t memory_limit){
        auto it = programs_.find(name);
        if(it != programs_.end()){
            error_log_.push_back(Error{ACCESS_ERROR, "The program has already been created.", *(it->second.get())});
            return nullptr;
        }
        Program* program = new Program{name, file_path, memory_limit, *this};
        programs_.insert({name, std::unique_ptr<Program>{program}});
        return program;
    }
};

}

#endif