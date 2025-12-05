#include <iostream>
#include <Memory/Manager.hpp>
#include <Memory/VariableDescriptor.hpp>
#include <Memory/ArrayDescriptor.hpp>
#include <Memory/SharedSegmentDescriptor.hpp>
#include <Memory/Program.hpp>

int main(){
    using namespace MemoryNameSpace;
    // int i = 0;

    Manager<300> manager;
    Program* prog = manager.add_program("VSCode", "/data/vscode", 200);

    struct s{
        size_t a = 9;   
        size_t b = 11;
        size_t c = 13;
        size_t d = 15;
    };

    s t;

    std::cout << sizeof(t) << std::endl;
    
    IMemoryElement* a = prog->allocate_element<VariableDescriptor>("A", 32);

    std::cout << a->get_name() << std::endl;
    try{
        a->set_value(t);
    }
    catch(...){
        std::cout << "oops" << std::endl;
    }
    
    s value;

    a->get_value(value);
    std::cout << value.c << std::endl;

    IMemoryElement* b = prog->allocate_element<SharedSegmentDescriptor>("B", 32, 8, prog);

    size_t a1 = 99;
    std::cout << b->get_name() << std::endl;
    std::cout << b->get_size() << std::endl;
    std::cout << b->get_elem_size() << std::endl;
    
    b->set_value(a1, 3);
    b->set_value(a1, 1);
    b->set_value(a1, 2);
    b->set_value(a1, 0);
    // size_t value1;
    // b->get_value(value, 0, 4);
    std::cout << value.a << value.b << value.c << value.d << std::endl;

    IMemoryElement* ref = manager.make_reference("c", "A", *prog);

    manager.show_errors();

    if(ref == nullptr) std:: cout << "BEBEBE" << std::endl;
    ref->get_value(value, 0, 4);
    // b->get_value(value, 0, 4);
    
    std::cout << value.a << value.b << value.c << value.d << std::endl;

    Program* prog1 = manager.add_program("VK", "/data/vscode", 50);
    dynamic_cast<SharedSegmentDescriptor*>(b)->insert_program(prog1);
    dynamic_cast<SharedSegmentDescriptor*>(b)->erase_program("VSCode");

    manager.show_errors();

    /*
    Manager manager;
    Presenter presenter(manager);
    View view(presenter);

    presenter.set_view(&view);

    view.show();
    */
    return 0;
}









/*
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

// Простейшая структура памяти для демонстрации
struct MemoryBlock {
    std::string name;
    size_t size;
    size_t offset;
};

int main() {
    // -----------------------------
    // Инициализация GLFW
    // -----------------------------
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Memory Manager", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // -----------------------------
    // Инициализация ImGui
    // -----------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // -----------------------------
    // Демо-данные памяти
    // -----------------------------
    std::vector<MemoryBlock> memoryBlocks = {
        {"VarA", 50, 0},
        {"ArrayB", 120, 50},
        {"SharedC", 80, 170}
    };

    // -----------------------------
    // Главный цикл
    // -----------------------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Memory Manager");

        // Таблица элементов
        if (ImGui::BeginTable("MemoryTable", 3)) {
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Size");
            ImGui::TableSetupColumn("Offset");
            ImGui::TableHeadersRow();

            for (auto& block : memoryBlocks) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Text("%s", block.name.c_str());
                ImGui::TableNextColumn(); ImGui::Text("%zu", block.size);
                ImGui::TableNextColumn(); ImGui::Text("%zu", block.offset);
            }
            ImGui::EndTable();
        }

        // Кнопки для действий
        if (ImGui::Button("Allocate Example")) {
            size_t newOffset = memoryBlocks.empty() ? 0 : memoryBlocks.back().offset + memoryBlocks.back().size;
            memoryBlocks.push_back({"NewBlock", 60, newOffset});
        }
        ImGui::SameLine();
        if (ImGui::Button("Free Last")) {
            if (!memoryBlocks.empty()) memoryBlocks.pop_back();
        }

        ImGui::End();

        // -----------------------------
        // Рендер
        // -----------------------------
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // -----------------------------
    // Очистка ресурсов
    // -----------------------------
    memoryBlocks.clear(); // чистим свой вектор для демонстрации

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
*/