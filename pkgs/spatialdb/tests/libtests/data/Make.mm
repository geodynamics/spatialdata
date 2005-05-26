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
		--dumper.className=spatialdata::TestSimpleDBQuery \
		--dumper.filename=TestSimpleDBQuery.dat

TestSimpleDBPoint:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbpoint \
		--dumper.className=spatialdata::TestSimpleDBPoint \
		--dumper.filename=TestSimpleDBPoint.dat \

TestSimpleDBLine:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbline \
		--dumper.className=spatialdata::TestSimpleDBLine \
		--dumper.filename=TestSimpleDBLine.dat \

TestSimpleDBArea:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbarea \
		--dumper.className=spatialdata::TestSimpleDBArea \
		--dumper.filename=TestSimpleDBArea.dat \

TestSimpleDBVolume:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbvolume \
		--dumper.className=spatialdata::TestSimpleDBVolume \
		--dumper.filename=TestSimpleDBVolume.dat \

# ----------------------------------------------------------------------

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:43:07 baagaard Exp $

# End of file 
