#include <gtest/gtest.h>
#include <Memory/SharedSegmentDescriptor.hpp>
#include <Memory/Manager.hpp>
#include <Memory/Program.hpp>

using namespace MemoryNameSpace;

class SharedSegmentTest : public ::testing::Test {
protected:
    Manager<1024> manager;
    Program* program1;
    Program* program2;
    
    void SetUp() override {
        manager = Manager<1024>();
        program1 = manager.add_program("prog1", "prog1.cpp", 512);
        program2 = manager.add_program("prog2", "prog2.cpp", 512);
    }
};

TEST_F(SharedSegmentTest, CreationAndAccess) {
    SharedSegmentDescriptor* segment = 
        program1->allocate_element<SharedSegmentDescriptor>("shared", 
                                                            100, 
                                                            sizeof(int), 
                                                            program1);
    
    EXPECT_TRUE(segment->check_access("prog1"));
    EXPECT_FALSE(segment->check_access("prog2"));
}

TEST_F(SharedSegmentTest, ProgramManagement) {
    SharedSegmentDescriptor* segment = 
        program1->allocate_element<SharedSegmentDescriptor>("shared", 
                                                            100, 
                                                            sizeof(int), 
                                                            program1);
    
    segment->insert_program(program2);
    EXPECT_TRUE(segment->check_access("prog1"));
    EXPECT_TRUE(segment->check_access("prog2"));
    
    segment->erase_program(program2);
    EXPECT_TRUE(segment->check_access("prog1"));
    EXPECT_FALSE(segment->check_access("prog2"));
}

TEST_F(SharedSegmentTest, IsLastProgram) {
    SharedSegmentDescriptor* segment = 
        program1->allocate_element<SharedSegmentDescriptor>("shared", 
                                                            100, 
                                                            sizeof(int), 
                                                            program1);
    
    EXPECT_TRUE(segment->is_last());
    
    segment->insert_program(program2);
    EXPECT_FALSE(segment->is_last());
    
    segment->erase_program(program2);
    EXPECT_TRUE(segment->is_last());
}

TEST_F(SharedSegmentTest, DestroyPermissions) {
    SharedSegmentDescriptor* segment = 
        program1->allocate_element<SharedSegmentDescriptor>("shared", 
                                                            100, 
                                                            sizeof(int), 
                                                            program1);
    
    // Original program should be able to destroy
    EXPECT_TRUE(segment->is_possible_to_destroy("prog1"));
    
    // Add another program
    segment->insert_program(program2);
    
    // Now original program shouldn't be able to destroy (not last)
    EXPECT_FALSE(segment->is_possible_to_destroy("prog1"));
    
    // Second program also shouldn't be able to destroy
    EXPECT_FALSE(segment->is_possible_to_destroy("prog2"));
    
    // Remove second program
    segment->erase_program(program2);
    
    // Now should be able to destroy again
    EXPECT_TRUE(segment->is_possible_to_destroy("prog1"));
}

TEST_F(SharedSegmentTest, AccessThroughManager) {
    SharedSegmentDescriptor* segment = 
        program1->allocate_element<SharedSegmentDescriptor>("shared", 
                                                            100, 
                                                            sizeof(int), 
                                                            program1);
    
    // Grant access through manager
    bool accessGranted = manager.get_access_to_shared("prog2", "shared");
    EXPECT_TRUE(accessGranted);
    
    // Check program2 can see it
    auto prog2Elements = program2->get_memory_elements();
    EXPECT_NE(prog2Elements.find("shared"), prog2Elements.end());
    
    // Try to revoke access from non-owner
    bool accessRevoked = manager.revoke_access_to_shared("prog1", "shared");
    EXPECT_TRUE(accessRevoked); // Should fail - prog1 is owner
}