# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
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
	SimpleGridDB.hh \
	SimpleGridDB.icc \
	GravityField.hh \
	GravityField.icc \
	SCECCVMH.hh \
	SCECCVMH.icc \
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
