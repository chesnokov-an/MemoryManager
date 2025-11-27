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

size_t ReferenceDescriptor::get_offset() const noexcept {
    return get_element()->get_offset();
}

bool ReferenceDescriptor::is_valid() const noexcept {
    return (get_element() != nullptr);
}

void ReferenceDescriptor::get_value(IBuffer* buffer, std::byte* value) const {
    get_element()->get_value(buffer, value);
}

void ReferenceDescriptor::set_value(IBuffer* buffer, const std::byte* value) {
    get_element()->set_value(buffer, value);
}

const std::string& ReferenceDescriptor::get_ref_name() const noexcept {
    return name_;
}

}