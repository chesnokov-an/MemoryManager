#include <iostream>
#include <Memory/Manager.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>
#include <Memory/Program.hpp>
#include <MVP/View.hpp>
#include <MVP/Presenter.hpp>

int main(){
    
    //    using namespace MemoryNameSpace;
    // // int i = 0;

    // Manager<300> manager;
    // Program* prog = manager.add_program("VSCode", "/data/vscode", 200);

    // struct s{
    //     size_t a = 9;   
    //     size_t b = 11;
    //     size_t c = 13;
    //     size_t d = 15;
    // };

    // s t;

    // std::cout << sizeof(t) << std::endl;
    
    // IMemoryElement* a = prog->allocate_element<VariableDescriptor>("A", 32);

    // std::cout << a->get_name() << std::endl;
    // try{
    //     a->set_value(t);
    // }
    // catch(...){
    //     std::cout << "oops" << std::endl;
    // }
    
    // s value;

    // a->get_value(value);
    // std::cout << value.c << std::endl;

    // IMemoryElement* b = prog->allocate_element<SharedSegmentDescriptor>("B", 32, 8, prog);

    // size_t a1 = 99;
    // std::cout << b->get_name() << std::endl;
    // std::cout << b->get_size() << std::endl;
    // std::cout << b->get_elem_size() << std::endl;
    
    // b->set_value(a1, 3);
    // b->set_value(a1, 1);
    // b->set_value(a1, 2);
    // b->set_value(a1, 0);
    // // size_t value1;
    // // b->get_value(value, 0, 4);
    // std::cout << value.a << value.b << value.c << value.d << std::endl;



    // Program* prog1 = manager.add_program("VK", "/data/vscode", 50);
    // manager.get_access_to_shared("VK", "B");
    // // manager.revoke_access_to_shared("VSCode", "B");
    // dynamic_cast<SharedSegmentDescriptor*>(b)->is_last();
    // IMemoryElement* k = prog1->allocate_element<VariableDescriptor>("K", 18);
    // // prog1->destroy_element("B");
    // std::cout << "CUR SIZE: " << prog1->get_used_memory() << std::endl;
    // // manager.show_errors();

    // IMemoryElement* ref = prog1->make_reference("t", "A");

    // // manager.show_errors();

    // // if(ref == nullptr) std:: cout << "BEBEBE" << std::endl;
    // // ref->get_value(value, 0, 4);
    // // b->get_value(value, 0, 4);
    
    // std::cout << value.a << " " << value.b << value.c << value.d << std::endl;

    // std::unordered_map<std::string, IMemoryElement*> elements = manager.get_memory_elements();
    // for(auto&& [name, ptr] : elements){
    //     std::cout << name << " " << ptr->get_size() << std::endl;
    // }

    // for(auto elem : manager.all_errors()){
    //     std::cout << elem.get_description() << std::endl;
    // }

    // for(auto elem : manager.dungling_reference()){
    //     std::cout << "DANGLING: " << elem->get_name() << std::endl;
    // }
    // std::cout << prog->get_used_memory() << " --- " << std::endl;
    // std::cout << prog1->get_used_memory() << " --- " << std::endl;
    // for(auto [name, part] : manager.statistics()){
    //     std::cout << name << " - " << part << std::endl;
    // }

    using namespace MVPNameSpace;

    Manager<10> manager;
    Presenter presenter(manager);
    View view(presenter);

    return view.show();

    return 0;
}