#include <gtest/gtest.h>
#include <Memory/Program.hpp>
#include <Memory/Manager.hpp>
#include <Memory/VariableDescriptor.hpp>

using namespace MemoryNameSpace;

class ProgramTest : public ::testing::Test {
protected:
    Manager<1024> manager;
    Program* program;
    
    void SetUp() override {
        manager = Manager<1024>();
        program = manager.add_program("test_program", "test.cpp", 512);
    }
};

TEST_F(ProgramTest, Construction) {
    EXPECT_EQ(program->get_name(), "test_program");
    EXPECT_EQ(program->get_used_memory(), 0);
}

TEST_F(ProgramTest, InsertAndEraseElement) {
    VariableDescriptor var("testVar", sizeof(int), 0, manager);
    
    program->insert_element(&var);
    auto elements = program->get_memory_elements();
    EXPECT_EQ(elements.size(), 1);
    EXPECT_NE(elements.find("testVar"), elements.end());
    
    program->erase_element(&var);
    elements = program->get_memory_elements();
    EXPECT_EQ(elements.size(), 0);
}

TEST_F(ProgramTest, GetUsedMemory) {
    EXPECT_EQ(program->get_used_memory(), 0);
    
    VariableDescriptor* var1 = program->allocate_element<VariableDescriptor>("var1", 100);
    VariableDescriptor* var2 = program->allocate_element<VariableDescriptor>("var2", 200);
    
    EXPECT_EQ(program->get_used_memory(), 300);
    
    program->destroy_element("var1");
    EXPECT_EQ(program->get_used_memory(), 200);
}

TEST_F(ProgramTest, PossibleForExpansion) {
    EXPECT_TRUE(program->possible_for_expansion(100));
    EXPECT_TRUE(program->possible_for_expansion(512));
    EXPECT_FALSE(program->possible_for_expansion(513));
    
    // Allocate some memory
    program->allocate_element<VariableDescriptor>("var1", 300);
    EXPECT_TRUE(program->possible_for_expansion(212));
    EXPECT_FALSE(program->possible_for_expansion(213));
}

TEST_F(ProgramTest, MemoryElementsAccess) {
    const auto& elements = program->get_memory_elements();
    EXPECT_TRUE(elements.empty());
    
    program->allocate_element<VariableDescriptor>("var1", sizeof(int));
    
    const auto& elements2 = program->get_memory_elements();
    EXPECT_EQ(elements2.size(), 1);
    EXPECT_NE(elements2.find("var1"), elements2.end());
}

TEST_F(ProgramTest, ProgramDestructor) {
    {
        Manager<1024> localManager;
        Program* localProg = localManager.add_program("local", "local.cpp", 100);
        
        // Allocate but don't free - should trigger memory leak in destructor
        localProg->allocate_element<VariableDescriptor>("leakyVar", 50);
    }
    // Destructor should have been called and recorded error
}