#include <Memory/MemoryElement.hpp>

namespace MemoryNameSpace{

const std::string& MemoryElement::get_name() const noexcept { return name_; }

size_t MemoryElement::get_size() const noexcept { return size_; }

void MemoryElement::get_value(IBuffer* buffer, const std::byte* value) const {
    std::byte* target = buffer->get_data() + offset_;
    std::copy(target, target + size_, value);
}

void MemoryElement::set_value(IBuffer* buffer, const std::byte* value){
    std::byte* target = buffer->get_data() + offset_;
    std::copy(value, value + size_, target);
}

ReferenceDescriptor MemoryElement::make_reference(std::string name, IManager& manager) {
    return ReferenceDescriptor{name, name_, manager};
}

}
