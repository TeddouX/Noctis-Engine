#include <input/input_system.hpp>

#include <GLFW/glfw3.h>

#include <core/assert.hpp>

namespace NoctisEngine
{

auto InputSystem::is_key_down(Key key) -> bool {
    return keyStates_[ordinal(key)].state == KeyState::Type::HELD
        || keyStates_[ordinal(key)].state == KeyState::Type::PRESSED;
}

auto InputSystem::is_key_up(Key key) -> bool {
    return keyStates_[ordinal(key)].state == KeyState::Type::UP;
}

auto InputSystem::is_key_held(Key key) -> bool {
    return keyStates_[ordinal(key)].state == KeyState::Type::HELD;

}

auto InputSystem::is_key_pressed(Key key) -> bool {
    return keyStates_[ordinal(key)].state == KeyState::Type::PRESSED;
}

auto InputSystem::get_key_modifiers(Key key) -> Modifier {
    return keyStates_[ordinal(key)].mods;
}

auto InputSystem::get_mouse_mouvement() -> MouseMouvement {
    return lastMouseMvt_;
}

auto InputSystem::is_mouse_button_down(MouseButton mb) -> bool {
    return mouseButtons_[static_cast<size_t>(mb)].state == KeyState::Type::PRESSED;
}

auto InputSystem::update() -> void {
    for (size_t key : releasedKeys_) {
        keyStates_[key] = KeyState{
            .state = KeyState::Type::UP,
            .mods = Modifier::NONE,
        };
    }
    releasedKeys_.clear();

    for (size_t mouseBtn : releasedMouseBtns_) {
        mouseButtons_[mouseBtn] = KeyState {
            .state = KeyState::Type::UP,
            .mods = Modifier::NONE,
        };
    }
    releasedMouseBtns_.clear();

    lastMouseMvt_.xDelta = 0;
    lastMouseMvt_.yDelta = 0;
}

auto InputSystem::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
    Key keyy = static_cast<Key>(key);
    Modifier modss = static_cast<Modifier>(mods);

    if (!check_key(keyy)) 
        return;

    size_t keyOrd = ordinal(keyy);
    KeyState::Type keyState = KeyState::Type::UP;
    
    if (action == GLFW_PRESS && InputSystem::is_key_up(keyy))
        keyState = KeyState::Type::PRESSED;
    else if (action == GLFW_REPEAT)
        keyState = KeyState::Type::HELD;
    else if (action == GLFW_RELEASE) {
        keyState = KeyState::Type::RELEASED;

        releasedKeys_.push_back(keyOrd);
    }

    keyStates_[keyOrd] = KeyState{
        .state = keyState,
        .mods = modss,
    };
}

auto InputSystem::GLFWCursorPosCallback(GLFWwindow *window, double xPos, double yPos) -> void {
    MouseMouvement mvt {
        .x = xPos,
        .y = yPos,
        .xDelta = xPos - lastMouseMvt_.x,
        .yDelta = yPos - lastMouseMvt_.y,
    };

    lastMouseMvt_ = mvt;
}

auto InputSystem::GLFWMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) -> void {
    MouseButton btn = static_cast<MouseButton>(button);
    Modifier modss = static_cast<Modifier>(mods);

    size_t btnOrd = static_cast<size_t>(btn);

    KeyState::Type btnState = KeyState::Type::PRESSED;
    if (action == GLFW_RELEASE) {
        btnState = KeyState::Type::RELEASED;

        releasedMouseBtns_.push_back(btnOrd);
    }

    mouseButtons_[btnOrd] = KeyState {
        .state = btnState,
        .mods = modss,
    };
}

auto InputSystem::check_key(Key key) -> bool {
    size_t keyOrd = ordinal(key);
    return ensure(keyOrd < keyStates_.size(), "Invalid key: {}", keyOrd);
}

} // namespace NoctisEngine

