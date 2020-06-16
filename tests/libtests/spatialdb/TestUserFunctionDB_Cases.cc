// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestUserFunctionDB.hh" // USES TestUserFunctionDB

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestUserFunctionDB_1D;
        class TestUserFunctionDB_2D;
        class TestUserFunctionDB_3D;
    } // spatialdb
} // spatialdata

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestUserFunctionDB_1D : public TestUserFunctionDB {
    CPPUNIT_TEST_SUB_SUITE(TestUserFunctionDB_1D, TestUserFunctionDB);
    CPPUNIT_TEST_SUITE_END();

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

    void setUp(void) {
        TestUserFunctionDB::setUp();
        _data = new TestUserFunctionDB_Data();CPPUNIT_ASSERT(_data);

        _data->numValues = 3;
        static const TestUserFunctionDB_Data::UserData values[3] = {
            {"density", density_units(), 1.0 },
            {"vs", vs_units(), 1000.0 },
            {"vp", vp_units(), 1000.0 },
        };
        _data->values = values;

        _data->cs = new spatialdata::geocoords::CSCart();CPPUNIT_ASSERT(_data->cs);
        _data->cs->setSpaceDim(1);

        _data->numQueryPoints = 4;
        static const double queryXYZ[4*1] = {
            0.0,
            -10.0,
            4.0,
            0.5,
        };
        _data->queryXYZ = queryXYZ;
        static const double queryValues[4*3] = {
            density(0.0),   vs(0.0),   vp(0.0),
            density(-10.0), vs(-10.0), vp(-10.0),
            density(4.0),   vs(4.0),   vp(4.0),
            density(0.5),   vs(0.5),   vp(0.5),
        };
        _data->queryValues = queryValues;

    } // setUp

    void _addValues(void) {
        CPPUNIT_ASSERT(_db);
        _db->addValue("density", density, density_units());
        _db->addValue("vs", vs, vs_units());
        _db->addValue("vp", vp, vp_units());
    } // _addValues

}; // TestUserFunctionDB_1D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestUserFunctionDB_1D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestUserFunctionDB_2D : public TestUserFunctionDB {
    CPPUNIT_TEST_SUB_SUITE(TestUserFunctionDB_2D, TestUserFunctionDB);
    CPPUNIT_TEST_SUITE_END();

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

    void setUp(void) {
        TestUserFunctionDB::setUp();
        _data = new TestUserFunctionDB_Data();CPPUNIT_ASSERT(_data);

        _data->numValues = 3;
        static const TestUserFunctionDB_Data::UserData values[3] = {
            { "vs", vs_units(), 1000.0, },
            { "vp", vp_units(), 1000.0, },
            { "density", density_units(), 1.0, },
        };
        _data->values = values;

        _data->cs = new spatialdata::geocoords::CSCart();CPPUNIT_ASSERT(_data->cs);
        _data->cs->setSpaceDim(2);

        _data->numQueryPoints = 4;
        static const double queryXYZ[4*2] = {
            0.0, 0.0,
            -10.0, 4.0,
            4.0, 2.0,
            0.5, 0.1,
        };
        _data->queryXYZ = queryXYZ;
        static const double queryValues[4*3] = {
            vs(0.0, 0.0),   vp(0.0, 0.0),   density(0.0, 0.0),
            vs(-10.0, 4.0), vp(-10.0, 4.0), density(-10.0, 4.0),
            vs(4.0, 2.0),   vp(4.0, 2.0),   density(4.0, 2.0),
            vs(0.5, 0.1),   vp(0.5, 0.1),   density(0.5, 0.1),
        };
        _data->queryValues = queryValues;

    } // setUp

    void _addValues(void) {
        CPPUNIT_ASSERT(_db);
        _db->addValue("vs", vs, vs_units());
        _db->addValue("vp", vp, vp_units());
        _db->addValue("density", density, density_units());
    } // _addValues

}; // TestUserFunctionDB_2D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestUserFunctionDB_2D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestUserFunctionDB_3D : public TestUserFunctionDB {
    CPPUNIT_TEST_SUB_SUITE(TestUserFunctionDB_3D, TestUserFunctionDB);
    CPPUNIT_TEST_SUITE_END();

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

    void setUp(void) {
        TestUserFunctionDB::setUp();
        _data = new TestUserFunctionDB_Data();CPPUNIT_ASSERT(_data);

        _data->numValues = 2;
        static const TestUserFunctionDB_Data::UserData values[2] = {
            { "density", density_units(), 1.0, },
            { "vs", vs_units(), 1000.0, },
        };
        _data->values = values;

        _data->cs = new spatialdata::geocoords::CSCart();CPPUNIT_ASSERT(_data->cs);
        _data->cs->setSpaceDim(3);

        _data->numQueryPoints = 2;
        static const double queryXYZ[2*3] = {
            0.0, 0.0, 0.0,
            1.0, 4.3, -3.6,
        };
        _data->queryXYZ = queryXYZ;
        static const double queryValues[2*2] = {
            density(0.0, 0.0, 0.0),  vs(0.0, 0.0, 0.0),
            density(1.0, 4.3, -3.6), vs(1.0, 4.3, -3.6),
        };
        _data->queryValues = queryValues;

    } // setUp

    void _addValues(void) {
        CPPUNIT_ASSERT(_db);
        _db->addValue("density", density, density_units());
        _db->addValue("vs", vs, vs_units());
    } // _addValues

}; // TestUserFunctionDB_3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestUserFunctionDB_3D);

// End of file
