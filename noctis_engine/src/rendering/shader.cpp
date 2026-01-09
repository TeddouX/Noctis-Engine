#include <rendering/shader.hpp>

#include <glad/gl.h>

#include <print>

#include <core/logging.hpp>
#include <core/exception.hpp>

namespace NoctisEngine
{
    
Shader::Shader(const std::string &code, const std::string &name) {
    vertShader_ = glCreateShader(GL_VERTEX_SHADER);
    fragShader_ = glCreateShader(GL_FRAGMENT_SHADER);

    glObjectLabel(GL_SHADER, vertShader_, -1, name.c_str());
    glObjectLabel(GL_SHADER, fragShader_, -1, name.c_str());

    const std::string header = std::string(OPENGL_VERSION) + "\n#extension GL_ARB_bindless_texture : require" + "\n#define ";
    const std::string vertCodeStr = header + "VERTEX\n" + code;
    const std::string fragCodeStr = header + "FRAGMENT\n" + code;

    const char* vertCode = vertCodeStr.c_str();
    const char* fragCode = fragCodeStr.c_str();
    
    glShaderSource(vertShader_, 1, &vertCode, nullptr);
    glShaderSource(fragShader_, 1, &fragCode, nullptr);
    
    programID_ = glCreateProgram();
    glObjectLabel(GL_PROGRAM, programID_, -1, name.c_str());
}

auto Shader::compile() -> void {
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
        throw Exception("Program linking failed, see errors above.");
    }

    // Cleanup
    glDeleteShader(vertShader_);
    glDeleteShader(fragShader_);
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

