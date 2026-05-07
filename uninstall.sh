#!/bin/bash
set -euo pipefail

echo "Removing HyprRestore..."

systemctl --user disable hyprrestore.save.timer || true
systemctl --user disable hyprrestore.restore.service || true
systemctl --user stop hyprrestore.save.timer || true
systemctl --user stop hyprrestore.restore.service || true

rm -f ~/.local/bin/hyprrestore-save
rm -f ~/.local/bin/hyprrestore-restore
rm -f ~/.config/systemd/user/hyprrestore.save.service
rm -f ~/.config/systemd/user/hyprrestore.save.timer
rm -f ~/.config/systemd/user/hyprrestore.restore.service

systemctl --user daemon-reload

echo "HyprRestore removed"
