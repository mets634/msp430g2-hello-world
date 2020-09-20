#!/bin/bash

TARGETS="button_blink timer_blink"

make clean
for target in $TARGETS; do
    make build TARGET=$target >/dev/null
    if [ $? == 0 ]; then
        echo "Successfully compiled $target"
    else
        echo "Failed to compile $target"
        exit 1
    fi
done
echo "Successfully compiled all targets!"
