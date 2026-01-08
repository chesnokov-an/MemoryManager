#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <Memory/IManager.hpp>

namespace MemoryNameSpace{

/**
 * @brief Forward declaration of IMemoryElement interface
 */
class IMemoryElement;  // forward

/**
 * @class Program
 * @brief Represents a program with memory management capabilities
 * 
 * The Program class encapsulates a single program instance with its own
 * memory limit, memory elements, and reference to a memory manager.
 * It provides methods for allocating, destroying, and managing memory
 * elements within the program's memory constraints.
 * 
 * @final This class cannot be inherited from
 */
class Program final{
private:
    std::string name_;                          ///< Name of the program
    std::string file_path_;                     ///< Path to the program file
    size_t memory_limit_;                       ///< Maximum memory limit for this program
    std::unordered_map<std::string, IMemoryElement*> memory_elements_; ///< Map of memory elements owned by this program
    IManager& manager_;                         ///< Reference to the memory manager

public:
    /**
     * @brief Constructs a new Program object
     * 
     * @param name Name of the program
     * @param file_path Path to the program file
     * @param memory_limit Maximum memory limit in bytes
     * @param manager Reference to the memory manager
     */
    Program(std::string name, std::string file_path, size_t memory_limit, IManager& manager)
            : name_(name), file_path_(file_path), memory_limit_(memory_limit), memory_elements_(), manager_(manager) {}
    
    /**
     * @brief Gets the name of the program
     * 
     * @return const std::string& Reference to the program name
     */
    const std::string& get_name() const;
    
    /**
     * @brief Inserts a memory element into the program
     * 
     * @param element Pointer to the memory element to insert
     */
    void insert_element(IMemoryElement* element);
    
    /**
     * @brief Erases a memory element from the program
     * 
     * @param element Pointer to the memory element to erase
     */
    void erase_element(IMemoryElement* element);
    
    /**
     * @brief Creates a reference to another memory element
     * 
     * @param name Name of the new reference
     * @param target_name Name of the target memory element
     * @return ReferenceDescriptor* Pointer to the created reference descriptor, or nullptr on failure
     */
    ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name);
    
    /**
     * @brief Records an error for this program
     * 
     * @param type Error type identifier
     * @param description Error description
     */
    void record_error(size_t type, const std::string& description);
    
    /**
     * @brief Destroys a memory element by name
     * 
     * @param name Name of the memory element to destroy
     * @return true if destruction was successful
     * @return false if destruction failed
     */
    bool destroy_element(const std::string& name);
    
    /**
     * @brief Checks if memory can be expanded by the given size
     * 
     * @param size Size to check for expansion
     * @return true if expansion is possible within memory limit
     * @return false if expansion would exceed memory limit
     */
    bool possible_for_expansion(size_t size) const;
    
    /**
     * @brief Gets the total used memory by this program
     * 
     * @return size_t Total used memory in bytes
     */
    size_t get_used_memory() const noexcept;
    
    /**
     * @brief Gets all memory elements owned by this program
     * 
     * @return const std::unordered_map<std::string, IMemoryElement*>& Const reference to memory elements map
     */
    const std::unordered_map<std::string, IMemoryElement*>& get_memory_elements() const noexcept;
    
    /**
     * @brief Destructor for Program
     */
    ~Program();

    /**
     * @brief Allocates a new memory element of specified type
     * 
     * @tparam Descriptor Type of memory element descriptor to allocate
     * @tparam ExtraArgs Types of additional arguments for descriptor construction
     * @param name Name of the new memory element
     * @param size Size of memory to allocate in bytes
     * @param args Additional arguments for descriptor construction
     * @return Descriptor* Pointer to the allocated descriptor, or nullptr on failure
     * 
     * @note This is a templated method that allocates memory elements through the manager
     */
    template <memory_element_t Descriptor, typename... ExtraArgs>
    Descriptor* allocate_element(const std::string& name, size_t size, ExtraArgs&&... args){
        if(possible_for_expansion(size) == false){
            manager_.record_error(SIZE_ERROR, "The memory limit in the '" + name_ + "' program has been exceeded.", name_);
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