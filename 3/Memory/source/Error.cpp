#include<Memory/Error.hpp>
#include<Memory/Program.hpp>

namespace MemoryNameSpace{

std::string Error::get_description() const {
    std::vector<std::string> messages{"SIZE_ERROR", "MEMORY_LEAK", "DOUBLE_FREE", "ACCESS_ERROR"};
    if(program_ == nullptr)
    return "Error: '" + messages[static_cast<size_t>(type_)] + "': " + description_;
    return "Error: '" + messages[static_cast<size_t>(type_)] + "' in program '" + program_->get_name() + "': " + description_;
}

const Program& Error::get_program() const {
    return *program_;
}

}
