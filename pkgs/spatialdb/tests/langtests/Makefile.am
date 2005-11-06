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
include $(top_srcdir)/pkgs/subpackage.am

TESTS = testlangspatial.py

check_SCRIPTS = testlangspatial.py

lib_LTLIBRARIES = \
	langtestspatialdbmodule.la

noinst_HEADERS = \
	ctestspatialdb.h \
	f77testspatialdb.h

langtestspatialdbmodule_la_SOURCES = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	ctestspatialdb.c \
	f77testspatialdb.f \
	langtestspatialdb.cc \
	langtestspatialdbmodule.cc

INCLUDES += -I$(PYTHON_INCDIR)

langtestspatialdbmodule_la_LDFLAGS = -module

langtestspatialdbmodule_la_LIBADD = \
	$(top_builddir)/pkgs/spatialdb/liblang/libspatialdatalang.la \
	$(top_builddir)/pkgs/spatialdb/lib/libspatialdata.la \
	-lpythiautil

noinst_PYTHON = \
	TestSpatialDB.py \
	testlangspatial.py

# version
# $Id$

# End of file 
