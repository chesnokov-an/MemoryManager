#ifndef VARIABLEDESCRIPTOR_HPP
#define VARIABLEDESCRIPTOR_HPP

#include <string>
#include <cstddef>
#include <Memory/MemoryElement.hpp>
#include <Memory/ReferenceDescriptor.hpp>

namespace MemoryNameSpace{

class VariableDescriptor final : public MemoryElement{
public:
    VariableDescriptor(const std::string& name, size_t size, size_t offset)
            : MemoryElement(name, size, offset) {};
};

}

#endif