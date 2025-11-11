#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstddef>
#include <array>

namespace MemoryNameSpace{

class IBuffer final{
public:
    virtual std::byte* get_data() noexcept = 0;
    virtual const std::byte* get_data() const noexcept = 0;
    virtual size_t get_size() const noexcept = 0;
    virtual size_t get_capacity() const noexcept = 0;
    virtual ~IBuffer(){}
};

template<size_t capacity_>
class Buffer final : public IBuffer{
private:
    std::array<std::byte, capacity_> buffer_;
    size_t size_;

public:
    std::byte* get_data() noexcept override {
        return buffer_.data();
    }
    const std::byte* get_data() const noexcept override {
        return buffer_.data();
    }
    constexpr size_t get_size() const noexcept override {
        return size_;
    }
    constexpr size_t get_capacity() const noexcept override {
        return capacity_;
    }
};

}

#endif