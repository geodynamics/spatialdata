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

subpackage = spatialdb
include $(top_srcdir)/pkgs/subpackage.am

SUBDIRS = data

TESTS = testspatial

check_PROGRAMS = testspatial

testspatial_SOURCES = \
	TestSimpleDBQuery.cc \
	TestSimpleDB.cc \
	TestSimpleDBPoint.cc \
	TestSimpleDBLine.cc \
	TestSimpleDBArea.cc \
	TestSimpleDBVolume.cc \
	TestSimpleIOAscii.cc \
	TestSpatialDB.cc \
	testspatial.cc

noinst_HEADERS = \
	TestSimpleDBArea.h \
	TestSimpleDB.h \
	TestSimpleDBLine.h \
	TestSimpleDBPoint.h \
	TestSimpleDBQuery.h \
	TestSimpleDBVolume.h \
	TestSimpleIOAscii.h \
	TestSpatialDB.h

testspatial_LDFLAGS =

INCLUDES +=

testspatial_LDADD = \
	-lcppunit -ldl \
	$(top_builddir)/pkgs/spatialdb/lib/libspatialdata.la \
	$(top_builddir)/pkgs/geocoords/lib/libspatialdatageocoords.la

# version
# $Id$

# End of file 
