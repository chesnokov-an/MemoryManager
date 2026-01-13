#include<Memory/Error.hpp>
#include<Memory/Program.hpp>

namespace MemoryNameSpace{

std::string Error::get_description() const {
    std::vector<std::string> messages{"SIZE_ERROR", "MEMORY_LEAK", "DOUBLE_FREE", "ACCESS_ERROR"};
    return "Error: '" + messages[static_cast<size_t>(type_)] + "' in program '" + program_name_ + "': " + description_;
}

const std::string& Error::get_program() const {
    return program_name_;
}

}
