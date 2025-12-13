#include <Memory/SharedSegmentDescriptor.hpp>

namespace MemoryNameSpace{

void SharedSegmentDescriptor::insert_program(const Program* program){
    programs_.insert({program->get_name(), program});
}

void SharedSegmentDescriptor::erase_program(const Program* program){
    auto it = programs_.find(program->get_name());
    if(it != programs_.end()) programs_.erase(it);
}

bool SharedSegmentDescriptor::check_access(const std::string& name) const {
    auto it = programs_.find(name);
    if(it != programs_.end()) return true;
    return false;
}

bool SharedSegmentDescriptor::is_last() const {
    return programs_.size() == 1;
}

bool SharedSegmentDescriptor::is_possible_to_destroy(const Program& prog) const {
    if(programs_.find(prog.get_name()) == programs_.end()){
        manager_.record_error(ACCESS_ERROR, "Program doesn't have acces for segment." + name_, prog);
        return false;
    }
    if(!is_last()){
        manager_.record_error(MEMORY_LEAK, "The segment '" + name_ + "' is is still used by others programs.", prog);
        return false;
    }
    return true;
}

}
