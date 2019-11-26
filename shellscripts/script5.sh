#!/bin/bash

if [ -d $1 ] # 如果是目录
then
  ls $1
elif [ -x $1 ] # 如果是可执行文件
then
  $1 
elif [ -r $1 ] # 如果是可读文件
then
  cat $1
else
  echo "no suitable condition."
fi
exit 0