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

SUBDIRS = data

TESTS = testspatial.py

noinst_PYTHON = \
	TestGenSimpleDBApp.py \
	TestSimpleIOAscii.py \
	TestSpatialDB.py \
	TestUniformDB.py \
	testspatial.py


data_DATA = \
	testgen1din2d.odb \
	testgen1din2d_one.odb \
	testgen1din2d_two.odb \
	gensimpledb.cfg

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/tests/pytests/spatialdb
export-data: $(data_DATA)
	for f in $(data_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

BUILT_SOURCES = export-data

CLEANFILES = \
	$(export_datadir)/$(data_DATA)

# End of file 
