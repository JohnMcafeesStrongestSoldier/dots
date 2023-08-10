#!/bin/sh

run_dwm() {
	while true; do
		dwm
	done
}

random_background() {
	while true; do
		feh --randomize --bg-fill ~/Downloads/Backgrounds/Slideshow/
		sleep 1m
	done
}
sh /home/james/.fehbg
run_dwm &
random_background &
#paperview /home/james/Downloads/Astro 7 &
dbus-run-session pulseaudio &
exec /usr/libexec/polkit-kde-authentication-agent-1 &
syncthingtray &
picom &
dunst &
#while true; do
#	xsetroot -name "$(date2) | $(mem) | $(cpu) | $(bat)"
#	sleep 10s
#
#
#
#
while true; do
	getdate="$(date +"%A, %B %d - %I:%M")"
	getmem="$(free -m | awk '/Mem/ {printf $3"/"$2}')"
	getbat="$(acpi)"
	read cpu a b c previdle rest </proc/stat
	prevtotal=$((a + b + c + previdle))
	sleep 0.5
	read cpu a b c idle rest </proc/stat
	total=$((a + b + c + idle))
	getcpu=$((100 * ((total - prevtotal) - (idle - previdle)) / (total - prevtotal)))
	xsetroot -name "Date: $getdate | ^c#938AA9^mem: $getmem | ^c#FFA066^cpu: $getcpu % | ^c#6A9589^$getbat"
	sleep 10
done
