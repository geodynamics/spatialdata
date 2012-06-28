# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

subpackage = spatialdb
include $(top_srcdir)/subpackage.am

SUBDIRS = data

TESTS = testspatial

check_PROGRAMS = testspatial

testspatial_SOURCES = \
	TestCompositeDB.cc \
	TestGravityField.cc \
	TestSCECCVMH.cc \
	TestSimpleDBData.cc \
	TestSimpleDBQuery.cc \
	TestSimpleDBQuery3D.cc \
	TestSimpleDB.cc \
	TestSimpleDBPoint3D.cc \
	TestSimpleDBLine3D.cc \
	TestSimpleDBArea3D.cc \
	TestSimpleDBVolume3D.cc \
	TestSimpleIOAscii.cc \
	TestSpatialDB.cc \
	TestTimeHistory.cc \
	TestTimeHistoryIO.cc \
	TestUniformDB.cc \
	TestGeoProjGridDB.cc \
	TestGeoProjGridDBCases.cc \
	testcquery.c \
	testspatial.cc

noinst_HEADERS = \
	TestCompositeDB.hh \
	TestGravityField.hh \
	TestSCECCVMH.hh \
	TestSimpleDBData.hh \
	TestSimpleDBQuery.hh \
	TestSimpleDBQuery3D.hh \
	TestSimpleDB.hh \
	TestSimpleDBPoint3D.hh \
	TestSimpleDBLine3D.hh \
	TestSimpleDBArea3D.hh \
	TestSimpleDBVolume3D.hh \
	TestSimpleIOAscii.hh \
	TestTimeHistory.hh \
	TestTimeHistoryIO.hh \
	TestUniformDB.hh \
	TestGeoProjGridDB.hh \
	TestGeoProjGridDBCases.hh \
	testcquery.h \
	TestSpatialDB.hh


testspatial_LDFLAGS =

AM_CPPFLAGS = $(PYTHON_EGG_CPPFLAGS) -I$(PYTHON_INCDIR) 

testspatial_LDADD = \
	$(top_builddir)/libsrc/libspatialdata.la \
	-lproj \
	-lcppunit -ldl \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)


# Source files associated with testing data
testspatial_SOURCES += \
	data/SimpleDBQueryData.cc \
	data/SimpleDBQueryData3D.cc \
	data/SimpleDBTestData.cc \
	data/SimpleDBTestDataPoint3D.cc \
	data/SimpleDBTestDataLine3D.cc \
	data/SimpleDBTestDataArea3D.cc \
	data/SimpleDBTestDataVolume3D.cc \
	data/GeoProjGridDBTestData.cc \
	data/GeoProjGridDBTestDataVolume3D.cc

noinst_HEADERS += \
	data/SimpleDBQueryData.hh \
	data/SimpleDBQueryData3D.hh \
	data/SimpleDBTestData.hh \
	data/SimpleDBTestDataPoint3D.hh \
	data/SimpleDBTestDataLine3D.hh \
	data/SimpleDBTestDataArea3D.hh \
	data/SimpleDBTestDataVolume3D.hh \
	data/GeoProjGridDBTestData.hh \
	data/GeoProjGridDBTestDataVolume3D.hh


# End of file 
