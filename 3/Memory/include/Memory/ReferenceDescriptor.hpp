#ifndef REFERENCEDESCRIPTOR_HPP
#define REFERENCEDESCRIPTOR_HPP

#include <string>
#include <memory>
#include <Memory/VariableDescriptor.hpp>

namespace MemoryNameSpace{

class ReferenceDescriptor final : public IMemoryElement{
public:
    using Pointer = IMemoryElement*;

private:
    std::string name_;
    Pointer pointer_;

public:
    ReferenceDescriptor(const std::string& name, Pointer pointer)
            : name_(name), pointer_(pointer) {};
    const std::string& get_name() const noexcept override;
    size_t get_size() const noexcept override;
    bool is_valid() const noexcept override;
    void get_value(IBuffer* buffer, const std::byte* value) const override;
    void set_value(IBuffer* buffer, const std::byte* value) override;
    const std::string& get_ref_name() const noexcept;
};

}

#endif