#!/bin/bash

pactl subscribe | while read -r line; do
	pactl get-sink-volume 0 | grep "Event \'change\' on sink " | awk '{printf "%s", $3; fflush()}'
	echo ""
done
