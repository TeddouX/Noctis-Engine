#include <debug/widget/stats_widget.hpp>

#include <imgui.h>

#include <debug/debug_ui.hpp>
#include <core/logging.hpp>

namespace NoctisEngine
{
 
auto StatsDbgWidget::on_attach(DebugUI *ui) -> void {
    parent_ = ui;
}

auto StatsDbgWidget::render() -> void {
    float dt = static_cast<float>(parent_->window()->delta_time());

    timeAcc_ += dt;
    frameCount_++;

    if (timeAcc_ >= 1.0) {
        fps_ = frameCount_ / timeAcc_;
        frameTime_ = 1000.0 / fps_;

        timeAcc_ = 0.0;
        frameCount_ = 0;
    }

    ImGui::Begin("Stats");

    ImGui::Text("FPS: %f", fps_);
    ImGui::Text("Frame time (ms): %f", frameTime_);

    ImGui::End();
}

} // namespace NoctisEngine
