# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# <LicenseText>
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
	-lcppunit -ldl \
	-lproj \
	$(top_builddir)/libsrc/libspatialdata.la

# version
# $Id$

# End of file 
