#ifndef ARRAYDESCRIPTOR_HPP
#define ARRAYDESCRIPTOR_HPP

#include <string>
#include <Memory/MemoryElement.hpp>

namespace MemoryNameSpace{

/**
 * @class ArrayDescriptor
 * @brief Descriptor for array memory elements
 * 
 * ArrayDescriptor extends MemoryElement to support array-like
 * memory elements with individual element access.
 */
class ArrayDescriptor : public MemoryElement{
protected:
    size_t element_size_;  ///< Size of individual array elements in bytes

public:
    /**
     * @brief Constructs a new ArrayDescriptor object
     * 
     * @param name Name of the array
     * @param size Total size in bytes
     * @param offset Offset in the memory buffer
     * @param element_size Size of individual elements in bytes
     * @param manager Reference to the memory manager
     */
    ArrayDescriptor(const std::string& name, size_t size, size_t offset, size_t element_size, IManager& manager)
            : MemoryElement(name, size, offset, manager), element_size_(element_size) {}
    
    /**
     * @brief Gets the size of individual array elements
     * 
     * @return size_t Element size in bytes
     */
    size_t get_elem_size() const noexcept override;
    
    /**
     * @brief Gets raw bytes from a portion of the array
     * 
     * @param value Buffer to store retrieved bytes
     * @param begin Starting byte offset within array
     * @param end Ending byte offset within array (0 for all)
     */
    void get_raw_value(std::byte* value, size_t begin, size_t end) const override;
    
    /**
     * @brief Sets raw bytes in a portion of the array
     * 
     * @param value Buffer containing bytes to set
     * @param begin Starting byte offset within array
     * @param end Ending byte offset within array (0 for all)
     */
    void set_raw_value(const std::byte* value, size_t begin, size_t end) override;
};

}

#endif