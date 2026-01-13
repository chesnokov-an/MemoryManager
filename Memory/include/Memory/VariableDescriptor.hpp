#ifndef VARIABLEDESCRIPTOR_HPP
#define VARIABLEDESCRIPTOR_HPP

#include <string>
#include <cstddef>
#include <Memory/MemoryElement.hpp>

namespace MemoryNameSpace{

/**
 * @class VariableDescriptor
 * @brief Descriptor for simple variable memory elements
 * 
 * VariableDescriptor represents simple, non-array memory elements.
 * It inherits all functionality from MemoryElement without modification.
 */
class VariableDescriptor final : public MemoryElement{
public:
    /**
     * @brief Constructs a new VariableDescriptor object
     * 
     * @param name Name of the variable
     * @param size Size in bytes
     * @param offset Offset in the memory buffer
     * @param manager Reference to the memory manager
     */
    VariableDescriptor(const std::string& name, size_t size, size_t offset, IManager& manager)
            : MemoryElement(name, size, offset, manager) {};
};

}

#endif