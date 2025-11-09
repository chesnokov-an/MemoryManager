#ifndef SHAREDSEGMENTDESCRIPTOR_HPP
#define SHAREDSEGMENTDESCRIPTOR_HPP

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Memory/MemoryElement.hpp"
#include "Memory/ArrayDescriptor.hpp"
#include "Memory/Program.hpp"

namespace MemoryNameSpace{

class SharedSegmentDescriptor final: public ArrayDescriptor{
private:
    std::vector<std::unique_ptr<Program>> programs_;

public:
    SharedSegmentDescriptor(const std::string& name, size_t size, size_t element_size, size_t offset, Program* program)
            : ArrayDescriptor(name, size, element_size, offset)
            , programs_(std::vector<std::unique_ptr<Program>>{std::unique_ptr<Program>{program}}) {};
    
    void insert_program(Program* program){
        programs_.push_back(std::unique_ptr<Program>{program});
    }

    void erase_program(Program* program){
        auto it = std::find_if(programs_.begin(), programs_.end(),
                                [&program](std::unique_ptr<Program> cur_program){ return cur_program.get() == program; });
        if(it != programs_.end()) programs_.erase(it);
    }

};

}

#endif