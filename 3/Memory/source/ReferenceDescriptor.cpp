#include <Memory/ReferenceDescriptor.hpp>
#include <Memory/Buffer.hpp>
#include <Memory/Manager.hpp>

namespace MemoryNameSpace{

IMemoryElement* ReferenceDescriptor::get_element() const {
    return manager_.get_element(target_name_);
}

const std::string& ReferenceDescriptor::get_name() const noexcept {
    return name_;
}

size_t ReferenceDescriptor::get_size() const noexcept {
    if(is_valid() == false) return 0;
    return get_element()->get_size();
}

size_t ReferenceDescriptor::get_elem_size() const noexcept {
    if(is_valid() == false) return 0;
    return get_element()->get_elem_size();
}

size_t ReferenceDescriptor::get_offset() const noexcept {
    if(is_valid() == false) return manager_.get_capacity();
    return get_element()->get_offset();
}

bool ReferenceDescriptor::is_valid() const noexcept {
    return (get_element() != nullptr);
}

void ReferenceDescriptor::get_raw_value(std::byte* value, size_t begin, size_t end) const {
    if(is_valid() == false) return;
    get_element()->get_raw_value(value, begin, end);
}

void ReferenceDescriptor::set_raw_value(const std::byte* value, size_t begin, size_t end) {
    if(is_valid() == false) return;
    get_element()->set_raw_value(value, begin, end);
}

const std::string& ReferenceDescriptor::get_ref_name() const noexcept {
    return name_;
}

}