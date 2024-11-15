#!/bin/bash

pactl subscribe | while read -r line; do
	# Check if the line indicates a sink volume change event
	if echo "$line" | grep -q "Event 'change' on sink"; then
		# Get the current volume of the specified sink
		pactl get-sink-volume 0 | awk '/Volume:/ {print substr($5, 1, length($5)-1)}'
	fi
done
