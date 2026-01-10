#include <noctis_engine/rendering/shader.hpp>
#include <noctis_engine/rendering/camera.hpp>
#include <noctis_engine/rendering/window.hpp>
#include <noctis_engine/rendering/graphics_handler.hpp>
#include <noctis_engine/input/input_system.hpp>
#include <noctis_engine/core/logging.hpp>
#include <noctis_engine/core/entrypoint.hpp>
#include <noctis_engine/ecs/component/transform.hpp>
#include <noctis_engine/asset/asset_manager.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

#include <print>

#include "main.h"


TestApp::TestApp() 
    : window_(800, 600, "Testing")
    , assetManager_(std::make_unique<NoctisEngine::AssetManager>())
    , meshManager_(std::make_shared<NoctisEngine::MeshManager>())
    , camera_(glm::vec3(-5, 1, 2), 800/600, 70.f, .1f, 1000.f)
    , scene_(meshManager_)
    , debugUI_(window_)
{
    graphicsHandler_.set_clear_screen_color(NoctisEngine::Color{9, 9, 9, 255});
    graphicsHandler_.set_backface_culling(false);
    graphicsHandler_.set_depth_testing(true);
    graphicsHandler_.set_throw_on_err(true);

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
    
    auto meshView = meshManager_->upload(PLANE);
    auto materialKey = materialManager_.upload(NoctisEngine::MaterialData{
        NoctisEngine::BindlessTexture{*texture}
    });

    for (int i = 0; i < 4; i++) {
        auto entity = scene_.create_entity();
        entity.add_component(meshView);
        entity.add_component(NoctisEngine::Transform{glm::vec3(0, i*2, 0), glm::vec3(1), glm::vec3(0)});
        entity.add_component(materialKey);
    }
}

auto TestApp::run() -> void {
    window_.lock_cursor();

    auto shader = assetManager_->try_get(shaderHandle_);
    if (!shader) 
        throw NoctisEngine::Exception("Getting the shader failed.");

    while (!window_.should_close()) {
        if (NoctisEngine::InputSystem::is_key_pressed(NoctisEngine::Key::ESCAPE)) {
            NoctisEngine::Log::Info("Esc pressed");
            if (!debugUI_.hidden()) {
                NoctisEngine::Log::Info("Hiding debug ui.");
                debugUI_.set_enabled(false);
            }
            else {
                NoctisEngine::Log::Info("Quitting");
                break;
            }
        }

        if (NoctisEngine::InputSystem::is_key_pressed(NoctisEngine::Key::V)) {
            NoctisEngine::Log::Info("Showing debug ui.");
            debugUI_.set_enabled(true);
        }

        bool debugUIEnabled = !debugUI_.hidden();

        graphicsHandler_.clear_screen();

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

        if (!debugUIEnabled) {
            // Camera movement
            NoctisEngine::MouseMouvement mouseMvt = NoctisEngine::InputSystem::get_mouse_mouvement();
            camera_.rotate_by_clamped(mouseMvt.xDelta * MOUSE_SENS, -mouseMvt.yDelta * MOUSE_SENS);

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
        }

        double time = window_.get_time();

        camera_.upload_data();

        shader->bind();

        scene_.update(dt);
        scene_.render(dt);

        debugUI_.render();
        
        window_.poll_events();
        window_.swap_buffers();
    }
}

auto NoctisEngine::create_application(int argc, char **argv) -> NoctisEngine::Application * {
    return new TestApp;
}
