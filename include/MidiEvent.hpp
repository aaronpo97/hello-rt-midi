
#pragma once
#include <cstdint>

struct MidiEvent {
    uint8_t pitch;    // The note number
    uint8_t velocity; // How hard the note is played
    bool    active;   // True if the note is on
    uint8_t channel;  // The channel number
};
