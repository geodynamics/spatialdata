#!/bin/bash

for suffix in .cc .icc .hh .h .am .py .i .odb .dat .in *.ac; do
  for f in `find . -name "*$suffix"` aclocal.m4 CHANGES README COPYING; do
    sed -e "s/Copyright (c) 2010-2017 University of California, Davis/Copyright (c) 2010-2017 University of California, Davis/g" $f > tmp && mv -f tmp $f
  done
done
