# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2023 University of California, Davis
#
# See LICENSE.md for license information.
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
	TestSimpleDBQuery.cc \
	TestSimpleDBQuery_Cases.cc \
	TestSimpleDB.cc \
	TestSimpleDB_Cases.cc \
	TestSimpleGridAscii.cc \
	TestSimpleGridDB.cc \
	TestSimpleGridDB_Cases.cc \
	TestCompositeDB.cc \
	TestSCECCVMH.cc \
	TestGravityField.cc \
	TestGravityField_Cases.cc \
	TestTimeHistoryIO.cc \
	TestTimeHistory.cc \
	test_driver.cc

noinst_HEADERS = \
	TestGravityField.hh \
	TestSimpleDBQuery.hh \
	TestSimpleDB.hh \
	TestSimpleGridDB.hh \
	TestUserFunctionDB.hh \
	TestSpatialDB.hh


testspatial_LDFLAGS =

AM_CPPFLAGS += -I$(PYTHON_INCDIR) 

testspatial_LDADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
	-lproj \
	-lcppunit -ldl \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)


# End of file
