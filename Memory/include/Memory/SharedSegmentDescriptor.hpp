#ifndef SHAREDSEGMENTDESCRIPTOR_HPP
#define SHAREDSEGMENTDESCRIPTOR_HPP

#include <string>
#include <unordered_map>
#include <algorithm>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/Program.hpp>

namespace MemoryNameSpace{

/**
 * @class SharedSegmentDescriptor
 * @brief Descriptor for memory segments that can be shared between multiple programs
 * 
 * SharedSegmentDescriptor extends ArrayDescriptor to support memory segments
 * that can be accessed by multiple programs simultaneously. It tracks which
 * programs have access to the segment and manages access permissions.
 */
class SharedSegmentDescriptor final: public ArrayDescriptor{
private:
    std::unordered_map<std::string, const Program*> programs_; ///< Map of programs with access to this segment

public:
    /**
     * @brief Constructs a new SharedSegmentDescriptor object
     * 
     * @param name Name of the shared segment
     * @param size Total size in bytes
     * @param offset Offset in the memory buffer
     * @param element_size Size of individual elements in bytes
     * @param program Initial program that owns the segment
     * @param manager Reference to the memory manager
     */
    SharedSegmentDescriptor(const std::string& name, size_t size, size_t offset, size_t element_size, const Program* program, IManager& manager)
            : ArrayDescriptor(name, size, offset, element_size, manager)
            , programs_(std::unordered_map<std::string, const Program*>{{program->get_name(), program}}) {};
    
    /**
     * @brief Grants access to the shared segment for a program
     * 
     * @param program Program to grant access to
     */
    void insert_program(const Program* program);
    
    /**
     * @brief Revokes access to the shared segment for a program
     * 
     * @param program Program to revoke access from
     */
    void erase_program(const Program* program);
    
    /**
     * @brief Checks if a program has access to this segment
     * 
     * @param name Name of program to check
     * @return true if program has access
     * @return false if program doesn't have access
     */
    bool check_access(const std::string& name) const;
    
    /**
     * @brief Checks if the segment can be destroyed by the specified program
     * 
     * Overrides base class method to add shared segment logic.
     * 
     * @param prog Name of program attempting destruction
     * @return true if destruction is allowed
     * @return false if destruction is not allowed
     */
    bool is_possible_to_destroy(const std::string& prog) const override;
    
    /**
     * @brief Checks if this is the last program accessing the segment
     * 
     * @return true if this is the only program with access
     * @return false if multiple programs have access
     */
    bool is_last() const;
};

}

#endif