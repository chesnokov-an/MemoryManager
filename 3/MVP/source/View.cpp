#include <MVP/View.hpp>
#include <cmath>

namespace MVPNameSpace {

void SetComfortableNeonPlasmaTheme(){
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

    auto RGBA = [](int r, int g, int b, float a = 1.0f){
        return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a);
    };

    ImVec4* c = style.Colors;
    c[ImGuiCol_Text]         = RGBA(235,245,255);
    c[ImGuiCol_TextDisabled] = RGBA(130,145,165);
    c[ImGuiCol_WindowBg] = RGBA(22, 28, 38);
    c[ImGuiCol_ChildBg]  = RGBA(26, 34, 46);
    c[ImGuiCol_PopupBg]  = RGBA(24, 30, 42);
    c[ImGuiCol_Border]       = RGBA(60, 90, 120);
    c[ImGuiCol_BorderShadow]= RGBA(0, 0, 0, 0);
    c[ImGuiCol_FrameBg]        = RGBA(35, 50, 70);
    c[ImGuiCol_FrameBgHovered] = RGBA(55, 90, 120);
    c[ImGuiCol_FrameBgActive]  = RGBA(80, 130, 170);
    c[ImGuiCol_TitleBg]          = RGBA(18, 24, 36);
    c[ImGuiCol_TitleBgActive]   = RGBA(22, 30, 46);
    c[ImGuiCol_TitleBgCollapsed]= RGBA(18, 24, 36);
    c[ImGuiCol_MenuBarBg]       = RGBA(26, 36, 52);
    c[ImGuiCol_ScrollbarBg]          = RGBA(18, 24, 36);
    c[ImGuiCol_ScrollbarGrab]        = RGBA(70, 130, 180);
    c[ImGuiCol_ScrollbarGrabHovered] = RGBA(100, 190, 255);
    c[ImGuiCol_ScrollbarGrabActive]  = RGBA(140, 220, 255);
    c[ImGuiCol_CheckMark]        = RGBA(0, 255, 210);
    c[ImGuiCol_SliderGrab]       = RGBA(0, 220, 255);
    c[ImGuiCol_SliderGrabActive] = RGBA(180, 255, 0);
    c[ImGuiCol_Button]        = RGBA(40, 70, 95);
    c[ImGuiCol_ButtonHovered] = RGBA(80, 150, 200);
    c[ImGuiCol_ButtonActive]  = RGBA(0, 240, 255);
    c[ImGuiCol_Header]        = RGBA(55, 85, 120);
    c[ImGuiCol_HeaderHovered] = RGBA(90, 160, 220);
    c[ImGuiCol_HeaderActive]  = RGBA(0, 200, 255);
    c[ImGuiCol_Tab]                = RGBA(30, 42, 60);
    c[ImGuiCol_TabHovered]         = RGBA(40, 110, 150);
    c[ImGuiCol_TabActive]          = RGBA(80, 150, 200);
    c[ImGuiCol_TabUnfocused]       = RGBA(25, 34, 50);
    c[ImGuiCol_TabUnfocusedActive] = RGBA(60, 120, 190);
    c[ImGuiCol_TableHeaderBg] = RGBA(22, 30, 46);
    c[ImGuiCol_TableBorderStrong] = RGBA(60, 90, 120);
    c[ImGuiCol_TableBorderLight]  = RGBA(30, 45, 65);
    c[ImGuiCol_TableRowBg]    = RGBA(28, 38, 56);
    c[ImGuiCol_TableRowBgAlt] = RGBA(34, 46, 68);
    c[ImGuiCol_TextSelectedBg]        = RGBA(0, 220, 255, 0.35f);
    c[ImGuiCol_DragDropTarget]        = RGBA(255, 0, 255);
    c[ImGuiCol_NavHighlight]          = RGBA(0, 255, 255);
    c[ImGuiCol_NavWindowingHighlight] = RGBA(255, 0, 255);
    c[ImGuiCol_NavWindowingDimBg]     = RGBA(20, 30, 60, 0.6f);
    c[ImGuiCol_ModalWindowDimBg]     = RGBA(50,45,139,0.502f);
    c[ImGuiCol_PlotLines]            = RGBA(133,153,179,1.0f);
    c[ImGuiCol_PlotLinesHovered]     = RGBA(10,250,250,1.0f);
    c[ImGuiCol_PlotHistogram]        = RGBA(8,242,215,1.0f);
    c[ImGuiCol_PlotHistogramHovered] = RGBA(80,150,200,1.0f);
}

enum class ThemeMode
{
    Normal,
    RGBHell
};

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

std::vector<std::string> View::program_combo(size_t& selected_program){
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
    return programs;
}

void View::type_combo(size_t& selected_type){
    if (ImGui::BeginCombo("Type", DataTypeNames[selected_type])){
        for (size_t i = 0; i < IM_ARRAYSIZE(DataTypeNames); i++){
            bool is_selected = (selected_type == i);
            if (ImGui::Selectable(DataTypeNames[i], is_selected))
                selected_type = i;
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}

void View::render_ui(){
    bool opened = true;
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
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

            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if (ImGui::BeginPopupModal("Create Variable Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
                static char var_name[128] = "";
                static size_t selected_type = 0;
                ImGui::InputText("Name", var_name, IM_ARRAYSIZE(var_name));

                type_combo(selected_type);

                ImGui::Separator();

                static size_t selected_program = 0;
                std::vector<std::string> programs = program_combo(selected_program);

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
                            great_add = presenter_.allocate_variable<bool>(programs[selected_program], var_name);
                            break;
                        case DataType::Char:
                            great_add = presenter_.allocate_variable<char>(programs[selected_program], var_name);
                            break;
                        case DataType::Int:
                            great_add = presenter_.allocate_variable<int>(programs[selected_program], var_name);
                            break;
                        case DataType::LongLong:
                            great_add = presenter_.allocate_variable<long long>(programs[selected_program], var_name);
                            break;
                        case DataType::SizeT:
                            great_add = presenter_.allocate_variable<size_t>(programs[selected_program], var_name);
                            break;
                        case DataType::Double:
                            great_add = presenter_.allocate_variable<double>(programs[selected_program], var_name);
                            break;
                        }

                        std::string message = great_add ? ("Variable " + std::string(var_name) + " was allocated")
                                                        : ("Something went wrong with allocating " + std::string(var_name) + "!");
                        output_buffer.push_back(message);
                        selected_program = 0;
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::SameLine();

                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    selected_program = 0;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if (ImGui::BeginPopupModal("Create Array Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
                static char var_name[128] = "";
                static size_t selected_type = 0;
                static size_t count_elements = 0;
                ImGui::InputText("Name", var_name, IM_ARRAYSIZE(var_name));
                ImGui::InputScalar("Number of elements", ImGuiDataType_U64, &count_elements);

                type_combo(selected_type);

                ImGui::Separator();

                static size_t selected_program = 0;
                std::vector<std::string> programs = program_combo(selected_program);

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
                            great_add = presenter_.allocate_array<bool>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::Char:
                            great_add = presenter_.allocate_array<char>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::Int:
                            great_add = presenter_.allocate_array<int>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::LongLong:
                            great_add = presenter_.allocate_array<long long>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::SizeT:
                            great_add = presenter_.allocate_array<size_t>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::Double:
                            great_add = presenter_.allocate_array<double>(programs[selected_program], var_name, count_elements);
                            break;
                        }

                        std::string message = great_add ? ("Array " + std::string(var_name) + " was allocated")
                                                        : ("Something went wrong with allocating " + std::string(var_name) + "!");
                        output_buffer.push_back(message);
                        selected_program = 0;
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::SameLine();

                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    selected_program = 0;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if (ImGui::BeginPopupModal("Create SharedSegment Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
                static char var_name[128] = "";
                static size_t selected_type = 0;
                static size_t count_elements = 0;
                ImGui::InputText("Name", var_name, IM_ARRAYSIZE(var_name));
                ImGui::InputScalar("Number of elements", ImGuiDataType_U64, &count_elements);

                type_combo(selected_type);

                ImGui::Separator();

                static size_t selected_program = 0;
                std::vector<std::string> programs = program_combo(selected_program);

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
                            great_add = presenter_.allocate_shared<bool>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::Char:
                            great_add = presenter_.allocate_shared<char>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::Int:
                            great_add = presenter_.allocate_shared<int>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::LongLong:
                            great_add = presenter_.allocate_shared<long long>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::SizeT:
                            great_add = presenter_.allocate_shared<size_t>(programs[selected_program], var_name, count_elements);
                            break;
                        case DataType::Double:
                            great_add = presenter_.allocate_shared<double>(programs[selected_program], var_name, count_elements);
                            break;
                        }

                        std::string message = great_add ? ("Shared segment " + std::string(var_name) + " was allocated")
                                                        : ("Something went wrong with allocating " + std::string(var_name) + "!");
                        output_buffer.push_back(message);
                        selected_program = 0;
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::SameLine();

                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    selected_program = 0;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if (ImGui::BeginPopupModal("Create Reference Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
                static char ref_name[128] = "";
                ImGui::InputText("Name", ref_name, IM_ARRAYSIZE(ref_name));

                ImGui::Separator();

                static size_t selected_program = 0;
                std::vector<std::string> programs = program_combo(selected_program);

                static size_t selected_element = 0;
                std::vector<std::string> elements = programs.empty()
                        ? std::vector<std::string>()
                        : presenter_.get_elements_by_program(programs[selected_program]);
                
                if (!programs.empty() && !elements.empty()){
                    std::string elem_name = elements[selected_element];
                    if (ImGui::BeginCombo("Elements", elem_name.c_str())){
                        for (size_t i = 0; i < elements.size(); i++){
                            bool is_selected = (selected_element == i);
                            if (ImGui::Selectable(elements[i].c_str(), is_selected))
                                selected_element = i;
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }
                }
                else{
                    ImGui::TextDisabled("There are no available elements");
                }

                ImGui::Separator();

                if (ImGui::Button("Ok", ImVec2(120, 0))) {
                    if(programs.empty() || elements.empty()){
                        ImGui::CloseCurrentPopup();
                    }
                    else{
                        bool great_add = presenter_.make_reference(ref_name, elements[selected_element], programs[selected_program]);
                        std::string message = great_add ? ("Reference " + std::string(ref_name) + " was created")
                                                        : ("Something went wrong with creating " + std::string(ref_name) + "!");
                        output_buffer.push_back(message);
                        selected_program = 0;
                        selected_element = 0;
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::SameLine();

                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    selected_program = 0;
                    selected_element = 0;
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

            ImGui::SameLine();
            if (ImGui::Button("Set value", ImVec2(300, 35)))
            {
                // TODO
            }

            ImGui::SameLine();
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

            if (ImGui::Button("Defragment memory", ImVec2(300, 35))){
                presenter_.defragment();
                output_buffer.push_back("Memory was defragmented");
            }

            ImGui::SameLine();
            if (ImGui::Button("Open Program", ImVec2(300, 35))){
                ImGui::OpenPopup("Open Program Popup");
            }
            
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
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
                    std::string message = great_add ? ("Program " + std::string(prog_name) + " was opened")
                                                    : ("Something went wrong with openning " + std::string(prog_name) + "!");
                    output_buffer.push_back(message);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Close Program", ImVec2(300, 35))){
                ImGui::OpenPopup("Close Program Popup");
            }
            
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if (ImGui::BeginPopupModal("Close Program Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
                static size_t selected_program = 0;
                std::vector<std::string> programs = program_combo(selected_program);

                ImGui::Separator();
                if (ImGui::Button("Ok", ImVec2(120, 0))) {
                    if(programs.empty()){
                        ImGui::CloseCurrentPopup();
                    }
                    else{
                        presenter_.delete_program(programs[selected_program]);
                        output_buffer.push_back("Program " + programs[selected_program] + " was closed");
                        selected_program = 0;
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    selected_program = 0;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::Separator();
            ImGui::BeginChild("output_block", ImVec2(925, 450), true);
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
            ImGui::Text("Dangling references:");
            ImGui::Separator();
            std::vector<std::string> dangling_references = presenter_.dungling_reference();
            for (auto& ref : dangling_references){
                ImGui::TextColored(ImVec4(0.5, 0.7, 1, 1), "%s", ref.c_str());
            }

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

    SetComfortableNeonPlasmaTheme();
    
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