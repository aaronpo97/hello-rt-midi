#include "RtMidi.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "../include/MidiListener.hpp"
#include "../include/MidiEvent.hpp"  

int main() {
    try {
        spdlog::init_thread_pool(8192, 1);

        auto console_sink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        console_sink->set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");

        auto const logger = std::make_shared<spdlog::async_logger>(
            "midi", console_sink, spdlog::thread_pool(),
            spdlog::async_overflow_policy::overrun_oldest);

        spdlog::register_logger(logger);
        spdlog::flush_every(std::chrono::seconds(5));

        logger->set_level(spdlog::level::info);

        MidiListener listener(logger);

        if (!listener.listPorts()) {
            throw std::runtime_error("Failed to list ports.");
        }
        if (!listener.openPort()) {
            throw std::runtime_error("Failed to open port.");
        }
        if (!listener.start()) {
            throw std::runtime_error("Failed to start listener.");
        }

        spdlog::shutdown();
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
