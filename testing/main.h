#pragma once
#include <noctis_engine/asset/asset_manager.hpp>
#include <noctis_engine/core/application.hpp>
#include <noctis_engine/core/scene.hpp>
#include <noctis_engine/rendering/window.hpp>
#include <noctis_engine/rendering/graphics_handler.hpp>
#include <noctis_engine/rendering/mesh/mesh_manager.hpp>
#include <noctis_engine/rendering/texture.hpp>
#include <noctis_engine/rendering/camera.hpp>
#include <noctis_engine/rendering/gpu_buffer.hpp>


constexpr float MOUSE_SENS = 1.0f/10.0f;
constexpr float CAM_SPEED = 2.5f;


const NoctisEngine::MeshInfo PLANE {
    "plane",
    {
        NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec3(0), glm::vec2(1, 1)),
        NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec3(0), glm::vec2(0, 1)),
        NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0), glm::vec2(1, 0)),
    },
    {0, 1, 2, 2, 3, 0}
};

const NoctisEngine::MeshInfo CUBE {
    "cube",
    {
        NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
        NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0), glm::vec3(0), glm::vec2(0)),
    },
    {
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

    std::shared_ptr<NoctisEngine::MeshManager>     meshManager_;

    NoctisEngine::MaterialManager materialManager_;
    NoctisEngine::Camera          camera_;

    NoctisEngine::Scene scene_;

    double timeAcc_{};
    int frameCount_{};
};
