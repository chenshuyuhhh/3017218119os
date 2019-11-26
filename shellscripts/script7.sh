#!/bin/bash

# 记录递归的根目录

listfile() {
    for file in ${1}/*; do
        if [ -f $file ]; then
            echo "$file"
        elif [ -d $file ]; then # 是目录的话，需要递归继续找
            echo "$file"
            listfile $file
        fi
    done
}

if [ $# = 0 ]; then
    rfile=$(
        #  cd $(dirname $0)
        pwd
    )
else
    rfile=$1
fi
echo $rfile
listfile $rfile
