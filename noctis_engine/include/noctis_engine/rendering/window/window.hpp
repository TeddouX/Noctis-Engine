#pragma once
#include <string>
#include <memory>
#include <queue>

#include "../../noctis_engine.hpp"
#include "window_event.hpp"

struct GLFWwindow;

namespace NoctisEngine
{

enum class VSyncMethod : int {
    NO_VSYNC = 0,
    VSYNC = 1,
    HALF_REFRESH_RATE = 2,
};

class NCENG_API Window {
public:
    Window(std::uint32_t width, std::uint32_t height, const std::string &title);

    auto should_close() const -> bool;
    auto set_should_close(bool b) const -> void;

    auto poll_events() -> void;

    auto swap_buffers() const -> void;

    auto get_time() const -> double;

    auto lock_cursor() const -> void;
    auto unlock_cursor() const -> void;

    // In seconds
    auto delta_time() const -> double;

    auto set_title(const std::string &newTitle) const -> void;

    auto get_events() -> std::queue<WindowEvent> &;

    auto glfw_ptr() -> GLFWwindow *;

    auto set_vsync(VSyncMethod method) -> void; 

private:
    GLFWwindow *m_glfwWindow = nullptr;

    double deltaTime_;
    double lastFrame_;

    std::queue<WindowEvent> events_;

    static auto GLFWErrorCallback(int code, const char *desc) -> void;
    static auto GLFWWindowCloseCallback(GLFWwindow *window) -> void;
    static auto GLFWWindowResizeCallback(GLFWwindow *window, int width, int height) -> void;
};

} // namespace NoctisEngine
