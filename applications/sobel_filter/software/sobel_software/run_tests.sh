#!/bin/sh

tests=`find tests/* -executable`

for t in $tests
do
    $t
done

exit 0
