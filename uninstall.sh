#!/bin/bash 

systemctl --user disable hyprrestore.save.timer
systemctl --user disable hyprrestore.restore.service 

systemctl --user stop hyprrestore.save.timer
systmectl --user stop hyprrestore.restore.service 

rm -f ~/.local/bin/hyprrestore-save
rm -f ~/.local/bin/hyprrestore-restore 

rm -f ~/.config/systemd/user/hyprrestore.*

systemctl --user daemon-reload

echo "HyprRestore removed"
