#!/bin/bash

i=$#
while (( $i > 0 ))
do
    str="echo -en \$$i"
    eval $str
    echo -en " "

    (( i=$i-1 ))
done
echo ""
exit 0