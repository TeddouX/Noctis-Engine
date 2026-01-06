#include <noctis_engine/rendering/shader.hpp>
#include <noctis_engine/rendering/vertex_array.hpp>
#include <noctis_engine/rendering/uniform_buffer.hpp>
#include <noctis_engine/rendering/camera.hpp>
#include <noctis_engine/rendering/ssbo.hpp>
#include <noctis_engine/rendering/window.hpp>
#include <noctis_engine/rendering/render_state.hpp>
#include <noctis_engine/input/input_system.hpp>
#include <noctis_engine/core/logging.hpp>
#include <noctis_engine/asset/asset_manager.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

#include <print>

constexpr float MOUSE_SENS = 1.0f/10.0f;
constexpr float CAM_SPEED = 2.5f;

glm::mat4x4 createModelMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) {
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

int main() {
    auto assetManager = std::make_unique<NoctisEngine::AssetManager>();

    NoctisEngine::Window window = NoctisEngine::create_context(800, 600, "Testing");

    auto handler = NoctisEngine::RenderState::init();
    NoctisEngine::RenderState::set_clear_screen_color(NoctisEngine::Color{9, 9, 9, 255});

    handler->set_backface_culling(false);
    handler->set_depth_testing(true);

    auto shaderHandle = assetManager->load_asset<NoctisEngine::Shader>("./testing/test_shader.glsl");
    auto shader = assetManager->try_get(shaderHandle);

    if (!shader || !shader->compile())
        return EXIT_FAILURE;

    NoctisEngine::VertexArrayInfo plane {
        .vertices = {
            NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(1, 1)),
            NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(1, 0)),
            NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0)),
            NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec2(0, 1)),
        },
        .indices = {0, 1, 2, 2, 3, 0}
    };

    NoctisEngine::VertexArrayInfo cube {
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

    auto vertArray = NoctisEngine::VertexArray(plane);
    auto testUB = NoctisEngine::UniformBuffer(1);

    glm::vec3 col(0);
    testUB.upload_data(sizeof(glm::vec3), &col);

    NoctisEngine::Camera cam(glm::vec3(-5, 1, 2), 800/600, 70.f, .1f, 1000.f);

    auto modelSSBO = NoctisEngine::SSBO(2);
    glm::mat4x4 modelMatrix = createModelMatrix(glm::vec3(0, 1, 0), glm::vec3(0, 90, 0), glm::vec3(1));
    modelSSBO.upload_data(sizeof(glm::mat4x4), &modelMatrix);

    window.lock_cursor();

    auto textureHandle = assetManager->load_asset<NoctisEngine::Texture>("./testing/drone.png");
    auto texture = assetManager->try_get(textureHandle);

    if (!texture)
        return EXIT_FAILURE;

    texture->set_min_function(NoctisEngine::Texture::MinifyingFunction::NEAREST);
    texture->set_mag_function(NoctisEngine::Texture::MagnifyingFunction::NEAREST);
    texture->set_wrap_function(NoctisEngine::Texture::WrapParam::REPEAT, NoctisEngine::Texture::WrapParam::REPEAT);

    double timeAccumulator{};
    int frameCount{};

    while (!window.should_close()) {
        if (NoctisEngine::InputSystem::is_key_pressed(NoctisEngine::Key::ESCAPE)) {
            NoctisEngine::Log::Info("Esc pressed");
            break;
        }

        handler->clear_screen();

        NoctisEngine::MouseMouvement mouseMvt = NoctisEngine::InputSystem::get_mouse_mouvement();
        cam.rotate_by_clamped(mouseMvt.xDelta * MOUSE_SENS, -mouseMvt.yDelta * MOUSE_SENS);

        float dt = static_cast<float>(window.delta_time());

        timeAccumulator += dt;
        frameCount++;

        if (timeAccumulator >= 1.0) {
            double averageFPS = frameCount / timeAccumulator;
            double frameTime = 1000.0 / averageFPS;

            window.set_title(std::format("Testing | FPS: {:.3f} | {:.3f} ms", averageFPS, frameTime));

            timeAccumulator = 0.0;
            frameCount = 0;
        }

        auto forward = cam.forward();
        auto right = cam.right();
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::W))
            cam.translate_by(forward * CAM_SPEED * dt);
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::S))
            cam.translate_by(-forward * CAM_SPEED * dt);
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::A))
            cam.translate_by(-right * CAM_SPEED * dt);
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::D))
            cam.translate_by(right * CAM_SPEED * dt);

        double time = window.get_time();
        col.r = static_cast<float>((sin(time + 0.0f) * 0.5f) + 0.5f);
        col.g = static_cast<float>((sin(time + 2.0f) * 0.5f) + 0.5f);
        col.b = static_cast<float>((sin(time + 4.0f) * 0.5f) + 0.5f);

        modelMatrix = createModelMatrix(glm::vec3(0, sin(time + 0.0f) * 0.5f, 0), glm::vec3(0, time * 8, 0), glm::vec3(1));
        modelSSBO.update_data(0, sizeof(glm::mat4x4), &modelMatrix);

        testUB.update_data(0, sizeof(glm::vec3), &col);
        cam.upload_data();

        shader->bind();

        texture->bind(0, shader);  

        vertArray.use();

        window.poll_events();
        window.swap_buffers();
    }

    return 0;
}
