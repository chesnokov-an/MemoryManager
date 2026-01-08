#include <Memory/Program.hpp>
#include <Memory/Manager.hpp>
#include <iostream>
#include <execution>
#include <numeric>
#include <ranges>
#include <thread>
#include <future>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include <tbb/concurrent_vector.h>

namespace MemoryNameSpace{

const std::string& Program::get_name() const {
    return name_;
}

void Program::insert_element(IMemoryElement* element){
    memory_elements_.try_emplace(element->get_name(), element);
}

void Program::erase_element(IMemoryElement* element){
    memory_elements_.erase(element->get_name());
}

ReferenceDescriptor* Program::make_reference(const std::string& name, const std::string& target_name){
    auto it = memory_elements_.find(target_name);
    if(it == memory_elements_.end()){
        record_error(ACCESS_ERROR, "The variable named '" + target_name + "' is not available for program.");
        return nullptr;
    }
    ReferenceDescriptor* reference = manager_.make_reference(name, target_name, *this);
    if(reference == nullptr) return nullptr;
    memory_elements_.insert({name, reference});
    return reference;
}

void Program::record_error(size_t type, const std::string& description){
    manager_.record_error(type, description, name_);
}

bool Program::destroy_element(const std::string& name){
    auto it = memory_elements_.find(name);
    if(it == memory_elements_.end()){
        record_error(ACCESS_ERROR, "The variable '" + name + "' is not available for program.");
        return false;
    }
    if(!it->second->is_possible_to_destroy(name_)) return false;
    return it->second->destroy(*this);
}

bool Program::possible_for_expansion(size_t size) const {
    if(size > memory_limit_ - get_used_memory())
        return false;
    return true;
}

// 1 thread

size_t Program::get_used_memory() const noexcept {
    return std::transform_reduce(memory_elements_.begin(), memory_elements_.end(), size_t{0}, std::plus<>{},
        [](const auto& pair) -> size_t {
            return pair.second->is_reference() ? 0 : pair.second->get_size();
        }
    );
}

// vector from views
/*
size_t Program::get_used_memory() const noexcept {
    auto range = memory_elements_ | std::views::values;
    std::vector<IMemoryElement*> vec(range.begin(), range.end());
    return std::transform_reduce(std::execution::par, vec.begin(), vec.end(), size_t{0}, std::plus<>{},
        [](const auto& ptr) -> size_t {
            return ptr->is_reference() ? 0 : ptr->get_size();
        }
    );
}*/

// manual multithreading
/*
size_t Program::get_used_memory() const noexcept {
    using It = decltype(memory_elements_.cbegin());
    size_t threadNum = std::thread::hardware_concurrency();
    if (threadNum == 0) threadNum = 64;
    size_t elements = memory_elements_.size();
    if (elements == 0) return 0;

    std::vector<size_t> results(threadNum, 0);
    std::vector<std::thread> threads(threadNum);

    It first = memory_elements_.cbegin();
    for (size_t i = 0; i < threadNum; ++i) {
        size_t start_i = i * elements / threadNum;
        size_t end_i = (i + 1) * elements / threadNum;
        It start = std::next(first, start_i);
        It end   = std::next(first, end_i);
        threads[i] = std::thread([start, end, &results, i]() {
            size_t local = 0;
            for (auto it = start; it != end; ++it) {
                const auto* ptr = it->second;
                if (!ptr->is_reference())
                    local += ptr->get_size();
            }
            results[i] = local;
        });
    }

    for (auto& th : threads)
        th.join();
    return std::accumulate(results.begin(), results.end(), size_t{0});
}*/

const std::unordered_map<std::string, IMemoryElement*>& Program::get_memory_elements() const noexcept {
    return memory_elements_;
}

Program::~Program(){
    for(auto&& [name, ptr] : memory_elements_){
        SharedSegmentDescriptor* segment = dynamic_cast<SharedSegmentDescriptor*>(ptr);
        if(!ptr->is_reference() && !segment)
            manager_.record_error(MEMORY_LEAK, "The element '" + name + "' is still reachable.", name_);
        if(segment)
            segment->erase_program(this);
            
    }
}

}
