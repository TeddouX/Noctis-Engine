#pragma once
#include "../shader.hpp"
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API ShaderOpenGL : public Shader {
public:
    ShaderOpenGL(const char *vertCode, const char *fragCode);

    void bind() override;
    void set_uniform(const UniformInfo &info) override;

private:
    uint32_t programID_;
};

} // namespace NoctisEngine
