#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <Memory/IManager.hpp>

namespace MemoryNameSpace{

class IMemoryElement;  // forward

class Program final{
private:
    std::string name_;
    std::string file_path_;
    size_t memory_limit_;
    size_t used_memory_;
    std::unordered_map<std::string, IMemoryElement*> memory_elements_;
    IManager& manager_;

public:
    Program(std::string name, std::string file_path, size_t memory_limit, IManager& manager)
            : name_(name), file_path_(file_path), memory_limit_(memory_limit), used_memory_(0), memory_elements_(), manager_(manager) {}
    
    const std::string& get_name() const;
    ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name);

    template <memory_element_t Descriptor, typename... ExtraArgs>
    Descriptor* allocate_element(const std::string& name, size_t size, ExtraArgs&&... args){
        if(size > memory_limit_ - used_memory_){
            manager_.record_error(SIZE_ERROR, "Еhe memory limit in the '" + name_ + "' program has been exceeded", *this);
            return nullptr;
        }
        Descriptor* element = manager_.allocate_element<Descriptor>(name, size, args..., *this);
        if(element == nullptr) return nullptr;
        memory_elements_.insert({name, element});
        used_memory_ += size;
        return element;
    }
};

}

#endif