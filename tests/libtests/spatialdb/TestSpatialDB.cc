// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "spatialdata/spatialdb/SpatialDB.hh" // Test subject

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleIO.hh" // USES SimpleIOAscii
#include "spatialdata/spatialdb/SimpleIOAscii.hh" // USES SimpleIOAscii
extern "C" {
#include "spatialdata/spatialdb/cspatialdb.h"
}

#include "spatialdata/geocoords/CoordSys.hh" // USES CSCart
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()
#include <cassert>

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSpatialDB;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSpatialDB {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor.
    TestSpatialDB(void);

    /// Destructor.
    ~TestSpatialDB(void);

    /// Test SpatialDB
    void testDB(void);

    /// Test SpatialDB queries w/multiple points.
    void testDBmulti(void);

    /// Test C API of SpatialDB
    void testDB_CAPI(void);

    // PRIVATE MEMBERS ////////////////////////////////////////////////////////////////////////////
private:

    SpatialDB* _db; ///< Test subject

}; // class TestSpatialDB

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestSpatialDB::testDB", "[TestSpatialDB]") {
    spatialdata::spatialdb::TestSpatialDB().testDB();
}
TEST_CASE("TestSpatialDB::testDBmulti", "[TestSpatialDB]") {
    spatialdata::spatialdb::TestSpatialDB().testDBmulti();
}
TEST_CASE("TestSpatialDB::testDB_CAPI", "[TestSpatialDB]") {
    spatialdata::spatialdb::TestSpatialDB().testDB_CAPI();
}

// ----------------------------------------------------------------------
// Constructor.
spatialdata::spatialdb::TestSpatialDB::TestSpatialDB(void) {
    spatialdata::spatialdb::SimpleDB* db = new spatialdata::spatialdb::SimpleDB;assert(db);

    const char* filename = "data/spatialdb.dat";
    SimpleIOAscii iohandler;
    iohandler.setFilename(filename);
    db->setIOHandler(&iohandler);
    db->open();
    db->setQueryType(spatialdata::spatialdb::SimpleDB::NEAREST);

    _db = db;
} // setUp


// ----------------------------------------------------------------------
// Destructor.
spatialdata::spatialdb::TestSpatialDB::~TestSpatialDB(void) {
    delete _db;_db = 0;
} // tearDown


// ----------------------------------------------------------------------
// Test SpatialDB
void
spatialdata::spatialdb::TestSpatialDB::testDB(void) { // testDB
    assert(_db);

    const char* names[4] = {"two", "one", "four", "three"};
    const size_t numVals = 4;
    const double queryLoc[3] = { 0.6, 0.1, 0.2 };
    const double vals[4] = { 6.3e+3, 4.7, 0.8, 1.2e+6 };
    const int errFlags[1] = { 0 };
    const int spaceDim = 3;

    _db->setQueryValues(names, numVals);

    double* valsQ = (0 < numVals) ? new double[numVals] : NULL;
    spatialdata::geocoords::CSCart csCart;
    const int err = _db->query(valsQ, numVals, queryLoc, spaceDim, &csCart);
    REQUIRE(err == errFlags[0]);

    const double tolerance = 1.0e-06;
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        const double toleranceV = fabs(vals[iVal]) * tolerance;
        CHECK_THAT(valsQ[iVal], Catch::Matchers::WithinAbs(vals[iVal], toleranceV));
    } // for

    delete[] valsQ;valsQ = NULL;
    _db->close();
} // testDB


// ----------------------------------------------------------------------
// Test SpatialDB queries w/multiple points.
void
spatialdata::spatialdb::TestSpatialDB::testDBmulti(void) { // testDBmulti
    assert(_db);

    const size_t numVals = 4;
    const size_t numLocs = 2;
    const size_t spaceDim = 3;
    const char* names[numVals] = {"two", "one", "four", "three"};
    const double queryLocs[numLocs*spaceDim] = {
        0.6, 0.1, 0.2,
        0.1, 0.6, 0.3,
    };
    const double vals[numLocs*numVals] = {
        6.3e+3, 4.7, 0.8, 1.2e+6,
        3.6e+3, 7.4, 8.0, 2.1e+6,
    };
    const int errFlags[numLocs] = { 0, 0 };

    _db->setQueryValues(names, numVals);

    size_t size = numLocs * numVals;
    double* valsQ = (0 < size) ? new double[size] : NULL;
    size = numLocs;
    int* errQ = (0 < size) ? new int[size] : NULL;

    spatialdata::geocoords::CSCart csCart;

    _db->multiquery(valsQ, numLocs, numVals,
                    errQ, numLocs, queryLocs, numLocs, spaceDim, &csCart);

    const double tolerance = 1.0e-06;
    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        REQUIRE(errFlags[iLoc] == errQ[iLoc]);
        for (size_t iVal = 0, index = 0; iVal < numVals; ++iVal, index++) {
            const double toleranceV = fabs(vals[index]) * tolerance;
            CHECK_THAT(valsQ[index], Catch::Matchers::WithinAbs(vals[index], toleranceV));
        }
    } // for

    delete[] valsQ;valsQ = NULL;
    delete[] errQ;errQ = NULL;

    _db->close();
} // testDBmulti


// ----------------------------------------------------------------------
// Test SpatialDB w/C query
void
spatialdata::spatialdb::TestSpatialDB::testDB_CAPI(void) {
    assert(_db);

    const char* names[2] = {"two", "one"};
    const size_t numVals = 2;
    const double queryLoc[3] = { 0.6, 0.1, 0.2 };
    const size_t spaceDim = 3;
    const double vals[2] = { 6.3e+3, 4.7 };
    const int errFlags[1] = { 0 };

    _db->setQueryValues(names, numVals);

    double* valsQ = (0 < numVals) ? new double[numVals] : 0;
    spatialdata::geocoords::CSCart csCart;

    const int err = spatialdb_query((void*) _db, valsQ, numVals, queryLoc, spaceDim, (void*) &csCart);
    REQUIRE(err == errFlags[0]);

    const double tolerance = 1.0e-06;
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        const double toleranceV = fabs(vals[iVal]) * tolerance;
        CHECK_THAT(valsQ[iVal], Catch::Matchers::WithinAbs(vals[iVal], toleranceV));
    } // for

    delete[] valsQ;valsQ = NULL;
    _db->close();
} // testDB_c


// End of file
