#!/bin/bash
set -euo pipefail

echo "Installing HyprRestore..."

mkdir -p build
if ! g++ -std=c++17 -Wall -Wextra -O2 ./src/save.cpp -o ./build/save; then
  echo "Build failed for save" >&2
  exit 1
fi
if ! g++ -std=c++17 -Wall -Wextra -O2 ./src/restore.cpp -o ./build/restore; then
  echo "Build failed for restore" >&2
  exit 1
fi

mkdir -p ~/.local/bin
cp build/save ~/.local/bin/hyprrestore-save
cp build/restore ~/.local/bin/hyprrestore-restore
chmod +x ~/.local/bin/hyprrestore-save
chmod +x ~/.local/bin/hyprrestore-restore

mkdir -p ~/.local/share/hyprrestore/snapshots
mkdir -p ~/.config/systemd/user
cp systemd/* ~/.config/systemd/user/

systemctl --user daemon-reload
systemctl --user enable hyprrestore.save.timer
systemctl --user enable hyprrestore.restore.service
systemctl --user start hyprrestore.save.timer
systemctl --user start hyprrestore.restore.service

echo "HyprRestore installed successfully"
