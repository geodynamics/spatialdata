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

data_DATA = \
	spatialdb.dat \
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
	gen1Din2D.spatialdb

noinst_HEADERS = \
	$(data_DATA)

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/tests/pytests/spatialdb/data
export-data: $(data_DATA)
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(data_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done; fi

clean-data:
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(data_DATA); do $(RM) $(RM_FLAGS) $(export_datadir)/$$f; done; fi

BUILT_SOURCES = export-data
clean-local: clean-data

CLEANFILES = \
	$(export_datadir)/$(data_CLEAN)


# End of file 
