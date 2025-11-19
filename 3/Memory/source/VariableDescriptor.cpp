#include <Memory/VariableDescriptor.hpp>
#include <Memory/ReferenceDescriptor.hpp>

namespace MemoryNameSpace{

ReferenceDescriptor VariableDescriptor::make_reference(std::string name){
    return ReferenceDescriptor{name, this};
}

}