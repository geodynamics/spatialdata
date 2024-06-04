# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	libsrc \
	modulesrc \
	spatialdata \
	templates \
	docs


if ENABLE_TESTING
  SUBDIRS += tests
endif

DISTCHECK_CONFIGURE_FLAGS = \
	--enable-testing \
	CPPFLAGS="-I${CXXMAPPING_INCDIR} -I${CATCH2_INCDIR} -I${PYTHIA_INCDIR}" \
	LDFLAGS="-L${CXXMAPPING_LIBDIR} -L${CATCH2_LIBDIR} "

EXTRA_DIST = \
    README.md \
    CHANGES.md \
    setup.py \
    setup.cfg \
    configure.ac \
	applications/gensimpledb.py \
    LICENSE.md \
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
