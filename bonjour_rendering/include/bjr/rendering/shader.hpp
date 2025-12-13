#pragma once
#include <variant>
#include <memory>
#include <string>

namespace Bjr
{

enum class UniformType { BOOL, INT, FLOAT };

struct UniformInfo {
    UniformType type;
    std::string name;
    std::variant<bool, int, float> val;
};

class Shader {
public:
    virtual ~Shader() = default;

    static std::unique_ptr<Shader> Create(
        const char *vertCode,
        const char *fragCode);

    virtual void bind() = 0;
    virtual void setUniform(const UniformInfo &info) = 0;
};
    
} // namespace Bjr
