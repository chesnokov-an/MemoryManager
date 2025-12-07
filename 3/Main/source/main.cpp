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

    IMemoryElement* ref = prog->make_reference("c", "A");

    manager.show_errors();

    if(ref == nullptr) std:: cout << "BEBEBE" << std::endl;
    ref->get_value(value, 0, 4);
    // b->get_value(value, 0, 4);
    
    std::cout << value.a << " " << value.b << value.c << value.d << std::endl;

    Program* prog1 = manager.add_program("VK", "/data/vscode", 50);
    manager.get_access_to_shared("VK", "B");
    manager.revoke_access_to_shared("VSCode", "B");
    dynamic_cast<SharedSegmentDescriptor*>(b)->is_last();
    IMemoryElement* k = prog1->allocate_element<VariableDescriptor>("K", 18);
    // prog1->destroy_element("B");
    std::cout << "CUR SIZE: " << prog1->get_used_memory() << std::endl;
    manager.show_errors();

    std::unordered_map<std::string, IMemoryElement*> elements = manager.get_memory_elements();
    for(auto&& [name, ptr] : elements){
        std::cout << name << " " << ptr->get_size() << std::endl;
    }

    
    // Manager manager;
    // Presenter presenter(manager);
    // View view(presenter);

    // presenter.set_view(&view);

    // view.show();
    
    return 0;
}


// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
// #include <GLFW/glfw3.h>
// #include <iostream>
// #include <vector>
// #include <string>

// // Простейшая структура памяти для демонстрации
// struct MemoryBlock {
//     std::string name;
//     size_t size;
//     size_t offset;
// };

// int main() {
//     // -----------------------------
//     // Инициализация GLFW
//     // -----------------------------
//     if (!glfwInit()) {
//         std::cerr << "Failed to initialize GLFW\n";
//         return -1;
//     }

//     GLFWwindow* window = glfwCreateWindow(800, 600, "Memory Manager", nullptr, nullptr);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window\n";
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     glfwSwapInterval(1); // vsync

//     // -----------------------------
//     // Инициализация ImGui
//     // -----------------------------
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;
//     ImGui::StyleColorsDark();

//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init("#version 130");

//     // -----------------------------
//     // Демо-данные памяти
//     // -----------------------------
//     std::vector<MemoryBlock> memoryBlocks = {
//         {"VarA", 50, 0},
//         {"ArrayB", 120, 50},
//         {"SharedC", 80, 170}
//     };

//     // -----------------------------
//     // Главный цикл
//     // -----------------------------
//     while (!glfwWindowShouldClose(window)) {
//         glfwPollEvents();

//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();

//         ImGui::Begin("Memory Manager");

//         // Таблица элементов
//         if (ImGui::BeginTable("MemoryTable", 3)) {
//             ImGui::TableSetupColumn("Name");
//             ImGui::TableSetupColumn("Size");
//             ImGui::TableSetupColumn("Offset");
//             ImGui::TableHeadersRow();

//             for (auto& block : memoryBlocks) {
//                 ImGui::TableNextRow();
//                 ImGui::TableNextColumn(); ImGui::Text("%s", block.name.c_str());
//                 ImGui::TableNextColumn(); ImGui::Text("%zu", block.size);
//                 ImGui::TableNextColumn(); ImGui::Text("%zu", block.offset);
//             }
//             ImGui::EndTable();
//         }

//         // Кнопки для действий
//         if (ImGui::Button("Allocate Example")) {
//             size_t newOffset = memoryBlocks.empty() ? 0 : memoryBlocks.back().offset + memoryBlocks.back().size;
//             memoryBlocks.push_back({"NewBlock", 60, newOffset});
//         }
//         ImGui::SameLine();
//         if (ImGui::Button("Free Last")) {
//             if (!memoryBlocks.empty()) memoryBlocks.pop_back();
//         }

//         ImGui::End();

//         // -----------------------------
//         // Рендер
//         // -----------------------------
//         ImGui::Render();
//         int display_w, display_h;
//         glfwGetFramebufferSize(window, &display_w, &display_h);
//         glViewport(0, 0, display_w, display_h);
//         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//         glfwSwapBuffers(window);
//     }

//     // -----------------------------
//     // Очистка ресурсов
//     // -----------------------------
//     memoryBlocks.clear(); // чистим свой вектор для демонстрации

//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();

//     glfwDestroyWindow(window);
//     glfwTerminate();

//     return 0;
// }


/*
// minimal_check_main.cpp (проверочный)
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

void RenderUI()
{
    ImGui::Begin("Memory Manager");

    if (ImGui::BeginTabBar("MainTabs"))
    {
        // ================================
        //  TAB 1 — OPERATIONS
        // ================================
        if (ImGui::BeginTabItem("Operations"))
        {
            ImGui::Text("Operations with Variables");
            ImGui::Separator();

            if (ImGui::Button("Create variable", ImVec2(200, 30)))
            {
                // TODO: call presenter
            }

            if (ImGui::Button("Delete variable", ImVec2(200, 30)))
            {
                // TODO
            }

            if (ImGui::Button("Set value", ImVec2(200, 30)))
            {
                // TODO
            }

            if (ImGui::Button("Get value", ImVec2(200, 30)))
            {
                // TODO
            }

            ImGui::Spacing();
            ImGui::Text("Segment access");
            ImGui::Separator();

            if (ImGui::Button("Request segment access", ImVec2(200, 30)))
            {
                // TODO
            }

            if (ImGui::Button("Revoke access", ImVec2(200, 30)))
            {
                // TODO
            }

            if (ImGui::Button("Create link", ImVec2(200, 30)))
            {
                // TODO
            }

            ImGui::Spacing();
            ImGui::Text("System");
            ImGui::Separator();

            if (ImGui::Button("Defragment memory", ImVec2(200, 30)))
            {
                // TODO
            }


            // --- Right side panel ---
            ImGui::SameLine(250);
            ImGui::BeginChild("output_block", ImVec2(350, 300), true);
            ImGui::Text("Output:");
            ImGui::Separator();
            // ImGui::TextWrapped("%s", output_log.c_str());    // your presenter text
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        // ================================
        //  TAB 2 — MEMORY MONITOR
        // ================================
        if (ImGui::BeginTabItem("Monitor"))
        {
            ImGui::Text("Memory usage by programs");
            ImGui::Separator();

            // Demo bar chart
            float values[] = { 40, 22, 33, 12 };
            const char* labels[] = { "Prog1", "Prog2", "Prog3", "Prog4" };
            int count = 4;

            ImGui::PlotHistogram("##MemoryUsage", values, count, 0, nullptr, 0.0f, 50.0f, ImVec2(400, 200));

            for (int i = 0; i < count; ++i)
            {
                ImGui::Text("%s: %.1f MB", labels[i], values[i]);
            }

            ImGui::EndTabItem();
        }

        // ================================
        //  TAB 3 — ERROR LOG
        // ================================
        if (ImGui::BeginTabItem("Error Log"))
        {
            ImGui::Text("Errors:");
            ImGui::Separator();

            ImGui::BeginChild("errors", ImVec2(400, 200), true);

            // for (auto& err : error_log)
            // {
            //     if (err.type == ErrorType::SIZE_ERROR)
            //         ImGui::TextColored(ImVec4(1, 0.8, 0, 1), "SIZE_ERROR: %s", err.text.c_str());
            //     else if (err.type == ErrorType::ACCESS_ERROR)
            //         ImGui::TextColored(ImVec4(1, 0.3, 0.3, 1), "ACCESS_ERROR: %s", err.text.c_str());
            //     else if (err.type == ErrorType::DOUBLE_FREE)
            //         ImGui::TextColored(ImVec4(1, 0.1, 0.1, 1), "DOUBLE_FREE: %s", err.text.c_str());
            // }

            ImGui::EndChild();

            ImGui::Spacing();
            ImGui::Text("Dangling links:");
            ImGui::Separator();

            // for (auto& link : dangling_links)
            // {
            //     ImGui::TextColored(ImVec4(0.5, 0.7, 1, 1), "%s", link.c_str());
            // }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}


int main()
{
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800,600,"Test",nullptr,nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // НУЖНЫЕ ВЫЗОВЫ ПЕРЕД РИСОВКОЙ UI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // отрисовка UI
        RenderUI();

        // завершение кадра
        ImGui::Render();
        int w,h; glfwGetFramebufferSize(window,&w,&h);
        glViewport(0,0,w,h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}*/