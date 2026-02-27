#pragma once
#include "mesh/mesh_manager.hpp"
#include "material/material_manager.hpp"
#include "../ecs/ecs.hpp"

namespace NoctisEngine
{
    
class NCENG_API Renderer {
public:
    Renderer(std::shared_ptr<MeshManager> meshManager);

    auto render(entt::registry &reg) -> void;

    void clear_screen() const;
    auto set_backface_culling(bool b) const -> void;
    auto set_depth_testing(bool b) const -> void;
    auto set_clear_screen_color(Color col) -> void;
    auto set_throw_on_err(bool b) -> void;

    auto set_viewport_size(int w, int h) -> void;

private:
    std::shared_ptr<MeshManager> meshManager_;
    GPUBuffer                    objectsSSBO_;
    GPUBuffer                    commandBuf_;

    Color clearScrCol_;
    bool throwOnErr_ = false;

    static void OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam);
};

} // namespace NoctisEngine
