# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

dist_noinst_DATA = \
	simple.spatialdb \
	grid.spatialdb \
	test_okay.timedb \
	timehistory.timedb \
	gen1Din2D_one_bg.spatialdb \
	gen1Din2D_one_add.spatialdb \
	gen1Din2D_one_multiply.spatialdb \
	gen1Din2D_two_bg.spatialdb \
	gen1Din2D_two_subtract.spatialdb \
	gen1Din2D_two_divide.spatialdb

data_CLEAN = \
	test.spatialdb \
	test.timedb \
	gen1Din2D.spatialdb \
	gridio3d.spatialdb \
	gridio2d.spatialdb


# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/tests/pytests/spatialdb/data
export-data: $(dist_noinst_DATA)
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_noinst_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done; fi

clean-data:
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_noinst_DATA); do $(RM) $(RM_FLAGS) $(export_datadir)/$$f; done; fi

BUILT_SOURCES = export-data
clean-local: clean-data

CLEANFILES = \
	$(export_datadir)/$(data_CLEAN)


# End of file
