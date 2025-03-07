#!/bin/bash

input=$1
args=$2

new_args=../$(echo "$(cat "$args")" | cut -d'/' -f2-)

output="output_tmp.txt"

app=../../app.exe
if [ -f "$args" ]; then
    app="$app $new_args"
fi

if $app < "$input" > $output; then
    exit 1
else
    exit 0
fi