#pragma once
#include "../shader.hpp"

namespace Bjr
{
    
class ShaderOpenGL : public Shader {
public:
    ShaderOpenGL(const char *vertCode, const char *fragCode);

    void bind() override;
    void setUniform(const UniformInfo &info) override;

private:
    uint32_t programID_;
};

} // namespace Bjr
