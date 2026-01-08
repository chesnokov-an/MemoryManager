#ifndef PRESENTER_HPP
#define PRESENTER_HPP

#include <Memory/IManager.hpp>
#include <Memory/Program.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>

namespace MVPNameSpace {

using namespace MemoryNameSpace;

enum class DataType {
    Bool,
    Char,
    Int,
    LongLong,
    SizeT,
    Double
};

class Presenter final {
private:
    IManager& manager_;
    std::unordered_map<std::string, DataType> elements_types;

public:
    Presenter(IManager& manager) : manager_(manager) {}
    std::vector<std::string> get_programs_names();
    std::vector<std::string> get_elements_by_program(const std::string& prog);
    std::vector<std::string> get_segments();
    std::vector<std::string> get_segments(const std::string& prog);
    DataType get_type(const std::string& name);
    std::string get_value(const std::string& name, size_t begin = 0, size_t end = 0);
    bool is_array(const std::string& name);
    bool add_program(const std::string& name, const std::string& file_path, size_t memory_limit);
    void delete_program(const std::string& name);
    bool make_reference(const std::string& name, const std::string& target_name, const std::string& prog);
    bool delete_element(const std::string& name, const std::string& prog);
    bool request_access(const std::string& segment, const std::string& program);
    bool revoke_access(const std::string& segment, const std::string& program);
    void defragment();
    void statistics(std::vector<float>& values, std::vector<std::string>& names);
    std::vector<std::string> errors();
    std::vector<std::string> dungling_reference();

    template<typename T>
    bool allocate_variable(const std::string& prog, const std::string& name, DataType type_name){
        auto it = manager_.get_programs().find(prog);
        auto elem = it->second->allocate_element<VariableDescriptor>(name, sizeof(T));
        if(elem != nullptr) elements_types.insert({elem->get_name(), type_name});
        return (elem != nullptr);
    }

    template<typename T>
    bool allocate_array(const std::string& prog, const std::string& name, const size_t& count_elements, DataType type_name){
        auto it = manager_.get_programs().find(prog);
        auto elem = it->second->allocate_element<ArrayDescriptor>(name, sizeof(T) * count_elements, sizeof(T));
        if(elem != nullptr) elements_types.insert({elem->get_name(), type_name});
        return (elem != nullptr);
    }

    template<typename T>
    bool allocate_shared(const std::string& prog, const std::string& name, const size_t& count_elements, DataType type_name){
        auto it = manager_.get_programs().find(prog);
        auto elem = it->second->allocate_element<SharedSegmentDescriptor>(name, sizeof(T) * count_elements, sizeof(T), it->second);
        if(elem != nullptr) elements_types.insert({elem->get_name(), type_name});
        return (elem != nullptr);
    }

    template<typename T>
    bool set_value(const std::string& name, T value, size_t begin = 0, size_t end = 0){
        try{
            manager_.get_memory_elements().find(name)->second->set_value(value, begin, end);
        }
        catch(const std::runtime_error& e){
            manager_.record_error(SIZE_ERROR, e.what(), "");
            return false;
        }
        return true;
    }
};

}

#endif