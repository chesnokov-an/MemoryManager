#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <optional>
#include <Memory/Buffer.hpp>
#include <Memory/MemoryElement.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>
#include <Memory/Error.hpp>

namespace MemoryNameSpace{

class VariableDescriptor;          // forward
class ArrayDescriptor;             // forward
class SharedSegmentDescriptor;     // forward
class ReferenceDescriptor;         // forward
class IMemoryElement;              // forward

class IManager {
public:
    virtual VariableDescriptor* allocate_variable(const std::string& name, size_t size, const Program& program) = 0;
    virtual ArrayDescriptor* allocate_array(const std::string& name, size_t size, size_t element_size, const Program& program) = 0;
    virtual SharedSegmentDescriptor* allocate_shared_segment(const std::string& name, size_t size, size_t element_size, const Program& program) = 0;
    virtual ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name, const Program& program) = 0;
    virtual void destroy_element(const std::string& name, const Program& program) = 0;
    virtual IMemoryElement* get_element(const std::string& target_name) const = 0;
    virtual void record_error(size_t type, std::string description, const Program& program) = 0;
};

template <size_t capacity_>
class Manager final : public IManager {
private:
    std::unique_ptr<IBuffer> buffer_;
    std::unordered_map<std::string, std::unique_ptr<IMemoryElement>> memory_elements_;
    std::vector<Error> error_log_;
    std::unordered_map<std::string, std::unique_ptr<Program>> programs_;

private:
    std::optional<size_t> valid_allocate(size_t size, const Program& program){
        size_t offset = 0;
        try{ offset = buffer_->allocate_block(size); }
        catch(const std::runtime_error& e){
            error_log_.push_back(Error{SIZE_ERROR, e.what(), program});
            return std::nullopt;
        }
        return offset;
    }

    bool valid_destroy(size_t offset, size_t size, const Program& program){
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

    bool check_exist_with_error(const std::string& name, const Program& program, const std::string& error_description){
        auto it = memory_elements_.find(name);
        if(it != memory_elements_.end()){
            error_log_.push_back(Error{MEMORY_LEAK, error_description, program});
            return true;
        }
        return false;
    }

    bool check_exist_with_allocate_error(const std::string& name, const Program& program){
        return check_exist_with_error(name, program, "Invalid write. The memory for variable '" + name + "' has already been allocated");
    }

    bool check_exist_with_destroy_error(const std::string& name, const Program& program){
        return check_exist_with_error(name, program, "Invalid free. The memory for variable '" + name + "' has already been free");
    }

public:
    Manager() : buffer_(std::unique_ptr<IBuffer>{new Buffer<capacity_>{}}) {};

    template <typename Descriptor, typename... ExtraArgs>
    Descriptor* allocate_element(const std::string& name, size_t size, const Program& program, ExtraArgs&&... args){
        if(check_exist_with_allocate_error(name, program)) return nullptr;
        if(auto offset = valid_allocate(size, program); offset.has_value()){
            Descriptor* element = new Descriptor{name, size, *offset, args...};
            memory_elements_.insert({name, std::unique_ptr<IMemoryElement>{element}});
            return element;
        }
        return nullptr; 
    }

    VariableDescriptor* allocate_variable(const std::string& name, size_t size, const Program& program) override {
        return allocate_element<VariableDescriptor>(name, size, program);
    }

    ArrayDescriptor* allocate_array(const std::string& name, size_t size, size_t element_size, const Program& program) override {
        return allocate_element<ArrayDescriptor>(name, size, program, element_size);
    }

    SharedSegmentDescriptor* allocate_shared_segment(const std::string& name, size_t size, size_t element_size, const Program& program) override {
        return allocate_element<SharedSegmentDescriptor>(name, size, program, element_size, &program);
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

    void record_error(size_t type, std::string description, const Program& program){
        error_log_.push_back(Error{type, description, program});
    }
};

}

#endif