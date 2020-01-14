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

TESTS = testgeocoords

check_PROGRAMS = testgeocoords

testgeocoords_SOURCES = \
	TestCSCart.cc \
	TestCSGeo.cc \
	TestCSPicklerAscii.cc \
	TestConverter.cc \
	TestConverter_Cases.cc \
	test_driver.cc

#TestConverter.cc


testgeocoords_LDFLAGS =

testgeocoords_LDADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
	-lproj \
	-lcppunit -ldl \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)


# End of file
