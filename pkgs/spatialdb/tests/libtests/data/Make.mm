# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ----------------------------------------------------------------------
#

PROJECT = spatialdata
PACKAGE = spatialdb/tests/libtests/data

default all:

datfiles: \
	TestSimpleDBQuery \
	TestSimpleDBPoint \
	TestSimpleDBLine \
	TestSimpleDBArea \
	TestSimpleDBVolume \

TestSimpleDBQuery:
	TestSimpleDBQuery.py \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBQuery \
		--dumper.filename=TestSimpleDBQuery.dat

TestSimpleDBPoint:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbpoint \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBPoint \
		--dumper.filename=TestSimpleDBPoint.dat \

TestSimpleDBLine:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbline \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBLine \
		--dumper.filename=TestSimpleDBLine.dat \

TestSimpleDBArea:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbarea \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBArea \
		--dumper.filename=TestSimpleDBArea.dat \

TestSimpleDBVolume:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbvolume \
		--dumper.className=spatialdata::spatialdb::TestSimpleDBVolume \
		--dumper.filename=TestSimpleDBVolume.dat \

# ----------------------------------------------------------------------

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:43:07 baagaard Exp $

# End of file 
