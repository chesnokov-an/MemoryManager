#ifndef MEMORYELEMENT_HPP
#define MEMORYELEMENT_HPP

#include <string>
#include <cstddef>
#include <Memory/IMemoryElement.hpp>
#include <Memory/ReferenceDescriptor.hpp>
#include <Memory/IManager.hpp>

namespace MemoryNameSpace{

/**
 * @class MemoryElement
 * @brief Base class for memory elements with common functionality
 * 
 * MemoryElement provides the basic implementation for memory elements
 * including name, size, offset management, and raw value operations.
 * It serves as a base class for specific memory element types.
 */
class MemoryElement : public IMemoryElement{
protected:
    std::string name_;     ///< Name of the memory element
    size_t size_;          ///< Total size in bytes
    size_t offset_;        ///< Offset in the memory buffer
    IManager& manager_;    ///< Reference to the memory manager

public:
    /**
     * @brief Constructs a new MemoryElement object
     * 
     * @param name Name of the memory element
     * @param size Total size in bytes
     * @param offset Offset in the memory buffer
     * @param manager Reference to the memory manager
     */
    MemoryElement(const std::string& name, size_t size, size_t offset, IManager& manager)
            : name_(name), size_(size), offset_(offset), manager_(manager) {}
    
    /**
     * @brief Gets the name of the memory element
     * 
     * @return const std::string& Reference to the element name
     */
    const std::string& get_name() const noexcept override;
    
    /**
     * @brief Gets the total size of the memory element
     * 
     * @return size_t Total size in bytes
     */
    size_t get_size() const noexcept override;
    
    /**
     * @brief Gets the element size (for arrays, returns element size; for variables, returns total size)
     * 
     * @return size_t Element size in bytes
     */
    size_t get_elem_size() const noexcept override;
    
    /**
     * @brief Gets the offset of the memory element in the buffer
     * 
     * @return size_t Offset in bytes
     */
    size_t get_offset() const noexcept override;
    
    /**
     * @brief Sets the offset of the memory element in the buffer
     * 
     * @param offset New offset in bytes
     */
    void set_offset(size_t offset) noexcept override;
    
    /**
     * @brief Gets raw bytes from the memory element
     * 
     * @param value Buffer to store retrieved bytes
     * @param begin Starting byte offset within element
     * @param end Ending byte offset within element (0 for all)
     */
    void get_raw_value(std::byte* value, size_t, size_t) const override;
    
    /**
     * @brief Sets raw bytes in the memory element
     * 
     * @param value Buffer containing bytes to set
     * @param begin Starting byte offset within element
     * @param end Ending byte offset within element (0 for all)
     */
    void set_raw_value(const std::byte* value, size_t , size_t) override;
    
    /**
     * @brief Checks if the element can be destroyed by the specified program
     * 
     * @param prog Name of program attempting destruction
     * @return true if destruction is allowed
     * @return false if destruction is not allowed
     */
    bool is_possible_to_destroy(const std::string& prog) const override;
    
    /**
     * @brief Destroys the memory element
     * 
     * @param prog Program requesting destruction
     * @return true if destruction successful
     * @return false if destruction failed
     */
    bool destroy(Program& prog) override;
    
    /**
     * @brief Checks if this is a reference element
     * 
     * @return false (MemoryElement is not a reference)
     */
    bool is_reference() const noexcept override;
    
    /**
     * @brief Creates a reference to this memory element
     * 
     * @param name Name for the new reference
     * @return ReferenceDescriptor New reference descriptor
     */
    virtual ReferenceDescriptor make_reference(std::string name);
    
    /**
     * @brief Virtual destructor for base class
     */
    virtual ~MemoryElement() = 0;
};

}

#endif