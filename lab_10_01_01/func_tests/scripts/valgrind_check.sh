#!/bin/bash


input=$1
valgrind_out="valgrind_out_temp.txt"
program_out="temp.txt"

valgrind valgrind --leak-check=full ../../app.exe < "$input" > $program_out 2> $valgrind_out
string="$(cat $valgrind_out)"

if [[ $string == *"no leaks are possible"* ]]; then
    exit 0
else
    exit 1
fi