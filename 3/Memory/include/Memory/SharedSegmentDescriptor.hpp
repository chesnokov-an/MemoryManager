#ifndef SHAREDSEGMENTDESCRIPTOR_HPP
#define SHAREDSEGMENTDESCRIPTOR_HPP

#include <string>
#include <unordered_map>
#include <algorithm>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/Program.hpp>

namespace MemoryNameSpace{

class SharedSegmentDescriptor final: public ArrayDescriptor{
private:
    std::unordered_map<std::string, const Program*> programs_;

public:
    SharedSegmentDescriptor(const std::string& name, size_t size, size_t element_size, size_t offset, const Program* program, IManager& manager)
            : ArrayDescriptor(name, size, offset, element_size, manager)
            , programs_(std::unordered_map<std::string, const Program*>{{program->get_name(), program}}) {};
    void insert_program(const Program* program);
    void erase_program(const std::string& name);
    bool check_access(const std::string& name) const;
};

}

#endif