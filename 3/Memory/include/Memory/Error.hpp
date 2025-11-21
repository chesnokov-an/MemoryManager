#ifndef ERROR_HPP
#define ERROR_HPP

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
    const Program& program_;

public:
    Error(int type, const Program& program) : type_(static_cast<error_t>(type)), program_(program) {}
    std::string get_description();
};

}

#endif