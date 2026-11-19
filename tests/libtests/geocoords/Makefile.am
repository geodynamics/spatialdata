# -*- makefile -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT 


include $(top_srcdir)/tests/check.am

TESTS = libtest_geocoords

check_PROGRAMS = libtest_geocoords

libtest_geocoords_SOURCES = \
	TestCSCart.cc \
	TestCSGeo.cc \
	TestCSGeoLocal.cc \
	TestCSPicklerAscii.cc \
	TestConverter.cc \
	TestConverter_Cases.cc \
	$(top_srcdir)/tests/src/driver_catch2.cc


noinst_HEADERS = \
	TestConverter.hh


# End of file
