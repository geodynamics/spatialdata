# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

subpackage = utils
include $(top_srcdir)/subpackage.am

TESTS = testutils.py
dist_check_SCRIPTS = testutils.py

TESTS_ENVIRONMENT = $(PYTHON)

noinst_PYTHON = \
	TestChangeCoordSys.py \
	TestConvertApp.py

data_TMP = in.txt out.txt


CLEANFILES = $(data_TMP) 


# End of file 
