#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <Memory/Buffer.hpp>
#include <Memory/MemoryElement.hpp>
#include <Memory/Error.hpp>

namespace MemoryNameSpace{

class IManager {
public:
    virtual VariableDescriptor allocate_variable(const std::string& name, size_t size) = 0;
    virtual ArrayDescriptor allocate_array(const std::string& name, size_t size, size_t element_size) = 0;
    virtual SharedSegmentDescriptor allocate_shared_segment(const std::string& name, size_t size, size_t element_size) = 0;
    virtual ReferenceDescriptor make_reference(const std::string& name, const std::string& target_name) = 0;
};

template <typename capacity_>
class Manager final : public IManager {
private:
    std::unique_ptr<IBuffer> buffer_;
    std::unordered_map<std::string, std::unique_ptr<IMemoryElement>> memory_elements_;
    std::vector<Error> error_log_;
    std::unordered_map<std::string, std::unique_ptr<Program>> programs_;

public:
    Manager() : buffer_(std::unique_ptr<IBuffer>{new Buffer<capacity_>{}}) {};
    // VariableDescriptor allocate_variable(const std::string& name, size_t size){
    //     size_t offset = 0;
    //     for(size_t i = 0; i < capacity_; i++){
    //         for(size_t j = i; j < capacity_; j++){
    //             if(buffer_[j] )
            
    //         }
    //     }

    //     memory_elements_.insert({name, std::unique_ptr<IMemoryElement>{new VariableDescriptor{name, size, offset}}});
    // }
};

}

#endif