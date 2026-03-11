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
    DebugUI(std::shared_ptr<Window> window);
    ~DebugUI();

    auto add_widget(std::shared_ptr<IDebugWidget> widget) -> void;
    auto set_enabled(bool b) -> void;
    auto render() -> void;

    auto hidden() const -> bool;

    auto window() const -> const std::shared_ptr<Window> &;

private:
    std::vector<std::shared_ptr<IDebugWidget>> widgets_;
    std::shared_ptr<Window> window_;
    bool hidden_;
};
    
} // namespace NoctisEngine
