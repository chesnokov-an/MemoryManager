#include <MVP/Presenter.hpp>

namespace MVPNameSpace {

    std::vector<std::string> Presenter::get_programs_names(){
        std::vector<std::string> names;
        auto programs = manager_.get_programs();
        for(auto&& [name, ptr] : programs)
            names.push_back(name);
        return names;
    }

    std::vector<std::string> Presenter::get_elements_by_program(const std::string& prog){
        auto it = manager_.get_programs().find(prog);
        std::vector<std::string> names;
        auto elements = it->second->get_memory_elements();
        for(auto&& [name, ptr] : elements){
            names.push_back(name);
        }
        return names;
    }

    std::vector<std::string> Presenter::get_segments(){
        auto elements = manager_.get_memory_elements();
        std::vector<std::string> segments;
        for(auto&& [name, ptr] : elements){
            SharedSegmentDescriptor* segment = dynamic_cast<SharedSegmentDescriptor*>(ptr);
            if(segment)
                segments.push_back(segment->get_name());
        }
        return segments;
    }

    std::vector<std::string> Presenter::get_segments(const std::string& prog){
        auto it = manager_.get_programs().find(prog);
        auto elements = it->second->get_memory_elements();
        std::vector<std::string> segments;
        for(auto&& [name, ptr] : elements){
            SharedSegmentDescriptor* segment = dynamic_cast<SharedSegmentDescriptor*>(ptr);
            if(segment)
                segments.push_back(segment->get_name());
        }
        return segments;
    }

    DataType Presenter::get_type(const std::string& name){
        return elements_types.find(name)->second;
    }

    bool Presenter::is_array(const std::string& name){
        auto it = manager_.get_element(name);
        auto array = dynamic_cast<ArrayDescriptor*>(it);
        if(array) return true;
        return false;
    }

    bool Presenter::add_program(const std::string& name, const std::string& file_path, size_t memory_limit){
        Program* prog = manager_.add_program(name, file_path, memory_limit);
        return (prog != nullptr);
    }

    void Presenter::delete_program(const std::string& name){
        manager_.delete_program(name);
    }

    bool Presenter::make_reference(const std::string& name, const std::string& target_name, const std::string& prog){
        auto it = manager_.get_programs().find(prog);
        ReferenceDescriptor* reference = it->second->make_reference(name, target_name);
        if(reference != nullptr) elements_types.insert({name, elements_types.find(name)->second});
        return (reference != nullptr);
    }

    bool Presenter::delete_element(const std::string& name, const std::string& prog){
        auto it = manager_.get_programs().find(prog);
        bool flag = it->second->destroy_element(name);
        if(flag) elements_types.erase(name);
        return flag;
    }

    bool Presenter::request_access(const std::string& segment, const std::string& program){
        return manager_.get_access_to_shared(program, segment);
    }

    bool Presenter::revoke_access(const std::string& segment, const std::string& program){
        return manager_.revoke_access_to_shared(program, segment);
    }

    void Presenter::defragment(){
        manager_.defragment_memory();
    }

    void Presenter::statistics(std::vector<float>& values, std::vector<std::string>& names){
        auto stat = manager_.statistics();
        values.reserve(stat.size());
        names.reserve(stat.size());
        for(auto&& [name, value] : stat){
            values.push_back(value);
            names.push_back(name);
        }
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