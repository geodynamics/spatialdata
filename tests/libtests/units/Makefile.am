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

subpackage = units
include $(top_srcdir)/subpackage.am

TESTS = testunits

check_PROGRAMS = testunits

testunits_SOURCES = \
	TestNondimensional.cc \
	testunits.cc

noinst_HEADERS = \
	TestNondimensional.hh

testunits_LDFLAGS =

testunits_LDADD = \
	-lcppunit -ldl \
	$(top_builddir)/libsrc/libspatialdata.la


# End of file 
