#include <gtest/gtest.h>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/ReferenceDescriptor.hpp>
#include <Memory/Manager.hpp>
#include <Memory/Program.hpp>

using namespace MemoryNameSpace;

class MemoryElementsTest : public ::testing::Test {
protected:
    Manager<1024> manager;
    Program* program;
    
    void SetUp() override {
        manager = Manager<1024>();
        program = manager.add_program("test", "test.cpp", 512);
    }
};

TEST_F(MemoryElementsTest, VariableDescriptorBasics) {
    VariableDescriptor* var = program->allocate_element<VariableDescriptor>("myVar", sizeof(int));
    
    EXPECT_EQ(var->get_name(), "myVar");
    EXPECT_EQ(var->get_size(), sizeof(int));
    EXPECT_EQ(var->get_elem_size(), sizeof(int));
    EXPECT_FALSE(var->is_reference());
    EXPECT_TRUE(var->is_possible_to_destroy("test"));
}

TEST_F(MemoryElementsTest, ArrayDescriptorBasics) {
    ArrayDescriptor* arr = program->allocate_element<ArrayDescriptor>("myArray", 
                                                                      10 * sizeof(int), 
                                                                      sizeof(int));
    
    EXPECT_EQ(arr->get_name(), "myArray");
    EXPECT_EQ(arr->get_size(), 10 * sizeof(int));
    EXPECT_EQ(arr->get_elem_size(), sizeof(int));
    
    // Test array access
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    arr->set_value(values, 0, 10);
    
    int retrieved[10];
    arr->get_value(retrieved, 0, 10);
    
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(retrieved[i], values[i]);
    }
}

TEST_F(MemoryElementsTest, ReferenceDescriptorBasics) {
    // Create original variable
    VariableDescriptor* var = program->allocate_element<VariableDescriptor>("original", sizeof(int));
    
    // Create reference
    ReferenceDescriptor* ref = program->make_reference("ref", "original");
    
    EXPECT_EQ(ref->get_name(), "ref");
    EXPECT_EQ(ref->get_ref_name(), "ref");
    EXPECT_TRUE(ref->is_reference());
    EXPECT_TRUE(ref->is_valid());
    
    // Reference should have same size as original
    EXPECT_EQ(ref->get_size(), var->get_size());
    
    // Test value access through reference
    int originalValue = 42;
    var->set_value(originalValue);
    
    int retrievedThroughRef;
    ref->get_value(retrievedThroughRef);
    EXPECT_EQ(retrievedThroughRef, originalValue);
    
    // Modify through reference
    int newValue = 100;
    ref->set_value(newValue);
    
    int retrievedFromOriginal;
    var->get_value(retrievedFromOriginal);
    EXPECT_EQ(retrievedFromOriginal, newValue);
}

TEST_F(MemoryElementsTest, ReferenceToDestroyedElement) {
    VariableDescriptor* var = program->allocate_element<VariableDescriptor>("temp", sizeof(int));
    ReferenceDescriptor* ref = program->make_reference("refToTemp", "temp");
    
    // Destroy original
    program->destroy_element("temp");
    
    EXPECT_FALSE(ref->is_valid());
    EXPECT_EQ(ref->get_size(), 0);
    EXPECT_EQ(ref->get_offset(), manager.get_capacity());
}

TEST_F(MemoryElementsTest, RawValueAccess) {
    VariableDescriptor* var = program->allocate_element<VariableDescriptor>("rawTest", sizeof(double));
    
    double original = 3.14159;
    var->set_value(original);
    
    std::byte rawBytes[sizeof(double)];
    var->get_raw_value(rawBytes, 0, 0);
    
    double retrieved;
    std::memcpy(&retrieved, rawBytes, sizeof(double));
    EXPECT_EQ(retrieved, original);
}

TEST_F(MemoryElementsTest, ElementDestruction) {
    VariableDescriptor* var = program->allocate_element<VariableDescriptor>("toDestroy", sizeof(int));
    
    EXPECT_TRUE(var->is_possible_to_destroy("test"));
    
    bool destroyed = var->destroy(*program);
    EXPECT_TRUE(destroyed);
    
    auto elements = program->get_memory_elements();
    EXPECT_EQ(elements.find("toDestroy"), elements.end());
}

TEST_F(MemoryElementsTest, OffsetManagement) {
    VariableDescriptor* var = program->allocate_element<VariableDescriptor>("var", 100);
    
    size_t originalOffset = var->get_offset();
    var->set_offset(originalOffset + 50);
    
    EXPECT_EQ(var->get_offset(), originalOffset + 50);
}