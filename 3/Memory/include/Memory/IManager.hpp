#ifndef IMANAGER_HPP
#define IMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <optional>
#include <Memory/Buffer.hpp>
#include <Memory/IMemoryElement.hpp>
#include <Memory/Error.hpp>

namespace MemoryNameSpace{

/**
 * @brief Forward declaration of ReferenceDescriptor class
 */
class ReferenceDescriptor;

/**
 * @brief Forward declaration of IMemoryElement interface
 */
class IMemoryElement; 

/**
 * @concept memory_element_t
 * @brief Concept for valid memory element descriptors
 * 
 * Valid memory element types must inherit from IMemoryElement
 * but cannot be IMemoryElement itself (prevents slicing).
 */
template<typename T>
concept memory_element_t =
    std::is_base_of_v<IMemoryElement, T> &&
    !std::is_same_v<IMemoryElement, T>;

/**
 * @class IManager
 * @brief Interface for memory manager implementations
 * 
 * The IManager interface defines the contract for all memory manager
 * implementations. It provides methods for memory allocation, deallocation,
 * program management, error handling, and memory operations.
 */
class IManager {
protected:
    /**
     * @brief Validates and performs memory allocation
     * 
     * @param size Size to allocate in bytes
     * @param program Program requesting allocation
     * @return std::optional<size_t> Offset of allocated block, or nullopt on failure
     */
    virtual std::optional<size_t> valid_allocate(size_t size, const Program& program) = 0;
    
    /**
     * @brief Validates and performs memory destruction
     * 
     * @param offset Offset of block to destroy
     * @param size Size of block to destroy
     * @param program Program requesting destruction
     * @return true if destruction successful
     * @return false if destruction failed
     */
    virtual bool valid_destroy(size_t offset, size_t size, const Program& program) = 0;
    
    /**
     * @brief Checks if element exists and records allocation error if it does
     * 
     * @param name Name of element to check
     * @param program Program making the request
     * @return true if element exists (error recorded)
     * @return false if element doesn't exist
     */
    virtual bool check_exist_with_allocate_error(const std::string& name, const Program& program) = 0;
    
    /**
     * @brief Checks if element exists and records destruction error if it doesn't
     * 
     * @param name Name of element to check
     * @param program Program making the request
     * @return true if element doesn't exist (error recorded)
     * @return false if element exists
     */
    virtual bool check_exist_with_destroy_error(const std::string& name, const Program& program) = 0;
    
public:
    /**
     * @brief Inserts a memory element into the manager
     * 
     * @param element Pointer to memory element to insert
     */
    virtual void insert_element(IMemoryElement* element) = 0;
    
    /**
     * @brief Erases a memory element from the manager
     * 
     * @param element Pointer to memory element to erase
     */
    virtual void erase_element(IMemoryElement* element) = 0;
    
    /**
     * @brief Creates a reference to another memory element
     * 
     * @param name Name of the new reference
     * @param target_name Name of target memory element
     * @param program Program creating the reference
     * @return ReferenceDescriptor* Pointer to created reference, or nullptr on failure
     */
    virtual ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name, const Program& program) = 0;
    
    /**
     * @brief Destroys a memory element by name
     * 
     * @param name Name of element to destroy
     * @param program Program requesting destruction
     * @return true if destruction successful
     * @return false if destruction failed
     */
    virtual bool destroy_element(const std::string& name, const Program& program) = 0;
    
    /**
     * @brief Adds a new program to the manager
     * 
     * @param name Name of the program
     * @param file_path Path to program file
     * @param memory_limit Memory limit for the program
     * @return Program* Pointer to created program, or nullptr on failure
     */
    virtual Program* add_program(const std::string& name, const std::string& file_path, size_t memory_limit) = 0;
    
    /**
     * @brief Deletes a program from the manager
     * 
     * @param name Name of program to delete
     */
    virtual void delete_program(const std::string& name) = 0;
    
    /**
     * @brief Records an error in the error log
     * 
     * @param type Error type identifier
     * @param description Error description
     * @param program Name of program where error occurred
     */
    virtual void record_error(size_t type, const std::string& description, const std::string& program) = 0;
    
    /**
     * @brief Grants access to a shared segment for a program
     * 
     * @param prog_name Name of program requesting access
     * @param segment_name Name of shared segment
     * @return true if access granted successfully
     * @return false if access denied
     */
    virtual bool get_access_to_shared(const std::string& prog_name, const std::string& segment_name) = 0;
    
    /**
     * @brief Revokes access to a shared segment for a program
     * 
     * @param prog_name Name of program to revoke access from
     * @param segment_name Name of shared segment
     * @return true if access revoked successfully
     * @return false if revocation failed
     */
    virtual bool revoke_access_to_shared(const std::string& prog_name, const std::string& segment_name) = 0;

    /**
     * @brief Gets a memory element by name
     * 
     * @param target_name Name of element to retrieve
     * @return IMemoryElement* Pointer to memory element, or nullptr if not found
     */
    virtual IMemoryElement* get_element(const std::string& target_name) const = 0;
    
    /**
     * @brief Gets all registered programs
     * 
     * @return std::unordered_map<std::string, Program*> Map of program names to pointers
     */
    virtual std::unordered_map<std::string, Program*> get_programs() const = 0;
    
    /**
     * @brief Gets raw data buffer pointer
     * 
     * @return std::byte* Pointer to raw memory buffer
     */
    virtual std::byte* get_data() noexcept = 0;
    
    /**
     * @brief Gets raw data buffer pointer (const version)
     * 
     * @return const std::byte* Const pointer to raw memory buffer
     */
    virtual const std::byte* get_data() const noexcept = 0;
    
    /**
     * @brief Gets the capacity of the memory buffer
     * 
     * @return size_t Buffer capacity in bytes
     */
    virtual size_t get_capacity() const noexcept = 0;
    
    /**
     * @brief Gets all memory elements managed by this manager
     * 
     * @return std::unordered_map<std::string, IMemoryElement*> Map of memory element names to pointers
     */
    virtual std::unordered_map<std::string, IMemoryElement*> get_memory_elements() const = 0;

    /**
     * @brief Gets all errors from the error log
     * 
     * @return std::vector<Error> Vector of all recorded errors
     */
    virtual std::vector<Error> all_errors() const = 0;
    
    /**
     * @brief Gets errors for a specific program
     * 
     * @param program_name Name of program to get errors for
     * @return std::vector<Error> Vector of errors for the specified program
     */
    virtual std::vector<Error> program_errors(const std::string& program_name) const = 0;
    
    /**
     * @brief Finds all dangling references
     * 
     * @return std::vector<ReferenceDescriptor*> Vector of dangling reference pointers
     */
    virtual std::vector<ReferenceDescriptor*> dungling_reference() const = 0;
    
    /**
     * @brief Gets memory usage statistics for all programs
     * 
     * @return std::unordered_map<std::string, double> Map of program names to memory usage ratio
     */
    virtual std::unordered_map<std::string, double> statistics() const = 0;
    
    /**
     * @brief Defragments memory by compacting allocated blocks
     */
    virtual void defragment_memory() = 0;
    
    /**
     * @brief Virtual destructor for interface
     */
    virtual ~IManager(){}

    /**
     * @brief Allocates a new memory element of specified type
     * 
     * @tparam Descriptor Type of memory element descriptor to allocate
     * @tparam ExtraArgs Types of additional arguments for descriptor construction
     * @param name Name of the new memory element
     * @param size Size of memory to allocate in bytes
     * @param program Program requesting allocation
     * @param args Additional arguments for descriptor construction
     * @return Descriptor* Pointer to allocated descriptor, or nullptr on failure
     */
    template <memory_element_t Descriptor, typename... ExtraArgs>
    Descriptor* allocate_element(const std::string& name, size_t size, const Program& program, ExtraArgs&&... args){
        if(check_exist_with_allocate_error(name, program)) return nullptr;
        if(auto offset = valid_allocate(size, program); offset.has_value()){
            Descriptor* element = new Descriptor(name, size, *offset, args..., *this);
            insert_element(element);
            return element;
        }
        return nullptr; 
    }
};

}

#endif