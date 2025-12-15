#ifndef VIEW_HPP
#define VIEW_HPP

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include <MVP/Presenter.hpp>

namespace MVPNameSpace {

class View final {
private:
    Presenter& presenter_;

    std::vector<std::string> program_combo(size_t& selected_program, size_t* selected_element = nullptr);
    void type_combo(size_t& selected_type);
    std::vector<std::string> elements_combo(size_t& selected_element,
            const std::vector<std::string>& programs, size_t& selected_program);

public:
    View(Presenter& presenter) : presenter_(presenter) {}
    void render_ui();
    int show();
};

}

#endif