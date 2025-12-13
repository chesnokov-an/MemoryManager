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
    std::unordered_map<std::string, IMemoryElement*> memory_elements_;
    IManager& manager_;

public:
    Program(std::string name, std::string file_path, size_t memory_limit, IManager& manager)
            : name_(name), file_path_(file_path), memory_limit_(memory_limit), memory_elements_(), manager_(manager) {}
    
    const std::string& get_name() const;
    void insert_element(IMemoryElement* element);
    void erase_element(IMemoryElement* element);
    ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name);
    void record_error(size_t type, const std::string& description);
    bool destroy_element(const std::string& name);
    bool possible_for_expansion(size_t size) const;
    size_t get_used_memory() const;
    const std::unordered_map<std::string, IMemoryElement*>& get_memory_elements() const noexcept;

    template <memory_element_t Descriptor, typename... ExtraArgs>
    Descriptor* allocate_element(const std::string& name, size_t size, ExtraArgs&&... args){
        if(possible_for_expansion(size) == false){
            manager_.record_error(SIZE_ERROR, "The memory limit in the '" + name_ + "' program has been exceeded", *this);
            return nullptr;
        }
        Descriptor* element = manager_.allocate_element<Descriptor>(name, size, *this, args...);
        if(element == nullptr) return nullptr;
        memory_elements_.insert({name, element});
        return element;
    }
};

}

#endif