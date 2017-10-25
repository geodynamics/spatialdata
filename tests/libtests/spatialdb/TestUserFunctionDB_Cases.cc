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

#define DENSITY_1D(x) 100.0*x
#define VS_1D(x) 2.0*x
#define VP_1D(x) 3.5*x

#define DENSITY_2D(x, y) 100.0*x*y
#define VS_2D(x, y) 2.0*x + 0.3*y
#define VP_2D(x, y) 0.2*x + 3.5*y

#define DENSITY_3D(x, y, z) 2.3 + 1.0*x*y + 0.3*z*x
#define VS_3D(x, y, z) 0.34 + 2.0*x + 0.2*y + 4.0*z


// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {

        class TestUserFunctionDB_1D : public TestUserFunctionDB {

	    CPPUNIT_TEST_SUB_SUITE(TestUserFunctionDB_1D, TestUserFunctionDB);
	    CPPUNIT_TEST_SUITE_END();
	    
	private:
	    
	    static int density(double* value, const double* x, const int dim) {
		if (!value || !x || 1 != dim) { return -1; }
		*value = DENSITY_1D(x[0]);
		return 0;
	    } // density

	    static int vs(double* value, const double* x, const int dim) {
		if (!value || !x || 1 != dim) { return -1; }
		*value = VS_1D(x[0]);
		return 0;
	    } // vs

	    static int vp(double* value, const double* x, const int dim) {
		if (!value || !x || 1 != dim) { return -1; }
		*value = VP_1D(x[0]);
		return 0;
	    } // vp

            void setUp(void) {
                TestUserFunctionDB::setUp();
                _data = new TestUserFunctionDB_Data(); CPPUNIT_ASSERT(_data);

		_data->numVals = 3;
		static const char* _values[3] = {"density", "vs", "vp"};
		_data->values = _values;

		static const TestUserFunctionDB_Data::UserData _functions[3] = {
		    { TestUserFunctionDB_1D::density, "kg/m**3", 1.0 },
		    { TestUserFunctionDB_1D::vs, "km/s", 1000.0 },
		    { TestUserFunctionDB_1D::vp, "km/s", 1000.0 },
		};
		_data->functions = const_cast<spatialdata::spatialdb::TestUserFunctionDB_Data::UserData*>(_functions);

		_data->cs = new spatialdata::geocoords::CSCart(); CPPUNIT_ASSERT(_data->cs);
		_data->cs->setSpaceDim(1);

		_data->numQueryPoints = 4;
		static const double _queryXYZ[4*1] = {
		    0.0,
		    -10.0,
		    4.0,
		    0.5,
		};
		_data->queryXYZ = const_cast<double*>(_queryXYZ);
		static const double _queryValues[4*3] = {
 		    DENSITY_1D(0.0), VS_1D(0.0), VP_1D(0.0),
 		    DENSITY_1D(-10.0), VS_1D(-10.0), VP_1D(-10.0),
 		    DENSITY_1D(4.0), VS_1D(4.0), VP_1D(4.0),
 		    DENSITY_1D(0.5), VS_1D(0.5), VP_1D(0.5),
		};
		_data->queryValues = const_cast<double*>(_queryValues);

            } // setUp

        }; // TestUserFunctionDB_1D
        CPPUNIT_TEST_SUITE_REGISTRATION(TestUserFunctionDB_1D);


        class TestUserFunctionDB_2D : public TestUserFunctionDB {

	    CPPUNIT_TEST_SUB_SUITE(TestUserFunctionDB_2D, TestUserFunctionDB);
	    CPPUNIT_TEST_SUITE_END();
	    
	private:
	    
	    static int density(double* value, const double* xy, const int dim) {
		if (!value || !xy || 2 != dim) { return -1; }
		*value = DENSITY_2D(xy[0], xy[1]);
		return 0;
	    } // density

	    static int vs(double* value, const double* xy, const int dim) {
		if (!value || !xy || 2 != dim) { return -1; }
		*value = VS_2D(xy[0], xy[1]);
		return 0;
	    } // vs

	    static int vp(double* value, const double* xy, const int dim) {
		if (!value || !xy || 2 != dim) { return -1; }
		*value = VP_2D(xy[0], xy[1]);
		return 0;
	    } // vp

            void setUp(void) {
                TestUserFunctionDB::setUp();
                _data = new TestUserFunctionDB_Data(); CPPUNIT_ASSERT(_data);

		_data->numVals = 3;
		static const char* _values[3] = {"vs", "vp", "density"};
		_data->values = _values;

		static const TestUserFunctionDB_Data::UserData _functions[3] = {
		    { TestUserFunctionDB_2D::vs, "km/s", 1000.0 },
		    { TestUserFunctionDB_2D::vp, "km/s", 1000.0 },
		    { TestUserFunctionDB_2D::density, "kg/m**3", 1.0 },
		};
		_data->functions = const_cast<spatialdata::spatialdb::TestUserFunctionDB_Data::UserData*>(_functions);

		_data->cs = new spatialdata::geocoords::CSCart(); CPPUNIT_ASSERT(_data->cs);
		_data->cs->setSpaceDim(2);

		_data->numQueryPoints = 4;
		static const double _queryXYZ[4*2] = {
		    0.0, 0.0,
		    -10.0, 4.0,
		    4.0, 2.0, 
		    0.5, 0.1,
		};
		_data->queryXYZ = const_cast<double*>(_queryXYZ);
		static const double _queryValues[4*3] = {
 		    VS_2D(0.0, 0.0),   VP_2D(0.0, 0.0),   DENSITY_2D(0.0, 0.0),
 		    VS_2D(-10.0, 4.0), VP_2D(-10.0, 4.0), DENSITY_2D(-10.0, 4.0),
 		    VS_2D(4.0, 2.0),   VP_2D(4.0, 2.0),	  DENSITY_2D(4.0, 2.0),
 		    VS_2D(0.5, 0.1),   VP_2D(0.5, 0.1),	  DENSITY_2D(0.5, 0.1),
		};
		_data->queryValues = const_cast<double*>(_queryValues);

            } // setUp

        }; // TestUserFunctionDB_2D
        CPPUNIT_TEST_SUITE_REGISTRATION(TestUserFunctionDB_2D);


        class TestUserFunctionDB_3D : public TestUserFunctionDB {

	    CPPUNIT_TEST_SUB_SUITE(TestUserFunctionDB_3D, TestUserFunctionDB);
	    CPPUNIT_TEST_SUITE_END();
	    
	private:
	    
	    static int density(double* value, const double* xyz, const int dim) {
		if (!value || !xyz || 3 != dim) { return -1; }
		*value = DENSITY_3D(xyz[0], xyz[1], xyz[2]);
		return 0;
	    } // density

	    static int vs(double* value, const double* xyz, const int dim) {
		if (!value || !xyz || 3 != dim) { return -1; }
		*value = VS_3D(xyz[0], xyz[1], xyz[2]);
		return 0;
	    } // vs
	    
            void setUp(void) {
                TestUserFunctionDB::setUp();
                _data = new TestUserFunctionDB_Data(); CPPUNIT_ASSERT(_data);

		_data->numVals = 2;
		static const char* _values[3] = {"density", "vs"};
		_data->values = _values;

		static const TestUserFunctionDB_Data::UserData _functions[3] = {
		    { TestUserFunctionDB_3D::density, "kg/m**3", 1.0 },
		    { TestUserFunctionDB_3D::vs, "km/s", 1000.0 },
		};
		_data->functions = const_cast<spatialdata::spatialdb::TestUserFunctionDB_Data::UserData*>(_functions);

		_data->cs = new spatialdata::geocoords::CSCart(); CPPUNIT_ASSERT(_data->cs);
		_data->cs->setSpaceDim(3);

		_data->numQueryPoints = 2;
		static const double _queryXYZ[2*3] = {
		    0.0, 0.0, 0.0,
		    1.0, 4.3, -3.6,
		};
		_data->queryXYZ = const_cast<double*>(_queryXYZ);
		static const double _queryValues[2*2] = {
 		    DENSITY_3D(0.0, 0.0, 0.0), VS_3D(0.0, 0.0, 0.0),
 		    DENSITY_3D(1.0, 4.3, -3.6), VS_3D(1.0, 4.3, -3.6),
		};
		_data->queryValues = const_cast<double*>(_queryValues);

            } // setUp

        }; // TestUserFunctionDB_3D
        CPPUNIT_TEST_SUITE_REGISTRATION(TestUserFunctionDB_3D);


    } // spatialdb
} // spatialdata

// End of file
