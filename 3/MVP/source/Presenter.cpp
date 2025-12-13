#include <MVP/Presenter.hpp>

namespace MVPNameSpace {
    bool Presenter::allocate_variable(const std::string& prog, const std::string& name, size_t size){
        auto it = manager_.get_programs().find(prog);
        auto elem = it->second->allocate_element<VariableDescriptor>(name, size);
        return (elem != nullptr);
    }
    std::vector<std::string> Presenter::get_programs_names(){
        std::vector<std::string> names;
        auto programs = manager_.get_programs();
        for(auto&& [name, ptr] : programs)
            names.push_back(name);
        return names;
    }
    bool Presenter::add_program(const std::string& name, const std::string& file_path, size_t memory_limit){
        Program* prog = manager_.add_program(name, file_path, memory_limit);
        return (prog != nullptr);
    }

    void Presenter::delete_program(const std::string& name){
        manager_.delete_program(name);
    }

    void Presenter::defragment(){
        manager_.defragment_memory();
    }

    std::vector<std::string> Presenter::errors(){
        std::vector<std::string> errors_list;
        auto errors_log = manager_.all_errors();
        for(auto&& elem : errors_log)
            errors_list.push_back(elem.get_description());
        return errors_list;
    }

    std::vector<std::string> Presenter::dungling_reference(){
        std::vector<std::string> references;
        auto cur_refs = manager_.dungling_reference();
        for(auto&& elem : cur_refs)
            references.push_back(elem->get_name());
        return references;
    }


}