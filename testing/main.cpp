#include <noctis_engine/rendering/shader.hpp>
#include <noctis_engine/rendering/vertex_array.hpp>
#include <noctis_engine/rendering/uniform_buffer.hpp>
#include <noctis_engine/rendering/camera.hpp>
#include <noctis_engine/rendering/ssbo.hpp>
#include <noctis_engine/rendering/window.hpp>
#include <noctis_engine/rendering/render_state.hpp>
#include <noctis_engine/input/input_system.hpp>
#include <noctis_engine/core/logging.hpp>

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
    NoctisEngine::Window window = NoctisEngine::create_context(800, 600, "Testing");
    
    auto handler = NoctisEngine::RenderState::init(NoctisEngine::GraphicsBackend::OPENGL);
    NoctisEngine::RenderState::set_clear_screen_color(NoctisEngine::Color{9, 9, 9, 255});

    auto shader = NoctisEngine::Shader::Create(
        "#version 430 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aNormal;\n"
        "layout (location = 2) in vec2 aTexCoord;\n"
        "layout(std140, binding = 0) uniform CameraBuffer {\n"
        "   mat4 projMat;\n"
        "   mat4 viewMat;\n"
        "} camera;\n"
        "uniform int modelIdx;\n"
        "layout(std430, binding = 2) buffer ModelMatrices {\n"
        "   mat4 modelMatrices[];\n"
        "} models;\n"   
        "out vec3 Pos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = camera.projMat * camera.viewMat * models.modelMatrices[modelIdx] * vec4(aPos, 1.0);\n"
        "   Pos = aPos;\n"
        "}\0",

        "#version 430 core\n"
        "in vec3 Pos;\n"
        "out vec4 FragColor;\n"
        "layout(std140, binding = 1) uniform TestBuffer {\n"
        "   vec3 col;\n"
        "} test;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(test.col, 1.0f);\n"
        "}\n\0"
    );

    NoctisEngine::VertexArrayInfo plane {
        .vertices = {
            NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
            NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
            NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0)),
            NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
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

    auto vertArray = NoctisEngine::VertexArray::Create(cube);
    auto testUB = NoctisEngine::UniformBuffer::Create(1);

    glm::vec3 col(0);
    testUB->upload_data(sizeof(glm::vec3), &col);

    NoctisEngine::Camera cam(glm::vec3(-5, 1, 2), 800/600, 70.f, .1f, 1000.f);
    // cam.rotate_by(-5.f, -10.f);

    auto modelSSBO = NoctisEngine::SSBO::Create(2);
    glm::mat4x4 modelMatrix = createModelMatrix(glm::vec3(0, 1, 0), glm::vec3(0, 90, 0), glm::vec3(1));
    modelSSBO->upload_data(sizeof(glm::mat4x4), &modelMatrix);

    window.lock_cursor();

    while (!window.should_close()) {
        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::E))
            NoctisEngine::Log::Info("E pressed");

        if (NoctisEngine::InputSystem::is_key_down(NoctisEngine::Key::ESCAPE)) {
            NoctisEngine::Log::Info("Esc pressed");
            break;
        }

        handler->clear_screen();
        
        NoctisEngine::MouseMouvement mouseMvt = NoctisEngine::InputSystem::get_mouse_mouvement();
        cam.rotate_by_clamped(mouseMvt.xDelta * MOUSE_SENS, -mouseMvt.yDelta * MOUSE_SENS);

        float dt = static_cast<float>(window.delta_time());

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
        modelSSBO->update_data(0, sizeof(glm::mat4x4), &modelMatrix);

        testUB->update_data(0, sizeof(glm::vec3), &col);
        cam.upload_data();

        shader->bind();
        vertArray->use();

        window.poll_events();
        window.swap_buffers();
    }

    return 0;
}