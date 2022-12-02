#!/bin/bash

for IN_FILE in tests/00{00..99} ; do
  if [ ! -e "${IN_FILE}_in.txt" ] ; then
    echo "All OK"
    exit 0
  fi
  ./prog06<"${IN_FILE}_in.txt" > /tmp/out.txt
  if ! diff -q "${IN_FILE}_out.txt" /tmp/out.txt ; then
    echo "Mismatch ${IN_FILE}_in.txt"
    exit 1
  fi
done