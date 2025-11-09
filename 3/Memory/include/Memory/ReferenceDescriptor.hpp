#ifndef REFERENCEDESCRIPTOR_HPP
#define REFERENCEDESCRIPTOR_HPP

#include <string>
#include <memory>
#include "Memory/VariableDescriptor.hpp"

namespace MemoryNameSpace{

class ReferenceDescriptor final : public MemoryElement{
private:
    std::unique_ptr<MemoryElement> pointer_;

public:
    ReferenceDescriptor(const std::string& name, MemoryElement* pointer)
            : MemoryElement(name), pointer_(pointer) {};

    std::byte* data(std::byte* buffer) override {
         return pointer_->data(buffer);
    }

    const std::byte* data(std::byte* buffer) const override {
        return pointer_->data(buffer);
    }

    void set_data(std::byte* buffer, const std::byte* data) override {
        pointer_->set_data(buffer, data);
    }

    bool is_valid() override {
        if(pointer_ == nullptr || pointer_->is_valid() == false)
            valid_ = false;
        return valid_;
    }
};

}

#endif