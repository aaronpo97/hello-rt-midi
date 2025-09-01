
# hello-rt-midi

A simple C++ project demonstrating MIDI input/output using [RtMidi](https://www.music.mcgill.ca/~gary/rtmidi/).

## Features

- Lists available MIDI input and output ports
- Sends and receives MIDI messages
- Simple example of using RtMidi in C++
- Cross-platform (tested on macOS, should work on Linux/Windows with RtMidi)

## Requirements

- C++23
- [RtMidi](https://www.music.mcgill.ca/~gary/rtmidi/) 
- CMake 3.16+

## Building

```sh
cmake -S . -B build
cmake --build build
```

## Running

```sh
./build/hello-rt-midi
```

## Project Structure

- `src/` — Source files
- `include/` — Header files
- `CMakeLists.txt` — Build configuration
- `format.sh` — Code formatting script

## License

MIT License