#!/bin/bash

if [ "$1" == "y" ]||[[ "$1" == "yes" ]]||[[ "$1" == "YES" ]]||[[ "$1" == "Y" ]]
then 
  exit 0
else 
  exit 1
fi
