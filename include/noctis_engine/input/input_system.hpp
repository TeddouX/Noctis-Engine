#pragma once
#include <array>
#include <vector>

#include "key.hpp"
#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API InputSystem {
public:
    InputSystem() = delete;

    static auto is_key_down(Key key) -> bool;
    static auto is_key_up(Key key) -> bool;
    static auto is_key_held(Key key) -> bool;
    static auto is_key_pressed(Key key) -> bool;

    static auto get_key_modifiers(Key key) -> Modifier;

private:
    struct KeyState {
        enum class Type { 
            UP,
            PRESSED,
            HELD,
            RELEASED 
        } state;
        Modifier mods = Modifier::NONE;
    };

    inline static std::array<KeyState, NUM_KEYS> keyStates_;
    inline static std::vector<size_t> releasedKeys_ = []{
        std::vector<size_t> v;
        v.reserve(NUM_KEYS / 4);
        return v;
    }();

    static auto update() -> void; 

    static auto set_key_pressed(Key key, Modifier mods) -> void;
    static auto set_key_held(Key key, Modifier mods) -> void;
    static auto set_key_released(Key key, Modifier mods) -> void;

    static auto check_key(Key key) -> bool;

    friend class Window;
};

} // namespace NoctisEngine
