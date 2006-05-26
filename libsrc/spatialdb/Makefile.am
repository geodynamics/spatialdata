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
include $(top_srcdir)/subpackage.am

lib_LTLIBRARIES = libspatialdataspatialdb.la

libspatialdataspatialdb_la_SOURCES = \
	SimpleDB.cc \
	SpatialDB.cc \
	SimpleDBQuery.cc \
	SimpleIO.cc \
	SimpleIOAscii.cc \
	cspatialdb.cc \
	f77spatialdb.cc

libspatialdataspatialdb_la_LDFLAGS =

INCLUDES +=

libspatialdataspatialdb_la_LIBADD = \
	$(top_builddir)/libsrc/geocoords/libspatialdatageocoords.la

subpkginclude_HEADERS = \
	Exception.hh \
	Exception.icc \
	SpatialDB.hh \
	SpatialDB.icc \
	SimpleDB.hh \
	SimpleDB.icc \
	SimpleIO.hh \
	SimpleIO.icc \
	SimpleIOAscii.hh \
	SimpleIOAscii.icc \
	cspatialdb.h \
	f77spatialdb.h \
	SimpleDBQuery.hh \
	SimpleDBTypes.hh \
	SimpleDBTypes.icc

noinst_HEADERS =

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# version
# $Id$

# End of file 
