# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

include $(top_srcdir)/tests/check.am

SUBDIRS = data

TESTS = libtest_spatialdb

check_PROGRAMS = libtest_spatialdb

libtest_spatialdb_SOURCES = \
    TestAnalyticDB.cc \
	TestUniformDB.cc \
	TestUserFunctionDB.cc \
	TestUserFunctionDB_Cases.cc \
	TestSimpleDBData.cc \
	TestSimpleIOAscii.cc \
	TestSimpleDBQuery.cc \
	TestSimpleDBQuery_Cases.cc \
	TestSimpleDB.cc \
	TestSimpleDB_Cases.cc \
	TestSimpleGridDB.cc \
	TestSimpleGridDB_Cases.cc \
	TestSimpleGridAscii.cc \
	TestCompositeDB.cc \
	TestSCECCVMH.cc \
	TestSpatialDB.cc \
	TestGravityField.cc \
	TestGravityField_Cases.cc \
	TestTimeHistoryIO.cc \
	TestTimeHistory.cc \
	$(top_srcdir)/tests/src/driver_catch2.cc


noinst_HEADERS = \
	TestGravityField.hh \
	TestSimpleDBQuery.hh \
	TestSimpleDB.hh \
	TestSimpleGridDB.hh \
	TestUserFunctionDB.hh

# End of file
