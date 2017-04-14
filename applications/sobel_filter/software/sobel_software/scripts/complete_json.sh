#!/bin/bash

filename=$1

mv $filename ${filename}.tmp
echo -n "[" > $filename
# remove final \n and ,
head -c -2 $filename.tmp >> $filename
echo "]" >> $filename
rm ${filename}.tmp
