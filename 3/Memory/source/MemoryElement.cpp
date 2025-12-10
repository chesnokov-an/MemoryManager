#include <Memory/MemoryElement.hpp>

namespace MemoryNameSpace{

MemoryElement::~MemoryElement() {}

const std::string& MemoryElement::get_name() const noexcept { return name_; }

size_t MemoryElement::get_size() const noexcept { return size_; }

size_t MemoryElement::get_elem_size() const noexcept { return size_; }

size_t MemoryElement::get_offset() const noexcept { return offset_; }

void MemoryElement::set_offset(size_t offset) noexcept {
    offset_ = offset;
}

void MemoryElement::get_raw_value(std::byte* value, size_t, size_t) const {
    std::byte* target = manager_.get_data() + offset_;
    std::copy(target, target + size_, value);
}

void MemoryElement::set_raw_value(const std::byte* value, size_t, size_t){
    std::byte* target = manager_.get_data() + offset_;
    std::copy(value, value + size_, target);
}

ReferenceDescriptor MemoryElement::make_reference(std::string name) {
    return ReferenceDescriptor{name, name_, manager_};
}

}
