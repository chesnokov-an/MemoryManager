#include <Memory/Program.hpp>
#include <Memory/Manager.hpp>

namespace MemoryNameSpace{

const std::string& Program::get_name() const {
    return name_;
}

void Program::insert_element(IMemoryElement* element){
    memory_elements_.emplace(element->get_name(), element);
}

void Program::erase_element(IMemoryElement* element){
    memory_elements_.erase(element->get_name());
}

ReferenceDescriptor* Program::make_reference(const std::string& name, const std::string& target_name){
    auto it = memory_elements_.find(target_name);
    if(it == memory_elements_.end()){
        record_error(ACCESS_ERROR, "The variable named '" + target_name + "' is not available for program.");
        return nullptr;
    }
    ReferenceDescriptor* reference = manager_.make_reference(name, target_name, *this);
    if(reference == nullptr) return nullptr;
    memory_elements_.insert({name, reference});
    return reference;
}

void Program::record_error(size_t type, const std::string& description){
    manager_.record_error(type, description, *this);
}

bool Program::increase_used_memory(size_t size){
    if(size > memory_limit_ - used_memory_){
        manager_.record_error(SIZE_ERROR, "Еhe memory limit in the '" + name_ + "' program has been exceeded", *this);
        return false;
    }
    used_memory_ += size;
    return true;
}

bool Program::destroy_element(const std::string& name){
    auto it = memory_elements_.find(name);
    if(it == memory_elements_.end()){
        record_error(ACCESS_ERROR, "The variable '" + name + "' is not available for program.");
        return false;
    }
    SharedSegmentDescriptor* segment = dynamic_cast<SharedSegmentDescriptor*>(it->second);
    if(segment && (!segment->is_last())){
        record_error(MEMORY_LEAK, "The segment '" + segment->get_name() + "' is is still used by others programs.");
        return false;
    }
    size_t size = it->second->get_size();
    erase_element(it->second);
    if(manager_.destroy_element(name, *this) == false){
        insert_element(it->second);
        return false;
    }
    used_memory_ -= size;
    return true;
}

}
