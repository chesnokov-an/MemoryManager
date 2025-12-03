#ifndef ARRAYDESCRIPTOR_HPP
#define ARRAYDESCRIPTOR_HPP

#include <string>
#include <Memory/MemoryElement.hpp>

namespace MemoryNameSpace{

class ArrayDescriptor : public MemoryElement{
protected:
    size_t element_size_;

public:
    ArrayDescriptor(const std::string& name, size_t size, size_t offset, size_t element_size, IManager& manager)
            : MemoryElement(name, size, offset, manager), element_size_(element_size) {}
    
    size_t get_elem_size() const noexcept override;
    void get_raw_value(std::byte* value, size_t begin, size_t end) const override;
    void set_raw_value(const std::byte* value, size_t begin, size_t end) override;
};

}

#endif