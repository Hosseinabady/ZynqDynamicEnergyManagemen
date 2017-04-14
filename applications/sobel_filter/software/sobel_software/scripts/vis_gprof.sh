#!/bin/bash

exe=$1


gprof $1 gmon.out > $1.prof
gprof2dot.py $1.prof >$1.prof.dot.badres
# put a better resolution

cat $1.prof.dot.badres | sed -e "s/^\(\s*\)graph \[/\1graph \[dpi=300, /g" > $1.prof.dot
rm $1.prof.dot.badres
dot -Tpng $1.prof.dot > $1.prof.png

eog $1.prof.png
