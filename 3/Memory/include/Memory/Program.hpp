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


namespace MemoryNameSpace{

class Program final{
private:
    std::string name_;
    std::string file_path_;
    size_t memory_limit_;
    std::unordered_map<std::string, IMemoryElement*> memory_elements_;
    IManager& manager_;

public:
    // VariableDescriptor allocate_variable(const std::string& name, size_t size){

    // }
};

}

#endif