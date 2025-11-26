#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <Memory/Manager.hpp>
#include <Memory/MemoryElement.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>
#include <Memory/ReferenceDescriptor.hpp>
#include <Memory/Error.hpp>


namespace MemoryNameSpace{

class Program final{
private:
    std::string name_;
    std::string file_path_;
    size_t memory_limit_;
    size_t used_memory_;
    std::unordered_map<std::string, IMemoryElement*> memory_elements_;
    IManager& manager_;

private:
    template <typename Alloc, typename... ExtraArgs>
    bool Program::allocate_element(const std::string& name, size_t size, Alloc&& allocator, ExtraArgs&&... args);

public:
    Program(std::string name, std::string file_path, size_t memory_limit, IManager& manager)
            : name_(name), file_path_(file_path), memory_limit_(memory_limit), used_memory_(0), memory_elements_(), manager_(manager) {}
    
    const std::string& get_name() const;
    bool allocate_variable(const std::string& name, size_t size);
    bool allocate_array(const std::string& name, size_t size, size_t element_size);
    bool allocate_shared_segment(const std::string& name, size_t size, size_t element_size);
    bool make_reference(const std::string& name, const std::string& target_name);
};

}

#endif