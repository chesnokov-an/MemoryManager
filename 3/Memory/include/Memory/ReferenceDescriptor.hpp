#ifndef REFERENCEDESCRIPTOR_HPP
#define REFERENCEDESCRIPTOR_HPP

#include <string>
#include <memory>
#include <Memory/VariableDescriptor.hpp>

namespace MemoryNameSpace{

class ReferenceDescriptor final : public IMemoryElement{
private:
    std::string name_;
    IMemoryElement* pointer_;

public:
    ReferenceDescriptor(const std::string& name, MemoryElement* pointer)
            : name_(name), pointer_(pointer) {};

    const std::string& get_name() const noexcept override {
        return pointer_->get_name();
    }
    size_t get_size() const noexcept override {
        return pointer_->get_size();
    }
    bool is_valid() const noexcept override {
        return pointer_->is_valid();
    }
    void get_value(IBuffer* buffer, const std::byte* value) const {
        pointer_->get_value(buffer, value);
    }
    void set_value(IBuffer* buffer, const std::byte* value) override {
        pointer_->set_value(buffer, value);
    }
    const std::string& get_ref_name() const noexcept {
        return name_;
    }
};

}

#endif