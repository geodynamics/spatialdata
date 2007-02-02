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
	SimpleDBQuery.hh \
	SimpleDBTypes.hh \
	SimpleDBTypes.icc

noinst_HEADERS =

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS


# End of file 
