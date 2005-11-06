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

data_DATA = \
	spatialdb.dat

noinst_HEADERS = \
	$(data_DATA)

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/pkgs/spatialdb/tests/langtests/data
export-data: $(data_DATA)
	for f in $(data_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

BUILT_SOURCES = export-data

CLEANFILES = \
	$(export_datadir)/$(data_DATA)

# version
# $Id$

# End of file 
