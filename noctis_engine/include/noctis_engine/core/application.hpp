#pragma once

namespace NoctisEngine
{

class Application {
public:
    Application() = default;
    virtual ~Application() = default;

    virtual void run() {};
    // virtual void shutdown() {};
};

Application* create_application();

} // namespace NoctisEngine
