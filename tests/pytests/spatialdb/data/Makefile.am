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
	spatialdb.dat \
	gen1Din2D_one_bg.spatialdb \
	gen1Din2D_one_add.spatialdb \
	gen1Din2D_one_multiply.spatialdb \
	gen1Din2D_two_bg.spatialdb \
	gen1Din2D_two_subtract.spatialdb \
	gen1Din2D_two_divide.spatialdb

data_CLEAN = \
	test.spatialdb \
	gen1Din2D.spatialdb

noinst_HEADERS = \
	$(data_DATA)

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/tests/pytests/spatialdb/data
export-data: $(data_DATA)
	for f in $(data_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

BUILT_SOURCES = export-data

CLEANFILES = \
	$(export_datadir)/$(data_DATA) \
	$(export_datadir)/$(data_CLEAN)


# End of file 
