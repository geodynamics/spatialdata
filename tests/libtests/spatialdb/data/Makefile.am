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

noinst_DATA = \
	spatialdb.dat

noinst_TMP = \
	spatial.dat

noinst_HEADERS = \
	header.hh

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/tests/libtests/spatialdb/data
export-data: $(noinst_DATA)
	for f in $(noinst_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

BUILT_SOURCES = export-data

CLEANFILES = \
	$(export_datadir)/$(noinst_DATA) \
	$(export_datadir)/$(noinst_TMP)

datafiles:
	bash generate.sh all

# End of file 
