#!/bin/bash
# -*- sh -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT


~/src/cig/pythia/bin/pyre_doc_components.py --package=SpatialData --src-path=$PYLITH_DIR/lib/python$PYTHON_VERSION/site-packages/spatialdata --output-path=./ --manual-toc=toc.json
cat index.md | sed -e "s#apps/index.md#implementations.md\\napps/index.md#g" > tmp.md && mv -f tmp.md index.md


# End of file
