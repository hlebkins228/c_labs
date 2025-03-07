#!/bin/bash

pwd

cd func_tests/scripts/
bash func_tests.sh
cd ../..
bash ./collect_coverage.sh