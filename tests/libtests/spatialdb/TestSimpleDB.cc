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

#include "TestSimpleDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery
#include "spatialdata/spatialdb/SimpleIOAscii.hh" // USES SimpleIOAscii

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ------------------------------------------------------------------------------------------------
// Constructor.
spatialdata::spatialdb::TestSimpleDB::TestSimpleDB(TestSimpleDB_Data* data) :
    _db(new SimpleDB()),
    _data(data) {
    assert(_db);
    assert(_data);
} // constructor


// ------------------------------------------------------------------------------------------------
// Deallocate test data;
spatialdata::spatialdb::TestSimpleDB::~TestSimpleDB(void) {
    delete _db;_db = NULL;
    delete _data;_data = NULL;
} // testDown


// ------------------------------------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleDB::testConstructors(void) {
    SimpleDB db;

    const std::string description("database A");
    SimpleDB db2(description.c_str());
    CHECK(description == std::string(db2.getDescription()));
} // testConstructors


// ------------------------------------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestSimpleDB::testAccessors(void) {
    SimpleDB db;

    const std::string description("database 2");
    db.setDescription(description.c_str());
    CHECK(description == std::string(db.getDescription()));

    spatialdata::spatialdb::SimpleIOAscii io;
    const std::string filename("db.spatialdb");
    io.setFilename(filename.c_str());
    db.setIOHandler(&io);
    assert(db._iohandler);
    CHECK(filename == std::string(db._iohandler->getFilename()));
} // testAccessors


// ------------------------------------------------------------------------------------------------
// Test getNamesDBValues().
void
spatialdata::spatialdb::TestSimpleDB::testGetNamesDBValues(void) {
    _initializeDB();

    assert(_db);
    assert(_data);

    const char** valueNames = NULL;
    size_t numValues = 0;
    _db->getNamesDBValues(&valueNames, &numValues);
    REQUIRE(_data->numValues == numValues);

    for (size_t i = 0; i < numValues; ++i) {
        CHECK(std::string(_data->names[i]) == std::string(valueNames[i]));
    } // for
    delete[] valueNames;valueNames = NULL;
    numValues = 0;
} // testGetDBValues


// ------------------------------------------------------------------------------------------------
// Test query() using nearest neighbor
void
spatialdata::spatialdb::TestSimpleDB::testQueryNearest(void) {
    _initializeDB();

    assert(_db);
    assert(_data);

    _db->setQueryType(SimpleDB::NEAREST);
    _checkQuery(_data->queryNearest, NULL);
} // testQueryNearest


// ------------------------------------------------------------------------------------------------
// Test query() using linear interpolation
void
spatialdata::spatialdb::TestSimpleDB::testQueryLinear(void) {
    _initializeDB();

    assert(_db);
    assert(_data);

    _db->setQueryType(SimpleDB::LINEAR);
    _checkQuery(_data->queryLinear, _data->errFlags);
} // _testQueryLinear


// ------------------------------------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleDB::_initializeDB(void) {
    assert(_data);

    SimpleDBData* dbData = new SimpleDBData;
    dbData->allocate(_data->numLocs, _data->numValues, _data->spaceDim, _data->dataDim);
    dbData->setData(_data->dbValues, _data->numLocs, _data->numValues);
    dbData->setCoordinates(_data->dbCoordinates, _data->numLocs, _data->spaceDim);
    dbData->setNames(_data->names, _data->numValues);
    dbData->setUnits(_data->units, _data->numValues);

    assert(_db);
    _db->_data = dbData;
    _db->_query = new SimpleDBQuery(*_db);
    _db->_cs = new spatialdata::geocoords::CSCart();
} // _setupDB


// ------------------------------------------------------------------------------------------------
// Test query method by doing query and checking values returned.
void
spatialdata::spatialdb::TestSimpleDB::_checkQuery(const double* queryData,
                                                  const int* flagsE) {
    assert(queryData);
    assert(_data);
    assert(_db);

    // Query values in reverse order for nontrivial test.
    const size_t numValues = _data->numValues;

    const char** queryNames = numValues > 0 ? new const char*[numValues] : NULL;
    for (size_t i = 0; i < numValues; ++i) {
        queryNames[numValues-i-1] = _data->names[i];
    } // for
    _db->setQueryValues(queryNames, numValues);
    delete[] queryNames;queryNames = NULL;

    double* values = (numValues > 0) ? new double[numValues] : 0;
    const double tolerance = 1.0e-06;

    const size_t spaceDim = _data->spaceDim;
    const size_t numQueries = _data->numQueries;
    const size_t locSize = spaceDim + numValues;
    spatialdata::geocoords::CSCart csCart;
    for (size_t iQuery = 0; iQuery < numQueries; ++iQuery) {
        const double* coordinates = &queryData[iQuery*locSize];
        const double* valuesE = &queryData[iQuery*locSize+spaceDim];
        const int err = _db->query(values, numValues, coordinates, spaceDim, &csCart);
        if (flagsE) {
            CHECK(flagsE[iQuery] == err);
        } else {
            CHECK(0 == err);
        } // if/else
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            const double valueE = valuesE[numValues-iVal-1];
            const double toleranceV = fabs(valueE) > 0.0 ? fabs(valueE) * tolerance : tolerance;
            CHECK_THAT(values[iVal], Catch::Matchers::WithinAbs(valueE, toleranceV));
        } // for
    } // for
    delete[] values;values = NULL;
} // _checkQuery


// ------------------------------------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::TestSimpleDB_Data::TestSimpleDB_Data(void) :
    numLocs(0),
    spaceDim(0),
    numValues(0),
    dataDim(0),
    numQueries(0),
    dbCoordinates(NULL),
    dbValues(NULL),
    names(NULL),
    units(NULL),
    queryNearest(NULL),
    queryLinear(NULL),
    errFlags(NULL) {}


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleDB_Data::~TestSimpleDB_Data(void) {
    // Set members holding static const data to NULL (no deallocation).
    dbCoordinates = NULL;
    dbValues = NULL;
    names = NULL;
    units = NULL;
    queryNearest = NULL;
    queryLinear = NULL;
    errFlags = NULL;
} // destructor


// End of file
