#ifndef MEMORYELEMENT_HPP
#define MEMORYELEMENT_HPP

#include <string>
#include <cstddef>
#include <Memory/IMemoryElement.hpp>
#include <Memory/ReferenceDescriptor.hpp>
#include <Memory/IManager.hpp>

namespace MemoryNameSpace{

class MemoryElement : public IMemoryElement{
protected:
    std::string name_;
    size_t size_;
    size_t offset_;
    IManager& manager_;

public:
    MemoryElement(const std::string& name, size_t size, size_t offset, IManager& manager)
            : name_(name), size_(size), offset_(offset), manager_(manager) {}
    const std::string& get_name() const noexcept override;
    size_t get_size() const noexcept override;
    size_t get_offset() const noexcept override;
    void get_raw_value(std::byte* value) const override;
    void set_raw_value(const std::byte* value) override;
    virtual ReferenceDescriptor make_reference(std::string name, IManager& manager);
    virtual ~MemoryElement() = 0;
};

}

#endif