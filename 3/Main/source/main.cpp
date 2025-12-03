#include <iostream>
#include <Memory/Manager.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>
#include <Memory/Program.hpp>

int main(){
    using namespace MemoryNameSpace;
    // int i = 0;

    Manager<300> manager;
    Program* prog = manager.add_program("VSCode", "/data/vscode", 200);

    struct s{
        size_t a = 9;
        size_t b = 11;
        size_t c = 13;
        size_t d = 15;
    };

    s t;

    std::cout << sizeof(t) << std::endl;
    
    IMemoryElement* a = prog->allocate_element<VariableDescriptor>("A", 32);

    std::cout << a->get_name() << std::endl;
    try{
        a->set_value(t);
    }
    catch(...){
        std::cout << "oops" << std::endl;
    }
    
    s value;

    a->get_value(value);
    std::cout << value.c << std::endl;

    IMemoryElement* b = prog->allocate_element<SharedSegmentDescriptor>("B", 32, 8, prog);

    size_t a1 = 99;
    std::cout << b->get_name() << std::endl;
    std::cout << b->get_size() << std::endl;
    std::cout << b->get_elem_size() << std::endl;
    
    b->set_value(a1, 3);
    b->set_value(a1, 1);
    b->set_value(a1, 2);
    b->set_value(a1, 0);
    // size_t value1;
    // b->get_value(value, 0, 4);
    std::cout << value.a << value.b << value.c << value.d << std::endl;

    IMemoryElement* ref = manager.make_reference("c", "A", *prog);

    manager.show_errors();

    if(ref == nullptr) std:: cout << "BEBEBE" << std::endl;
    ref->get_value(value, 0, 4);
    // b->get_value(value, 0, 4);
    
    std::cout << value.a << value.b << value.c << value.d << std::endl;

    Program* prog1 = manager.add_program("VK", "/data/vscode", 50);
    dynamic_cast<SharedSegmentDescriptor*>(b)->insert_program(prog1);
    dynamic_cast<SharedSegmentDescriptor*>(b)->erase_program("VSCode");




    manager.show_errors();
    return 0;
}