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

subpackage = units
include $(top_srcdir)/subpackage.am

subpkginclude_HEADERS = \
	NondimElastic.hh \
	NondimElastic.icc

noinst_HEADERS =

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# End of file 
