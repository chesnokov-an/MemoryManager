#ifndef REFERENCEDESCRIPTOR_HPP
#define REFERENCEDESCRIPTOR_HPP

#include <string>
#include <memory>
#include <Memory/IMemoryElement.hpp>

namespace MemoryNameSpace{

class IMemoryElement;
class IManager;
class IBuffer;

class ReferenceDescriptor final : public IMemoryElement{
private:
    std::string name_;
    std::string target_name_;
    IManager& manager_;

private:
    IMemoryElement* get_element() const;

public:
    ReferenceDescriptor(const std::string& name, const std::string& target_name, IManager& manager)
            : name_(name), target_name_(target_name), manager_(manager) {};
    const std::string& get_name() const noexcept override;
    size_t get_size() const noexcept override;
    size_t get_elem_size() const noexcept override;
    size_t get_offset() const noexcept override;
    void set_offset(size_t offset) noexcept override;
    bool is_valid() const noexcept;
    void get_raw_value(std::byte* value, size_t begin, size_t end) const override;
    void set_raw_value(const std::byte* value, size_t begin, size_t end) override;
    const std::string& get_ref_name() const noexcept;
};

}

#endif