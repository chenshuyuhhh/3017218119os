#!/bin/bash

if [ $# -lt $MAXFILE ]
then
    for i in 1 ... $#; do
        rm $$i
    done
else
    for i in $(seq 1 $#); do
        echo "Are you sure ?"
        read yorn
        if [ $yorn == 'y' ]; then
            str="rm \$$i"
            eval $str
        fi
    done
fi
