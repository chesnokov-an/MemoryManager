#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <optional>
#include <Memory/Buffer.hpp>
#include <Memory/MemoryElement.hpp>
#include <Memory/Error.hpp>

namespace MemoryNameSpace{

class IManager {
public:
    virtual VariableDescriptor* allocate_variable(const std::string& name, size_t size, const Program& program) = 0;
    virtual ArrayDescriptor* allocate_array(const std::string& name, size_t size, size_t element_size, const Program& program) = 0;
    virtual SharedSegmentDescriptor* allocate_shared_segment(const std::string& name, size_t size, size_t element_size, const Program& program) = 0;
    virtual ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name, const Program& program) = 0;
    virtual IMemoryElement* get_element(const std::string& target_name) const = 0;
};

template <typename capacity_>
class Manager final : public IManager {
private:
    std::unique_ptr<IBuffer> buffer_;
    std::unordered_map<std::string, std::unique_ptr<IMemoryElement>> memory_elements_;
    std::vector<Error> error_log_;
    std::unordered_map<std::string, std::unique_ptr<Program>> programs_;

    std::optional<size_t> valid_allocate(size_t size, const Program& program){
        size_t offset = 0;
        try{
            offset = buffer_.allocate_block(size);
        }
        catch(const std::out_of_range& e){
            error_log_.push_back(Error{SIZE_ERROR, program});
            return std::nullopt;
        }
        catch(const std::runtime_error& e){
            error_log_.push_back(Error{DOUBLE_FREE, program});
            return std::nullopt;
        }
        return offset;
    }

public:
    Manager() : buffer_(std::unique_ptr<IBuffer>{new Buffer<capacity_>{}}) {};

    VariableDescriptor* allocate_variable(const std::string& name, size_t size, const Program& program) override {
        auto it = memory_elements_.find(name);
        if(it != memory_elements_.end()){
            if(it->second->is_valid()){
                error_log_.push_back(Error{MEMORY_LEAK, program});
                return nullptr;
            }
            if(auto offset = valid_allocate(size, program); offset.has_value()){
                it->second->size = size;
                it->second->offset = *offset;
                return it->second.get();
            }
            return nullptr;
        }
        if(auto offset = valid_allocate(size, program); offset.has_value()){
            VariableDescriptor* variable = new VariableDescriptor{name, size, *offset};
            memory_elements_.insert({name, std::unique_ptr<IMemoryElement>{variable}});
            return variable;
        }
        return nullptr;
    }

    ArrayDescriptor* allocate_array(const std::string& name, size_t size, size_t element_size, const Program& program) override {
        auto it = memory_elements_.find(name);
        if(it != memory_elements_.end()){
            if(it->second->is_valid()){
                error_log_.push_back(Error{MEMORY_LEAK, program});
                return nullptr;
            }
            if(auto offset = valid_allocate(size, program); offset.has_value()){
                it->second->size = size;
                it->second->offset = *offset;
                it->second->element_size = element_size;
                return it->second.get();
            }
            return nullptr;
        }
        if(auto offset = valid_allocate(size, program); offset.has_value()){
            ArrayDescriptor* array = new ArrayDescriptor{name, size, *offset, element_size};
            memory_elements_.insert({name, std::unique_ptr<IMemoryElement>{array}});
            return array;
        }
        return nullptr;
    }

    SharedSegmentDescriptor* allocate_shared_segment(const std::string& name, size_t size, size_t element_size, const Program& program) override {
        auto it = memory_elements_.find(name);
        if(it != memory_elements_.end()){
            if(!it->second->check_access(program.get_name())){
                error_log_.push_back(Error{ACCESS_ERROR, program});
                return nullptr;
            }
            if(it->second->is_valid()){
                error_log_.push_back(Error{MEMORY_LEAK, program});
                return nullptr;
            }
            if(auto offset = valid_allocate(size, program); offset.has_value()){
                it->second->size = size;
                it->second->offset = *offset;
                it->second->element_size = element_size;
                return it->second.get();
            }
            return nullptr;
        }
        if(auto offset = valid_allocate(size, program); offset.has_value()){
            SharedSegmentDescriptor* shared_segment = new SharedSegmentDescriptor{name, size, *offset, element_size, program};
            memory_elements_.insert({name, std::unique_ptr<IMemoryElement>{shared_segment}});
            return shared_segment;
        }
        return nullptr;
    }

    ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name, const Program& program) override {
        auto it = memory_elements_.find(target_name);
        if(it != memory_elements_.end())
            ReferenceDescriptor reference = it->second->make_reference(name);
        
        error_log_.push_back(Error{ACCESS_ERROR, program});
    }

    IMemoryElement* get_element(const std::string& target_name) const {
        auto it = memory_elements_.find(target_name);
        if(it == memory_elements_.end()) return nullptr;
        return it->second.get();
    }
};

}

#endif