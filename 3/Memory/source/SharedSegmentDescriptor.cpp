#include <Memory/SharedSegmentDescriptor.hpp>

namespace MemoryNameSpace{

void SharedSegmentDescriptor::insert_program(const Program* program){
    programs_.insert({program->get_name(), program});
}

void SharedSegmentDescriptor::erase_program(const std::string& name){
    auto it = programs_.find(name);
    if(it != programs_.end()) programs_.erase(it);
}

bool SharedSegmentDescriptor::check_access(const std::string& name) const {
    auto it = programs_.find(name);
    if(it != programs_.end()) return true;
    return false;
}

}
