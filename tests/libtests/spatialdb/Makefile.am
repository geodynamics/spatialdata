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
	TestSimpleDBQuery3D.cc \
	TestSimpleDB.cc \
	TestSimpleDBPoint3D.cc \
	TestSimpleDBLine3D.cc \
	TestSimpleDBArea3D.cc \
	TestSimpleDBVolume3D.cc \
	TestSimpleIOAscii.cc \
	TestSpatialDB.cc \
	testcquery.c \
	testspatial.cc

noinst_HEADERS = \
	TestSimpleDBQuery.hh \
	TestSimpleDBQuery3D.cc \
	TestSimpleDB.hh \
	TestSimpleDBPoint3D.hh \
	TestSimpleDBLine3D.hh \
	TestSimpleDBArea3D.hh \
	TestSimpleDBVolume3D.hh \
	TestSimpleIOAscii.hh \
	testcquery.h \
	TestSpatialDB.hh


testspatial_LDFLAGS =

INCLUDES +=

testspatial_LDADD = \
	-lcppunit -ldl \
	$(top_builddir)/libsrc/spatialdb/libspatialdataspatialdb.la \
	$(top_builddir)/libsrc/geocoords/libspatialdatageocoords.la


# Source files associated with testing data
testspatial_SOURCES += \
	data/SimpleDBQueryData.cc \
	data/SimpleDBQueryData3D.cc \
	data/SimpleDBData.cc \
	data/SimpleDBDataPoint3D.cc \
	data/SimpleDBDataLine3D.cc \
	data/SimpleDBDataArea3D.cc \
	data/SimpleDBDataVolume3D.cc

noinst_HEADERS += \
	data/SimpleDBQueryData.hh \
	data/SimpleDBQueryData3D.hh \
	data/SimpleDBData.hh \
	data/SimpleDBDataPoint3D.hh \
	data/SimpleDBDataLine3D.hh \
	data/SimpleDBDataArea3D.hh \
	data/SimpleDBDataVolume3D.hh


# End of file 
