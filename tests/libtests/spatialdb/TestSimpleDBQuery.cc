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

#include "TestSimpleDBQuery.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery
#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

// ----------------------------------------------------------------------
// Setup test data.
void
spatialdata::spatialdb::TestSimpleDBQuery::setUp(void) {
    _data = NULL;
    _db = new SimpleDB;CPPUNIT_ASSERT(_db);
    _query = new SimpleDBQuery(*_db);CPPUNIT_ASSERT(_query);
} // setUp


// ----------------------------------------------------------------------
// Destroy test data.
void
spatialdata::spatialdb::TestSimpleDBQuery::tearDown(void) {
    delete _data;_data = NULL;
    delete _db;_db = NULL;
    delete _query;_query = NULL;
} // tearDown


// ----------------------------------------------------------------------
// Test Constructor()
void
spatialdata::spatialdb::TestSimpleDBQuery::testConstructor(void) {
    CPPUNIT_ASSERT(_query);
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestSimpleDBQuery::testAccessors(void) {
    CPPUNIT_ASSERT(_query);

    const SimpleDB::QueryEnum queryTypeDefault = SimpleDB::NEAREST;
    _query->setQueryType(queryTypeDefault);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default query type.", queryTypeDefault, _query->_queryType);

    const SimpleDB::QueryEnum queryTypeUser = SimpleDB::LINEAR;
    _query->setQueryType(queryTypeUser);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in user query type.", queryTypeUser, _query->_queryType);
} // testAccessors


// ----------------------------------------------------------------------
// Test setQueryValues()
void
spatialdata::spatialdb::TestSimpleDBQuery::testQueryVals(void) {
    _initializeDB();

    const size_t numNames = 3;
    const char* names[3] = { "two", "one", "three" };
    const size_t queryIndices[3] = { 1, 0, 2 };

    CPPUNIT_ASSERT(_query);
    _query->setQueryValues(names, numNames);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of query values.", numNames, _query->_querySize);
    for (size_t i = 0; i < numNames; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query indices.", queryIndices[i], _query->_queryValues[i]);
    } // for
} // testQueryVals


// ----------------------------------------------------------------------
// Test distSquared()
void
spatialdata::spatialdb::TestSimpleDBQuery::testDistSquared(void) {
    _initializeDB();
    CPPUNIT_ASSERT(_data);

    CPPUNIT_ASSERT(_data->numPoints >= 2);
    const size_t spaceDim = _data->spaceDim;
    const double dist2 = SimpleDBQuery::_distSquared(&_data->coordinates[0*spaceDim], &_data->coordinates[1*spaceDim]);
    const double tolerance = 1.0e-06;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dist2/_data->dist2, tolerance);
} // _testDistSquared


// ----------------------------------------------------------------------
// Test area()
void
spatialdata::spatialdb::TestSimpleDBQuery::testArea(void) {
    _initializeDB();
    CPPUNIT_ASSERT(_data);

    const size_t spaceDim = _data->spaceDim;
    if (spaceDim < 2) { return; }

    CPPUNIT_ASSERT(_data->numPoints >= 3);
    double area = 0;
    double areaDir[3];
    SimpleDBQuery::_area(&area, areaDir,
                         &_data->coordinates[0*spaceDim],
                         &_data->coordinates[1*spaceDim],
                         &_data->coordinates[2*spaceDim]);
    const double tolerance = 1.0e-06;
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in area.", 1.0, area/_data->area, tolerance);
    for (size_t i = 0; i < spaceDim; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in area direction.", 1.0, areaDir[i]/_data->areaDir[i], tolerance);
    } // for
} // _testArea


// ----------------------------------------------------------------------
// Test volume()
void
spatialdata::spatialdb::TestSimpleDBQuery::testVolume(void) {
    _initializeDB();
    CPPUNIT_ASSERT(_data);

    const size_t spaceDim = _data->spaceDim;
    if (spaceDim < 3) { return; }

    CPPUNIT_ASSERT(_data->numPoints >= 4);
    const double volume =
        SimpleDBQuery::_volume(&_data->coordinates[0*spaceDim],
                               &_data->coordinates[1*spaceDim],
                               &_data->coordinates[2*spaceDim],
                               &_data->coordinates[3*spaceDim]);
    const double tolerance = 1.0e-06;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, volume/_data->volume, tolerance);
} // testVolume


// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleDBQuery::_initializeDB(void) {
    CPPUNIT_ASSERT(_data);

    SimpleDBData* dbData = new SimpleDBData;CPPUNIT_ASSERT(dbData);
    dbData->allocate(_data->numLocs, _data->numValues, _data->spaceDim, _data->dataDim);
    dbData->setData(_data->dbValues, _data->numLocs, _data->numValues);
    dbData->setCoordinates(_data->dbCoordinates, _data->numLocs, _data->spaceDim);
    dbData->setNames(_data->names, _data->numValues);
    dbData->setUnits(_data->units, _data->numValues);

    delete _db->_data;_db->_data = dbData;
    delete _db->_cs;_db->_cs = new spatialdata::geocoords::CSCart;CPPUNIT_ASSERT(_db->_cs);
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
