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
	CompositeDB.hh \
	Exception.hh \
	Exception.icc \
	GocadVoxet.hh \
	GravityField.hh \
	GravityField.icc \
	SCECCVMH.hh \
	SCECCVMH.icc \
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
	SimpleDBData.hh \
	SimpleDBData.icc \
	TimeHistory.hh \
	TimeHistory.icc \
	TimeHistoryIO.hh \
	UniformDB.hh \
	UniformDB.icc \
	spatialdbfwd.hh

noinst_HEADERS =

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS


# End of file 
