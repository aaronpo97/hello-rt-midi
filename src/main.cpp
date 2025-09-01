#include "RtMidi.h"

#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

struct MidiEvent
{
  uint8_t pitch;
  uint8_t velocity;
  bool    active; // true = note-on, false = note-off
  uint8_t channel;
};

std::ostream &operator<<(std::ostream &os, MidiEvent const &event)
{
  os << "\n";
  os << std::left;

  os << std::setw(12) << "Status:" << (event.active ? "Note On" : "Note Off")
     << "\n";
  os << std::setw(12) << "Pitch: " << static_cast<uint>(event.pitch) << "\n";
  os << std::setw(12) << "Velocity: " << static_cast<uint>(event.velocity)
     << "\n";

  os << std::setw(12) << "Channel: " << static_cast<uint>(event.channel)
     << "\n";

  return os;
}

uint8_t constexpr noteOff     = 0x80;
uint8_t constexpr noteOn      = 0x90;
uint8_t constexpr typeMask    = 0xF0; // message type nibble
uint8_t constexpr channelMask = 0x0F;

int main()
{
  try
  {
    auto midiIn = std::make_unique<RtMidiIn>();

    // List ports
    uint32_t const numPorts = midiIn->getPortCount();
    if (numPorts == 0)
    {
      std::cout << "No MIDI input ports available.\n";
      return EXIT_SUCCESS;
    }

    std::cout << "Available MIDI input ports:\n";
    for (unsigned int i = 0; i < numPorts; ++i)
    {
      std::cout << "  [" << i << "] " << midiIn->getPortName(i) << "\n";
    }

    std::string input;
    int         portNumber{};

    bool isValidPort      = false;
    auto checkIfValidPort = [numPorts](int const port) -> bool
    { return port >= 0 && port < numPorts; };

    while (!isValidPort)
    {
      std::cout << "Please provide a port number and press ENTER: ";
      if (std::getline(std::cin, input))
      {
        try
        {
          portNumber = std::stoi(input); // convert string to int
          if (!checkIfValidPort(portNumber))
          {
            throw std::runtime_error("Invalid port number.");
          }

          isValidPort = true;
        }
        catch (std::exception &)
        {
          portNumber = -1;
          std::cout << "Please try again." << "\n";
        }
      }
    }
    midiIn->openPort(portNumber);

    // Receive everything (sysex/timing/active-sensing)
    midiIn->ignoreTypes(false, false, false);

    // decode Note On/Off and print
    RtMidiIn::RtMidiCallback callback =
        +[](double, std::vector<unsigned char> *msg, void *)
    {
      if (!msg || msg->size() < 3)
        return;

      uint8_t const status = msg->at(0);

      uint8_t const type  = status & typeMask;    // message type nibble
      uint8_t const chan  = status & channelMask; // channel (0–15)
      uint8_t const data1 = msg->at(1);
      uint8_t const data2 = msg->at(2);

      // Only handle channel voice Note Off (0x80) and Note On (0x90)
      if (type == noteOff)
      {
        MidiEvent const ev{.pitch    = data1,
                           .velocity = data2,
                           .active   = false,
                           .channel  = chan};

        std::cout << ev;
      }
      else if (type == noteOn)
      {
        // Velocity 0 is treated as Note Off by many devices
        bool const isOn = (data2 != 0);
        MidiEvent  ev{data1, data2, isOn, chan};
        std::cout << ev;
      }
      // Other message types ignored
    };

    midiIn->setCallback(callback, nullptr);

    std::cout << "\nReading MIDI input from port " << portNumber
              << " ... press <Enter> to quit.\n";

    std::cin.get(); // block until Enter
  }
  catch (RtMidiError &e)
  {
    std::cerr << "RtMidiError: " << e.getMessage() << "\n";
    return EXIT_FAILURE;
  }
  catch (std::exception const &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
