#ifndef IMANAGER_HPP
#define IMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <optional>
#include <Memory/Buffer.hpp>
#include <Memory/IMemoryElement.hpp>
#include <Memory/Error.hpp>

namespace MemoryNameSpace{

class ReferenceDescriptor;         // forward
class IMemoryElement; 

template<typename T>
concept memory_element_t =
    std::is_base_of_v<IMemoryElement, T> &&
    !std::is_same_v<IMemoryElement, T>;

class IManager {
protected:
    virtual std::optional<size_t> valid_allocate(size_t size, const Program& program) = 0;
    virtual bool valid_destroy(size_t offset, size_t size, const Program& program) = 0;
    virtual bool check_exist_with_allocate_error(const std::string& name, const Program& program) = 0;
    virtual bool check_exist_with_destroy_error(const std::string& name, const Program& program) = 0;
    
public:
    virtual void insert_element(IMemoryElement* element) = 0;
    virtual void erase_element(IMemoryElement* element) = 0;
    virtual ReferenceDescriptor* make_reference(const std::string& name, const std::string& target_name, const Program& program) = 0;
    virtual bool destroy_element(const std::string& name, const Program& program) = 0;
    virtual Program* add_program(const std::string& name, const std::string& file_path, size_t memory_limit) = 0;
    virtual void delete_program(const std::string& name) = 0;
    virtual void record_error(size_t type, const std::string& description, const std::string& program) = 0;
    
    virtual bool get_access_to_shared(const std::string& prog_name, const std::string& segment_name) = 0;
    virtual bool revoke_access_to_shared(const std::string& prog_name, const std::string& segment_name) = 0;

    virtual IMemoryElement* get_element(const std::string& target_name) const = 0;
    virtual std::unordered_map<std::string, Program*> get_programs() const = 0;
    virtual std::byte* get_data() noexcept = 0;
    virtual const std::byte* get_data() const noexcept = 0;
    virtual size_t get_capacity() const noexcept = 0;
    virtual std::unordered_map<std::string, IMemoryElement*> get_memory_elements() const = 0;

    virtual std::vector<Error> all_errors() const = 0;
    virtual std::vector<Error> program_errors(const std::string& program_name) const = 0;
    virtual std::vector<ReferenceDescriptor*> dungling_reference() const = 0;
    virtual std::unordered_map<std::string, double> statistics() const = 0;
    virtual void defragment_memory() = 0;
    virtual ~IManager(){}

    template <memory_element_t Descriptor, typename... ExtraArgs>
    Descriptor* allocate_element(const std::string& name, size_t size, const Program& program, ExtraArgs&&... args){
        if(check_exist_with_allocate_error(name, program)) return nullptr;
        if(auto offset = valid_allocate(size, program); offset.has_value()){
            Descriptor* element = new Descriptor(name, size, *offset, args..., *this);
            insert_element(element);
            return element;
        }
        return nullptr; 
    }
};

}

#endif