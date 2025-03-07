#!/bin/bash

input=$1
output_exp=$2
args=$3
output="output_tmp.txt"

new_args=../$(echo "$(cat "$args")" | cut -d'/' -f2-)

app=../../app.exe
if [ -f "$args" ]; then
    app="$app $new_args"
fi

if $app < "$input" > $output; then
    if bash ./comparator.sh "$output" "$output_exp"; then
        exit 0
    else
        exit 1
    fi
else
    exit 1
fi