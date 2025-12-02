#include <Memory/MemoryElement.hpp>

namespace MemoryNameSpace{

MemoryElement::~MemoryElement() {}

const std::string& MemoryElement::get_name() const noexcept { return name_; }

size_t MemoryElement::get_size() const noexcept { return size_; }

size_t MemoryElement::get_offset() const noexcept { return offset_; }

void MemoryElement::get_raw_value(std::byte* value) const {
    std::byte* target = manager_.get_data() + offset_;
    std::copy(target, target + size_, value);
}

void MemoryElement::set_raw_value(const std::byte* value){
    std::byte* target = manager_.get_data() + offset_;
    std::copy(value, value + size_, target);
}

ReferenceDescriptor MemoryElement::make_reference(std::string name, IManager& manager) {
    return ReferenceDescriptor{name, name_, manager};
}

}
