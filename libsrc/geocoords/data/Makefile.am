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

subpackage = geocoords
include $(top_srcdir)/subpackage.am

subpkgdata_DATA = \
	ww15mgh.dac

# 'export' the input files by performing a mock install
export_datadir = $(subpkgdatadir)
export-data: $(subpkgdata_DATA)
	$(mkinstalldirs) $(subpkgdatadir)
	for f in $(subpkgdata_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

# export
BUILT_SOURCES = export-data

# version
# $Id$

# End of file 
