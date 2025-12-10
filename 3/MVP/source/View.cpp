#include <MVP/View.hpp>

namespace MVPNameSpace {

void View::render_ui(){
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

int View::show(){
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
        render_ui();

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
}

}