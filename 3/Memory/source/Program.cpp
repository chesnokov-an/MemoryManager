#include <Memory/Program.hpp>

namespace MemoryNameSpace{

const std::string& Program::get_name() const {
    return name_;
}

template <typename Alloc, typename... ExtraArgs>
bool Program::allocate_element(const std::string& name, size_t size, Alloc&& allocator, ExtraArgs&&... args){
    if(size > memory_limit_ - used_memory_){
        manager_.record_error(SIZE_ERROR, "Еhe memory limit in the '" + name_ + "' program has been exceeded", *this);
        return false;
    }
    IMemoryElement* element = (manager_.*allocator)(name, size, args..., *this);
    if(element == nullptr) return false;
    memory_elements_.insert({name, element});
    used_memory_ += size;
    return true;
}

bool Program::allocate_variable(const std::string& name, size_t size){
    return allocate_element(name, size, &IManager::allocate_variable);
}

bool Program::allocate_array(const std::string& name, size_t size, size_t element_size){
    return allocate_element(name, size, &IManager::allocate_array, element_size);
}

bool Program::allocate_shared_segment(const std::string& name, size_t size, size_t element_size){
    return allocate_element(name, size, &IManager::allocate_shared_segment, element_size);
}

bool Program::make_reference(const std::string& name, const std::string& target_name){
    ReferenceDescriptor* reference = manager_.make_reference(name, target_name, *this);
    if(reference == nullptr) return false;
    memory_elements_.insert({name, reference});
    return true;
}

}
