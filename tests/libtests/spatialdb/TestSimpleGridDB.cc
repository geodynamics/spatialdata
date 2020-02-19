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

#include "TestSimpleGridDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleGridDB.hh" // USES SimpleGridDB
#include "spatialdata/spatialdb/SimpleGridAscii.hh" // USES SimpleGridAscii

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

// ----------------------------------------------------------------------
// Setup testing data.
void
spatialdata::spatialdb::TestSimpleGridDB::setUp(void) {
    _data = new TestSimpleGridDB_Data;CPPUNIT_ASSERT(_data);
} // setUp


// ----------------------------------------------------------------------
// Tear down testing data.
void
spatialdata::spatialdb::TestSimpleGridDB::tearDown(void) {
    delete _data;_data = NULL;
} // tearDown


// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleGridDB::testConstructor(void) {
    SimpleGridDB db;
} // testConstructor


// ----------------------------------------------------------------------
// Test label()
void
spatialdata::spatialdb::TestSimpleGridDB::testAccessors(void) {
    SimpleGridDB db;
    const std::string label("database 2");
    const std::string filename("mydb.spatialdb");

    db.setLabel(label.c_str());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in label.", label, std::string(db.getLabel()));

    db.setFilename(filename.c_str());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in filename.", filename, db._filename);

    // Test default (nearest)
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default query type.", SimpleGridDB::NEAREST, db._queryType);

    db.setQueryType(SimpleGridDB::LINEAR);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in linear query type.", SimpleGridDB::LINEAR, db._queryType);

    db.setQueryType(SimpleGridDB::NEAREST);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in nearest query type.", SimpleGridDB::NEAREST, db._queryType);
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
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in indexA.", indexA, index, tolerance);

    const double xB = -1.0;
    const double indexB = 1.0;
    index = db._search(xB, x, numX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in indexB.", indexB, index, tolerance);

    const double xC = +3.0;
    const double indexC = 2.6;
    index = db._search(xC, x, numX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in indexC.", indexC, index, tolerance);

    const double xD = -20.0;
    const double indexD = 0.0;
    index = db._search(xD, x, numX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in indexD.", indexD, index, tolerance);

    db.setQueryType(SimpleGridDB::LINEAR);

    // Test data and expected results
    const double xE = -20.0;
    const double indexE = -1.0;
    index = db._search(xE, x, numX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in indexE.", indexE, index, tolerance);

    const double xF = -1.0;
    const double indexF = 1.0;
    index = db._search(xF, x, numX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in indexF.", indexF, index, tolerance);

    const double xG = +3.0;
    const double indexG = 2.6;
    index = db._search(xG, x, numX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in indexG.", indexG, index, tolerance);

    const double xH = -20.0;
    const double indexH = -1.0;
    index = db._search(xH, x, numX);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in indexH.", indexH, index, tolerance);
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

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in index 0.", size_t(0), db._getDataIndex(0, db._numX, 0, db._numY, 0, db._numZ));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in index z.", size_t(1*3*4*10), db._getDataIndex(0, db._numX, 0, db._numY, 1, db._numZ));

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in index y.", size_t(1*4*10), db._getDataIndex(0, db._numX, 1, db._numY, 0, db._numZ));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in index yz.", size_t(4*3*4*10 + 1*4*10), db._getDataIndex(0, db._numX, 1, db._numY, 4, db._numZ));

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in index x.", size_t(1*10), db._getDataIndex(1, db._numX, 0, db._numY, 0, db._numZ));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in index xyz.", size_t(3*4*3*10 + 1*4*10 + 2*10), db._getDataIndex(2, db._numX, 1, db._numY, 3, db._numZ));
} // testDataIndex


// ----------------------------------------------------------------------
// Test query() using nearest neighbor.
void
spatialdata::spatialdb::TestSimpleGridDB::testQueryNearest(void) {
    CPPUNIT_ASSERT(_data);

    SimpleGridDB db;
    _setupDB(&db);
    db.setQueryType(SimpleGridDB::NEAREST);
    _checkQuery(db, _data->names, _data->queryNearest, 0, _data->numQueries, _data->spaceDim, _data->numValues);
} // _testQueryNearest


// ----------------------------------------------------------------------
// Test query() using linear interpolation.
void
spatialdata::spatialdb::TestSimpleGridDB::testQueryLinear(void) {
    CPPUNIT_ASSERT(_data);

    SimpleGridDB db;
    _setupDB(&db);
    db.setQueryType(SimpleGridDB::LINEAR);
    _checkQuery(db, _data->names, _data->queryLinear, _data->errFlags, _data->numQueries, _data->spaceDim, _data->numValues);
} // _testQueryLinear


// ----------------------------------------------------------------------
// Test read().
void
spatialdata::spatialdb::TestSimpleGridDB::testRead(void) {
    CPPUNIT_ASSERT(_data);

    SimpleGridDB db;
    db.setFilename(_data->filename);
    db.open();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in spatial dimension.", _data->spaceDim, db._spaceDim);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", _data->numValues, db._numValues);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in data dimension.", _data->dataDim, db._dataDim);

    const size_t numValues = _data->numValues;
    for (size_t i = 0; i < numValues; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in names of values.", std::string(_data->names[i]), db._names[i]);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in units of values.", std::string(_data->units[i]), db._units[i]);
    } // for

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along x-axis.", _data->numX, db._numX);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along y-axis.", _data->numY, db._numY);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along z-axis.", _data->numZ, db._numZ);

    const double tolerance = 1.0e-6;
    size_t totalSize = 1;
    if (_data->numX > 1) {
        totalSize *= _data->numX;
        for (size_t i = 0; i < _data->numX; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in x coordinates.", _data->dbX[i], db._x[i], tolerance);
        } // for
    } // if
    if (_data->numY > 1) {
        totalSize *= _data->numY;
        for (size_t i = 0; i < _data->numY; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in y coordinates.", _data->dbY[i], db._y[i], tolerance);
        } // for
    } // if
    if (_data->numZ > 1) {
        totalSize *= _data->numZ;
        for (size_t i = 0; i < _data->numZ; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in z coordinates.", _data->dbZ[i], db._z[i], tolerance);
        } // for
    } // if

    for (size_t i = 0; i < totalSize; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in data values.", _data->dbData[i], db._data[i], tolerance);
    } // for
} // testRead


// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleGridDB::_setupDB(SimpleGridDB* const db) {
    CPPUNIT_ASSERT(db);
    CPPUNIT_ASSERT(_data);
    CPPUNIT_ASSERT(_data->numValues > 0);

    delete[] db->_x;db->_x = NULL;
    delete[] db->_y;db->_y = NULL;
    delete[] db->_z;db->_z = NULL;
    delete[] db->_data;db->_data = NULL;
    delete[] db->_names;db->_names = NULL;
    delete[] db->_units;db->_units = NULL;

    db->setLabel("Test database");
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
                                                      char** const names,
                                                      const double* queryData,
                                                      const int* flagsE,
                                                      const size_t numQueries,
                                                      const size_t spaceDim,
                                                      const size_t numValues) {
    CPPUNIT_ASSERT(names);
    CPPUNIT_ASSERT(queryData);
    CPPUNIT_ASSERT(numQueries);
    CPPUNIT_ASSERT(spaceDim);
    CPPUNIT_ASSERT(numValues);

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
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in error flag.", flagsE[iQuery], err);
        } else {
            CPPUNIT_ASSERT(!err);
            for (size_t iVal = 0; iVal < numValues; ++iVal) {
                if (valsE[numValues-iVal-1] > tolerance) {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in relative value.", 1.0, vals[iVal]/valsE[numValues-iVal-1], tolerance);
                } else {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in absolute value.", valsE[numValues-iVal-1], vals[iVal], tolerance);
                } // if/else
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
