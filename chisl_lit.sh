#!/bin/sh

DIR="folly"

REGEXP="\b[0-9]+('?[0-9]+)*(u|U|l|L|ll|LL|z|Z)?\b"

for f in `find $DIR -name "*.cpp"`; do
    echo "*** File $f"
    grep -o -E $REGEXP $f
done
