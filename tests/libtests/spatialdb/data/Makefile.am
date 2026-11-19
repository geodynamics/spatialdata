# -*- makefile -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT 


dist_noinst_DATA = \
	spatialdb.dat \
	spatial_comments.dat \
	grid_line1d.spatialdb \
	grid_line2d.spatialdb \
	grid_line3d.spatialdb \
	grid_area2d.spatialdb \
	grid_area3d.spatialdb \
	grid_volume3d.spatialdb \
	grid_comments.spatialdb \
	timehistory_comments.dat \
	timehistory.timedb

noinst_TMP = \
	spatial.dat \
	grid_xyz.spatialdb \
	grid_geo.spatialdb \
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
