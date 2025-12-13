#ifndef PRESENTER_HPP
#define PRESENTER_HPP

#include <Memory/IManager.hpp>
#include <Memory/Program.hpp>
#include <Memory/VariableDescriptor.hpp>

namespace MVPNameSpace {

using namespace MemoryNameSpace;

class Presenter final {
private:
    IManager& manager_;

public:
    Presenter(IManager& manager) : manager_(manager) {}

    bool allocate_variable(const std::string& prog, const std::string& name, size_t size);
    std::vector<std::string> get_programs_names();
    bool add_program(const std::string& name, const std::string& file_path, size_t memory_limit);
    std::vector<std::string> errors();
};

}

#endif