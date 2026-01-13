#include <gtest/gtest.h>
#include <Memory/Manager.hpp>
#include <Memory/Program.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <type_traits>

using namespace MemoryNameSpace;

class ManagerTest : public ::testing::Test {
protected:
    Manager<1024> manager;
    
    void SetUp() override {
        // Clear any previous state
        manager = Manager<1024>();
    }
};

TEST_F(ManagerTest, AddAndDeleteProgram) {
    Program* prog = manager.add_program("prog1", "test.cpp", 512);
    ASSERT_NE(prog, nullptr);
    EXPECT_EQ(prog->get_name(), "prog1");
    
    auto programs = manager.get_programs();
    EXPECT_EQ(programs.size(), 1);
    EXPECT_NE(programs.find("prog1"), programs.end());
    
    // Add duplicate program
    Program* prog2 = manager.add_program("prog1", "test2.cpp", 512);
    EXPECT_EQ(prog2, nullptr);
    
    manager.delete_program("prog1");
    programs = manager.get_programs();
    EXPECT_EQ(programs.size(), 0);
}

TEST_F(ManagerTest, AllocateVariable) {
    Program* prog = manager.add_program("prog1", "test.cpp", 512);
    
    VariableDescriptor* var = prog->allocate_element<VariableDescriptor>("myVar", sizeof(int));
    ASSERT_NE(var, nullptr);
    EXPECT_EQ(var->get_name(), "myVar");
    EXPECT_EQ(var->get_size(), sizeof(int));
    
    // Try to allocate duplicate
    VariableDescriptor* var2 = prog->allocate_element<VariableDescriptor>("myVar", sizeof(int));
    EXPECT_EQ(var2, nullptr);
    
    // Check memory usage
    EXPECT_EQ(prog->get_used_memory(), sizeof(int));
}

TEST_F(ManagerTest, AllocateArray) {
    Program* prog = manager.add_program("prog1", "test.cpp", 512);
    
    ArrayDescriptor* arr = prog->allocate_element<ArrayDescriptor>("myArray", 
                                                                   10 * sizeof(int), 
                                                                   sizeof(int));
    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(arr->get_name(), "myArray");
    EXPECT_EQ(arr->get_size(), 10 * sizeof(int));
    EXPECT_EQ(arr->get_elem_size(), sizeof(int));
}

TEST_F(ManagerTest, MemoryLimitExceeded) {
    Program* prog = manager.add_program("prog1", "test.cpp", 100);
    
    // This should succeed
    VariableDescriptor* var1 = prog->allocate_element<VariableDescriptor>("var1", 50);
    ASSERT_NE(var1, nullptr);
    
    // This should fail due to memory limit
    VariableDescriptor* var2 = prog->allocate_element<VariableDescriptor>("var2", 60);
    EXPECT_EQ(var2, nullptr);
    
    auto errors = manager.program_errors("prog1");
    EXPECT_FALSE(errors.empty());
}

TEST_F(ManagerTest, DestroyElement) {
    Program* prog = manager.add_program("prog1", "test.cpp", 512);
    
    VariableDescriptor* var = prog->allocate_element<VariableDescriptor>("myVar", sizeof(int));
    ASSERT_NE(var, nullptr);
    
    bool destroyed = prog->destroy_element("myVar");
    EXPECT_TRUE(destroyed);
    
    // Try to destroy non-existent element
    bool destroyed2 = prog->destroy_element("nonExistent");
    EXPECT_FALSE(destroyed2);
}

TEST_F(ManagerTest, CreateReference) {
    Program* prog = manager.add_program("prog1", "test.cpp", 512);
    
    VariableDescriptor* var = prog->allocate_element<VariableDescriptor>("myVar", sizeof(int));
    ASSERT_NE(var, nullptr);
    
    // Create reference to variable
    ReferenceDescriptor* ref = prog->make_reference("myRef", "myVar");
    ASSERT_NE(ref, nullptr);
    EXPECT_EQ(ref->get_name(), "myRef");
    EXPECT_TRUE(ref->is_reference());
    EXPECT_TRUE(ref->is_valid());
    
    // Try to create reference to non-existent variable
    ReferenceDescriptor* ref2 = prog->make_reference("badRef", "nonExistent");
    EXPECT_EQ(ref2, nullptr);
}

TEST_F(ManagerTest, DanglingReferenceDetection) {
    Program* prog = manager.add_program("prog1", "test.cpp", 512);
    
    VariableDescriptor* var = prog->allocate_element<VariableDescriptor>("myVar", sizeof(int));
    ReferenceDescriptor* ref = prog->make_reference("myRef", "myVar");
    
    // Destroy the original variable
    prog->destroy_element("myVar");
    
    auto dangling = manager.dungling_reference();
    EXPECT_EQ(dangling.size(), 1);
    EXPECT_FALSE(dangling[0]->is_valid());
}

TEST_F(ManagerTest, AccessToSharedSegment) {
    Program* prog1 = manager.add_program("prog1", "test1.cpp", 512);
    Program* prog2 = manager.add_program("prog2", "test2.cpp", 512);
    
    // Create shared segment from prog1
    SharedSegmentDescriptor* segment = 
        prog1->allocate_element<SharedSegmentDescriptor>("sharedSeg", 
                                                         100, 
                                                         sizeof(int), 
                                                         prog1);
    ASSERT_NE(segment, nullptr);
    
    // Grant access to prog2
    bool accessGranted = manager.get_access_to_shared("prog2", "sharedSeg");
    EXPECT_TRUE(accessGranted);
    
    // Check prog2 can access it
    auto prog2Elements = prog2->get_memory_elements();
    EXPECT_NE(prog2Elements.find("sharedSeg"), prog2Elements.end());
    
    // Revoke access
    bool accessRevoked = manager.revoke_access_to_shared("prog2", "sharedSeg");
    EXPECT_TRUE(accessRevoked);
}

TEST_F(ManagerTest, Statistics) {
    Program* prog1 = manager.add_program("prog1", "test1.cpp", 512);
    Program* prog2 = manager.add_program("prog2", "test2.cpp", 512);
    
    prog1->allocate_element<VariableDescriptor>("var1", 100);
    prog2->allocate_element<VariableDescriptor>("var2", 200);
    
    auto stats = manager.statistics();
    EXPECT_EQ(stats.size(), 2);
    EXPECT_GT(stats["prog1"], 0.0);
    EXPECT_GT(stats["prog2"], 0.0);
}

TEST_F(ManagerTest, Defragmentation) {
    Program* prog = manager.add_program("prog1", "test.cpp", 1024);
    
    // Allocate and free to create fragmentation
    VariableDescriptor* var1 = prog->allocate_element<VariableDescriptor>("var1", 100);
    VariableDescriptor* var2 = prog->allocate_element<VariableDescriptor>("var2", 200);
    VariableDescriptor* var3 = prog->allocate_element<VariableDescriptor>("var3", 300);
    
    size_t originalOffset2 = var2->get_offset();
    size_t originalOffset3 = var3->get_offset();
    
    // Free middle element
    prog->destroy_element("var2");
    
    // Defragment
    manager.defragment_memory();
    
    // Check if var3 moved
    EXPECT_EQ(var3->get_offset(), originalOffset2);
    
    // Allocate new variable should use freed space
    VariableDescriptor* var4 = prog->allocate_element<VariableDescriptor>("var4", 200);
    ASSERT_NE(var4, nullptr);
    EXPECT_EQ(var4->get_offset(), var3->get_offset() + var3->get_size());
}

TEST_F(ManagerTest, GetAllElements) {
    Program* prog = manager.add_program("prog1", "test.cpp", 512);
    
    prog->allocate_element<VariableDescriptor>("var1", sizeof(int));
    prog->allocate_element<VariableDescriptor>("var2", sizeof(double));
    
    auto allElements = manager.get_memory_elements();
    EXPECT_EQ(allElements.size(), 2);
    EXPECT_NE(allElements.find("var1"), allElements.end());
    EXPECT_NE(allElements.find("var2"), allElements.end());
}

TEST_F(ManagerTest, ErrorRecording) {
    Program* prog = manager.add_program("prog1", "test.cpp", 100);
    
    // Trigger error by exceeding memory
    prog->allocate_element<VariableDescriptor>("var1", 150);
    
    auto allErrors = manager.all_errors();
    auto progErrors = manager.program_errors("prog1");
    
    EXPECT_FALSE(allErrors.empty());
    EXPECT_FALSE(progErrors.empty());
    
    for (const auto& error : progErrors) {
        EXPECT_EQ(error.get_program(), "prog1");
    }
}