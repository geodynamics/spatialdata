#!/bin/bash

for suffix in .cc .icc .hh .h .am .py .i .odb .dat .in; do
  for f in `find . -name "*$suffix"` configure.ac aclocal.m4 CHANGES README COPYING; do
    sed -e "s/Copyright (c) 2010 University of California, Davis/Copyright (c) 2010-2015 University of California, Davis/g" $f > tmp && mv -f tmp $f
    sed -e "s/Copyright (c) 2010-2014 University of California, Davis/Copyright (c) 2010-2015 University of California, Davis/g" $f > tmp && mv -f tmp $f
  done
done
