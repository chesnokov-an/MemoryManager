#ifndef ARRAYDESCRIPTOR_HPP
#define ARRAYDESCRIPTOR_HPP

#include <string>
#include <Memory/MemoryElement.hpp>
#include <Memory/ReferenceDescriptor.hpp>

namespace MemoryNameSpace{

class ArrayDescriptor : public MemoryElement{
protected:
    size_t element_size_;

public:
    ArrayDescriptor(const std::string& name, size_t size, size_t offset, size_t element_size)
            : MemoryElement(name, size, offset), element_size_(element_size) {};

    using MemoryElement::get_value;
    void get_value(IBuffer* buffer, size_t index, const std::byte* value) const {
        std::byte* target = buffer->get_data() + offset_ + index * element_size_;
        std::copy(target, target + element_size_, value);
    }
    void get_value(IBuffer* buffer, size_t begin, size_t end, const std::byte* value) const {
        std::byte* target = buffer->get_data() + offset_ + begin * element_size_;
        std::copy(target, target + element_size_ * (end - begin), value);
    }

    using MemoryElement::set_value;
    void set_value(IBuffer* buffer, size_t index, const std::byte* value){
        std::byte* target = buffer->get_data() + offset_ + index * element_size_;
        std::copy(value, value + element_size_, target);
    }

    ReferenceDescriptor make_reference(std::string name){
        return ReferenceDescriptor{name, this};
    }
};

}

#endif