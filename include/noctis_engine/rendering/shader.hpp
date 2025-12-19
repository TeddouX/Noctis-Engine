#pragma once
#include <variant>
#include <memory>
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
    virtual ~Shader() = default;

    static std::unique_ptr<Shader> Create(
        const char *vertCode,
        const char *fragCode);

    virtual void bind() = 0;
    virtual void set_uniform(const UniformInfo &info) = 0;
};
    
} // namespace NoctisEngine
