
#include "../include/MidiListener.hpp"
#include <iostream>
#include <stdexcept>

MidiListener::MidiListener(std::shared_ptr<spdlog::logger> const &logger)
    : m_logger(logger), m_midiIn(std::make_unique<RtMidiIn>()) {
}

bool MidiListener::listPorts() const {
    uint32_t const numPorts = m_midiIn->getPortCount();
    if (numPorts == 0) {
        m_logger->info("No MIDI input ports available.\n");
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

    // This checks if the port number is good
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
            // lambda function cast to a function pointer to handle incoming
            // MIDI messages
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

                // Make a MIDI event
                MidiEvent ev = {.pitch    = d1,
                                .velocity = d2,
                                .active   = (type == c_noteOn && d2 > 0),
                                .channel  = chan};

                // Print the MIDI event
                log->info("t={:<5.2f} {:<9} pitch={:<3} vel={:<4} chan={:<2}",
                          timestamp,
                          (type == c_noteOff || (type == c_noteOn && d2 == 0)
                               ? "Note Off"
                               : "Note On"),
                          ev.pitch, ev.velocity, ev.channel + 1);
            },
            m_logger.get());

        m_logger->info(
            "Listening to MIDI input from port {} ... press <Enter> to quit.",
            m_portNumber);

        std::cin.get();             // Wait for user to press Enter
        m_midiIn->cancelCallback(); // Stop listening
        m_midiIn->closePort();      // Close the port
        return true;
    } catch (...) {
        return false;
    }
}
