#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <Memory/Buffer.hpp>
#include <Memory/MemoryElement.hpp>
#include <Memory/Error.hpp>

namespace MemoryNameSpace{

class Manager final{
private:
    std::unique_ptr<IBuffer> buffer_;
    std::unordered_map<std::string, std::unique_ptr<IMemoryElement>> memory_elements_;
    std::vector<Error> error_log_;
    std::unordered_map<std::string, std::unique_ptr<Program>> programs_;

public:
    VariableDescriptor allocate_variable(const std::string& name, size_t size){

    }
};

}

#endif