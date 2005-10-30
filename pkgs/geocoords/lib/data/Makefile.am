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
include $(top_srcdir)/pkgs/subpackage.am

pkgdata_DATA = \
	ww15mgh.dac

# 'export' the input files by performing a mock install
export_datadir = $(subpkgdatadir)
export-data: $(pkgdata_DATA)
	$(mkinstalldirs) $(subpkgdatadir)
	for f in $(pkgdata_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

# export
BUILT_SOURCES = export-data

# version
# $Id: Makefile.am,v 1.2 2005/10/11 20:11:28 brad Exp $

# End of file 
