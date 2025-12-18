#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <vector>

namespace MemoryNameSpace{

/**
 * @brief Forward declaration of Program class
 */
class Program;

/**
 * @enum error_t
 * @brief Enumeration of error types in the memory management system
 */
enum error_t {
    SIZE_ERROR = 0,    ///< Memory size related errors (overflow, limit exceeded)
    MEMORY_LEAK = 1,   ///< Memory leak errors (double allocation, invalid free)
    DOUBLE_FREE = 2,   ///< Double free errors
    ACCESS_ERROR = 3,  ///< Access permission errors
};

/**
 * @class Error
 * @brief Represents an error in the memory management system
 * 
 * The Error class encapsulates information about errors that occur
 * during memory operations, including type, description, and program context.
 */
class Error final{
private:
    error_t type_;              ///< Type of error
    std::string description_;   ///< Error description
    std::string program_name_;  ///< Name of program where error occurred

public:
    /**
     * @brief Constructs a new Error object
     * 
     * @param type Error type identifier
     * @param description Error description
     * @param program_name Name of program where error occurred
     */
    Error(size_t type, std::string description, const std::string& program_name)
            : type_(static_cast<error_t>(type)), description_(description), program_name_(program_name) {}
    
    /**
     * @brief Gets the error description
     * 
     * @return std::string Error description
     */
    std::string get_description() const;
    
    /**
     * @brief Gets the program name where error occurred
     * 
     * @return const std::string& Reference to program name
     */
    const std::string& get_program() const;
};

}

#endif