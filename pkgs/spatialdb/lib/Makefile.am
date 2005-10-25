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

lib_LTLIBRARIES = libspatialdata.la

libspatialdata_la_SOURCES = \
	SimpleDB.cc \
	SpatialDB.cc \
	SimpleDBQuery.cc \
	SimpleIO.cc \
	SimpleIOAscii.cc

libspatialdata_la_LDFLAGS =

INCLUDES +=

libspatialdata_la_LIBADD = \
	$(top_builddir)/pkgs/geocoords/lib/libspatialdatageocoords.la

subpkginclude_HEADERS = \
	SpatialDB.h \
	SpatialDB.icc \
	SimpleDB.h \
	SimpleDB.icc \
	SimpleIO.h \
	SimpleIO.icc \
	SimpleIOAscii.h \
	SimpleIOAscii.icc

noinst_HEADERS =

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# version
# $Id$

# End of file 
