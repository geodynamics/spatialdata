# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import unittest

from spatialdata.testing.TestCases import make_suite
from spatialdata.utils.utils import SpatialdataVersion


class TestSpatialdataVersion(unittest.TestCase):

    def test_isRelease(self):
        isRelease = SpatialdataVersion.isRelease()

    def test_version(self):
        version = SpatialdataVersion.version()
        # Check that version is of the form X.X.X
        import re
        match = re.search("[0-9]+\.[0-9]+\.[0-9]+", version)
        self.assertFalse(match is None)

    def test_gitVersion(self):
        revision = SpatialdataVersion.gitRevision()
        if SpatialdataVersion.isRelease():
            self.assertEqual("unknown", revision)
        else:
            # Check that revision is of the form v2.1.3-16-g9323114
            import re
            match = re.search("v[0-9]+\.[0-9]+\.[0-9]+", revision)
            if match is None:
                match = re.search("v[0-9]+\.[0-9]+\.[0-9]+-[0-9]+-g[0-9,a-z]+", revision)
            self.assertFalse(match is None)

    def test_gitHash(self):
        tag = SpatialdataVersion.gitHash()
        if SpatialdataVersion.isRelease():
            self.assertEqual("unknown", tag)
        else:
            # Check form of hash
            import re
            match = re.search("[0-9,a-z]+", tag)
            self.assertFalse(match is None)

    def test_gitDate(self):
        value = SpatialdataVersion.gitDate()
        if SpatialdataVersion.isRelease():
            self.assertEqual("unknown", value)
        else:
            # Check form of datetime
            import datetime
            fields = value.split()
            d = datetime.datetime.strptime(fields[0], "%Y-%m-%d")
            t = datetime.datetime.strptime(fields[1], "%H:%M:%S")

    def test_gitBranch(self):
        branch = SpatialdataVersion.gitBranch()
        if SpatialdataVersion.isRelease():
            self.assertEqual("unknown", branch)
        else:
            self.assertFalse(len(branch) == 0)

    def test_projVersion(self):
        version = SpatialdataVersion.projVersion()
        # Check that version is of the form XXX
        import re
        match = re.search("[0-9]+", version)
        self.assertFalse(match is None)


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestSpatialdataVersion]
    return make_suite(test_classes=TEST_CLASSES, loader=loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
