#!/bin/sh

# Param 1 --> Width
# Param 2 --> Height
# Param 3 --> Map output

w=0
h=0

file="$3"

while [ $w -lt "$1" ] ; do

    while [ $h -lt "$2" ] ; do
    ((h++))
    done
    ((w++))
done
