#include <input/input_system.hpp>
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

auto InputSystem::update() -> void {
    for (size_t key : releasedKeys_) {
        keyStates_[key] = KeyState{
            .state = KeyState::Type::UP,
            .mods = Modifier::NONE,
        };
    }
}

auto InputSystem::set_key_pressed(Key key, Modifier mods) -> void {
    if (!check_key(key)) 
        return;

    keyStates_[ordinal(key)] = KeyState{
        .state = KeyState::Type::PRESSED,
        .mods = mods,
    };
}

auto InputSystem::set_key_held(Key key, Modifier mods) -> void {
    if (!check_key(key)) 
        return;

    keyStates_[ordinal(key)] = KeyState{
        .state = KeyState::Type::HELD,
        .mods = mods,
    };
}

auto InputSystem::set_key_released(Key key, Modifier mods) -> void {
    if (!check_key(key)) 
        return;

    size_t keyOrd = ordinal(key);

    keyStates_[keyOrd] = KeyState{
        .state = KeyState::Type::RELEASED,
        .mods = mods,
    };

    releasedKeys_.push_back(keyOrd);
}

auto InputSystem::check_key(Key key) -> bool {
    size_t keyOrd = ordinal(key);
    return ensure(keyOrd < keyStates_.size(), "Invalid key: {}", keyOrd);
}

} // namespace NoctisEngine

