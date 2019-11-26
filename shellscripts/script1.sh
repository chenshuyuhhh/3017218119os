#!/bin/bash

for i in {1..10}
do
  printf "%d: %d %d\n" $((i)) $((i*i)) $((i*i*i))
done
exit 0
