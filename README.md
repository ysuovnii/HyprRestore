# HyprRestore
**HyprRestore** is a lightweight session persistence tool for **Hyprland** that automatically saves and restores your workspace state, running applications, and window layout using a native **C++ backend** integrated with **systemd user services**.

## Features

- Session snapshot capture (Hyprland clients)
- Automatic restore on login
- Systemd user service integration
- Lightweight C++ implementation with minimal dependencies
- JSON-based snapshot storage

## Architecture

HyprRestore is composed of two core components:

- **Save Engine**
  - Captures active Hyprland client state
  - Writes snapshot JSON to `~/.local/share/hyprrestore/snapshots`

- **Restore Engine**
  - Reads saved snapshot
  - Re-launches applications using the saved window class

## Project Structure

```bash
hyprrestore/
├── src/
│   ├── save.cpp
│   ├── restore.cpp
├── systemd/
│   ├── hyprrestore.save.service
│   ├── hyprrestore.save.timer
│   ├── hyprrestore.restore.service
├── build/
│   ├── save
│   ├── restore
├── install.sh
├── uninstall.sh
├── Makefile
└── README.md
```

## Requirements

- Linux with Hyprland compositor
- C++17 or later
- `g++`
- `libnlohmann-json-dev` or equivalent header-only JSON library
- `systemd` user mode enabled
- `hyprctl` available in PATH

## Installation

### 1. Clone Repository
```bash
git clone https://github.com/ysuovnii/hyprrestore.git
cd hyprrestore
```

### 2. Build and Install
```bash
make
./install.sh
```

### 3. Enable and Start Services
```bash
systemctl --user daemon-reload
systemctl --user enable hyprrestore.save.timer
systemctl --user enable hyprrestore.restore.service
systemctl --user start hyprrestore.save.timer
systemctl --user start hyprrestore.restore.service
```

### 4. Snapshot Location
- `~/.local/share/hyprrestore/snapshots/snapshot.json`

## Known Issues
- Some applications may fail to launch if the recorded window class is not an executable name
- Browser restore is best-effort and depends on the saved title format

## Roadmap
- Flatpak / native app resolver
- Multi-monitor layout restoration
- Window geometry persistence
- Improved error handling and recovery

## License

This project is licensed under the MIT License.
