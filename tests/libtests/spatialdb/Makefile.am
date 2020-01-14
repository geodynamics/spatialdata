# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

include $(top_srcdir)/check.am

SUBDIRS = data

TESTS = testspatial

check_PROGRAMS = testspatial

testspatial_SOURCES = \
	TestUniformDB.cc \
	TestUserFunctionDB.cc \
	TestUserFunctionDB_Cases.cc \
	TestSimpleDBData.cc \
	TestSimpleIOAscii.cc \
	TestTimeHistoryIO.cc \
	TestTimeHistory.cc \
	test_driver.cc


# TestCompositeDB.cc \
# TestGravityField.cc \
# TestSCECCVMH.cc

# TestSimpleDBQuery.cc \
# TestSimpleDBQuery3D.cc

# TestSimpleDB.cc \
# TestSimpleDBPoint3D.cc \
# TestSimpleDBLine3D.cc \
# TestSimpleDBArea3D.cc \
# TestSimpleDBVolume3D.cc

# TestSpatialDB.cc 

# TestSimpleGridDB.cc \
# TestSimpleGridDBCases.cc 



noinst_HEADERS = \
	TestCompositeDB.hh \
	TestGravityField.hh \
	TestSCECCVMH.hh \
	TestSimpleDBQuery.hh \
	TestSimpleDBQuery3D.hh \
	TestSimpleDB.hh \
	TestSimpleDBPoint3D.hh \
	TestSimpleDBLine3D.hh \
	TestSimpleDBArea3D.hh \
	TestSimpleDBVolume3D.hh \
	TestSimpleGridDB.hh \
	TestSimpleGridDBCases.hh \
	TestUserFunctionDB.hh \
	TestSpatialDB.hh


testspatial_LDFLAGS =

AM_CPPFLAGS += $(PYTHON_EGG_CPPFLAGS) -I$(PYTHON_INCDIR) 

testspatial_LDADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
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
	data/SimpleGridDBTestData.cc \
	data/SimpleGridDBTestDataLine1D.cc \
	data/SimpleGridDBTestDataLine2D.cc \
	data/SimpleGridDBTestDataLine3D.cc \
	data/SimpleGridDBTestDataArea2D.cc \
	data/SimpleGridDBTestDataArea3D.cc \
	data/SimpleGridDBTestDataVolume3D.cc

noinst_HEADERS += \
	data/SimpleDBQueryData.hh \
	data/SimpleDBQueryData3D.hh \
	data/SimpleDBTestData.hh \
	data/SimpleDBTestDataPoint3D.hh \
	data/SimpleDBTestDataLine3D.hh \
	data/SimpleDBTestDataArea3D.hh \
	data/SimpleDBTestDataVolume3D.hh \
	data/SimpleGridDBTestData.hh \
	data/SimpleGridDBTestDataLine1D.hh \
	data/SimpleGridDBTestDataLine2D.hh \
	data/SimpleGridDBTestDataLine3D.hh \
	data/SimpleGridDBTestDataArea2D.hh \
	data/SimpleGridDBTestDataArea3D.hh \
	data/SimpleGridDBTestDataVolume3D.hh


# End of file 
