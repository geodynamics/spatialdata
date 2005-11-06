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

noinst_LTLIBRARIES = libf77testspatialdata.la

libf77testspatialdata_la_SOURCES = \
	f77testspatialdb.f

libf77testspatialdata_la_LDFLAGS =

INCLUDES +=

libf77testspatialdata_la_LIBADD = \
	$(top_builddir)/pkgs/spatialdb/liblang/libspatialdatalang.la \
	$(top_builddir)/pkgs/spatialdb/lib/libspatialdata.la

subpkginclude_HEADERS =

noinst_HEADERS = \
	f77testspatialdb.h

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# version
# $Id$

# End of file 
