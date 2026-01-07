#pragma once
#include <noctis_engine/asset/asset_manager.hpp>
#include <noctis_engine/core/application.hpp>
#include <noctis_engine/rendering/window.hpp>
#include <noctis_engine/rendering/graphics_handler.hpp>
#include <noctis_engine/rendering/vertex_array.hpp>
#include <noctis_engine/rendering/uniform_buffer.hpp>
#include <noctis_engine/rendering/texture.hpp>
#include <noctis_engine/rendering/camera.hpp>
#include <noctis_engine/rendering/ssbo.hpp>


constexpr float MOUSE_SENS = 1.0f/10.0f;
constexpr float CAM_SPEED = 2.5f;


const NoctisEngine::VertexArrayInfo PLANE {
    .vertices = {
        NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(1, 1)),
        NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(1, 0)),
        NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec2(0, 1)),
    },
    .indices = {0, 1, 2, 2, 3, 0}
};

const NoctisEngine::VertexArrayInfo CUBE {
    .vertices = {
        // Front face
        NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0), glm::vec2(0)),
    },
    .indices = {
        // Front
        0, 1, 2,  2, 3, 0,
        // Right
        1, 5, 6,  6, 2, 1,
        // Back
        5, 4, 7,  7, 6, 5,
        // Left
        4, 0, 3,  3, 7, 4,
        // Top
        3, 2, 6,  6, 7, 3,
        // Bottom
        4, 5, 1,  1, 0, 4
    }
};


auto create_model_matrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) -> glm::mat4x4;


class TestApp : public NoctisEngine::Application {
public:
    TestApp();
    ~TestApp() = default;

    auto run() -> void override;

private:
    NoctisEngine::Window window_;
    NoctisEngine::GraphicsHandler graphicsHandler_;
    
    std::unique_ptr<NoctisEngine::AssetManager> assetManager_;
    NoctisEngine::TextureHandle texHandle_;
    NoctisEngine::ShaderHandle  shaderHandle_;

    NoctisEngine::VertexArray   vertArray_;
    NoctisEngine::UniformBuffer testUB_;
    NoctisEngine::SSBO          modelSSBO_;
    glm::mat4x4                 modelMatrix_;
    NoctisEngine::Camera        camera_;

    double timeAcc_{};
    int frameCount_{};
};
