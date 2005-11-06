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

noinst_LTLIBRARIES = langtestspatialdatamodule.la

langtestspatialdatamodule_la_SOURCES = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	langtestspatialdb.cc

INCLUDES += -I$(PYTHON_INCDIR)

langtestspatialdatamodule_la_LDFLAGS = -module

langtestspatialdatamodule_la_LIBADD = \
	$(top_builddir)/pkgs/spatialdb/liblang/libspatialdatalang.la \
	$(top_builddir)/pkgs/spatialdb/lib/libspatialdata.la

# version
# $Id$

# End of file 
