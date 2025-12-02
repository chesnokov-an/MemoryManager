#include <iostream>
#include <Memory/Manager.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/Program.hpp>

int main(){
    using namespace MemoryNameSpace;
    int i = 0;
    std::cout << i++;
    Manager<15> manager;
    std::cout << i++;
    Program* prog = manager.add_program("VSCode", "/data/vscode", 32);
    std::cout << i++;
    VariableDescriptor* a = prog->allocate_element<VariableDescriptor>("A", 4);
    std::cout << i++;
    std::cout << a->get_name();
    std::cout << i++;

    return 0;
}