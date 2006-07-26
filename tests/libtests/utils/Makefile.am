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

INCLUDES +=

testutils_LDADD = \
	-lcppunit -ldl \
	$(top_builddir)/libsrc/utils/libspatialdatautils.la

# version
# $Id$

# End of file 
