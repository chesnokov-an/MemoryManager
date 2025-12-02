#include <Memory/Program.hpp>
#include <Memory/Manager.hpp>

namespace MemoryNameSpace{

const std::string& Program::get_name() const {
    return name_;
}

ReferenceDescriptor* Program::make_reference(const std::string& name, const std::string& target_name){
    ReferenceDescriptor* reference = manager_.make_reference(name, target_name, *this);
    if(reference == nullptr) return nullptr;
    memory_elements_.insert({name, reference});
    return reference;
}

}
