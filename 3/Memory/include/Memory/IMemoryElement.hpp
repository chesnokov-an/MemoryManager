#ifndef IMEMORYELEMENT_HPP
#define IMEMORYELEMENT_HPP

#include <string>
#include <cstddef>
#include <Memory/Buffer.hpp>

namespace MemoryNameSpace{

class IMemoryElement{
public:
    friend class IManager;

    virtual const std::string& get_name() const noexcept = 0;
    virtual size_t get_size() const noexcept = 0;
    virtual size_t get_offset() const noexcept = 0;
    virtual void get_value(IBuffer* buffer, std::byte* value) const = 0;
    virtual void set_value(IBuffer* buffer, const std::byte* value) = 0;
    virtual ~IMemoryElement(){};
};

}

#endif