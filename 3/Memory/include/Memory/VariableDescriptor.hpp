#ifndef VARIABLEDESCRIPTOR_HPP
#define VARIABLEDESCRIPTOR_HPP

#include <string>
#include "Memory/MemoryElement.hpp"
#include "Memory/ReferenceDescriptor.hpp"

namespace MemoryNameSpace{

class VariableDescriptor final : public MemoryElement{
private:
    size_t size_;
    size_t offset_;

public:
    VariableDescriptor(const std::string& name, size_t size, size_t offset)
            : MemoryElement(name), size_(size), offset_(offset) {};

    std::byte* data(std::byte* buffer) override {
        return buffer + offset_;
    }

    const std::byte* data(std::byte* buffer) const override {
        return buffer + offset_;
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