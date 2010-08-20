# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

subpackage = geocoords
include $(top_srcdir)/subpackage.am

dist_subpkgdata_DATA = \
	ww15mgh.dac

# 'export' the input files by performing a mock install
export_datadir = $(subpkgdatadir)
export-data: $(dist_subpkgdata_DATA)
	$(mkinstalldirs) $(subpkgdatadir)
	for f in $(dist_subpkgdata_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

# export
BUILT_SOURCES = export-data


# End of file 
