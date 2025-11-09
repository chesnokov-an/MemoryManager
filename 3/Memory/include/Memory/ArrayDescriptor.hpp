#ifndef ARRAYDESCRIPTOR_HPP
#define ARRAYDESCRIPTOR_HPP

#include <string>
#include "Memory/MemoryElement.hpp"
#include "Memory/ReferenceDescriptor.hpp"

namespace MemoryNameSpace{

class ArrayDescriptor : public MemoryElement{
protected:
    size_t size_;
    size_t element_size_;
    size_t offset_;

public:
    ArrayDescriptor(const std::string& name, size_t size, size_t element_size, size_t offset)
            : MemoryElement(name), size_(size), element_size_(element_size), offset_(offset) {};

    std::byte* data(std::byte* buffer) override {
        return buffer + offset_;
    }

    const std::byte* data(std::byte* buffer) const override {
        return buffer + offset_;
    }

    std::byte* data(std::byte* buffer, size_t index){
        return buffer + offset_ + index;
    }

    const std::byte* data(std::byte* buffer, size_t index) const {
        return buffer + offset_ + index;
    }

    std::pair<std::byte*, std::byte*> data(std::byte* buffer, size_t begin, size_t end){
        return std::pair<std::byte*, std::byte*>{buffer + offset_ + begin, buffer + offset_ + end};
    }
    
    std::pair<const std::byte*, const std::byte*> data(std::byte* buffer, size_t begin, size_t end) const{
        return std::pair<const std::byte*, const std::byte*>{buffer + offset_ + begin, buffer + offset_ + end};
    }

    void set_data(std::byte* buffer, const std::byte* data) override {
        std::copy(data, data + size_, buffer + offset_);
    }

    ReferenceDescriptor make_reference(std::string name){
        return ReferenceDescriptor{name, this};
    }
};

}

#endif