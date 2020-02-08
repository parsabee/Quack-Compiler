#!/bin/bash

if [[ $# != 1 ]]; then
  echo "usage: test.sh <qkc binary>"
  exit 1
fi

status=0
for file in bads/*
do
  echo "testing " $file
  $1 $file > /dev/null 2>&1
  if [[ $? != 1 ]] ; then
    echo -e "[FAIL]\n\n"
    echo "failed test: " $file
    status=1
  else
    echo "[PASS]"
  fi
done
exit $status