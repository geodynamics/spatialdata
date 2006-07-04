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
include $(top_srcdir)/subpackage.am

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
	TestSimpleDBArea.hh \
	TestSimpleDB.hh \
	TestSimpleDBLine.hh \
	TestSimpleDBPoint.hh \
	TestSimpleDBQuery.hh \
	TestSimpleDBVolume.hh \
	TestSimpleIOAscii.hh \
	TestSpatialDB.hh

testspatial_LDFLAGS =

INCLUDES +=

testspatial_LDADD = \
	-lcppunit -ldl \
	$(top_builddir)/libsrc/spatialdb/libspatialdataspatialdb.la \
	$(top_builddir)/libsrc/geocoords/libspatialdatageocoords.la

# version
# $Id$

# End of file 
