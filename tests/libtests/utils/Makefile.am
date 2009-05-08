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

subpackage = utils
include $(top_srcdir)/subpackage.am

SUBDIRS = data

TESTS = testutils

check_PROGRAMS = testutils

testutils_SOURCES = \
	TestPointsStream.cc \
	testutils.cc

noinst_HEADERS = \
	TestPointsStream.hh

testutils_LDFLAGS =

testutils_LDADD = \
	-lcppunit -ldl \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS) \
	$(top_builddir)/libsrc/libspatialdata.la


# End of file 
