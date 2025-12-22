#include <input/input_system.hpp>

#include <GLFW/glfw3.h>

#include <core/assert.hpp>

namespace NoctisEngine
{

auto InputSystem::is_key_down(Key key) -> bool {
    return keyStates_[ordinal(key)].state == InputState::State::HELD
        || keyStates_[ordinal(key)].state == InputState::State::PRESSED;
}

auto InputSystem::is_key_up(Key key) -> bool {
    return keyStates_[ordinal(key)].state == InputState::State::UP;
}

auto InputSystem::is_key_held(Key key) -> bool {
    return keyStates_[ordinal(key)].state == InputState::State::HELD;
}

auto InputSystem::is_key_pressed(Key key) -> bool {
    return keyStates_[ordinal(key)].state == InputState::State::PRESSED;
}

auto InputSystem::is_key_released(Key key) -> bool {
    return keyStates_[ordinal(key)].state == InputState::State::RELEASED;
}

auto InputSystem::get_key_modifiers(Key key) -> Modifier {
    return keyStates_[ordinal(key)].mods;
}

auto InputSystem::get_mouse_mouvement() -> MouseMouvement {
    return lastMouseMvt_;
}

auto InputSystem::is_mouse_button_down(MouseButton mb) -> bool {
    return mouseButtons_[static_cast<size_t>(mb)].state == InputState::State::PRESSED;
}

auto InputSystem::update() -> void {
    for (size_t dirtyKeyOrd : dirtyKeys_) {
        InputState &state = keyStates_[dirtyKeyOrd];
        update_state(state);
    }

    for (size_t i = 0; i < mouseButtons_.size(); i++) {
        InputState &state = keyStates_[i];
        update_state(state);
    }

    lastMouseMvt_.xDelta = 0;
    lastMouseMvt_.yDelta = 0;
}

auto InputSystem::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
    if (action == GLFW_REPEAT)
        return;

    Key keyy = static_cast<Key>(key);
    Modifier modss = static_cast<Modifier>(mods);

    if (!check_key(keyy)) 
        return;

    size_t keyOrd = ordinal(keyy);
    InputState::State keyState = InputState::State::UP;
    
    if (action == GLFW_PRESS && InputSystem::is_key_up(keyy)) {
        keyState = InputState::State::PRESSED;
        dirtyKeys_.push_back(keyOrd);
    }
    else if (action == GLFW_RELEASE) {
        keyState = InputState::State::RELEASED;
        dirtyKeys_.push_back(keyOrd);
    }

    keyStates_[keyOrd] = InputState{
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

    InputState::State btnState = InputState::State::PRESSED;
    if (action == GLFW_RELEASE)
        btnState = InputState::State::RELEASED;

    mouseButtons_[btnOrd] = InputState {
        .state = btnState,
        .mods = modss,
    };
}

auto InputSystem::check_key(Key key) -> bool {
    size_t keyOrd = ordinal(key);
    return expect(keyOrd < keyStates_.size(), "Invalid key: {}", keyOrd);
}

auto InputSystem::update_state(InputState &state) -> void {
    if (state.state == InputState::State::UP || state.state == InputState::State::HELD)
        return;
    
    if (state.state == InputState::State::RELEASED) {
        state.state = InputState::State::UP;
        state.mods = Modifier::NONE;
    }
    else if (state.state == InputState::State::PRESSED)
        state.state = InputState::State::HELD;
}

} // namespace NoctisEngine
