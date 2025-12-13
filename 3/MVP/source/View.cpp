#include <MVP/View.hpp>

namespace MVPNameSpace {

void SetComfortableDarkCyanTheme(){
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 1.0f;
    style.WindowPadding = ImVec2(20.0f, 20.0f);
    style.WindowRounding = 11.5f;
    style.WindowBorderSize = 0.0f;
    style.WindowMinSize = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildRounding = 20.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 17.4f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(20.0f, 3.4f);
    style.FrameRounding = 11.9f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.9f, 13.4f);
    style.ItemInnerSpacing = ImVec2(7.1f, 1.8f);
    style.CellPadding = ImVec2(12.1f, 9.2f);
    style.IndentSpacing = 0.0f;
    style.ColumnsMinSpacing = 8.7f;
    style.ScrollbarSize = 11.6f;
    style.ScrollbarRounding = 15.9f;
    style.GrabMinSize = 3.7f;
    style.GrabRounding = 20.0f;
    style.TabRounding = 9.8f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    auto RGBA = [](int r, int g, int b, float a){
        return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a);
    };

    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text]                 = RGBA(255,255,255,1.0f);
    colors[ImGuiCol_TextDisabled]         = RGBA(70,81,115,1.0f);
    colors[ImGuiCol_WindowBg]             = RGBA(20,22,26,1.0f);
    colors[ImGuiCol_ChildBg]              = RGBA(24,26,30,1.0f);
    colors[ImGuiCol_PopupBg]              = RGBA(20,22,26,1.0f);
    colors[ImGuiCol_Border]               = RGBA(40,43,49,1.0f);
    colors[ImGuiCol_BorderShadow]         = RGBA(20,22,26,1.0f);
    colors[ImGuiCol_FrameBg]              = RGBA(29,32,39,1.0f);
    colors[ImGuiCol_FrameBgHovered]       = RGBA(40,43,49,1.0f);
    colors[ImGuiCol_FrameBgActive]        = RGBA(40,43,49,1.0f);
    colors[ImGuiCol_TitleBg]              = RGBA(12,14,18,1.0f);
    colors[ImGuiCol_TitleBgActive]        = RGBA(12,14,18,1.0f);
    colors[ImGuiCol_TitleBgCollapsed]     = RGBA(20,22,26,1.0f);
    colors[ImGuiCol_MenuBarBg]            = RGBA(25,27,31,1.0f);
    colors[ImGuiCol_ScrollbarBg]          = RGBA(12,14,18,1.0f);
    colors[ImGuiCol_ScrollbarGrab]        = RGBA(30,34,38,1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = RGBA(40,43,49,1.0f);
    colors[ImGuiCol_ScrollbarGrabActive]  = RGBA(30,34,38,1.0f);
    colors[ImGuiCol_CheckMark]            = RGBA(8,242,215,1.0f);
    colors[ImGuiCol_SliderGrab]           = RGBA(8,242,215,1.0f);
    colors[ImGuiCol_SliderGrabActive]     = RGBA(153,246,8,1.0f);
    colors[ImGuiCol_Button]               = RGBA(30,34,38,1.0f);
    colors[ImGuiCol_ButtonHovered]        = RGBA(46,48,50,1.0f);
    colors[ImGuiCol_ButtonActive]         = RGBA(39,39,39,1.0f);
    colors[ImGuiCol_Header]               = RGBA(36,42,53,1.0f);
    colors[ImGuiCol_HeaderHovered]        = RGBA(27,27,27,1.0f);
    colors[ImGuiCol_HeaderActive]         = RGBA(20,22,26,1.0f);
    colors[ImGuiCol_Separator]            = RGBA(33,38,49,1.0f);
    colors[ImGuiCol_SeparatorHovered]     = RGBA(40,47,64,1.0f);
    colors[ImGuiCol_SeparatorActive]      = RGBA(40,47,64,1.0f);
    colors[ImGuiCol_ResizeGrip]           = RGBA(37,37,37,1.0f);
    colors[ImGuiCol_ResizeGripHovered]    = RGBA(8,242,215,1.0f);
    colors[ImGuiCol_ResizeGripActive]     = RGBA(255,255,255,1.0f);
    colors[ImGuiCol_Tab]                  = RGBA(20,22,26,1.0f);
    colors[ImGuiCol_TabHovered]           = RGBA(30,34,38,1.0f);
    colors[ImGuiCol_TabActive]            = RGBA(30,34,38,1.0f);
    colors[ImGuiCol_TabUnfocused]         = RGBA(20,22,26,1.0f);
    colors[ImGuiCol_TabUnfocusedActive]   = RGBA(32,70,146,1.0f);
    colors[ImGuiCol_PlotLines]            = RGBA(133,153,179,1.0f);
    colors[ImGuiCol_PlotLinesHovered]     = RGBA(10,250,250,1.0f);
    colors[ImGuiCol_PlotHistogram]        = RGBA(8,242,215,1.0f);
    colors[ImGuiCol_PlotHistogramHovered] = RGBA(40,47,64,1.0f);
    colors[ImGuiCol_TableHeaderBg]        = RGBA(12,14,18,1.0f);
    colors[ImGuiCol_TableBorderStrong]    = RGBA(12,14,18,1.0f);
    colors[ImGuiCol_TableBorderLight]     = RGBA(0,0,0,1.0f);
    colors[ImGuiCol_TableRowBg]           = RGBA(30,34,38,1.0f);
    colors[ImGuiCol_TableRowBgAlt]        = RGBA(25,27,31,1.0f);
    colors[ImGuiCol_TextSelectedBg]       = RGBA(239,239,239,1.0f);
    colors[ImGuiCol_DragDropTarget]       = RGBA(127,131,255,1.0f);
    colors[ImGuiCol_NavHighlight]         = RGBA(68,74,255,1.0f);
    colors[ImGuiCol_NavWindowingHighlight]= RGBA(127,131,255,1.0f);
    colors[ImGuiCol_NavWindowingDimBg]    = RGBA(50,45,139,0.502f);
    colors[ImGuiCol_ModalWindowDimBg]     = RGBA(50,45,139,0.502f);
}


const char* types[] = {"variable", "array", "shared segment", "reference"};
int type_id = 0;

enum class DataType {
    Bool,
    Char,
    Int,
    LongLong,
    SizeT,
    Double
};

static const char* DataTypeNames[] = {
    "bool",
    "char",
    "int",
    "long long",
    "size_t",
    "double"
};

std::vector<std::string> output_buffer;

void View::render_ui(){
    bool opened = true;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(965, 960));
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::Begin("Memory Manager", &opened, flags);
    if (ImGui::BeginTabBar("MainTabs")){
        // ================================
        //  TAB 1 — OPERATIONS
        // ================================
        
        if (ImGui::BeginTabItem("Operations"))
        {
            ImGui::Text("Operations with Variables");
            ImGui::Separator();

            if (ImGui::Button("Create element", ImVec2(300, 35))){
                switch (type_id){
                case 0:
                    ImGui::OpenPopup("Create Variable Popup");
                    break;
                case 1:
                    ImGui::OpenPopup("Create Array Popup");
                    break;
                case 2:
                    ImGui::OpenPopup("Create SharedSegment Popup");
                    break;
                case 3:
                    ImGui::OpenPopup("Create Reference Popup");
                    break;
                }
            }

            if (ImGui::BeginPopupModal("Create Variable Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
                static char var_name[128] = "";
                static size_t selected_type = 0;
                ImGui::InputText("Name", var_name, IM_ARRAYSIZE(var_name));

                ImGui::Text("Type");
                if (ImGui::BeginCombo("##datatype", DataTypeNames[selected_type])){
                    for (size_t i = 0; i < IM_ARRAYSIZE(DataTypeNames); i++){
                        bool is_selected = (selected_type == i);
                        if (ImGui::Selectable(DataTypeNames[i], is_selected))
                            selected_type = i;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                ImGui::Separator();

                static size_t selected_program = 0;
                std::vector<std::string> programs = presenter_.get_programs_names();
                if (!programs.empty()){
                    std::string prog_name = programs[selected_program];
                    if (ImGui::BeginCombo("Program", prog_name.c_str())){
                        for (size_t i = 0; i < programs.size(); i++){
                            bool is_selected = (selected_program == i);
                            if (ImGui::Selectable(programs[i].c_str(), is_selected))
                                selected_program = i;
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }
                }
                else{
                    ImGui::TextDisabled("There are no available programs");
                }

                ImGui::Separator();

                if (ImGui::Button("Ok", ImVec2(120, 0))) {
                    if(programs.empty()){
                        ImGui::CloseCurrentPopup();
                    }
                    else{
                        DataType type = static_cast<DataType>(selected_type);
                        bool great_add = false;
                        switch (type){
                        case DataType::Bool:
                            great_add = presenter_.allocate_variable(programs[selected_program], var_name, sizeof(bool));
                            break;
                        case DataType::Char:
                            great_add = presenter_.allocate_variable(programs[selected_program], var_name, sizeof(char));
                            break;
                        case DataType::Int:
                            great_add = presenter_.allocate_variable(programs[selected_program], var_name, sizeof(int));
                            break;
                        case DataType::LongLong:
                            great_add = presenter_.allocate_variable(programs[selected_program], var_name, sizeof(long long));
                            break;
                        case DataType::SizeT:
                            great_add = presenter_.allocate_variable(programs[selected_program], var_name, sizeof(size_t));
                            break;
                        case DataType::Double:
                            great_add = presenter_.allocate_variable(programs[selected_program], var_name, sizeof(double));
                            break;
                        }

                        std::string message = great_add ? ("Variable " + std::string(var_name) + " was allocated!")
                                                        : ("Something went wrong with allocating " + std::string(var_name));
                        output_buffer.push_back(message);

                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::SameLine();

                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SameLine();
            ImGui::SetNextItemWidth(300);
            ImGui::Combo("Element type", &type_id, types, IM_ARRAYSIZE(types));

            if (ImGui::Button("Delete variable", ImVec2(300, 35)))
            {
                // TODO
            }

            if (ImGui::Button("Set value", ImVec2(300, 35)))
            {
                // TODO
            }

            if (ImGui::Button("Get value", ImVec2(300, 35)))
            {
                // TODO
            }

            ImGui::Spacing();
            ImGui::Text("Segment access");
            ImGui::Separator();

            if (ImGui::Button("Request segment access", ImVec2(300, 35)))
            {
                // TODO
            }

            ImGui::SameLine();
            if (ImGui::Button("Revoke access", ImVec2(300, 35)))
            {
                // TODO
            }

            ImGui::Spacing();
            ImGui::Text("System");
            ImGui::Separator();

            if (ImGui::Button("Defragment memory", ImVec2(300, 35)))
            {
                // TODO
            }

            ImGui::SameLine();
            if (ImGui::Button("Open Program", ImVec2(300, 35))){
                ImGui::OpenPopup("Open Program Popup");
            }

            if (ImGui::BeginPopupModal("Open Program Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
                static char prog_name[128] = "";
                static char file_path[128] = "";
                static size_t memory_limit = 0;

                ImGui::InputText("Name", prog_name, IM_ARRAYSIZE(prog_name));
                ImGui::InputText("File path", file_path, IM_ARRAYSIZE(file_path));
                ImGui::InputScalar("Memory limit", ImGuiDataType_U64, &memory_limit);
                ImGui::Separator();
                bool great_add = false;
                if (ImGui::Button("Ok", ImVec2(120, 0))) {
                    great_add = presenter_.add_program(prog_name, file_path, memory_limit);
                    std::string message = great_add ? ("Program " + std::string(prog_name) + " was opened!")
                                                    : ("Something went wrong with openning " + std::string(prog_name));
                    output_buffer.push_back(message);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();

                // === Cancel ===
                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Close Program", ImVec2(300, 35)))
            {
                // TODO
            }


            // --- Right side panel ---
            ImGui::Separator();
            ImGui::BeginChild("output_block", ImVec2(925, 363), true);
            ImGui::Text("Output:");
            ImGui::Separator();
            for(auto&& message : output_buffer){
                ImGui::TextWrapped("%s", message.c_str());
            }
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

            ImGui::BeginChild("errors", ImVec2(925, 450), true);
            std::vector<std::string> errors_list = presenter_.errors();
            for(auto&& error : errors_list){
                ImGui::TextWrapped("%s\n\n", error.c_str());
            }

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

    GLFWwindow* window = glfwCreateWindow(965, 960, "Memory Manager",nullptr,nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    

    SetComfortableDarkCyanTheme();
    ImGuiIO& io = ImGui::GetIO(); 
    io.Fonts->AddFontFromFileTTF("../MVP/JetBrainsMonoNL-Medium.ttf", 24.0f);

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