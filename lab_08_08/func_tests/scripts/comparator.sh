#!/bin/bash

res1=$(< "$1")
res2=$(< "$2")

if [ "$res1" == "$res2" ]; then
    exit 0
else
    exit 1
fi
