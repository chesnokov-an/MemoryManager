#ifndef ARRAYDESCRIPTOR_HPP
#define ARRAYDESCRIPTOR_HPP

#include <string>
#include <Memory/MemoryElement.hpp>

namespace MemoryNameSpace{

class ArrayDescriptor : public MemoryElement{
protected:
    size_t element_size_;

public:
    ArrayDescriptor(const std::string& name, size_t size, size_t offset, size_t element_size)
            : MemoryElement(name, size, offset), element_size_(element_size) {}
    using MemoryElement::get_value;
    void get_value(IBuffer* buffer, size_t index, std::byte* value) const;
    void get_value(IBuffer* buffer, size_t begin, size_t end, std::byte* value) const;
    using MemoryElement::set_value;
    void set_value(IBuffer* buffer, size_t index, const std::byte* value);
};

}

#endif