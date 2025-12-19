#pragma once

namespace NoctisEngine
{
    
enum class Key {

};

enum class Modifier {
    NONE = 0,
};

struct KeyPressInfo {
    Key key;
    Modifier mod;
    bool released = false;
};

} // namespace NoctisEngine

