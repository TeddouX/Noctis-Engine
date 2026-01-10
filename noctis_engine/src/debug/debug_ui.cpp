#include <debug/debug_ui.hpp>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace NoctisEngine
{
    
DebugUI::DebugUI(std::shared_ptr<Window> window) 
    : window_(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->glfw_ptr(), true);
    ImGui_ImplOpenGL3_Init(OPENGL_VERSION);
}

DebugUI::~DebugUI() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

auto DebugUI::set_enabled(bool b) -> void {
    if (b) window_->unlock_cursor();
    else   window_->lock_cursor();

    hidden_ = !b;
}

auto DebugUI::render() -> void {
    if (hidden_)
        return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto &widget : widgets_)
        widget->render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

auto DebugUI::hidden() const -> bool {
    return hidden_;
}

auto DebugUI::add_widget(std::shared_ptr<IDebugWidget> widget) -> void {
    widgets_.push_back(widget);
    widget->on_attach(this);
}

auto DebugUI::window() const -> const std::shared_ptr<Window> & {
    return window_;
}

} // namespace NoctisEngine
