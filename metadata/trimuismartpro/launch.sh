#!/bin/sh
echo $0 $*
PROGDIR=/mnt/SDCARD/Apps/puzzleland

cd $PROGDIR
HOME=$PROGDIR/ ./game -f
