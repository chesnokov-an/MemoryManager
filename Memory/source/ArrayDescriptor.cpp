#include <Memory/ArrayDescriptor.hpp>

namespace MemoryNameSpace{

size_t ArrayDescriptor::get_elem_size() const noexcept { return element_size_; }

void ArrayDescriptor::get_raw_value(std::byte *value, size_t begin, size_t end) const {
    std::byte* target = manager_.get_data() + offset_ + begin * element_size_;
    if(end == 0){
        std::copy(target, target + element_size_, value);
        return;
    }
    std::copy(target, target + element_size_ * (end - begin), value);
}

void ArrayDescriptor::set_raw_value(const std::byte *value, size_t begin, size_t end){
    std::byte* target = manager_.get_data() + offset_ + begin * element_size_;
    if(end == 0){
        std::copy(value, value + element_size_, target);
        return;
    }
    std::copy(value, value + element_size_ * (end - begin), target);
}

}