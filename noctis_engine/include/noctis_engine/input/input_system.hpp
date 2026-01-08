#pragma once
#include <array>
#include <vector>

#include "key.hpp"
#include "mouse.hpp"
#include "../noctis_engine.hpp"

struct GLFWwindow;

namespace NoctisEngine
{
    
class NCENG_API InputSystem {
public:
    InputSystem() = delete;

    static auto is_key_down(Key key) -> bool;
    static auto is_key_up(Key key) -> bool;
    static auto is_key_held(Key key) -> bool;
    static auto is_key_released(Key key) -> bool;
    static auto is_key_pressed(Key key) -> bool;

    static auto get_key_modifiers(Key key) -> Modifier;

    static auto get_mouse_mouvement() -> MouseMouvement;
    static auto is_mouse_button_down(MouseButton mb) -> bool;

private:
    struct InputState {
        enum class State { 
            UP,
            PRESSED,
            HELD,
            RELEASED 
        } state;
        Modifier mods;
    };

    inline static std::array<InputState, NUM_KEYS> keyStates_;
    inline static std::vector<size_t> dirtyKeys_;

    inline static std::array<InputState, NUM_MOUSE_BUTTONS> mouseButtons_;
    inline static MouseMouvement lastMouseMvt_;

    static auto update() -> void;
    static auto check_key(Key key) -> bool;
    static auto update_state(InputState &state) -> void;

    static auto GLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) -> void;
    static auto GLFWCursorPosCallback(GLFWwindow *window, double xPos, double yPos) -> void;
    static auto GLFWMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) -> void;

    friend class Window;
};

} // namespace NoctisEngine
