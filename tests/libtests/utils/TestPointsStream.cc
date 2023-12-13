// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "spatialdata/utils/PointsStream.hh" // USES PointStream

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <sstream> // USES std::stringstream

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace utils {
        class TestPointsStream;
    } // utils
} // spatialdata

class spatialdata::utils::TestPointsStream {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test accessors.
    static
    void testAccessors(void);

    /// Test write()/read()
    static
    void testWriteRead(void);

    // PRIVATE METHODS ////////////////////////////////////////////////////////////////////////////
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

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestPointsStream::testAccessors", "[TestPointsStream]") {
    spatialdata::utils::TestPointsStream::testAccessors();
}
TEST_CASE("TestPointsStream::testWriteRead", "[TestPointsStream]") {
    spatialdata::utils::TestPointsStream::testWriteRead();
}

// ------------------------------------------------------------------------------------------------
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

    CHECK(filename == std::string(s.getFilename()));
    CHECK(flag == std::string(s.getCommentFlag()));
    CHECK(fieldWidth == s.getFieldWidth());
    CHECK(precision == s.getPrecision());
} // testAccessors


// ------------------------------------------------------------------------------------------------
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

    REQUIRE(_NUMPTS == numPts);
    REQUIRE(_NUMDIMS == numDims);

    const size_t size = _NUMPTS * _NUMDIMS;
    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < size; ++i) {
        CHECK_THAT(points[i], Catch::Matchers::WithinAbs(_POINTS[i], tolerance));
    } // for

    delete[] points;points = NULL;
} // testWriteRead


// End of file
