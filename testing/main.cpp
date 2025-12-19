#include <noctis_engine/rendering/shader.hpp>
#include <noctis_engine/rendering/vertex_array.hpp>
#include <noctis_engine/rendering/uniform_buffer.hpp>
#include <noctis_engine/rendering/camera.hpp>
#include <noctis_engine/rendering/ssbo.hpp>
#include <noctis_engine/rendering/window.hpp>
#include <noctis_engine/rendering/render_state.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

#include <print>

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
    NoctisEngine::RenderState::set_clear_screen_color(NoctisEngine::Color{255, 0, 0, 255});

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

    glm::vec3 col(0, 0, 0);
    testUB->upload_data(sizeof(glm::vec3), &col);

    NoctisEngine::Camera cam(glm::vec3(-5, 1, 2), 800/600, 70.f, .1f, 1000.f);
    cam.rotate_by(-5.f, -10.f);

    auto modelSSBO = NoctisEngine::SSBO::Create(2);
    glm::mat4x4 modelMatrix = createModelMatrix(glm::vec3(0, 1, 0), glm::vec3(0, 90, 0), glm::vec3(1));
    modelSSBO->upload_data(sizeof(glm::mat4x4), &modelMatrix);

    while (!window.should_close()) {
        window.poll_events();

        handler->clear_screen();
        
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

        window.swap_buffers();
    }

    return 0;
}