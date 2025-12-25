#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <memory>

#include <Memory/Manager.hpp>
#include <Memory/Program.hpp>
#include <Memory/VariableDescriptor.hpp>

using namespace MemoryNameSpace;

// Простой бенчмарк для метода get_used_memory()
void simple_benchmark_get_used_memory() {
    std::cout << "=== Простой бенчмарк метода get_used_memory() ===\n";
    
    // Разные объемы данных для тестирования
    const std::vector<size_t> element_counts = {100000};
    const int warmup_runs = 0;
    const int measured_runs = 1;
    
    // Создаем менеджер с большим объемом памяти
    const size_t total_memory = 1024 * 1024 * 200; // 200 MB
    Manager<total_memory> manager;
    
    // Создаем программу
    Program* program = manager.add_program("benchmark", "benchmark.cpp", total_memory);
    if (!program) {
        std::cerr << "Ошибка создания программы!\n";
        return;
    }
    
    // Случайный генератор для размеров элементов
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> size_dist(16, 256); // 16-256 байт
    
    for (size_t num_elements : element_counts) {
        std::cout << "\nКоличество элементов: " << num_elements << "\n";
        
        // Создаем элементы
        std::vector<VariableDescriptor*> elements;
        size_t total_expected_memory = 0;
        
        for (size_t i = 0; i < num_elements; ++i) {
            std::string name = "var_" + std::to_string(i);
            size_t element_size = size_dist(gen);
            total_expected_memory += element_size;
            
            auto* elem = program->allocate_element<VariableDescriptor>(name, element_size);
            if (elem) {
                elements.push_back(elem);
            } else {
                std::cerr << "Ошибка выделения элемента " << i << "\n";
            }
        }
        
        std::cout << "Ожидаемая используемая память: " << total_expected_memory << " байт\n";
        
        // Прогревочные запуски
        for (int i = 0; i < warmup_runs; ++i) {
            size_t used = program->get_used_memory();
            (void)used; // Подавляем предупреждение
        }
        
        // Измеряемые запуски
        long long total_time_ns = 0;
        long long min_time_ns = std::numeric_limits<long long>::max();
        long long max_time_ns = 0;
        
        for (int i = 0; i < measured_runs; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            
            size_t actual_used_memory = program->get_used_memory();
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            
            long long time_ns = duration.count();
            total_time_ns += time_ns;
            min_time_ns = std::min(min_time_ns, time_ns);
            max_time_ns = std::max(max_time_ns, time_ns);
            
            if (i == 0) {
                std::cout << "Фактическая используемая память: " << actual_used_memory << " байт\n";
                if (actual_used_memory != total_expected_memory) {
                    std::cout << "⚠️  Расхождение! Ожидалось: " << total_expected_memory 
                              << ", получено: " << actual_used_memory << "\n";
                }
            }
        }
        
        // Статистика
        double avg_time_ns = static_cast<double>(total_time_ns) / measured_runs;
        
        std::cout << "Время выполнения (среднее за " << measured_runs << " запусков):\n";
        std::cout << "  " << avg_time_ns << " нс\n";
        std::cout << "  " << (avg_time_ns / 1000.0) << " мкс\n";
        std::cout << "  " << (avg_time_ns / 1000000.0) << " мс\n";
        std::cout << "  Минимум: " << min_time_ns << " нс\n";
        std::cout << "  Максимум: " << max_time_ns << " нс\n";
        
        // Очищаем элементы
        for (auto* elem : elements) {
            program->destroy_element(elem->get_name());
        }
    }
    
    std::cout << "\n=== Бенчмарк завершен ===\n";
}

int main() {
    std::cout << "Запуск простого бенчмарка для get_used_memory()\n";
    
    try {
        simple_benchmark_get_used_memory();
        
        // Опционально: дополнительный тест с фиксированным размером
        // benchmark_fixed_size_elements();
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}