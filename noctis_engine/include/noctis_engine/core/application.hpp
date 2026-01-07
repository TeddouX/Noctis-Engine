#pragma once

namespace NoctisEngine
{

class Application {
public:
    Application() = default;
    virtual ~Application() = default;

    virtual auto run() -> void {};
    // virtual void shutdown() {};
};

auto create_application(int argc, char **argv) -> Application *;

} // namespace NoctisEngine
