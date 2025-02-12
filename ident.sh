#!/bin/sh

DIR="folly"

REGEXP="([a-zA-Z_][a-zA-Z0-9_])*"

for f in `find $DIR -name "*.cpp"`; do
    echo "*** File $f"
    grep -o -E $REGEXP $f
done
