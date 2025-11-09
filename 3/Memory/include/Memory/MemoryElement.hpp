#ifndef MEMORYELEMENT_HPP
#define MEMORYELEMENT_HPP

#include <string>
#include <cstddef>
namespace MemoryNameSpace{

class MemoryElement{
protected:
    std::string name_;
    bool valid_;

public:
    MemoryElement(const std::string& name) : name_(name), valid_(true) {};
    virtual std::byte* data(std::byte* buffer) = 0;
    virtual const std::byte* data(std::byte* buffer) const = 0;
    virtual void set_data(std::byte* buffer, const std::byte* data) = 0;
    virtual ~MemoryElement() {};
    virtual bool is_valid() { return valid_; }
};

struct memory_wrapper final{
    size_t size;
    size_t offset;
};

}

#endif