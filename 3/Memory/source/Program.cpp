#include <Memory/Program.hpp>
#include <Memory/Manager.hpp>
#include <iostream>

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
    manager_.record_error(type, description, name_);
}

bool Program::destroy_element(const std::string& name){
    auto it = memory_elements_.find(name);
    if(it == memory_elements_.end()){
        record_error(ACCESS_ERROR, "The variable '" + name + "' is not available for program.");
        return false;
    }
    if(!it->second->is_possible_to_destroy(name_)) return false;
    return it->second->destroy(*this);
}

bool Program::possible_for_expansion(size_t size) const {
    if(size > memory_limit_ - get_used_memory())
        return false;
    return true;
}

size_t Program::get_used_memory() const {
    size_t res = 0;
    for(auto&& [name, ptr] : memory_elements_){
        if(!ptr->is_reference())
            res += ptr->get_size();
    }
    return res;
}

const std::unordered_map<std::string, IMemoryElement*>& Program::get_memory_elements() const noexcept {
    return memory_elements_;
}

Program::~Program(){
    for(auto&& [name, ptr] : memory_elements_){
        if(!ptr->is_reference())
            manager_.record_error(MEMORY_LEAK, "The element '" + name + "' is still reachable.", name_);
    }
}

}
