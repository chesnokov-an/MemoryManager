#ifndef SHAREDSEGMENTDESCRIPTOR_HPP
#define SHAREDSEGMENTDESCRIPTOR_HPP

#include <string>
#include <unordered_map>
#include <algorithm>
#include <Memory/MemoryElement.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/Program.hpp>

namespace MemoryNameSpace{

class SharedSegmentDescriptor final: public ArrayDescriptor{
private:
    std::unordered_map<std::string, Program*> programs_;

public:
    SharedSegmentDescriptor(const std::string& name, size_t size, size_t element_size, size_t offset, Program* program)
            : ArrayDescriptor(name, size, offset, element_size)
            , programs_(std::unordered_map<std::string, Program*>{{program->get_name(), program}}) {};
    void insert_program(Program* program);
    void erase_program(const std::string& name);
    bool check_access(const std::string& name) const;
};

}

#endif