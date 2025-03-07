#!/bin/bash

input=$1
args=$2

new_args=../../$(echo "$(cat "$args")")

output="output_tmp.txt"

app=../../app.exe
if [ -f "$args" ]; then
    app="$app $new_args"
fi

if $app; then
    exit 1
else
    exit 0
fi