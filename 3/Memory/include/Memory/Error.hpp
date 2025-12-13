#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <vector>

namespace MemoryNameSpace{

class Program;    // forward

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
    std::string program_name_;

public:
    Error(size_t type, std::string description, const std::string& program_name)
            : type_(static_cast<error_t>(type)), description_(description), program_name_(program_name) {}
    std::string get_description() const;
    const std::string& get_program() const;
};

}

#endif