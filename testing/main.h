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

class TestApp : public NoctisEngine::Application {
public:
    TestApp();
    ~TestApp() = default;

    void run() override;

private:
    NoctisEngine::Window window_;
    
    std::unique_ptr<NoctisEngine::GraphicsHandler> graphicsHandler_;
    std::unique_ptr<NoctisEngine::AssetManager>    assetManager_;

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
