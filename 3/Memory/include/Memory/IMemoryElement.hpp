#ifndef IMEMORYELEMENT_HPP
#define IMEMORYELEMENT_HPP

#include <string>
#include <cstddef>
#include <Memory/Buffer.hpp>

namespace MemoryNameSpace{

/**
 * @brief Forward declaration of Program class
 */
class Program;

/**
 * @class IMemoryElement
 * @brief Interface for all memory elements in the memory management system
 * 
 * IMemoryElement defines the common interface for all memory elements
 * including variables, arrays, references, and shared segments.
 * It provides methods for accessing and manipulating memory content.
 */
class IMemoryElement{
public:
    /**
     * @brief Gets the name of the memory element
     * 
     * @return const std::string& Reference to the element name
     */
    virtual const std::string& get_name() const noexcept = 0;
    
    /**
     * @brief Gets the total size of the memory element
     * 
     * @return size_t Total size in bytes
     */
    virtual size_t get_size() const noexcept = 0;
    
    /**
     * @brief Gets the element size
     * 
     * For arrays, returns the size of individual elements.
     * For variables, returns the total size.
     * 
     * @return size_t Element size in bytes
     */
    virtual size_t get_elem_size() const noexcept = 0;
    
    /**
     * @brief Gets the offset of the memory element in the buffer
     * 
     * @return size_t Offset in bytes
     */
    virtual size_t get_offset() const noexcept = 0;
    
    /**
     * @brief Sets the offset of the memory element in the buffer
     * 
     * @param offset New offset in bytes
     */
    virtual void set_offset(size_t offset) noexcept = 0;
    
    /**
     * @brief Gets raw bytes from the memory element
     * 
     * @param value Buffer to store retrieved bytes
     * @param begin Starting byte offset within element
     * @param end Ending byte offset within element (0 for all)
     */
    virtual void get_raw_value(std::byte* value, size_t begin, size_t end) const = 0;
    
    /**
     * @brief Sets raw bytes in the memory element
     * 
     * @param value Buffer containing bytes to set
     * @param begin Starting byte offset within element
     * @param end Ending byte offset within element (0 for all)
     */
    virtual void set_raw_value(const std::byte* value, size_t begin, size_t end) = 0;
    
    /**
     * @brief Checks if the element can be destroyed by the specified program
     * 
     * @param prog Name of program attempting destruction
     * @return true if destruction is allowed
     * @return false if destruction is not allowed
     */
    virtual bool is_possible_to_destroy(const std::string& prog) const = 0;
    
    /**
     * @brief Destroys the memory element
     * 
     * @param prog Program requesting destruction
     * @return true if destruction successful
     * @return false if destruction failed
     */
    virtual bool destroy(Program& prog) = 0;
    
    /**
     * @brief Checks if this is a reference element
     * 
     * @return true if this is a reference element
     * @return false if this is not a reference element
     */
    virtual bool is_reference() const noexcept = 0;
    
    /**
     * @brief Virtual destructor for interface
     */
    virtual ~IMemoryElement(){};
    
    /**
     * @brief Gets a typed value from the memory element
     * 
     * @tparam T Type of value to retrieve (must be trivially copyable)
     * @param value Reference to store retrieved value
     * @param begin Starting byte offset within element
     * @param end Ending byte offset within element (0 for all)
     * @throws std::runtime_error If type size doesn't match element size
     */
    template<typename T>
    void get_value(T& value, size_t begin = 0, size_t end = 0) const{
        static_assert(std::is_trivially_copyable_v<T>, "MemoryElement::set_value<T> requires trivially copyable type T.");
        if (get_elem_size() != sizeof(T) && get_size() != sizeof(T))
            throw std::runtime_error("Size mismatch in MemoryElement::get_value<T>.");
        get_raw_value(reinterpret_cast<std::byte*>(&value), begin, end);
    }
    
    /**
     * @brief Sets a typed value in the memory element
     * 
     * @tparam T Type of value to set (must be trivially copyable)
     * @param value Value to set
     * @param begin Starting byte offset within element
     * @param end Ending byte offset within element (0 for all)
     * @throws std::runtime_error If type size doesn't match element size
     */
    template<typename T>
    void set_value(const T& value, size_t begin = 0, size_t end = 0){
        static_assert(std::is_trivially_copyable_v<T>, "MemoryElement::get_value<T> requires trivially copyable type T.");
        if (get_elem_size() != sizeof(T) && get_size() != sizeof(T))
            throw std::runtime_error("Size mismatch in MemoryElement::set_value<T>.");
        set_raw_value(reinterpret_cast<const std::byte*>(&value), begin, end);
    }
};

}

#endif