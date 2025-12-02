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
    virtual void get_raw_value(std::byte* value) const = 0;
    virtual void set_raw_value(const std::byte* value) = 0;
    virtual ~IMemoryElement(){};
    
    template<typename T, typename... Args>
    void get_value(T& value, Args&&... args) const{
        static_assert(std::is_trivially_copyable_v<T>, "MemoryElement::set_value<T> requires trivially copyable type T");
        if (get_size() != sizeof(T))
            throw std::runtime_error("Size mismatch in MemoryElement::get_value<T>");
        get_raw_value(reinterpret_cast<std::byte*>(&value), args...);
    }
    template<typename T, typename... Args>
    void set_value(const T& value, Args&&... args){
        static_assert(std::is_trivially_copyable_v<T>, "MemoryElement::get_value<T> requires trivially copyable type T");
        if (get_size() != sizeof(T))
            throw std::runtime_error("Size mismatch in MemoryElement::set_value<T>");
        set_raw_value(reinterpret_cast<const std::byte*>(&value), args...);
    }
};

}

#endif