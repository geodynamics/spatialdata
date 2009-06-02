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

dist_noinst_DATA = \
	spatialdb.dat \
	spatial_comments.dat \
	timehistory_comments.dat \
	timehistory.timedb

noinst_TMP = \
	spatial.dat \
	timehistory.dat

noinst_HEADERS = \
	header.hh

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
