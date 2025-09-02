
#pragma once

#include "./MidiEvent.hpp"
#include "RtMidi.h"
#include "spdlog/spdlog.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

constexpr uint8_t c_noteOff     = 0x80; // Note Off message
constexpr uint8_t c_noteOn      = 0x90; // Note On message
constexpr uint8_t c_typeMask    = 0xF0; // Type mask
constexpr uint8_t c_channelMask = 0x0F; // Channel mask

class MidiListener {
    std::shared_ptr<spdlog::logger>
                              m_logger; // the logger used to log midi events
    std::unique_ptr<RtMidiIn> m_midiIn; // the RtMidiIn instance
    int                       m_portNumber = -1;

  public:
    explicit MidiListener(std::shared_ptr<spdlog::logger> const &logger);

    /**
     * \brief Lists available MIDI input ports
     *
     *
     * \return true if successful
     * \return false if an error occurred
     */
    [[nodiscard]] bool listPorts() const;

    /**
     * \brief Opens a MIDI input port
     *
     * This will prompt the user to select a port number.
     *
     * \return true if successful
     * \return false if an error occurred
     */
    [[nodiscard]] bool openPort();

    /**
     * \brief Starts listening to MIDI input
     *
     * \return true if successful
     * \return false if an error occurred
     */
    [[nodiscard]] bool start() const;
};
