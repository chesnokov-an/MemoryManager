#include <Memory/ArrayDescriptor.hpp>

namespace MemoryNameSpace{

void ArrayDescriptor::get_value(IBuffer *buffer, size_t index, const std::byte *value) const {
    std::byte* target = buffer->get_data() + offset_ + index * element_size_;
    std::copy(target, target + element_size_, value);
}

void ArrayDescriptor::get_value(MemoryNameSpace::IBuffer *buffer, size_t begin, size_t end, const std::byte *value) const {
    std::byte* target = buffer->get_data() + offset_ + begin * element_size_;
    std::copy(target, target + element_size_ * (end - begin), value);
}

void ArrayDescriptor::set_value(IBuffer *buffer, size_t index, const std::byte *value){
    std::byte* target = buffer->get_data() + offset_ + index * element_size_;
    std::copy(value, value + element_size_, target);
}

}