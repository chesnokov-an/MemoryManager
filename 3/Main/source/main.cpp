#include <iostream>
#include <Memory/Manager.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>
#include <Memory/Program.hpp>
#include <MVP/View.hpp>
#include <MVP/Presenter.hpp>

int main(){
    
    // using namespace MemoryNameSpace;

    // Manager<20> manager;
    // Program* prog = manager.add_program("VSCode", "/data/vscode", 20);
    // std::vector<IMemoryElement*> elems;
    // elems.push_back(prog->allocate_element<VariableDescriptor>("a", sizeof(int))); // 1  
    // elems.push_back(prog->allocate_element<VariableDescriptor>("b", sizeof(int))); // 2  
    // elems.push_back(prog->allocate_element<VariableDescriptor>("c", sizeof(int))); // 3  --
    // elems.push_back(prog->allocate_element<VariableDescriptor>("d", sizeof(int))); // 4  
    // elems.push_back(prog->allocate_element<VariableDescriptor>("e", sizeof(int))); // 5  --
    // // elems.push_back(prog->allocate_element<VariableDescriptor>("f", sizeof(int)));

    // for(int i = 1; i < elems.size()+1; ++i){
    //     if(elems[i-1])
    //         elems[i-1]->set_value(i);
    // }

    // prog->destroy_element("c");
    // prog->destroy_element("e");

    // manager.defragment_memory();

    // IMemoryElement* k = prog->allocate_element<VariableDescriptor>("k", sizeof(int) * 2);

    // size_t k_val = 999;
    // k->set_value(k_val);

    // for(auto elem : manager.all_errors()){
    //     std::cout << elem.get_description() << std::endl;
    // }

    // for(auto [name, ptr] : manager.get_memory_elements()){
    //     std::cout << ptr->get_name() << std::endl;
    // }

    // std::cout << std::endl;

    // for(int i = 0; i < 5; ++i){
    //     std::cout << *(reinterpret_cast<int*>(manager.get_data()) + i) << std::endl;
    // }

    using namespace MVPNameSpace;

    Manager<300> manager;
    Presenter presenter(manager);
    View view(presenter);

    return view.show();

    return 0;
}