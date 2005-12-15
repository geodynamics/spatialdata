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
	TestSimpleDBArea.dat \
	TestSimpleDBLine.dat \
	TestSimpleDBPoint.dat \
	TestSimpleDBQuery.dat \
	TestSimpleDBVolume.dat

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/pkgs/spatialdb/tests/libtests/data
export-data: $(noinst_DATA)
	for f in $(noinst_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

BUILT_SOURCES = export-data

CLEANFILES = \
	$(export_datadir)/$(noinst_DATA) \
	$(export_datadir)/$(noinst_TMP)

datfiles: \
	TestSimpleDBQuery \
	TestSimpleDBPoint \
	TestSimpleDBLine \
	TestSimpleDBArea \
	TestSimpleDBVolume

TestSimpleDBQuery:
	TestSimpleDBQuery.py \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBQuery \
		--dumper.filename=TestSimpleDBQuery.dat

TestSimpleDBPoint:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbpoint \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBPoint \
		--dumper.filename=TestSimpleDBPoint.dat

TestSimpleDBLine:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbline \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBLine \
		--dumper.filename=TestSimpleDBLine.dat

TestSimpleDBArea:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbarea \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBArea \
		--dumper.filename=TestSimpleDBArea.dat

TestSimpleDBVolume:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbvolume \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBVolume \
		--dumper.filename=TestSimpleDBVolume.dat

# version
# $Id$

# End of file 
