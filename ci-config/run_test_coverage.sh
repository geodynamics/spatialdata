#!/bin/bash

# Run tests to generate coverage information. Upload test coverage data.

make -j$(nproc) install
make -j$(nproc) check VERBOSE=1
make coverage-libsrc

# Must run codeocov script in top-level source directory.
cd ../src && bash <(curl -s https://codecov.io/bash) -X gcov -f ../build/coverage.info -F libsrc -y ci-config/codecov.yml"

exit 0
