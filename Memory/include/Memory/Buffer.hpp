#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstddef>
#include <array>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>

namespace MemoryNameSpace{

/**
 * @struct Block
 * @brief Represents a block of memory in the buffer
 */
struct Block{
    size_t offset = 0;  ///< Starting offset of the block
    size_t size = 0;    ///< Size of the block in bytes
};

/**
 * @class IBuffer
 * @brief Interface for memory buffer implementations
 * 
 * IBuffer defines the interface for memory buffers that manage
 * raw memory allocation and deallocation using a block-based approach.
 */
class IBuffer{
public:
    /**
     * @brief Gets raw data buffer pointer
     * 
     * @return std::byte* Pointer to raw memory buffer
     */
    virtual std::byte* get_data() noexcept = 0;
    
    /**
     * @brief Gets raw data buffer pointer (const version)
     * 
     * @return const std::byte* Const pointer to raw memory buffer
     */
    virtual const std::byte* get_data() const noexcept = 0;
    
    /**
     * @brief Gets the capacity of the buffer
     * 
     * @return size_t Buffer capacity in bytes
     */
    virtual size_t get_capacity() const noexcept = 0;
    
    /**
     * @brief Allocates a block of memory
     * 
     * @param size Size to allocate in bytes
     * @return size_t Offset of allocated block
     * @throws std::runtime_error If buffer overflow occurs
     */
    virtual size_t allocate_block(size_t size) = 0;
    
    /**
     * @brief Destroys a block of memory
     * 
     * @param offset Offset of block to destroy
     * @param size Size of block to destroy
     * @throws std::out_of_range If offset/size are invalid
     * @throws std::runtime_error If double free occurs
     */
    virtual void destroy_block(size_t offset, size_t size) = 0;
    
    /**
     * @brief Gets the list of free blocks
     * 
     * @return std::vector<Block>& Reference to vector of free blocks
     */
    virtual std::vector<Block>& get_blocks() = 0;
    
    /**
     * @brief Virtual destructor for interface
     */
    virtual ~IBuffer() = default;
};

/**
 * @class Buffer
 * @brief Fixed-size memory buffer implementation
 * 
 * Buffer implements IBuffer using a fixed-size array and
 * maintains a list of free blocks for allocation.
 * 
 * @tparam capacity_ Fixed capacity of the buffer in bytes
 */
template<size_t capacity_>
class Buffer final : public IBuffer{
private:
    std::array<std::byte, capacity_> buffer_; ///< Underlying memory storage
    std::vector<Block> blocks_;               ///< List of free memory blocks

public:
    /**
     * @brief Constructs a new Buffer object
     * 
     * Initializes with a single free block covering the entire buffer.
     */
    Buffer() : IBuffer(), blocks_(std::vector<Block>{{0, capacity_}}) {};
    
    /**
     * @brief Destructor for Buffer
     */
    ~Buffer() override = default;
    
    /**
     * @brief Gets raw data buffer pointer
     * 
     * @return std::byte* Pointer to raw memory buffer
     */
    std::byte* get_data() noexcept override { return buffer_.data(); }
    
    /**
     * @brief Gets raw data buffer pointer (const version)
     * 
     * @return const std::byte* Const pointer to raw memory buffer
     */
    const std::byte* get_data() const noexcept override { return buffer_.data(); }
    
    /**
     * @brief Gets the capacity of the buffer
     * 
     * @return constexpr size_t Buffer capacity in bytes
     */
    constexpr size_t get_capacity() const noexcept override { return capacity_; }
    
    /**
     * @brief Allocates a block of memory
     * 
     * Uses first-fit algorithm to find a suitable free block.
     * 
     * @param size Size to allocate in bytes
     * @return size_t Offset of allocated block
     * @throws std::runtime_error If no suitable free block found (buffer overflow)
     */
    size_t allocate_block(size_t size) override {
        size_t offset_res = 0;
        auto it = std::find_if(blocks_.begin(), blocks_.end(),
                                [size](const Block& block){ return block.size >= size; });
        if(it == blocks_.end()) throw std::runtime_error("Buffer overflow.");
        offset_res = it->offset;
        if(size == it->size) blocks_.erase(it);
        else{
            it->offset = it->offset + size;
            it->size = it->size - size;
        }
        return offset_res;
    }
    
    /**
     * @brief Destroys a block of memory
     * 
     * Returns memory to the free list and merges adjacent free blocks.
     * 
     * @param offset Offset of block to destroy
     * @param size Size of block to destroy
     * @throws std::out_of_range If offset/size are outside buffer bounds
     * @throws std::runtime_error If block is already free (double free)
     */
    void destroy_block(size_t offset, size_t size) override {
        if((offset > capacity_) || (size > capacity_ - offset))
            throw std::out_of_range("Invalid offset " + std::to_string(offset) + " with size " + std::to_string(size) + ".");
        auto it = std::upper_bound(blocks_.begin(), blocks_.end(), offset,
                                [](size_t offset, const Block& block){ return offset < block.offset; });
        auto prev = (it != blocks_.begin()) ? std::prev(it) : blocks_.end();
        if(((it != blocks_.end()) && (offset + size > it->offset)) || ((it != blocks_.begin()) && (prev->offset + prev->size > offset)))
            throw std::runtime_error("Double free.");
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

    /**
     * @brief Gets the list of free blocks
     * 
     * @return std::vector<Block>& Reference to vector of free blocks
     */
    std::vector<Block>& get_blocks() override {
        return blocks_;
    }
};

}

#endif