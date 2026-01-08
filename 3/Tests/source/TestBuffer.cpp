#include <gtest/gtest.h>
#include <Memory/Buffer.hpp>

using namespace MemoryNameSpace;

TEST(BufferTest, Initialization) {
    Buffer<1024> buffer;
    
    EXPECT_EQ(buffer.get_capacity(), 1024);
    EXPECT_NE(buffer.get_data(), nullptr);
}

TEST(BufferTest, AllocateBlock) {
    Buffer<1024> buffer;
    
    size_t offset1 = buffer.allocate_block(100);
    EXPECT_EQ(offset1, 0);
    
    size_t offset2 = buffer.allocate_block(200);
    EXPECT_EQ(offset2, 100);
}

TEST(BufferTest, AllocateExactFit) {
    Buffer<100> buffer;
    
    size_t offset = buffer.allocate_block(100);
    EXPECT_EQ(offset, 0);
    
    EXPECT_THROW(buffer.allocate_block(1), std::runtime_error);
}

TEST(BufferTest, DestroyBlock) {
    Buffer<1024> buffer;
    
    size_t offset = buffer.allocate_block(100);
    buffer.destroy_block(offset, 100);
    
    // Should be able to allocate again
    size_t new_offset = buffer.allocate_block(100);
    EXPECT_EQ(new_offset, 0);
}

TEST(BufferTest, DestroyBlockInvalidOffset) {
    Buffer<100> buffer;
    
    EXPECT_THROW(buffer.destroy_block(1000, 10), std::out_of_range);
    EXPECT_THROW(buffer.destroy_block(90, 20), std::out_of_range);
}

TEST(BufferTest, DoubleFreeDetection) {
    Buffer<1024> buffer;
    
    size_t offset = buffer.allocate_block(100);
    buffer.destroy_block(offset, 100);
    
    EXPECT_THROW(buffer.destroy_block(offset, 100), std::runtime_error);
}

TEST(BufferTest, MergeAdjacentBlocks) {
    Buffer<1024> buffer;
    
    // Allocate and free blocks to create fragmentation
    size_t offset1 = buffer.allocate_block(100);
    size_t offset2 = buffer.allocate_block(100);
    size_t offset3 = buffer.allocate_block(100);
    
    buffer.destroy_block(offset1, 100); // Free first block
    buffer.destroy_block(offset3, 100); // Free third block
    
    // Free middle block - all should merge
    buffer.destroy_block(offset2, 100);
    
    // Should be able to allocate entire buffer
    size_t new_offset = buffer.allocate_block(1024);
    EXPECT_EQ(new_offset, 0);
}

TEST(BufferTest, GetBlocks) {
    Buffer<1024> buffer;
    
    buffer.allocate_block(100);
    buffer.allocate_block(200);
    
    auto& blocks = buffer.get_blocks();
    EXPECT_EQ(blocks.size(), 1);
    EXPECT_EQ(blocks[0].offset, 300);
    EXPECT_EQ(blocks[0].size, 724);
}