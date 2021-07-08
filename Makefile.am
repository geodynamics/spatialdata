# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	libsrc \
	modulesrc \
	spatialdata \
	templates


if ENABLE_TESTING
  SUBDIRS += tests
endif

DISTCHECK_CONFIGURE_FLAGS = \
	--enable-testing \
	CPPFLAGS="-I${PROJ4_INCDIR} -I${CPPUNIT_INCDIR} -I${PYTHIA_INCDIR} -I${CIG_INCDIR}" \
	LDFLAGS="-L${PROJ4_LIBDIR} -L${CPPUNIT_LIBDIR} -L${CIG_LIBDIR}"

EXTRA_DIST = \
	CHANGES \
	docker/spatialdata-testenv \
	ci-config/run_tests.sh \
	ci-config/codecov.yml


.PHONY: coverage-libtests coverage-pytests coverage-html clean-coverage

if ENABLE_TEST_COVERAGE
coverage-libtests:
	$(LCOV) --directory libsrc --capture --output-file coverage-libtests.info
	$(LCOV) --remove coverage-libtests.info '/usr/*' '/Library/*' "v1" "*/testing/TestDriver.*" -o coverage-libtests.info
	$(LCOV) --list coverage-libtests.info

coverage-pytests:
	$(PYTHON_COVERAGE) combine tests/pytests/*/.coverage
	$(PYTHON_COVERAGE) xml -o coverage-pytests.xml

coverage-html: coverage-libtests coverage-pytests
	genhtml -o coverage-libtests coverage-libtests.info
	$(PYTHON_COVERAGE) html -d coverage-pytests

clean-coverage:
	$(RM) `find . -name "*.gcda"`
	$(RM) `find . -name ".coverage"`

else
coverage-libtests coverage-pytests coverage-html clean-coverage:
	$(warning Test coverage not enabled. Ignoring test coverage targets)
endif


# End of file 
