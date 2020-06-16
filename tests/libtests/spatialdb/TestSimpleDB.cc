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

#include "TestSimpleDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery
#include "spatialdata/spatialdb/SimpleIOAscii.hh" // USES SimpleIOAscii

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

// ----------------------------------------------------------------------
// Initialize test subject.
void
spatialdata::spatialdb::TestSimpleDB::setUp(void) {
    _db = new SimpleDB();
    _data = NULL;
} // setUp


// ----------------------------------------------------------------------
// Deallocate test data;
void
spatialdata::spatialdb::TestSimpleDB::tearDown(void) {
    delete _db;_db = NULL;
    delete _data;_data = NULL;
} // testDown


// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleDB::testConstructors(void) {
    SimpleDB db;

    const std::string label("database A");
    SimpleDB db2(label.c_str());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in database label.", label, std::string(db2.getLabel()));
} // testConstructors


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestSimpleDB::testAccessors(void) {
    CPPUNIT_ASSERT(_db);

    const std::string label("database 2");
    _db->setLabel(label.c_str());
    CPPUNIT_ASSERT_EQUAL(label, std::string(_db->getLabel()));

    spatialdata::spatialdb::SimpleIOAscii io;
    const std::string filename("db.spatialdb");
    io.setFilename(filename.c_str());
    _db->setIOHandler(&io);
    CPPUNIT_ASSERT(_db->_iohandler);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in I/O handler filename.", filename, std::string(_db->_iohandler->getFilename()));
} // testAccessors


// ----------------------------------------------------------------------
// Test getNamesDBValues().
void
spatialdata::spatialdb::TestSimpleDB::testGetNamesDBValues(void) {
    _initializeDB();

    CPPUNIT_ASSERT(_db);
    CPPUNIT_ASSERT(_data);

    const char** valueNames = NULL;
    size_t numValues = 0;
    _db->getNamesDBValues(&valueNames, &numValues);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", _data->numValues, numValues);

    for (size_t i = 0; i < numValues; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in names of values.",
                                     std::string(_data->names[i]), std::string(valueNames[i]));
    } // for
    delete[] valueNames;valueNames = NULL;
    numValues = 0;
} // testGetDBValues


// ----------------------------------------------------------------------
// Test query() using nearest neighbor
void
spatialdata::spatialdb::TestSimpleDB::testQueryNearest(void) {
    _initializeDB();

    CPPUNIT_ASSERT(_db);
    CPPUNIT_ASSERT(_data);

    _db->setQueryType(SimpleDB::NEAREST);
    _checkQuery(_data->queryNearest, NULL);
} // testQueryNearest


// ----------------------------------------------------------------------
// Test query() using linear interpolation
void
spatialdata::spatialdb::TestSimpleDB::testQueryLinear(void) {
    _initializeDB();

    CPPUNIT_ASSERT(_db);
    CPPUNIT_ASSERT(_data);

    _db->setQueryType(SimpleDB::LINEAR);
    _checkQuery(_data->queryLinear, _data->errFlags);
} // _testQueryLinear


// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleDB::_initializeDB(void) {
    CPPUNIT_ASSERT(_data);

    SimpleDBData* dbData = new SimpleDBData;
    dbData->allocate(_data->numLocs, _data->numValues, _data->spaceDim, _data->dataDim);
    dbData->setData(_data->dbValues, _data->numLocs, _data->numValues);
    dbData->setCoordinates(_data->dbCoordinates, _data->numLocs, _data->spaceDim);
    dbData->setNames(_data->names, _data->numValues);
    dbData->setUnits(_data->units, _data->numValues);

    CPPUNIT_ASSERT(_db);
    _db->_data = dbData;
    _db->_query = new SimpleDBQuery(*_db);
    _db->_cs = new spatialdata::geocoords::CSCart();
} // _setupDB


// ----------------------------------------------------------------------
// Test query method by doing query and checking values returned.
void
spatialdata::spatialdb::TestSimpleDB::_checkQuery(const double* queryData,
                                                  const int* flagsE) {
    CPPUNIT_ASSERT(queryData);
    CPPUNIT_ASSERT(_data);
    CPPUNIT_ASSERT(_db);

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
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query return value.", flagsE[iQuery], err);
        } else {
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query return value.", 0, err);
        } // if/else
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            if (valuesE[numValues-iVal-1] > tolerance) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, values[iVal]/valuesE[numValues-iVal-1], tolerance);
            } else {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(valuesE[numValues-iVal-1], values[iVal], tolerance);
            } // if/else
        } // for
    } // for
    delete[] values;values = NULL;
} // _checkQuery


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
