#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstddef>
#include <array>
#include <vector>
#include <algorithm>
#include <exception>

namespace MemoryNameSpace{

class IBuffer final{
public:
    virtual std::byte* get_data() noexcept = 0;
    virtual const std::byte* get_data() const noexcept = 0;
    virtual size_t get_size() const noexcept = 0;
    virtual size_t get_capacity() const noexcept = 0;
    virtual size_t allocate_block(size_t size) = 0;
    virtual void destroy_block(size_t offset, size_t size) = 0;
    virtual ~IBuffer(){}
};

struct Block{
    size_t offset;
    size_t size;
};

template<size_t capacity_>
class Buffer final : public IBuffer{
private:
    std::array<std::byte, capacity_> buffer_;
    size_t size_;
    std::vector<Block> blocks_;

public:
    Buffer() : buffer_(), size_(0), blocks_(std::vector<Block>{{0, capacity_}}) {};
    
    std::byte* get_data() noexcept override { return buffer_.data(); }
    const std::byte* get_data() const noexcept override { return buffer_.data(); }
    constexpr size_t get_size() const noexcept override { return size_; }
    constexpr size_t get_capacity() const noexcept override { return capacity_; }
    
    size_t allocate_block(size_t size) override {
        size_t offset_res = 0;
        auto it = std::find_if(blocks_.begin(), blocks_.end(),
                                [size](const Block& block){ return block.size >= size; });
        if(it == blocks_.end()) throw std::runtime_error("Buffer overflow");
        offset_res = it->offset;
        if(size == it->size) blocks_.erase(it);
        else{
            it->offset = it->offset + size;
            it->size = it->size - size;
        }
        return offset_res;
    }
    void destroy_block(size_t offset, size_t size) override {
        if((offset > capacity_) || (size > capacity_ - offset)) throw std::out_of_range("Invalid offset to destroy");
        auto it = std::upper_bound(blocks_.begin(), blocks_.end(), offset,
                                [](size_t offset, const Block& block){ return offset < block.offset });
        auto prev = (it != blocks_.begin()) ? std::prev(it) : blocks_.end();
        if(((it != blocks_.end()) && (offset + size > it->offset)) || ((it != blocks_.begin()) && (prev->offset + prev->size > offset)))
            throw std::runtime_error("Double free");
        if((it != blocks_.begin()) && (prev->offset + prev->size == offset)){
            prev->size += size;
            if((it != blocks_.end()) && (offset + size == it->offset)){
                prev->size += it->size;
                blocks_.erase(it);
            }
            return;
        }
        if((it != blocks_.end()) && (offset + size == it->offset)){
            it->offset = offset;
            it->size += size;
            return;
        }
        blocks_.insert(it, Block{offset, size});
    }

};

}

#endif