#!/bin/sh

DIR="folly"

REGEXP="\b(int|double|float|long|short)\b"

for f in `find $DIR -name "*.cpp"`; do
    echo "*** File $f"
    grep -o -E $REGEXP $f
done
