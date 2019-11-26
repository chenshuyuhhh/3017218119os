#! /bin/bash

#将自变量形式给出的目录下的全部普通文件名和权限列出
# 对于目录变量下的每一个文件
for i in $1/*
do
if [ -f "$i" ]
# 如果是文件
then
# 找出文件权限，为1-10个字符
j=`ls -l "$i"|cut -c 1-10`
# 输出文件权限和文件名
echo -e "$j\t$i"
fi
done 