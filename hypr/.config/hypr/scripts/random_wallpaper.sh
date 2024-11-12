#!/bin/bash

slideshow_dir="$HOME/Downloads/Backgrounds/Slideshow/"

slideshow=$(find "$slideshow_dir" -type f)
sleep 1s

while true; do
	wallpaper=$(printf "%s \n" ${slideshow[@]} | shuf -n 1)
	hyprctl hyprpaper unload all
	hyprctl hyprpaper preload "$wallpaper"
	sleep 1s
	hyprctl hyprpaper wallpaper eDP-1, "$wallpaper"
	sleep 5m
done
