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

#include "TestUserFunctionDB.hh" // USES TestUserFunctionDB

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "catch2/catch_test_macros.hpp"

#include <cassert>

namespace spatialdata {
    namespace spatialdb {
        class TestUserFunctionDB_1D;
        class TestUserFunctionDB_2D;
        class TestUserFunctionDB_3D;
    } // spatialdb
} // spatialdata

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestUserFunctionDB_1D {
public:

    // Factories
    static
    TestUserFunctionDB_Data* createData(void);

    static
    UserFunctionDB* createDB(void);

private:

    static double density(const double x) {
        return 100.0*x;
    }

    static const char* density_units(void) {
        return "kg/m**3";
    }

    static double vs(const double x) {
        return 2.0*x;
    }

    static const char* vs_units(void) {
        return "km/s";
    }

    static double vp(const double x) {
        return 3.5*x;
    }

    static const char* vp_units(void) {
        return "km/s";
    }

}; // TestUserFunctionDB_1D

// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestUserFunctionDB_Data*
spatialdata::spatialdb::TestUserFunctionDB_1D::createData(void) {
    spatialdata::spatialdb::TestUserFunctionDB_Data* data = new TestUserFunctionDB_Data();assert(data);

    data->numValues = 3;
    static const TestUserFunctionDB_Data::UserData values[3] = {
        {"density", density_units(), 1.0 },
        {"vs", vs_units(), 1000.0 },
        {"vp", vp_units(), 1000.0 },
    };
    data->values = values;

    data->cs = new spatialdata::geocoords::CSCart();assert(data->cs);
    data->cs->setSpaceDim(1);

    data->numQueryPoints = 4;
    static const double queryXYZ[4*1] = {
        0.0,
        -10.0,
        4.0,
        0.5,
    };
    data->queryXYZ = queryXYZ;
    static const double queryValues[4*3] = {
        density(0.0),   vs(0.0),   vp(0.0),
        density(-10.0), vs(-10.0), vp(-10.0),
        density(4.0),   vs(4.0),   vp(4.0),
        density(0.5),   vs(0.5),   vp(0.5),
    };
    data->queryValues = queryValues;

    return data;
} // createData


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::UserFunctionDB*
spatialdata::spatialdb::TestUserFunctionDB_1D::createDB(void) {
    UserFunctionDB* db = new UserFunctionDB();assert(db);

    db->addValue("density", density, density_units());
    db->addValue("vs", vs, vs_units());
    db->addValue("vp", vp, vp_units());

    return db;
} // createData


// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestUserFunctionDB_2D {
public:

    // Factories
    static
    TestUserFunctionDB_Data* createData(void);

    static
    UserFunctionDB* createDB(void);

private:

    static double density(const double x,
                          const double y) {
        return 100.0*x*y;
    }

    static const char* density_units(void) {
        return "kg/m**3";
    }

    static double vs(const double x,
                     const double y) {
        return 2.0*x + 0.3*y;
    }

    static const char* vs_units(void) {
        return "km/s";
    }

    static double vp(const double x,
                     const double y) {
        return 0.2*x + 3.5*y;
    }

    static const char* vp_units(void) {
        return "km/s";
    }

}; // TestUserFunctionDB_2D

// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestUserFunctionDB_Data*
spatialdata::spatialdb::TestUserFunctionDB_2D::createData(void) {
    spatialdata::spatialdb::TestUserFunctionDB_Data* data = new TestUserFunctionDB_Data();assert(data);

    data->numValues = 3;
    static const TestUserFunctionDB_Data::UserData values[3] = {
        { "vs", vs_units(), 1000.0, },
        { "vp", vp_units(), 1000.0, },
        { "density", density_units(), 1.0, },
    };
    data->values = values;

    data->cs = new spatialdata::geocoords::CSCart();assert(data->cs);
    data->cs->setSpaceDim(2);

    data->numQueryPoints = 4;
    static const double queryXYZ[4*2] = {
        0.0, 0.0,
        -10.0, 4.0,
        4.0, 2.0,
        0.5, 0.1,
    };
    data->queryXYZ = queryXYZ;
    static const double queryValues[4*3] = {
        vs(0.0, 0.0),   vp(0.0, 0.0),   density(0.0, 0.0),
        vs(-10.0, 4.0), vp(-10.0, 4.0), density(-10.0, 4.0),
        vs(4.0, 2.0),   vp(4.0, 2.0),   density(4.0, 2.0),
        vs(0.5, 0.1),   vp(0.5, 0.1),   density(0.5, 0.1),
    };
    data->queryValues = queryValues;

    return data;
} // createData


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::UserFunctionDB*
spatialdata::spatialdb::TestUserFunctionDB_2D::createDB(void) {
    UserFunctionDB* db = new UserFunctionDB();assert(db);

    db->addValue("vs", vs, vs_units());
    db->addValue("vp", vp, vp_units());
    db->addValue("density", density, density_units());

    return db;
} // _addValues


// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestUserFunctionDB_3D {
public:

    // Factories
    static
    TestUserFunctionDB_Data* createData(void);

    static
    UserFunctionDB* createDB(void);

private:

    static double density(const double x,
                          const double y,
                          const double z) {
        return 2.3 + 1.0*x*y + 0.3*z*x;
    }

    static const char* density_units(void) {
        return "kg/m**3";
    }

    static double vs(const double x,
                     const double y,
                     const double z) {
        return 0.34 + 2.0*x + 0.2*y + 4.0*z;
    }

    static const char* vs_units(void) {
        return "km/s";
    }

}; // TestUserFunctionDB_3D

// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestUserFunctionDB_Data*
spatialdata::spatialdb::TestUserFunctionDB_3D::createData(void) {
    spatialdata::spatialdb::TestUserFunctionDB_Data* data = new TestUserFunctionDB_Data();assert(data);

    data->numValues = 2;
    static const TestUserFunctionDB_Data::UserData values[2] = {
        { "density", density_units(), 1.0, },
        { "vs", vs_units(), 1000.0, },
    };
    data->values = values;

    data->cs = new spatialdata::geocoords::CSCart();assert(data->cs);
    data->cs->setSpaceDim(3);

    data->numQueryPoints = 2;
    static const double queryXYZ[2*3] = {
        0.0, 0.0, 0.0,
        1.0, 4.3, -3.6,
    };
    data->queryXYZ = queryXYZ;
    static const double queryValues[2*2] = {
        density(0.0, 0.0, 0.0),  vs(0.0, 0.0, 0.0),
        density(1.0, 4.3, -3.6), vs(1.0, 4.3, -3.6),
    };
    data->queryValues = queryValues;

    return data;
} // setUp


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::UserFunctionDB*
spatialdata::spatialdb::TestUserFunctionDB_3D::createDB(void) {
    UserFunctionDB* db = new UserFunctionDB();assert(db);

    db->addValue("density", density, density_units());
    db->addValue("vs", vs, vs_units());

    return db;
} // createDB


// ------------------------------------------------------------------------------------------------
// Static test cases
TEST_CASE("TestUserFunctionDB::testConstructor", "[TestUserFunctionDB]") {
    spatialdata::spatialdb::TestUserFunctionDB::testConstructor();
}
TEST_CASE("TestUserFunctionDB::testDescription", "[TestUserFunctionDB]") {
    spatialdata::spatialdb::TestUserFunctionDB::testDescription();
}
TEST_CASE("TestUserFunctionDB::testCoordsys", "[TestUserFunctionDB]") {
    spatialdata::spatialdb::TestUserFunctionDB::testCoordsys();
}

// Data test cases
TEST_CASE("TestUserFunctionDB::testAddValue", "[TestUserFunctionDB][1D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_1D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_1D::createDB()).testAddValue();
}
TEST_CASE("TestUserFunctionDB::testOpenClose", "[TestUserFunctionDB][1D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_1D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_1D::createDB()).testOpenClose();
}
TEST_CASE("TestUserFunctionDB::testGetNamesDBValues", "[TestUserFunctionDB][1D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_1D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_1D::createDB()).testGetNamesDBValues();
}
TEST_CASE("TestUserFunctionDB::testQueryVals", "[TestUserFunctionDB][1D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_1D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_1D::createDB()).testQueryVals();
}
TEST_CASE("TestUserFunctionDB::testQuery", "[TestUserFunctionDB][1D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_1D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_1D::createDB()).testQuery();
}

TEST_CASE("TestUserFunctionDB::testAddValue", "[TestUserFunctionDB][2D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_2D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_2D::createDB()).testAddValue();
}
TEST_CASE("TestUserFunctionDB::testOpenClose", "[TestUserFunctionDB][2D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_2D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_2D::createDB()).testOpenClose();
}
TEST_CASE("TestUserFunctionDB::testGetNamesDBValues", "[TestUserFunctionDB][2D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_2D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_2D::createDB()).testGetNamesDBValues();
}
TEST_CASE("TestUserFunctionDB::testQueryVals", "[TestUserFunctionDB][2D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_2D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_2D::createDB()).testQueryVals();
}
TEST_CASE("TestUserFunctionDB::testQuery", "[TestUserFunctionDB][2D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_2D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_2D::createDB()).testQuery();
}

TEST_CASE("TestUserFunctionDB::testAddValue", "[TestUserFunctionDB][3D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_3D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_3D::createDB()).testAddValue();
}
TEST_CASE("TestUserFunctionDB::testOpenClose", "[TestUserFunctionDB][3D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_3D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_3D::createDB()).testOpenClose();
}
TEST_CASE("TestUserFunctionDB::testGetNamesDBValues", "[TestUserFunctionDB][3D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_3D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_3D::createDB()).testGetNamesDBValues();
}
TEST_CASE("TestUserFunctionDB::testQueryVals", "[TestUserFunctionDB][3D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_3D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_3D::createDB()).testQueryVals();
}
TEST_CASE("TestUserFunctionDB::testQuery", "[TestUserFunctionDB][3D]") {
    spatialdata::spatialdb::TestUserFunctionDB(spatialdata::spatialdb::TestUserFunctionDB_3D::createData(),
                                               spatialdata::spatialdb::TestUserFunctionDB_3D::createDB()).testQuery();
}

// End of file
