#ifndef ERROR_HPP
#define ERROR_HPP

#include <Memory/Program.hpp>

namespace MemoryNameSpace{

enum error_t {
    SIZE_ERROR = 1,
    MEMORY_LEAK = 2,
    DOUBLE_FREE = 3,
    ACCESS_ERROR = 4,
};

class Error final{
private:
    error_t type_;
    Program& program_;

public:
    Error(int type, Program& program) : type_(static_cast<error_t>(type)), program_(program) {}
    std::string get_description();
};

}

#endif