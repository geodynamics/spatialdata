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
include $(top_srcdir)/pkgs/subpackage.am

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
	TestConverter.h \
	TestCSCart.h \
	TestCSGeo.h \
	TestCSGeoLocalCart.h \
	TestCSGeoProj.h \
	TestCSPicklerAscii.h \
	TestGeoid.h \
	TestProjector.h

testgeocoords_LDFLAGS =

INCLUDES +=

testgeocoords_LDADD = \
	-lcppunit -ldl \
	-lproj \
	$(top_builddir)/pkgs/geocoords/lib/libspatialdatageocoords.la

if ENABLE_PYTHIA
testgeocoords_LDADD += -lpythiautil
endif

# version
# $Id$

# End of file 
