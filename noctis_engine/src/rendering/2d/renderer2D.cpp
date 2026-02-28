#include "rendering/2d/renderer2D.hpp"

#include <glad/gl.h>

#include "ecs/component/transform2D.hpp"
#include "ecs/component/sprite2D.hpp"

namespace NoctisEngine
{
    
Renderer2D::Renderer2D(std::shared_ptr<MeshManager> meshManager) {
    init(meshManager);
}

auto Renderer2D::render_entities(entt::registry &reg) -> void {
    auto view = reg.view<const Transform2D, const Sprite2D, const MaterialKey>();

    std::vector<DrawElementsIndirectCommand> commands;
    std::vector<ObjectData> objects;

    for (const auto &[entity, transform, sprite, matKey] : view.each()) {
        MeshView meshView = sprite.get_mesh_view();

        commands.push_back(DrawElementsIndirectCommand{
            .count         = static_cast<GLuint>(meshView.indicesCount),
            .instanceCount = 1u,
            .firstIndex    = static_cast<GLuint>(meshView.indicesOffset),
            .baseVertex    = static_cast<GLint>(meshView.verticesOffset),
            .baseInstance  = 0, 
        });

        objects.push_back(ObjectData{
            .modelMat = transform.model_matrix(sprite.get_z_order()),
            .materialIdx = static_cast<GLuint>(matKey),
        });
    }

    render(commands, objects);
}

} // namespace NoctisEngine
