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

struct MidiEvent {
    uint8_t pitch;
    uint8_t velocity;
    bool    active;
    uint8_t channel;
};

constexpr uint8_t c_noteOff     = 0x80;
constexpr uint8_t c_noteOn      = 0x90;
constexpr uint8_t c_typeMask    = 0xF0;
constexpr uint8_t c_channelMask = 0x0F;

class MidiListener {
    std::shared_ptr<spdlog::logger> m_logger;
    std::unique_ptr<RtMidiIn>       m_midiIn;
    int                             m_portNumber = -1;

  public:
    explicit MidiListener(std::shared_ptr<spdlog::logger> logger);
    [[nodiscard]] bool listPorts() const;
    bool               openPort();
    bool               start() const;
};

MidiListener::MidiListener(std::shared_ptr<spdlog::logger> logger)
    : m_logger(std::move(logger)), m_midiIn(std::make_unique<RtMidiIn>()) {
}

bool MidiListener::listPorts() const {
    uint32_t const numPorts = m_midiIn->getPortCount();
    if (numPorts == 0) {
        std::cout << "No MIDI input ports available.\n";
        return false;
    }
    std::cout << "Available MIDI input ports:\n";
    for (unsigned int i = 0; i < numPorts; ++i)
        std::cout << "  [" << i << "] " << m_midiIn->getPortName(i) << "\n";
    return true;
}

bool MidiListener::openPort() {
    uint32_t numPorts = m_midiIn->getPortCount();
    if (numPorts == 0) {
        return false;
    }

    std::string input;
    int         portNumber{};

    auto checkIfValidPort = [numPorts](int const port) -> bool {
        return port >= 0 && port < static_cast<int>(numPorts);
    };

    while (true) {
        std::cout << "Please provide a port number and press ENTER: ";
        if (!std::getline(std::cin, input))
            return false;
        try {
            portNumber = std::stoi(input);
            if (!checkIfValidPort(portNumber))
                throw std::runtime_error("Invalid port number.");
            break;
        } catch (...) {
            std::cout << "Please try again.\n";
        }
    }

    m_midiIn->openPort(portNumber);
    m_midiIn->ignoreTypes(false, false, false);
    m_portNumber = portNumber;
    return true;
}

bool MidiListener::start() const {
    try {
        m_midiIn->setCallback(
            +[](double timestamp, std::vector<unsigned char> *msg,
                void *user) noexcept {
                if (!msg || msg->size() < 3) {
                    return;
                }

                auto *log = static_cast<spdlog::logger *>(user);

                uint8_t const status = (*msg)[0];
                uint8_t const type   = status & c_typeMask;
                uint8_t const chan   = status & c_channelMask;
                uint8_t const d1     = (*msg)[1];
                uint8_t const d2     = (*msg)[2];

                MidiEvent ev = {.pitch    = d1,
                                .velocity = d2,
                                .active   = (type == c_noteOn && d2 > 0),
                                .channel  = chan};

                log->info("t={:<5.2f} {:<9} pitch={:<3} vel={:<4} chan={:<2}",
                          timestamp,
                          (type == c_noteOff || (type == c_noteOn && d2 == 0)
                               ? "Note Off"
                               : "Note On"),
                          ev.pitch, ev.velocity, ev.channel + 1);
            },
            m_logger.get());

        std::cout << "\nReading MIDI input from port " << m_portNumber
                  << " ... press <Enter> to quit.\n";
        std::cin.get();
        m_midiIn->cancelCallback();
        m_midiIn->closePort();
        return true;
    } catch (...) {
        return false;
    }
}

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
