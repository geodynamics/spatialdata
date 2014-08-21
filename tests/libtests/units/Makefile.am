# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2014 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

include $(top_srcdir)/check.am

TESTS = testunits

check_PROGRAMS = testunits

testunits_SOURCES = \
	TestNondimensional.cc \
	TestParser.cc \
	testunits.cc

noinst_HEADERS = \
	TestNondimensional.hh \
	TestParser.hh

AM_CPPFLAGS += -I$(PYTHON_INCDIR) $(PYTHON_EGG_CPPFLAGS)

testunits_LDFLAGS = \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

testunits_LDADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
	-lproj \
	-lcppunit -ldl \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)


# End of file 
