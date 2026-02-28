#include <noctis_engine/rendering/shader.hpp>
#include <noctis_engine/rendering/camera.hpp>
#include <noctis_engine/rendering/renderer3D.hpp>
#include <noctis_engine/input/input_system.hpp>
#include <noctis_engine/core/logging.hpp>
#include <noctis_engine/core/entrypoint.hpp>
#include <noctis_engine/ecs/component/transform.hpp>
#include <noctis_engine/asset/asset_manager.hpp>
#include <noctis_engine/debug/widget/stats_widget.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

#include <print>

#include "main.h"


TestApp::TestApp() 
    : window_(std::make_shared<NoctisEngine::Window>(800, 600, "Testing"))
    , assetManager_(std::make_unique<NoctisEngine::AssetManager>())
    , meshManager_(std::make_shared<NoctisEngine::MeshManager>())
    , renderer_{std::make_shared<NoctisEngine::Renderer3D>(meshManager_)}
    , camera_(glm::vec3(-5, 1, 2), 800/600, 70.f, .1f, 1000.f)
    , debugUI_(window_)
    , scene_{}
{
    renderer_->set_clear_screen_color(NoctisEngine::Color{9, 9, 9, 255});
    renderer_->set_backface_culling(false);
    renderer_->set_depth_testing(true);
    renderer_->set_throw_on_err(true);

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

    debugUI_.add_widget(std::make_shared<NoctisEngine::StatsDbgWidget>());
}

auto TestApp::run() -> void {
    window_->lock_cursor();

    auto shader = assetManager_->try_get(shaderHandle_);
    if (!shader) 
        throw NoctisEngine::Exception("Getting the shader failed.");

    while (!window_->should_close()) {
        if (NoctisEngine::InputSystem::is_key_pressed(NoctisEngine::Key::ESCAPE)) {
            NoctisEngine::Log::Info("Esc pressed");
            break;
        }

        if (NoctisEngine::InputSystem::is_key_pressed(NoctisEngine::Key::G)) {
            NoctisEngine::Log::Info("Debug UI enabled");
            debugUI_.set_enabled(debugUI_.hidden());
        }

        renderer_->clear_screen();

        NoctisEngine::MouseMouvement mouseMvt = NoctisEngine::InputSystem::get_mouse_mouvement();
        camera_.rotate_by_clamped(mouseMvt.xDelta * MOUSE_SENS, -mouseMvt.yDelta * MOUSE_SENS);

        float dt = static_cast<float>(window_->delta_time());

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

        camera_.upload_data();

        debugUI_.render();

        shader->bind();

        scene_.update(dt);
        renderer_->render_entities(scene_.get_all_entities());
        
        window_->poll_events();
        window_->swap_buffers();
    }
}

auto NoctisEngine::create_application(int argc, char **argv) -> NoctisEngine::Application * {
    return new TestApp;
}
