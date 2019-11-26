#!/bin/bash

for ((i = $#; i > 0; i--)); do
    str="echo -en \$$i"
    eval $str
    echo -en " "

   #((i = $i - 1))
done
echo ""
