#ifndef MEMORYELEMENT_HPP
#define MEMORYELEMENT_HPP

#include <string>
#include <cstddef>
#include <Memory/Buffer.hpp>

namespace MemoryNameSpace{

class IMemoryElement{
public:
    virtual const std::string& get_name() const noexcept = 0;
    virtual size_t get_size() const noexcept = 0;
    virtual bool is_valid() const noexcept = 0;
    virtual void get_value(IBuffer* buffer, const std::byte* value) const = 0;
    virtual void set_value(IBuffer* buffer, const std::byte* value) = 0;
    virtual ~IMemoryElement(){};
};

class MemoryElement : public IMemoryElement{
protected:
    std::string name_;
    size_t size_;
    size_t offset_;
    bool valid_;

public:
    MemoryElement(const std::string& name, size_t size, size_t offset)
            : name_(name), size_(size), offset_(offset), valid_(true) {};
    const std::string& get_name() const noexcept { return name_; }
    size_t get_size() const noexcept { return size_; }
    bool is_valid() const noexcept { return valid_; }
    void get_value(IBuffer* buffer, const std::byte* value) const override {
        std::byte* target = buffer->get_data() + offset_;
        std::copy(target, target + size_, value);
    }
    void set_value(IBuffer* buffer, const std::byte* value) override {
        std::byte* target = buffer->get_data() + offset_;
        std::copy(value, value + size_, target);
    }
    virtual void make_abstract() const noexcept = 0;
    virtual ~MemoryElement(){};
};

}

#endif