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
    Shader(const char *vertCode, const char *fragCode);
    ~Shader() = default;

    void bind();
    void set_uniform(const UniformInfo &info);

private:
    uint32_t programID_;
};

} // namespace NoctisEngine
