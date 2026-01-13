#ifndef REFERENCEDESCRIPTOR_HPP
#define REFERENCEDESCRIPTOR_HPP

#include <string>
#include <memory>
#include <Memory/IMemoryElement.hpp>
#include <Memory/Program.hpp>

namespace MemoryNameSpace{

/**
 * @brief Forward declaration of IMemoryElement interface
 */
class IMemoryElement;

/**
 * @brief Forward declaration of IManager interface
 */
class IManager;

/**
 * @brief Forward declaration of IBuffer interface
 */
class IBuffer;

/**
 * @class ReferenceDescriptor
 * @brief Descriptor for references to other memory elements
 * 
 * ReferenceDescriptor implements a reference to another memory element.
 * It tracks the target element and provides transparent access to its
 * data while managing reference validity.
 */
class ReferenceDescriptor final : public IMemoryElement{
private:
    std::string name_;         ///< Name of the reference
    std::string target_name_;  ///< Name of the target memory element
    IManager& manager_;        ///< Reference to the memory manager

private:
    /**
     * @brief Gets the target memory element
     * 
     * @return IMemoryElement* Pointer to target element, or nullptr if not found
     */
    IMemoryElement* get_element() const;

public:
    /**
     * @brief Constructs a new ReferenceDescriptor object
     * 
     * @param name Name of the reference
     * @param target_name Name of the target memory element
     * @param manager Reference to the memory manager
     */
    ReferenceDescriptor(const std::string& name, const std::string& target_name, IManager& manager)
            : name_(name), target_name_(target_name), manager_(manager) {};
    
    /**
     * @brief Gets the name of the reference
     * 
     * @return const std::string& Reference to the reference name
     */
    const std::string& get_name() const noexcept override;
    
    /**
     * @brief Gets the size of the referenced element
     * 
     * @return size_t Size of target element in bytes
     */
    size_t get_size() const noexcept override;
    
    /**
     * @brief Gets the element size of the referenced element
     * 
     * @return size_t Element size of target element in bytes
     */
    size_t get_elem_size() const noexcept override;
    
    /**
     * @brief Gets the offset of the referenced element
     * 
     * @return size_t Offset of target element in bytes
     */
    size_t get_offset() const noexcept override;
    
    /**
     * @brief Sets the offset (not allowed for references)
     * 
     * @param offset New offset (ignored for references)
     */
    void set_offset(size_t offset) noexcept override;
    
    /**
     * @brief Checks if the reference is valid (target exists)
     * 
     * @return true if target element exists
     * @return false if target element doesn't exist
     */
    bool is_valid() const noexcept;
    
    /**
     * @brief Gets raw bytes from the referenced element
     * 
     * @param value Buffer to store retrieved bytes
     * @param begin Starting byte offset within element
     * @param end Ending byte offset within element (0 for all)
     */
    void get_raw_value(std::byte* value, size_t begin, size_t end) const override;
    
    /**
     * @brief Sets raw bytes in the referenced element
     * 
     * @param value Buffer containing bytes to set
     * @param begin Starting byte offset within element
     * @param end Ending byte offset within element (0 for all)
     */
    void set_raw_value(const std::byte* value, size_t begin, size_t end) override;
    
    /**
     * @brief Checks if the reference can be destroyed
     * 
     * @param prog Name of program attempting destruction
     * @return true if destruction is allowed
     * @return false if destruction is not allowed
     */
    bool is_possible_to_destroy(const std::string& prog) const override;
    
    /**
     * @brief Destroys the reference
     * 
     * @param prog Program requesting destruction
     * @return true if destruction successful
     * @return false if destruction failed
     */
    bool destroy(Program& prog) override;
    
    /**
     * @brief Checks if this is a reference element
     * 
     * @return true (ReferenceDescriptor is always a reference)
     */
    bool is_reference() const noexcept override;
    
    /**
     * @brief Gets the name of the target element
     * 
     * @return const std::string& Reference to target element name
     */
    const std::string& get_ref_name() const noexcept;
};

}

#endif