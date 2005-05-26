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

PROJECT = spatialdata/geocoords/tests/libtests
PACKAGE = data

default all:

datfiles: \
	Projector \
	GeoCSConverter \
	GeoLocalConverter \

Projector:
	ConvertDataApp.py \
		--data=projector \
		--dumper.className=spatialdata::TestProjector \
		--dumper.filename=TestProjector.dat

GeoCSConverter:
	ConvertDataApp.py \
		--data=geocsconverter \
		--dumper.className=spatialdata::TestGeoCSConverter \
		--dumper.filename=TestGeoCSConverter.dat

GeoLocalConverter:
	ConvertDataApp.py \
		--data=geolocalconverter \
		--dumper.className=spatialdata::TestGeoLocalConverter \
		--dumper.filename=TestGeoLocalConverter.dat


# ----------------------------------------------------------------------

# version
# $Id: Make.mm,v 1.1 2005/05/25 17:30:44 baagaard Exp $

# End of file 
