#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <Memory/Program.hpp>

namespace MemoryNameSpace{

enum error_t {
    SIZE_ERROR = 0,
    MEMORY_LEAK = 1,
    DOUBLE_FREE = 2,
    ACCESS_ERROR = 3,
};

class Error final{
private:
    error_t type_;
    std::string description_;
    const Program& program_;

public:
    Error(int type, std::string description, const Program& program)
            : type_(static_cast<error_t>(type)), description_(description), program_(program) {}
    std::string get_description();
};

}

#endif