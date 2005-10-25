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

lib_LTLIBRARIES = libspatialdatalang.la

libspatialdatalang_la_SOURCES = \
	cspatialdb.cc \
	f77spatialdb.cc

libspatialdatalang_la_LDFLAGS =

libspatialdatalang_la_LIBADD = \
	$(top_builddir)/pkgs/spatialdb/lib/libspatialdata.la

subpkginclude_HEADERS = \
	cspatialdb.h

noinst_HEADERS = \
	f77spatialdb.h

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# version
# $Id$

# End of file 
