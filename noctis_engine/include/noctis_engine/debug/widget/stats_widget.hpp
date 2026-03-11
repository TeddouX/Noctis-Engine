#pragma once
#include "debug_widget.hpp"

namespace NoctisEngine
{
    
class NCENG_API StatsDbgWidget : public IDebugWidget {
public:
    StatsDbgWidget() = default;

    auto render() -> void override;
    auto on_attach(DebugUI *parent) -> void override;

private:
    DebugUI *parent_;

    float timeAcc_{};
    int frameCount_{};

    float frameTime_{};
    float fps_{};
};

} // namespace NoctisEngine
