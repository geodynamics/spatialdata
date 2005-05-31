# -*- Makefile -*-
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ======================================================================
#

PROJECT = spatialdata
PACKAGE = geocoords/applications

# ----------------------------------------------------------------------

all: export

# ----------------------------------------------------------------------

EXPORT_BINS = \
    convert.py \

export:: export-binaries

# version
# $Id: Make.mm,v 1.1 2005/05/31 15:18:43 baagaard Exp $

# End of file
