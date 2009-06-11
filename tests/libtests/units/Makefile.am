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
	TestParser.cc \
	testunits.cc

noinst_HEADERS = \
	TestNondimensional.hh \
	TestParser.hh

AM_CPPFLAGS = \
	$(PETSC_INCLUDE) -I$(PYTHON_INCDIR) $(PYTHON_EGG_CPPFLAGS)

testunits_LDFLAGS = \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

testunits_LDADD = \
	$(top_builddir)/libsrc/libspatialdata.la \
	-lproj \
	-lcppunit -ldl \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)


# End of file 
