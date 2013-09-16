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

subpackage = geocoords
include $(top_srcdir)/subpackage.am

SUBDIRS = data

TESTS = testgeocoords

check_PROGRAMS = testgeocoords

testgeocoords_SOURCES = \
	TestConverter.cc \
	TestCSCart.cc \
	TestCSGeo.cc \
	TestCSGeoLocalCart.cc \
	TestCSGeoProj.cc \
	TestCSPicklerAscii.cc \
	TestGeoid.cc \
	TestProjector.cc \
	testgeocoords.cc

noinst_HEADERS = \
	TestConverter.hh \
	TestCSCart.hh \
	TestCSGeo.hh \
	TestCSGeoLocalCart.hh \
	TestCSGeoProj.hh \
	TestCSPicklerAscii.hh \
	TestGeoid.hh \
	TestProjector.hh

testgeocoords_LDFLAGS =

INCLUDES +=

testgeocoords_LDADD = \
	$(top_builddir)/libsrc/libspatialdata.la \
	-lproj \
	-lcppunit -ldl \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)


# End of file 
