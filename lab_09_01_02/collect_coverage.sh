#!/bin/bash

gcov -o ./out/ ./src/*.c
mv ./*.gcov ./out/