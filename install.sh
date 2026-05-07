#!/bin/bash
set -e
echo "Installing HyprRestore..."

mkdir -p build 
g++ ./src/save.cpp -o ./build/save
g++ ./src/restore.cpp -o ./build/restore

mkdir -p ~/.local/bin 
cp build/save ~/.local/bin/hyprrestore-save
cp build/restore ~/.local/bin/hyprrestore-restore
chmod +x ~/.local/bin/hyprrestore-save
chmod +x ~/.local/bin/hyprrestore-restore

mkdir -p ~/.local/share/hyprrestore

mkdir -p ~/.config/systemd/user
cp systemd/* ~/.config/systemd/user/ 

systemctl --user daemon-reload
systemctl --user enable hyprrestore.save.timer
systemctl --user enable hyprrestore.restore.service 

systemctl --uesr start hyprrestore.save.timer
systemctl --user start hyprrestore.restore.service 

echo "HyprRestore installed successfully"
