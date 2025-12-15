#ifndef PRESENTER_HPP
#define PRESENTER_HPP

#include <Memory/IManager.hpp>
#include <Memory/Program.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>

namespace MVPNameSpace {

using namespace MemoryNameSpace;

class Presenter final {
private:
    IManager& manager_;

public:
    Presenter(IManager& manager) : manager_(manager) {}
    std::vector<std::string> get_programs_names();
    std::vector<std::string> get_elements_by_program(const std::string& prog);
    bool add_program(const std::string& name, const std::string& file_path, size_t memory_limit);
    void delete_program(const std::string& name);
    bool make_reference(const std::string& name, const std::string& target_name, const std::string& prog);
    void defragment();
    std::vector<std::string> errors();
    std::vector<std::string> dungling_reference();

    template<typename T>
    bool allocate_variable(const std::string& prog, const std::string& name){
        auto it = manager_.get_programs().find(prog);
        auto elem = it->second->allocate_element<VariableDescriptor>(name, sizeof(T));
        return (elem != nullptr);
    }

    template<typename T>
    bool allocate_array(const std::string& prog, const std::string& name, const size_t& count_elements){
        auto it = manager_.get_programs().find(prog);
        auto elem = it->second->allocate_element<ArrayDescriptor>(name, sizeof(T) * count_elements, count_elements);
        return (elem != nullptr);
    }

    template<typename T>
    bool allocate_shared(const std::string& prog, const std::string& name, const size_t& count_elements){
        auto it = manager_.get_programs().find(prog);
        auto elem = it->second->allocate_element<SharedSegmentDescriptor>(name, sizeof(T) * count_elements, count_elements, it->second);
        return (elem != nullptr);
    }
};

}

#endif