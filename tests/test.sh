#!/bin/sh

for file in maps/* ; do
    SECONDS=0
    res=$(timeout 4s ./check $file)
    echo "$res" > results
    res=$(tail -1 results)
    echo "$res"

    if [[ "$res" ~= 'crashed' ]] ; then
        echo "Crashed"
    else
        echo "Success"
    fi
done

echo "Executed all tests"
rm results
