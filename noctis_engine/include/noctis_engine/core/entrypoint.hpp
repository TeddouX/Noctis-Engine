#pragma once
#include <exception>
#include <stacktrace>

#include "application.hpp"
#include "assert.hpp"
#include "exception.hpp"

extern auto NoctisEngine::create_application(int argc, char **argv) -> NoctisEngine::Application *;

auto main(int argc, char **argv) -> int {
    NoctisEngine::Application *app = nullptr;
    int exitCode = EXIT_FAILURE;

    try {
        app = NoctisEngine::create_application(argc, argv);
        app->run();

        exitCode = EXIT_SUCCESS;
    } catch (const NoctisEngine::Exception &e) {
        NoctisEngine::Log::Critical("Exception occured: {}", e);
    } catch (...) {
        NoctisEngine::Log::Critical("Uncaught exception");
    }

    delete app;

    return exitCode;
}
