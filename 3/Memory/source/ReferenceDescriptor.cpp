#include <string>
#include <memory>
#include <Memory/ReferenceDescriptor.hpp>

namespace MemoryNameSpace{

const std::string& ReferenceDescriptor::get_name() const noexcept {
    return pointer_->get_name();
}
size_t ReferenceDescriptor::get_size() const noexcept {
    return pointer_->get_size();
}
bool ReferenceDescriptor::is_valid() const noexcept {
    return pointer_->is_valid();
}
void ReferenceDescriptor::get_value(IBuffer* buffer, const std::byte* value) const {
    pointer_->get_value(buffer, value);
}
void ReferenceDescriptor::set_value(IBuffer* buffer, const std::byte* value) {
    pointer_->set_value(buffer, value);
}
const std::string& ReferenceDescriptor::get_ref_name() const noexcept {
    return name_;
}

}