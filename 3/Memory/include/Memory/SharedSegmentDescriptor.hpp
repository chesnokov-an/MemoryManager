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
    
    void insert_program(Program* program){
        programs_.push_back(program);
    }
    void erase_program(Program* program){
        auto it = std::find_if(programs_.begin(), programs_.end(),
                                [&program](Program* cur_program){ return cur_program == program; });
        if(it != programs_.end()) programs_.erase(it);
    }

};

}

#endif