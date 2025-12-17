#include <gtest/gtest.h>
#include <Memory/Error.hpp>

using namespace MemoryNameSpace;

TEST(ErrorTest, ConstructionAndGetters) {
    Error error(SIZE_ERROR, "Memory limit exceeded", "test_program");
    
    EXPECT_EQ(error.get_program(), "test_program");
    
    std::string desc = error.get_description();
    EXPECT_TRUE(desc.find("SIZE_ERROR") != std::string::npos);
    EXPECT_TRUE(desc.find("test_program") != std::string::npos);
    EXPECT_TRUE(desc.find("Memory limit exceeded") != std::string::npos);
}

TEST(ErrorTest, AllErrorTypes) {
    Error error1(SIZE_ERROR, "msg1", "prog1");
    Error error2(MEMORY_LEAK, "msg2", "prog2");
    Error error3(DOUBLE_FREE, "msg3", "prog3");
    Error error4(ACCESS_ERROR, "msg4", "prog4");
    
    EXPECT_EQ(error1.get_program(), "prog1");
    EXPECT_EQ(error2.get_program(), "prog2");
    EXPECT_EQ(error3.get_program(), "prog3");
    EXPECT_EQ(error4.get_program(), "prog4");
}