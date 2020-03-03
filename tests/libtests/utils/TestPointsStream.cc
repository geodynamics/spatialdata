// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/utils/PointsStream.hh" // USES PointStream

#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace utils {
        class TestPointsStream;
    } // utils
} // spatialdata

class spatialdata::utils::TestPointsStream : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestPointsStream);

    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testWriteRead);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test accessors.
    void testAccessors(void);

    /// Test write()/read()
    void testWriteRead(void);

    // PRIVATE METHODS ////////////////////////////////////////////////////
private:

    static const double _POINTS[]; ///< Array of points
    static const size_t _NUMPTS; ///< Number of points
    static const size_t _NUMDIMS; ///< Number of dimensions

}; // class TestPointsStream
const size_t spatialdata::utils::TestPointsStream::_NUMPTS = 4;
const size_t spatialdata::utils::TestPointsStream::_NUMDIMS = 3;
const double spatialdata::utils::TestPointsStream::_POINTS[4*3] = {
    1.0, 2.0, 3.0,
    1.1, 2.1, 3.1,
    1.2, 2.2, 3.2,
    1.3, 2.3, 3.3
};

CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::utils::TestPointsStream);

// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::utils::TestPointsStream::testAccessors(void) {
    const std::string filename("test.text");
    const std::string flag("%");
    const size_t fieldWidth(18);
    const size_t precision(3);

    PointsStream s;
    s.setFilename(filename.c_str());
    s.setCommentFlag(flag.c_str());
    s.setFieldWidth(fieldWidth);
    s.setPrecision(precision);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in filename.", filename, std::string(s.getFilename()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in comment flag.", flag, std::string(s.getCommentFlag()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in field width.", fieldWidth, s.getFieldWidth());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in precision.", precision, s.getPrecision());
} // testAccessors


// ----------------------------------------------------------------------
// Test write() and read()
void
spatialdata::utils::TestPointsStream::testWriteRead(void) {
    const char* filename = "tmp_pointstream.txt";

    PointsStream s;
    s.setFilename(filename);
    s.write(_POINTS, _NUMPTS, _NUMDIMS);

    double* points = NULL;
    size_t numPts = 0;
    size_t numDims = 0;
    s.read(&points, &numPts, &numDims);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points.", _NUMPTS, numPts);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in spatial dimension.", _NUMDIMS, numDims);

    const size_t size = _NUMPTS * _NUMDIMS;
    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < size; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in point values.", _POINTS[i], points[i], tolerance);
    } // for

    delete[] points;points = NULL;
} // testWriteRead


// End of file
