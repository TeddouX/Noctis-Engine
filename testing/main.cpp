#include <noctis_engine/rendering/shader.hpp>
#include <noctis_engine/rendering/vertex_array.hpp>
#include <noctis_engine/rendering/uniform_buffer.hpp>
#include <noctis_engine/rendering/camera.hpp>
#include <noctis_engine/rendering/ssbo.hpp>
#include <noctis_engine/rendering/window.hpp>
#include <noctis_engine/rendering/graphics_handler.hpp>
#include <noctis_engine/input/input_system.hpp>
#include <noctis_engine/core/logging.hpp>
#include <noctis_engine/core/entrypoint.hpp>
#include <noctis_engine/asset/asset_manager.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

#include <print>

#include "main.h"


TestApp::TestApp() 
    : window_(800, 600, "Testing")
    , assetManager_(std::make_unique<NoctisEngine::AssetManager>())
    , camera_(glm::vec3(-5, 1, 2), 800/600, 70.f, .1f, 1000.f) 
{
    graphicsHandler_.set_clear_screen_color(NoctisEngine::Color{9, 9, 9, 255});
    graphicsHandler_.set_backface_culling(false);
    graphicsHandler_.set_depth_testing(true);
    graphicsHandler_.set_throw_on_err(true);

    {
        shaderHandle_ = assetManager_->load_asset<NoctisEngine::Shader>("./testing/test_shader.glsl");
        shaderHandle_.expect_valid("Failed to load shader.");
        
        texHandle_ = assetManager_->load_asset<NoctisEngine::Texture>("./testing/drone.png");
        texHandle_.expect_valid("Failed to load texture.");

        auto shader = assetManager_->try_get(shaderHandle_);
        shader->compile();

        auto texture = assetManager_->try_get(texHandle_);
        texture->set_min_function(NoctisEngine::Texture::MinifyingFunction::NEAREST);
        texture->set_mag_function(NoctisEngine::Texture::MagnifyingFunction::NEAREST);
        texture->set_wrap_function(NoctisEngine::Texture::WrapParam::REPEAT, NoctisEngine::Texture::WrapParam::REPEAT);
    }

    modelSSBO_ = NoctisEngine::SSBO(2);
    modelMatrix_ = create_model_matrix(glm::vec3(0, 1, 0), glm::vec3(0, 90, 0), glm::vec3(1));
    modelSSBO_.upload_data(sizeof(glm::mat4x4), &modelMatrix_);

    vertArray_ = NoctisEngine::VertexArray(PLANE);
}

auto TestApp::run() -> void {
    window_.lock_cursor();

    auto shader = assetManager_->try_get(shaderHandle_);
    auto texture = assetManager_->try_get(texHandle_);

    if(shader == nullptr || texture == nullptr) 
        throw std::runtime_error("Getting the texture and shader failed.");

    while (!window_.should_close()) {
        if (NoctisEngine::InputSystem::is_key_pressed(NoctisEngine::Key::ESCAPE)) {
            NoctisEngine::Log::Info("Esc pressed");
            break;
        }

        graphicsHandler_.clear_screen();

        NoctisEngine::MouseMouvement mouseMvt = NoctisEngine::InputSystem::get_mouse_mouvement();
        camera_.rotate_by_clamped(mouseMvt.xDelta * MOUSE_SENS, -mouseMvt.yDelta * MOUSE_SENS);

        float dt = static_cast<float>(window_.delta_time());

        timeAcc_ += dt;
        frameCount_++;

        if (timeAcc_ >= 1.0) {
            double averageFPS = frameCount_ / timeAcc_;
            double frameTime = 1000.0 / averageFPS;

            window_.set_title(std::format("Testing | FPS: {:.3f} | {:.3f} ms", averageFPS, frameTime));

            timeAcc_ = 0.0;
            frameCount_ = 0;
        }

        auto forward = camera_.forward();
        auto right = camera_.right();
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::W))
            camera_.translate_by(forward * CAM_SPEED * dt);
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::S))
            camera_.translate_by(-forward * CAM_SPEED * dt);
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::A))
            camera_.translate_by(-right * CAM_SPEED * dt);
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::D))
            camera_.translate_by(right * CAM_SPEED * dt);

        double time = window_.get_time();

        modelMatrix_ = create_model_matrix(glm::vec3(0, sin(time + 0.0f) * 0.5f, 0), glm::vec3(0, time * 8, 0), glm::vec3(1));
        modelSSBO_.update_data(0, sizeof(glm::mat4x4), &modelMatrix_);

        camera_.upload_data();

        shader->bind();
        texture->bind(0, shader);  

        vertArray_.use();

        window_.poll_events();
        window_.swap_buffers();
    }
}

auto NoctisEngine::create_application(int argc, char **argv) -> NoctisEngine::Application * {
    return new TestApp;
}


auto create_model_matrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) -> glm::mat4x4 {
    // Identity
    glm::mat4x4 model(1);

    // Translation
    model = glm::translate(model, pos);
    // Rotation
    glm::quat quaternion(glm::radians(rot));
    glm::mat4x4 rotationMatrix = glm::toMat4(quaternion);
    model *= rotationMatrix;
    // Scale
    model = glm::scale(model, scale);

    return model;
}
