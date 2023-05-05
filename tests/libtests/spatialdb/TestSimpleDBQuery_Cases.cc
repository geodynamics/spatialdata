// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSimpleDBQuery.hh" // ISA TestSimpleDBQuery

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDBQuery_3D;
    } // spatialdb
} // spatialdata

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDBQuery_3D : public TestSimpleDBQuery {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleDBQuery_3D, TestSimpleDBQuery);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleDBQuery::setUp();
        _data = new TestSimpleDBQuery_Data;CPPUNIT_ASSERT(_data);

        _data->numLocs = 5;
        _data->spaceDim = 3;
        _data->numValues = 3;
        _data->dataDim = 3;
        _data->numPoints = 4;

        _data->dist2 = 9.86850000e+00;
        _data->area = 7.28666752e+00;
        _data->volume = 2.95458000e+00;

        static const double dbCoordinates[5*3] = {
            0.00000000e+00,  0.00000000e+00,  0.00000000e+00,
            1.00000000e+00,  1.00000000e-01,  3.00000000e-01,
            2.00000000e+00,  2.00000000e-01,  2.00000000e-01,
            3.00000000e+00,  3.00000000e-01,  1.00000000e-01,
            4.00000000e+00,  4.00000000e-01,  9.00000000e-01,
        };
        _data->dbCoordinates = dbCoordinates;

        static const double dbValues[5*3] = {
            1.1,  5.5,  3.4,
            2.2,  6.6,  4.5,
            3.3,  7.7,  5.6,
            4.4,  8.8,  6.7,
            4.5,  9.9,  7.8,
        };
        _data->dbValues = dbValues;

        static const char* names[3] = {
            "one",
            "two",
            "three",
        };
        _data->names = names;

        static const char* units[3] = {
            "m",
            "s",
            "m/s",
        };
        _data->units = units;

        static const double coordinates[4*3] = {
            2.95000000e+00,  4.48000000e+00,  3.44000000e+00,
            5.80000000e+00,  5.32000000e+00,  4.46000000e+00,
            7.97000000e+00,  1.06200000e+01,  7.00000000e+00,
            8.38000000e+00,  1.30100000e+01,  9.34000000e+00,
        };
        _data->coordinates = coordinates;

        static const double areaDir[3] = {
            -2.24547092e-01, -3.44848999e-01,  9.11404285e-01,
        };
        _data->areaDir = areaDir;

    } // setUp

}; // TestSimpleGriDB_3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleDBQuery_3D);

// End of file
