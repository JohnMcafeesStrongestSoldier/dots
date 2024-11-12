#!/bin/bash

slideshow_dir="$HOME/Downloads/Backgrounds/Slideshow/"

slideshow=$(find "$slideshow_dir" -type f)

while true; do
	wallpaper=$(printf "%s \n" ${slideshow[@]} | shuf -n 1)
	hyprctl hyprpaper unload all
	hyprctl hyprpaper preload "$wallpaper"
	sleep 1s
	hyprctl hyprpaper wallpaper ,"$wallpaper"
	sleep 5s
done
