#pragma once
#include "mesh/mesh_manager.hpp"
#include "material/material_manager.hpp"
#include "../ecs/ecs.hpp"

namespace NoctisEngine
{
    
struct DrawElementsIndirectCommand {
    std::uint32_t count;
    std::uint32_t instanceCount;
    std::uint32_t firstIndex;
    int           baseVertex;
    std::uint32_t baseInstance;
};

struct alignas(16) ObjectData {
    glm::mat4     modelMat;
    std::uint32_t materialIdx;
};

enum class BlendFunc {
    ZERO = 0, 
    ONE = 1,

    SRC_COLOR = 0x0300, 
    ONE_MINUS_SRC_COLOR = 0x0301, 

    SRC_ALPHA = 0x0302, 
    ONE_MINUS_SRC_ALPHA = 0x0303, 

    DST_ALPHA = 0x0304, 
    ONE_MINUS_DST_ALPHA = 0x0305, 

    DST_COLOR = 0x0306, 
    ONE_MINUS_DST_COLOR = 0x0307,

    CONSTANT_COLOR = 0x8001,
    ONE_MINUS_CONSTANT_COLOR = 0x8002,

    CONSTANT_ALPHA = 0x8003,
    ONE_MINUS_CONSTANT_ALPHA = 0x8004
};

class NCENG_API Renderer {
public:
    virtual ~Renderer() = default;

    virtual auto render_entities(entt::registry &reg) -> void = 0;

    void clear_screen() const;
    auto set_backface_culling(bool b) const -> void;
    auto set_depth_testing(bool b) const -> void;
    auto set_clear_screen_color(Color col) -> void;
    auto set_throw_on_err(bool b) -> void;
    auto set_blend(bool b) -> void;
    auto set_blend_func(BlendFunc sFactor, BlendFunc dFactor) -> void;

    auto set_viewport_size(int w, int h) -> void;

protected:
    auto init(std::shared_ptr<MeshManager> meshManager) -> void;

    auto render(
        std::vector<DrawElementsIndirectCommand> commands, 
        std::vector<ObjectData> objects
    ) -> void;

    std::shared_ptr<MeshManager> meshManager_;
    GPUBuffer                    objectsSSBO_;
    GPUBuffer                    commandBuf_;

    bool throwOnErr_ = false;

private:
    static void OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam);
};

} // namespace NoctisEngine
