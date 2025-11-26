#include<Memory/Error.hpp>

namespace MemoryNameSpace{

std::string Error::get_description(){
    std::vector<std::string> messages{"SIZE_ERROR", "MEMORY_LEAK", "DOUBLE_FREE", "ACCESS_ERROR"};
    return "Error: " + messages[static_cast<size_t>(type_)] + ": " + description_;
}

}
