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
