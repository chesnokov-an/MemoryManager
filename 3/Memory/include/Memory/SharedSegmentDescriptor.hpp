#ifndef SHAREDSEGMENTDESCRIPTOR_HPP
#define SHAREDSEGMENTDESCRIPTOR_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <Memory/MemoryElement.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/Program.hpp>

namespace MemoryNameSpace{

class SharedSegmentDescriptor final: public ArrayDescriptor{
private:
    std::vector<Program*> programs_;

public:
    SharedSegmentDescriptor(const std::string& name, size_t size, size_t element_size, size_t offset, Program* program)
            : ArrayDescriptor(name, size, offset, element_size), programs_(std::vector<Program*>{program}) {};
    void insert_program(Program* program);
    void erase_program(Program* program);

};

}

#endif