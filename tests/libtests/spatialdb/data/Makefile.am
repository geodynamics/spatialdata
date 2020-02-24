# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

dist_noinst_DATA = \
	spatialdb.dat \
	spatial_comments.dat \
	grid_line1d.spatialdb \
	grid_line2d.spatialdb \
	grid_line3d.spatialdb \
	grid_area2d.spatialdb \
	grid_area3d.spatialdb \
	grid_volume3d.spatialdb \
	timehistory_comments.dat \
	timehistory.timedb

noinst_TMP = \
	spatial.dat \
	grid.spatialdb \
	timehistory.data


# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/tests/libtests/spatialdb/data
export-data: $(dist_noinst_DATA)
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_noinst_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done; fi

clean-data:
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_noinst_DATA) $(noinst_TMP); do $(RM) $(RM_FLAGS) $(export_datadir)/$$f; done; fi

BUILT_SOURCES = export-data
clean-local: clean-data

datafiles:
	bash generate.sh all

# End of file 
