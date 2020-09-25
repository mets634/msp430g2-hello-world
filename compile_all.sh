#!/bin/bash

make clean
for target in $(ls $(pwd)/source); do
    make build TARGET=$target >/dev/null
    if [ $? == 0 ]; then
        echo "Successfully compiled $target"
    else
        echo "Failed to compile $target"
        exit 1
    fi
done
echo "Successfully compiled all targets!"
