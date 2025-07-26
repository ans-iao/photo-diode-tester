# Photodiode Tester

A simple C++ application that flashes a fullscreen window between black and white to test **photodiode response** and *
*LSL-based network delay** across systems.

## Overview

This project is designed for latency testing and synchronization validation in neuroscience or psychophysics experiments
involving **visual stimuli** and **photodiodes**. It sends LSL (Lab Streaming Layer) markers at each color switch while
toggling the window background between **black** and **white** at controlled intervals.

In a real setup:

- **Photodiodes** are physically placed on the display region showing this window.
- One photodiode is connected to a local **acquisition PC**.
- A **second photodiode** is attached to a different PC in the same network.
- Both PCs stream/receive LSL markers to compare **temporal alignment** and **network delay**.

## Features

- Fullscreen or resizable window using [SFML](https://www.sfml-dev.org/).
- Background toggles between white and black with custom durations:
    - White: 1 second
    - Black: 2 seconds
- Sends corresponding LSL markers (`0` for black, `1` for white).
- Synchronized toggling with `sleep_until` to minimize drift.

## How to Build

### 🔧 Prerequisites

- C++17 or newer
- [SFML 3.0.1](https://github.com/SFML/SFML)
- [liblsl (prebuilt)](https://github.com/sccn/liblsl/releases) >= 1.16.2
- [CMake](https://cmake.org/download/) >= 3.31.6
- g++/gcc >= 13.1.0 (https://www.mingw-w64.org/)
- git (for fetching sfml git repo)

### Setup (with CMake)

1. Clone this repository:

```bash
git clone https://github.com/ans-iao/photo-diode-tester.git
cd photo-diode-tester
```

2. Download the prebuilt [liblsl](https://github.com/sccn/liblsl/releases) extract the content and place the content at:

```
photo-diode-tester/
├──liblsl/
    ├── include/
    ├── lib/
    └── bin/ (for DLLs)
```

3. Build using CMake (Windows with MinGW):

```
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

Or using IDEs such as [Clion](https://www.jetbrains.com/clion/) would make the process easier.

## Runtime Notes

- On Windows, make sure liblsl.dll is in the same folder as the executable, or added to your system PATH.
- At each toggle, a marker is sent over LSL:

    - `1` when screen turns **white**
    - `0` when screen turns **black**

### Use Case

This tool is ideal for:

- EEG/MEG/ECG setup validation with photodiodes
- Cross-PC latency benchmarking via LSL
- Visual perception or stimulus timing experiments

### License

MIT License. See `LICENSE` file for details
