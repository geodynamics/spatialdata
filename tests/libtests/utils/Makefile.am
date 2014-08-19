# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

include $(top_srcdir)/check.am

SUBDIRS = data

TESTS = testutils

check_PROGRAMS = testutils

testutils_SOURCES = \
	TestPointsStream.cc \
	testutils.cc

noinst_HEADERS = \
	TestPointsStream.hh

testutils_LDFLAGS =

testutils_LDADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
	-lproj \
	-lcppunit -ldl \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)


# End of file 
