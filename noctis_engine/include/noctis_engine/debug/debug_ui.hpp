#pragma once
#include <vector>
#include <memory>

#include "widget/debug_widget.hpp"
#include "../noctis_engine.hpp"
#include "../rendering/window.hpp"

namespace NoctisEngine
{
    
class NCENG_API DebugUI {
public:
    DebugUI(Window &window);
    ~DebugUI();

    auto add_widget(std::shared_ptr<IDebugWidget> widget);
    auto set_enabled(bool b) -> void;
    auto render() -> void;

    auto hidden() const -> bool;

private:
    std::vector<std::shared_ptr<IDebugWidget>> widgets;
    Window window_;
    bool hidden_;
};
    
} // namespace NoctisEngine
