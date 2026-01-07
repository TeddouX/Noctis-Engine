#pragma once
#include <exception>
#include <stacktrace>

#include "./application.hpp"
#include "./assert.hpp"

extern auto NoctisEngine::create_application(int argc, char **argv) -> NoctisEngine::Application *;

auto main(int argc, char **argv) -> int {
    NoctisEngine::Application *app = nullptr;
    int exitCode = EXIT_SUCCESS;

    try {
        app = NoctisEngine::create_application(argc, argv);
        app->run();
    } catch (const std::exception &e) {
        NoctisEngine::Log::Critical("Exception occured: {}", e.what());
        // NoctisEngine::Log::Critical("\n{}", std::stacktrace::current(1));
        
        exitCode = EXIT_FAILURE;
    }

    delete app;

    return exitCode;
}
