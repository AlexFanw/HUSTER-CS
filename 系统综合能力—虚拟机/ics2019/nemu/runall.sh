#!/bin/bash

ISA=${1#*ISA=}
nemu=build/$ISA-nemu

echo "compiling NEMU..."
if make ISA=$ISA; then
  echo "NEMU compile OK"
else
  echo "NEMU compile error... exit..."
  exit
fi

echo "compiling testcases..."
if make -C $AM_HOME/tests/cputest ARCH=$ISA-nemu &> /dev/null; then
  echo "testcases compile OK"
else
  echo "testcases compile error... exit..."
  exit
fi

files=`ls $AM_HOME/tests/cputest/build/*-$ISA-nemu.bin`
ori_log="build/nemu-log.txt"

for file in $files; do
  base=`basename $file | sed -e "s/-$ISA-nemu.bin//"`
  printf "[%14s] " $base
  logfile=$base-log.txt
  make ISA=$ISA run ARGS="-b -l $ori_log $file" &> $logfile

  if (grep 'nemu: .*HIT GOOD TRAP' $logfile > /dev/null) then
    echo -e "\033[1;32mPASS!\033[0m"
    rm $logfile
  else
    echo -e "\033[1;31mFAIL!\033[0m see $logfile for more information"
    if (test -e $ori_log) then
      echo -e "\n\n===== the original log.txt =====\n" >> $logfile
      cat $ori_log >> $logfile
    fi
  fi
done
