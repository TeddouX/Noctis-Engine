#include <rendering/shader.hpp>

#include <glad/glad.h>

#include <print>

#include <core/logging.hpp>

namespace NoctisEngine
{
    
Shader::Shader(const char *vertCode, const char *fragCode) {
    vertShader_ = glCreateShader(GL_VERTEX_SHADER);
    fragShader_ = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertShader_, 1, &vertCode, nullptr);
    glShaderSource(fragShader_, 1, &fragCode, nullptr);
    
    programID_ = glCreateProgram();
}

auto Shader::compile() -> bool {
    int success;
    char infolog[1024];

    glCompileShader(vertShader_);
    glGetShaderiv(vertShader_, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertShader_, sizeof(infolog), nullptr, infolog);
        Log::Error("Vertex shader compilation failed: {}", infolog);
    }

    glCompileShader(fragShader_);
    glGetShaderiv(fragShader_, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragShader_, sizeof(infolog), nullptr, infolog);
        Log::Error("Fragment shader compilation failed: {}", infolog);
    }

    glAttachShader(programID_, vertShader_);
    glAttachShader(programID_, fragShader_);
    glLinkProgram(programID_);
    glGetProgramiv(programID_, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programID_, sizeof(infolog), nullptr, infolog);
        Log::Error("Program linking failed: {}", infolog);

        return false;
    }

    // Cleanup
    glDeleteShader(vertShader_);
    glDeleteShader(fragShader_);

    return true;
}

void Shader::bind() {
    glUseProgram(programID_);
}

auto Shader::set_uniform(const UniformInfo &info) const -> bool {
    int loc = glGetUniformLocation(programID_, info.name.c_str());
    
    if (loc < 0) {
        Log::Warn("Uniform {} couldn't be found", info.name);
        return false;
    }

    switch (info.type) {
        case UniformType::BOOL:  glUniform1i(loc, std::get<bool>(info.val)); break;
        case UniformType::INT:   glUniform1i(loc, std::get<int>(info.val)); break;
        case UniformType::FLOAT: glUniform1f(loc, std::get<float>(info.val)); break;
    }

    return true;
}

} // namespace NoctisEngine

