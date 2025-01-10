# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

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
