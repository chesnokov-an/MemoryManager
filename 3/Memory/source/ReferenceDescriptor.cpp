#include <Memory/ReferenceDescriptor.hpp>
#include <Memory/Buffer.hpp>
#include <Memory/Manager.hpp>

namespace MemoryNameSpace{

IMemoryElement* ReferenceDescriptor::get_element() const {
    return manager_.get_element(target_name_);
}

const std::string& ReferenceDescriptor::get_name() const noexcept {
    return get_element()->get_name();
}

size_t ReferenceDescriptor::get_size() const noexcept {
    return get_element()->get_size();
}

size_t ReferenceDescriptor::get_elem_size() const noexcept {
    return get_element()->get_elem_size();
}

size_t ReferenceDescriptor::get_offset() const noexcept {
    return get_element()->get_offset();
}

bool ReferenceDescriptor::is_valid() const noexcept {
    return (get_element() != nullptr);
}

void ReferenceDescriptor::get_raw_value(std::byte* value, size_t, size_t) const {
    get_element()->get_raw_value(value);
}

void ReferenceDescriptor::set_raw_value(const std::byte* value, size_t, size_t) {
    get_element()->set_raw_value(value);
}

const std::string& ReferenceDescriptor::get_ref_name() const noexcept {
    return name_;
}

}