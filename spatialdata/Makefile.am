# -*- makefile -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT 


if PIP_BUILD_ISOLATION
else
PIP_ISOLATION_FLAG=--no-build-isolation
endif
install-exec-local:
	$(PYTHON) -m pip install --prefix=$(prefix) $(PIP_ISOLATION_FLAG) $(top_srcdir)

EXTRA_DIST = \
	__init__.py \
	geocoords/CSCart.py \
	geocoords/CSGeo.py \
	geocoords/CSGeoLocal.py \
	geocoords/Converter.py \
	geocoords/CoordSys.py \
	geocoords/__init__.py \
	spatialdb/AnalyticDB.py \
	spatialdb/CompositeDB.py \
	spatialdb/GravityField.py \
	spatialdb/SCECCVMH.py \
	spatialdb/SimpleDB.py \
	spatialdb/SimpleGridAscii.py \
	spatialdb/SimpleGridDB.py \
	spatialdb/SimpleIO.py \
	spatialdb/SimpleIOAscii.py \
	spatialdb/SpatialDBObj.py \
	spatialdb/TimeHistory.py \
	spatialdb/TimeHistoryIO.py \
	spatialdb/UniformDB.py \
	spatialdb/AnalyticDB.py \
	spatialdb/UserFunctionDB.py \
	spatialdb/__init__.py \
	spatialdb/generator/GenSimpleDBApp.py \
	spatialdb/generator/Geometry.py \
	spatialdb/generator/Shaper.py \
	spatialdb/generator/Value.py \
	spatialdb/generator/__init__.py \
	testing/__init__.py \
	testing/UnitTestApp.py \
	testing/TestCases.py \
	utils/PointsStream.py \
	utils/__init__.py


# End of file 
