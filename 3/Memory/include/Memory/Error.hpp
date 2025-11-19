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
};

}

#endif