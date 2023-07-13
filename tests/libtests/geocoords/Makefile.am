# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2023 University of California, Davis
#
# See LICENSE.md for license information.
#
# ----------------------------------------------------------------------
#

include $(top_srcdir)/tests/check.am

TESTS = libtest_geocoords

check_PROGRAMS = libtest_geocoords

libtest_geocoords_SOURCES = \
	TestCSCart.cc \
	TestCSGeo.cc \
	TestCSPicklerAscii.cc \
	TestConverter.cc \
	TestConverter_Cases.cc \
	$(top_srcdir)/tests/src/driver_catch2.cc


noinst_HEADERS = \
	TestConverter.hh


# End of file
