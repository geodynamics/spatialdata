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

lib_LTLIBRARIES = libctestspatialdata.la

libctestspatialdata_la_SOURCES = \
	ctestspatialdb.c

libctestspatialdata_la_LDFLAGS =

INCLUDES +=

libctestspatialdata_la_LIBADD = \
	$(top_builddir)/pkgs/geocoords/lib/libspatialdatalang.la \
	$(top_builddir)/pkgs/geocoords/lib/libspatialdata.la

subpkginclude_HEADERS =

noinst_HEADERS = \
	ctestspatialdb.h

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# version
# $Id$

# End of file 
