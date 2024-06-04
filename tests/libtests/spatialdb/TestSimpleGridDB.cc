// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "TestSimpleGridDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleGridDB.hh" // USES SimpleGridDB
#include "spatialdata/spatialdb/SimpleGridAscii.hh" // USES SimpleGridAscii

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ----------------------------------------------------------------------
// Constructor.
spatialdata::spatialdb::TestSimpleGridDB::TestSimpleGridDB(TestSimpleGridDB_Data* data) :
    _data(data) {
    assert(_data);
} // setUp


// ----------------------------------------------------------------------
// Tear down testing data.
spatialdata::spatialdb::TestSimpleGridDB::~TestSimpleGridDB(void) {
    delete _data;_data = NULL;
} // tearDown


// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleGridDB::testConstructor(void) {
    SimpleGridDB db;
} // testConstructor


// ----------------------------------------------------------------------
// Test setDescription()
void
spatialdata::spatialdb::TestSimpleGridDB::testAccessors(void) {
    SimpleGridDB db;
    const std::string description("database 2");
    const std::string filename("mydb.spatialdb");

    db.setDescription(description.c_str());
    CHECK(description == std::string(db.getDescription()));

    db.setFilename(filename.c_str());
    CHECK(filename == db._filename);

    // Test query type.
    CHECK(SimpleGridDB::NEAREST == db._queryType);

    db.setQueryType(SimpleGridDB::LINEAR);
    CHECK(SimpleGridDB::LINEAR == db._queryType);

    db.setQueryType(SimpleGridDB::NEAREST);
    CHECK(SimpleGridDB::NEAREST == db._queryType);
} // testAccessors


// ----------------------------------------------------------------------
// Test _search()
void
spatialdata::spatialdb::TestSimpleGridDB::testSearch(void) {
    const size_t numX = 5;
    const double x[numX] = {
        -3.0, -1.0, 0.0, 5.0, 8.0,
    };
    const double tolerance = 1.0e-6;

    SimpleGridDB db;

    db.setQueryType(SimpleGridDB::NEAREST);

    // Test data and expected results
    const double xA = -20.0;
    const double indexA = 0.0;
    double index = db._search(xA, x, numX);
    CHECK_THAT(index, Catch::Matchers::WithinAbs(indexA, tolerance));

    const double xB = -1.0;
    const double indexB = 1.0;
    index = db._search(xB, x, numX);
    CHECK_THAT(index, Catch::Matchers::WithinAbs(indexB, tolerance));

    const double xC = +3.0;
    const double indexC = 2.6;
    index = db._search(xC, x, numX);
    CHECK_THAT(index, Catch::Matchers::WithinAbs(indexC, tolerance));

    const double xD = -20.0;
    const double indexD = 0.0;
    index = db._search(xD, x, numX);
    CHECK_THAT(index, Catch::Matchers::WithinAbs(indexD, tolerance));

    db.setQueryType(SimpleGridDB::LINEAR);

    // Test data and expected results
    const double xE = -20.0;
    const double indexE = -1.0;
    index = db._search(xE, x, numX);
    CHECK_THAT(index, Catch::Matchers::WithinAbs(indexE, tolerance));

    const double xF = -1.0;
    const double indexF = 1.0;
    index = db._search(xF, x, numX);
    CHECK_THAT(index, Catch::Matchers::WithinAbs(indexF, tolerance));

    const double xG = +3.0;
    const double indexG = 2.6;
    index = db._search(xG, x, numX);
    CHECK_THAT(index, Catch::Matchers::WithinAbs(indexG, tolerance));

    const double xH = -20.0;
    const double indexH = -1.0;
    index = db._search(xH, x, numX);
    CHECK_THAT(index, Catch::Matchers::WithinAbs(indexH, tolerance));
} // testSearch


// ----------------------------------------------------------------------
// Test _getDataIndex()
void
spatialdata::spatialdb::TestSimpleGridDB::testDataIndex(void) {
    SimpleGridDB db;
    db._numX = 4;
    db._numY = 3;
    db._numZ = 5;
    db._numValues = 10;

    CHECK(size_t(0) == db._getDataIndex(0, db._numX, 0, db._numY, 0, db._numZ));
    CHECK(size_t(1*3*4*10) == db._getDataIndex(0, db._numX, 0, db._numY, 1, db._numZ));

    CHECK(size_t(1*4*10) == db._getDataIndex(0, db._numX, 1, db._numY, 0, db._numZ));
    CHECK(size_t(4*3*4*10 + 1*4*10) == db._getDataIndex(0, db._numX, 1, db._numY, 4, db._numZ));

    CHECK(size_t(1*10) == db._getDataIndex(1, db._numX, 0, db._numY, 0, db._numZ));
    CHECK(size_t(3*4*3*10 + 1*4*10 + 2*10) == db._getDataIndex(2, db._numX, 1, db._numY, 3, db._numZ));
} // testDataIndex


// ----------------------------------------------------------------------
// Test getNamesDBValues().
void
spatialdata::spatialdb::TestSimpleGridDB::testGetNamesDBValues(void) {
    assert(_data);

    SimpleGridDB db;
    _setupDB(&db);

    const char** valueNames = NULL;
    size_t numValues = 0;
    db.getNamesDBValues(&valueNames, &numValues);
    REQUIRE(_data->numValues == numValues);

    for (size_t i = 0; i < numValues; ++i) {
        CHECK(std::string(_data->names[i]) == std::string(valueNames[i]));
    } // for
    delete[] valueNames;valueNames = NULL;
    numValues = 0;
} // testGetDBValues


// ----------------------------------------------------------------------
// Test query() using nearest neighbor.
void
spatialdata::spatialdb::TestSimpleGridDB::testQueryNearest(void) {
    assert(_data);

    SimpleGridDB db;
    _setupDB(&db);
    db.setQueryType(SimpleGridDB::NEAREST);
    _checkQuery(db, _data->names, _data->queryNearest, 0, _data->numQueries, _data->spaceDim, _data->numValues);
} // _testQueryNearest


// ----------------------------------------------------------------------
// Test query() using linear interpolation.
void
spatialdata::spatialdb::TestSimpleGridDB::testQueryLinear(void) {
    assert(_data);

    SimpleGridDB db;
    _setupDB(&db);
    db.setQueryType(SimpleGridDB::LINEAR);
    _checkQuery(db, _data->names, _data->queryLinear, _data->errFlags, _data->numQueries, _data->spaceDim, _data->numValues);
} // _testQueryLinear


// ----------------------------------------------------------------------
// Test read().
void
spatialdata::spatialdb::TestSimpleGridDB::testRead(void) {
    assert(_data);

    SimpleGridDB db;
    db.setFilename(_data->filename);
    db.open();

    CHECK(_data->spaceDim == db._spaceDim);
    CHECK(_data->dataDim == db._dataDim);
    REQUIRE(_data->numValues == db._numValues);

    const size_t numValues = _data->numValues;
    for (size_t i = 0; i < numValues; ++i) {
        CHECK(std::string(_data->names[i]) == db._names[i]);
        CHECK(std::string(_data->units[i]) == db._units[i]);
    } // for

    CHECK(_data->numX == db._numX);
    CHECK(_data->numY == db._numY);
    CHECK(_data->numZ == db._numZ);

    const double tolerance = 1.0e-6;
    size_t totalSize = 1;
    if (_data->numX > 1) {
        totalSize *= _data->numX;
        for (size_t i = 0; i < _data->numX; ++i) {
            CHECK_THAT(db._x[i], Catch::Matchers::WithinAbs(_data->dbX[i], tolerance));
        } // for
    } // if
    if (_data->numY > 1) {
        totalSize *= _data->numY;
        for (size_t i = 0; i < _data->numY; ++i) {
            CHECK_THAT(db._y[i], Catch::Matchers::WithinAbs(_data->dbY[i], tolerance));
        } // for
    } // if
    if (_data->numZ > 1) {
        totalSize *= _data->numZ;
        for (size_t i = 0; i < _data->numZ; ++i) {
            CHECK_THAT(db._z[i], Catch::Matchers::WithinAbs(_data->dbZ[i], tolerance));
        } // for
    } // if

    for (size_t i = 0; i < totalSize; ++i) {
        CHECK_THAT(db._data[i], Catch::Matchers::WithinAbs(_data->dbData[i], tolerance));
    } // for

    CHECK(_data->numValues == db._querySize);
    for (size_t i = 0; i < _data->numValues; ++i) {
        CHECK(i == db._queryValues[i]);
    } // for

    db.close();
} // testRead


// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleGridDB::_setupDB(SimpleGridDB* const db) {
    assert(db);
    assert(_data);
    assert(_data->numValues > 0);

    delete[] db->_x;db->_x = NULL;
    delete[] db->_y;db->_y = NULL;
    delete[] db->_z;db->_z = NULL;
    delete[] db->_data;db->_data = NULL;
    delete[] db->_names;db->_names = NULL;
    delete[] db->_units;db->_units = NULL;

    db->setDescription("Test database");
    db->_numValues = _data->numValues;
    db->_spaceDim = _data->spaceDim;
    db->_dataDim = _data->dataDim;
    db->_numX = _data->numX;
    db->_numY = _data->numY;
    db->_numZ = _data->numZ;

    size_t numLocs = 1;
    if (_data->numX > 1) {
        numLocs *= _data->numX;
        db->_x = new double[_data->numX];
        for (size_t i = 0; i < _data->numX; ++i) {
            db->_x[i] = _data->dbX[i];
        } // for
    } // if
    if (_data->numY > 1) {
        numLocs *= _data->numY;
        db->_y = new double[_data->numY];
        for (size_t i = 0; i < _data->numY; ++i) {
            db->_y[i] = _data->dbY[i];
        } // for
    } // if
    if (_data->numZ > 1) {
        numLocs *= _data->numZ;
        db->_z = new double[_data->numZ];
        for (size_t i = 0; i < _data->numZ; ++i) {
            db->_z[i] = _data->dbZ[i];
        } // for
    } // if

    db->_data = (numLocs > 0) ? new double[numLocs*_data->numValues] : NULL;
    for (size_t i = 0; i < numLocs*_data->numValues; ++i) {
        db->_data[i] = _data->dbData[i];
    } // for

    db->_names = (_data->numValues > 0) ? new std::string[_data->numValues] : NULL;
    for (size_t i = 0; i < _data->numValues; ++i) {
        db->_names[i] = _data->names[i];
    } // for

    db->_units = (_data->numValues > 0) ? new std::string[_data->numValues] : NULL;
    for (size_t i = 0; i < _data->numValues; ++i) {
        db->_units[i] = _data->units[i];
    } // for

    delete db->_cs;
    db->_cs = new spatialdata::geocoords::CSCart();
    db->_cs->setSpaceDim(_data->spaceDim);
} // _setupDB


// ----------------------------------------------------------------------
// Test query method by doing query and checking values returned.
void
spatialdata::spatialdb::TestSimpleGridDB::_checkQuery(SimpleGridDB& db,
                                                      const char** const names,
                                                      const double* queryData,
                                                      const int* flagsE,
                                                      const size_t numQueries,
                                                      const size_t spaceDim,
                                                      const size_t numValues) {
    assert(names);
    assert(queryData);
    assert(numQueries);
    assert(spaceDim);
    assert(numValues);

    // reverse order of vals in queries
    const char* valNames[numValues];
    for (size_t i = 0; i < numValues; ++i) {
        valNames[numValues-i-1] = names[i];
    }
    db.setQueryValues(valNames, numValues);

    double* vals = (0 < numValues) ? new double[numValues] : NULL;
    const double tolerance = 1.0e-06;

    const size_t locSize = spaceDim + numValues;
    spatialdata::geocoords::CSCart csCart;
    csCart.setSpaceDim(spaceDim);
    for (size_t iQuery = 0; iQuery < numQueries; ++iQuery) {
        const double* coords = &queryData[iQuery*locSize];
        const double* valsE = &queryData[iQuery*locSize+spaceDim];
        const int err = db.query(vals, numValues, coords, spaceDim, &csCart);
        if (0 != flagsE) {
            REQUIRE(flagsE[iQuery] == err);
        } else {
            REQUIRE(!err);
            for (size_t iVal = 0; iVal < numValues; ++iVal) {
                const double valueE = valsE[numValues-iVal-1];
                const double toleranceV = fabs(valueE) > 0.0 ? fabs(valueE) * tolerance : tolerance;
                CHECK_THAT(vals[iVal], Catch::Matchers::WithinAbs(valueE, toleranceV));
            } // for
        } // if/else
    } // for
    delete[] vals;vals = NULL;
} // _checkQuery


// ----------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleGridDB_Data::TestSimpleGridDB_Data(void) :
    numX(0),
    numY(0),
    numZ(0),
    spaceDim(0),
    numValues(0),
    dataDim(0),
    dbX(NULL),
    dbY(NULL),
    dbZ(NULL),
    dbData(NULL),
    names(NULL),
    units(NULL),
    numQueries(0),
    queryNearest(NULL),
    queryLinear(NULL),
    errFlags(NULL),
    filename(NULL) {}


// ----------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleGridDB_Data::~TestSimpleGridDB_Data(void) {
    numX = 0;
    numY = 0;
    numZ = 0;
    spaceDim = 0;
    numValues = 0;
    dataDim = 0;
    dbX = NULL;
    dbY = NULL;
    dbZ = NULL;
    dbData = NULL;
    names = NULL;
    units = NULL;
    numQueries = 0;
    queryNearest = NULL;
    queryLinear = NULL;
    errFlags = NULL;
    filename = NULL;
} // destructor


// End of file
