#ifndef IMEMORYELEMENT_HPP
#define IMEMORYELEMENT_HPP

#include <string>
#include <cstddef>
#include <Memory/Buffer.hpp>

namespace MemoryNameSpace{

class IMemoryElement{
public:
    virtual const std::string& get_name() const noexcept = 0;
    virtual size_t get_size() const noexcept = 0;
    virtual size_t get_elem_size() const noexcept = 0;
    virtual size_t get_offset() const noexcept = 0;
    virtual void get_raw_value(std::byte* value, size_t begin, size_t end) const = 0;
    virtual void set_raw_value(const std::byte* value, size_t begin, size_t end) = 0;
    virtual ~IMemoryElement(){};
    
    template<typename T>
    void get_value(T& value, size_t begin = 0, size_t end = 0) const{
        static_assert(std::is_trivially_copyable_v<T>, "MemoryElement::set_value<T> requires trivially copyable type T");
        if (get_elem_size() != sizeof(T) && get_size() != sizeof(T))
            throw std::runtime_error("Size mismatch in MemoryElement::get_value<T>");
        get_raw_value(reinterpret_cast<std::byte*>(&value), begin, end);
    }
    template<typename T>
    void set_value(const T& value, size_t begin = 0, size_t end = 0){
        static_assert(std::is_trivially_copyable_v<T>, "MemoryElement::get_value<T> requires trivially copyable type T");
        if (get_elem_size() != sizeof(T) && get_size() != sizeof(T))
            throw std::runtime_error("Size mismatch in MemoryElement::set_value<T>");
        set_raw_value(reinterpret_cast<const std::byte*>(&value), begin, end);
    }
};

}

#endif