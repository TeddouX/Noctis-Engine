#pragma once
#include <exception>
#include <stacktrace>

#include "./application.hpp"
#include "./assert.hpp"

extern NoctisEngine::Application *NoctisEngine::create_application();

int main(int argc, char **argv) {
    NoctisEngine::Application *app = nullptr;
    int exitCode = EXIT_SUCCESS;

    try {
        app = NoctisEngine::create_application();
        app->run();
    } catch (const std::exception &e) {
        NoctisEngine::Log::Critical("Exception occured: {}", e.what());
        NoctisEngine::Log::Critical("\n{}", std::stacktrace::current(1));
        
        exitCode = EXIT_FAILURE;
    }

    delete app;

    return exitCode;
}
