# HyprRestore
**HyprRestore** is a lightweight session persistence tool for **Hyprland** that automatically saves and restores your workspace state, running applications, and window layout using a native **C++ backend** integrated with **systemd user services**.

## Features

- Session snapshot capture (workspaces + applications)
- Automatic session restore on login
- Systemd user service integration
- Hyprland-native control via `hyprctl`
- Lightweight C++ implementation with minimal dependencies
- JSON-based snapshot storage

## Architecture

HyprRestore is composed of two core components:

- **Save Engine**
  - Periodically captures active Hyprland state
  - Stores data in structured JSON snapshots

- **Restore Engine**
  - Reads saved snapshot
  - Re-launches applications and reconstructs workspace layout

## Project Structure

```bash
hyprrestore/
├── src/
│   ├── save.cpp              # Session capture logic
│   ├── restore.cpp           # Session restoration logic
│
├── systemd/
│   ├── hyprrestore-save.service
│   ├── hyprrestore-save.timer
│   ├── hyprrestore-restore.service
│
├── Install.sh
├── Makefile
├── Uninstall.sh
│
└── README.md
```

## Requirements

- Linux with Hyprland compositor
- C++17 or later
- systemd (user mode enabled)
- `hyprctl` available in PATH


## Installation

### 1. Clone Repository
- ⚠️ Recommended location: `~/.config`
```bash
git clone https://github.com/ysuovnii/hyprrestore.git
cd hyprrestore
```

### 2. Build the Project
```bash
mkdir -p build
g++ src/save.cpp -o build/save
g++ src/restore.cpp -o build/restore
```

### 3. Install Systemd User Services
```bash
mkdir -p ~/.config/systemd/user

cp systemd/*.service ~/.config/systemd/user/
cp systemd/*.timer ~/.config/systemd/user/

systemctl --user daemon-reload
```

### 4. Enable Service
```bash
systemctl --user enable hyprrestore-save.timer
systemctl --user enable hyprrestore-restore.service
```

### 5. Start Services 
```bash
systemctl --user start hyprrestore-save.service
systemctl --user start hyprrestore-restore.service
```

## Known Issues
- Some applications may fail to launch if command mapping is incorrect (Flatpak vs native binaries)
- Certain window classes require manual mapping in restore logic


## Roadmap
- Flatpak + native app resolver
- Multi-monitor layout restoration
- Window geometry persistence
- Improved error handling and recovery system

## License

This project is licensed under the MIT License.
