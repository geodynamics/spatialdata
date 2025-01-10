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

#include "TestSimpleDBQuery.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery
#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ----------------------------------------------------------------------
// Constructor.
spatialdata::spatialdb::TestSimpleDBQuery::TestSimpleDBQuery(TestSimpleDBQuery_Data* data) :
    _data(data) {
    _db = new SimpleDB;assert(_db);
    _query = new SimpleDBQuery(*_db);assert(_query);
} // constructor


// ----------------------------------------------------------------------
// Destructor.
spatialdata::spatialdb::TestSimpleDBQuery::~TestSimpleDBQuery(void) {
    delete _data;_data = NULL;
    delete _db;_db = NULL;
    delete _query;_query = NULL;
} // destructor


// ----------------------------------------------------------------------
// Test Constructor()
void
spatialdata::spatialdb::TestSimpleDBQuery::testConstructor(void) {
    assert(_query);
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestSimpleDBQuery::testAccessors(void) {
    assert(_query);

    const SimpleDB::QueryEnum queryTypeDefault = SimpleDB::NEAREST;
    _query->setQueryType(queryTypeDefault);
    CHECK(queryTypeDefault == _query->_queryType);

    const SimpleDB::QueryEnum queryTypeUser = SimpleDB::LINEAR;
    _query->setQueryType(queryTypeUser);
    CHECK(queryTypeUser == _query->_queryType);
} // testAccessors


// ----------------------------------------------------------------------
// Test setQueryValues()
void
spatialdata::spatialdb::TestSimpleDBQuery::testQueryVals(void) {
    _initializeDB();

    const size_t numNames = 3;
    const char* names[3] = { "two", "one", "three" };
    const size_t queryIndices[3] = { 1, 0, 2 };

    assert(_query);
    _query->setQueryValues(names, numNames);
    REQUIRE(numNames == _query->_querySize);
    for (size_t i = 0; i < numNames; ++i) {
        CHECK(queryIndices[i] == _query->_queryValues[i]);
    } // for
} // testQueryVals


// ----------------------------------------------------------------------
// Test distSquared()
void
spatialdata::spatialdb::TestSimpleDBQuery::testDistSquared(void) {
    _initializeDB();
    assert(_data);

    assert(_data->numPoints >= 2);
    const size_t spaceDim = _data->spaceDim;
    const double dist2 = SimpleDBQuery::_distSquared(&_data->coordinates[0*spaceDim], &_data->coordinates[1*spaceDim]);
    const double tolerance = 1.0e-06;
    const double toleranceV = fabs(_data->dist2) > 0.0 ? fabs(_data->dist2) * tolerance : tolerance;
    CHECK_THAT(dist2, Catch::Matchers::WithinAbs(_data->dist2, toleranceV));
} // _testDistSquared


// ----------------------------------------------------------------------
// Test area()
void
spatialdata::spatialdb::TestSimpleDBQuery::testArea(void) {
    _initializeDB();
    assert(_data);

    const size_t spaceDim = _data->spaceDim;
    if (spaceDim < 2) { return; }

    assert(_data->numPoints >= 3);
    double area = 0;
    double areaDir[3];
    SimpleDBQuery::_area(&area, areaDir,
                         &_data->coordinates[0*spaceDim],
                         &_data->coordinates[1*spaceDim],
                         &_data->coordinates[2*spaceDim]);
    const double tolerance = 1.0e-06;
    double toleranceV = fabs(_data->area) > 0.0 ? fabs(_data->area) * tolerance : tolerance;
    CHECK_THAT(area, Catch::Matchers::WithinAbs(_data->area, toleranceV));
    for (size_t i = 0; i < spaceDim; ++i) {
        toleranceV = fabs(_data->areaDir[i]) > 0.0 ? fabs(_data->areaDir[i]) * tolerance : tolerance;
        CHECK_THAT(areaDir[i], Catch::Matchers::WithinAbs(_data->areaDir[i], toleranceV));
    } // for
} // _testArea


// ----------------------------------------------------------------------
// Test volume()
void
spatialdata::spatialdb::TestSimpleDBQuery::testVolume(void) {
    _initializeDB();
    assert(_data);

    const size_t spaceDim = _data->spaceDim;
    if (spaceDim < 3) { return; }

    assert(_data->numPoints >= 4);
    const double volume =
        SimpleDBQuery::_volume(&_data->coordinates[0*spaceDim],
                               &_data->coordinates[1*spaceDim],
                               &_data->coordinates[2*spaceDim],
                               &_data->coordinates[3*spaceDim]);
    const double tolerance = 1.0e-06;
    const double toleranceV = fabs(_data->volume) > 0.0 ? fabs(_data->volume) * tolerance : tolerance;
    CHECK_THAT(volume, Catch::Matchers::WithinAbs(_data->volume, toleranceV));
} // testVolume


// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleDBQuery::_initializeDB(void) {
    assert(_data);

    SimpleDBData* dbData = new SimpleDBData;assert(dbData);
    dbData->allocate(_data->numLocs, _data->numValues, _data->spaceDim, _data->dataDim);
    dbData->setData(_data->dbValues, _data->numLocs, _data->numValues);
    dbData->setCoordinates(_data->dbCoordinates, _data->numLocs, _data->spaceDim);
    dbData->setNames(_data->names, _data->numValues);
    dbData->setUnits(_data->units, _data->numValues);

    delete _db->_data;_db->_data = dbData;
    delete _db->_cs;_db->_cs = new spatialdata::geocoords::CSCart;assert(_db->_cs);
} // _initializeDB


// ----------------------------------------------------------------------
// Constructor.
spatialdata::spatialdb::TestSimpleDBQuery_Data::TestSimpleDBQuery_Data(void) :
    numLocs(0),
    spaceDim(0),
    numValues(0),
    dataDim(0),
    dbCoordinates(NULL),
    dbValues(NULL),
    names(NULL),
    units(NULL),
    numPoints(0),
    coordinates(NULL),
    dist2(0.0),
    areaDir(NULL),
    volume(0.0) {}


// ----------------------------------------------------------------------
// Constructor.
spatialdata::spatialdb::TestSimpleDBQuery_Data::~TestSimpleDBQuery_Data(void) {
    // Set static const data in derived classes to NULL (don't deallocate).
    dbCoordinates = NULL;
    dbValues = NULL;
    names = NULL;
    units = NULL;
    coordinates = NULL;
    areaDir = NULL;

} // destructor


// End of file
