#!/bin/bash

pactl subscribe | while read -r line; do 
    pactl get-sink-volume 0 | awk '{printf "%s", $5; fflush()}'
    echo ""
done
