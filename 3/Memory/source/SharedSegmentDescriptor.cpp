#include <string>
#include <vector>
#include <algorithm>
#include <Memory/MemoryElement.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/Program.hpp>

namespace MemoryNameSpace{

void SharedSegmentDescriptor::insert_program(Program* program){
    programs_.push_back(program);
}
void SharedSegmentDescriptor::erase_program(Program* program){
    auto it = std::find_if(programs_.begin(), programs_.end(),
                            [&program](Program* cur_program){ return cur_program == program; });
    if(it != programs_.end()) programs_.erase(it);
}

}
