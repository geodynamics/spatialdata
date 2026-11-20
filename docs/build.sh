#!/bin/bash
# -*- sh -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT 


formats=("html")
if [ $# -gt 0 ]; then
    formats="$@"
fi

SRC_DIR=.
BUILD_DIR=_build

for format in ${formats[*]}; do
    sphinx-build -b ${format} ${SRC_DIR} ${BUILD_DIR}/${format}
done

exit 0


# End of file
