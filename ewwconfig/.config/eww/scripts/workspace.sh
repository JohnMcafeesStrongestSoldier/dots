#!/usr/bin/env bash

function all_ws {
	wmctrl -d |
		cut -d " " -f1
}

function active_ws {
	wmctrl -d |
		grep "*" |
		cut -d " " -f1
}

function occupied_ws {
	wmctrl -l |
		cut -d " " -f3 |
		sort -u
}

box_attrs=':orientation "h" :class "workspaces" :space-evenly false :halign "start" :spacing 0'
function eww_buttons {
	button=""
	for ws in $(all_ws); do
		icon="$((ws + 1))"
		class="empty"
		if [ "${ws}" = "$(active_ws)" ]; then
			class="active"
		else
			for workspace in $(occupied_ws); do
				if [ "${ws}" = "${workspace}" ]; then
					class="occupied"
					break
				fi
			done
		fi
		button+="(button :class \"${class}\" :onclick \"wmctrl -s ${ws}\" \"${icon}\")"
	done
	echo "(box ${box_attrs} ${button})"
}

xprop -spy -root _NET_CURRENT_DESKTOP | while read -r; do
	eww_buttons
done
