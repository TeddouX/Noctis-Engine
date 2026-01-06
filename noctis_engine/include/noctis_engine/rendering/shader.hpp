#pragma once
#include <variant>
#include <string>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
enum class UniformType { BOOL, INT, FLOAT };

struct UniformInfo {
    UniformType type;
    std::string name;
    std::variant<bool, int, float> val;
};

class NCENG_API Shader {
public:
    Shader(const std::string &code, const std::string &name);
    ~Shader() = default;

    auto compile() -> bool;
    auto bind() -> void;
    auto set_uniform(const UniformInfo &info) const -> bool;

private:
    uint32_t programID_;
    uint32_t vertShader_, fragShader_;
};

} // namespace NoctisEngine
