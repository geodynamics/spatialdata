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

PROJECT = spatialdata/tests
PACKAGE = libtests/data

default all:

datfiles: \
	TestSimpleDBQuery \
	TestSimpleDBPoint \
	TestSimpleDBLine \
	TestSimpleDBArea \
	TestSimpleDBVolume \

TestSimpleDBQuery:
	TestSimpleDBQuery.py \
		--dumper.className=spatial::TestSimpleDBQuery \
		--dumper.filename=TestSimpleDBQuery.dat

TestSimpleDBPoint:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbpoint \
		--dumper.className=spatial::TestSimpleDBPoint \
		--dumper.filename=TestSimpleDBPoint.dat \

TestSimpleDBLine:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbline \
		--dumper.className=spatial::TestSimpleDBLine \
		--dumper.filename=TestSimpleDBLine.dat \

TestSimpleDBArea:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbarea \
		--dumper.className=spatial::TestSimpleDBArea \
		--dumper.filename=TestSimpleDBArea.dat \

TestSimpleDBVolume:
	TestSimpleDBDataApp.py \
		--query_data=testsimpledbvolume \
		--dumper.className=spatial::TestSimpleDBVolume \
		--dumper.filename=TestSimpleDBVolume.dat \

# ----------------------------------------------------------------------

# version
# $Id: Make.mm,v 1.1 2005/03/17 22:18:34 baagaard Exp $

# End of file 
