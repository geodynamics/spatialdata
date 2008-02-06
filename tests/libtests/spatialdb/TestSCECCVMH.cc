// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSCECCVMH.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SCECCVMH.hh" // USES SCECCVMH

#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include <math.h> // USES fabs()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSCECCVMH );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestSCECCVMH::testConstructor(void)
{ // testConstructor
  SCECCVMH db;
} // testConstructor

// ----------------------------------------------------------------------
// Test Label().
void
spatialdata::spatialdb::TestSCECCVMH::testLabel(void)
{ // testLabel
  SCECCVMH db;
  const char* label = "database 2";
  db.label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test dataDir().
void
spatialdata::spatialdb::TestSCECCVMH::testDataDir(void)
{ // testDataDir
  SCECCVMH db;

  const char* dir = "/path/to/data/dir";

  db.dataDir(dir);

  CPPUNIT_ASSERT_EQUAL(std::string(dir), std::string(db._dataDir));
} // testDataDir

// ----------------------------------------------------------------------
// Test squashed().
void
spatialdata::spatialdb::TestSCECCVMH::testSquashed(void)
{ // testSquashed
  SCECCVMH db;

  const double limitDefault = -2000.0;
  const double limit = -4000.0;

  CPPUNIT_ASSERT_EQUAL(false, db._squashTopo);
  CPPUNIT_ASSERT_EQUAL(limitDefault, db._squashLimit);

  db.squash(true);
  CPPUNIT_ASSERT_EQUAL(true, db._squashTopo);
  CPPUNIT_ASSERT_EQUAL(limitDefault, db._squashLimit);

  db.squash(true, limit);
  CPPUNIT_ASSERT_EQUAL(true, db._squashTopo);
  CPPUNIT_ASSERT_EQUAL(limit, db._squashLimit);
} // testDataDir

// ----------------------------------------------------------------------
// Test queryVals().
void
spatialdata::spatialdb::TestSCECCVMH::testQueryVals(void)
{ // testQueryVals
  SCECCVMH db;

  { // all values
    const int querySize = 7;
    const char* queryNames[] = { 
      "moho-depth",
      "topo-elev",
      "vp-tag",
      "Basement-Depth",
      "vP",
      "DenSity",
      "VS"
    };
    const int queryVals[] = { 
      SCECCVMH::QUERY_MOHODEPTH,
      SCECCVMH::QUERY_TOPOELEV,
      SCECCVMH::QUERY_VPTAG,
      SCECCVMH::QUERY_BASEDEPTH,
      SCECCVMH::QUERY_VP,
      SCECCVMH::QUERY_DENSITY,
      SCECCVMH::QUERY_VS
    };

    db.queryVals(queryNames, querySize);
    CPPUNIT_ASSERT_EQUAL(querySize, db._querySize);
    for (int i=0; i < querySize; ++i)
      CPPUNIT_ASSERT_EQUAL(queryVals[i], db._queryVals[i]);
  } // all values

  { // subset of values
    const int querySize = 3;
    const char* queryNames[] = { 
      "Basement-Depth",
      "vp-tag",
      "VS"
    };
    const int queryVals[] = { 
      SCECCVMH::QUERY_BASEDEPTH,
      SCECCVMH::QUERY_VPTAG,
      SCECCVMH::QUERY_VS
    };

    db.queryVals(queryNames, querySize);
    CPPUNIT_ASSERT_EQUAL(querySize, db._querySize);
    for (int i=0; i < querySize; ++i)
      CPPUNIT_ASSERT_EQUAL(queryVals[i], db._queryVals[i]);
  } // subset of values
} // testQueryVals

#if defined(SCECCVMH_DATADIR)
// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestSCECCVMH::testQuery(void)
{ // testQuery
  SCECCVMH db;
  db.dataDir(SCECCVMH_DATADIR);

  spatialdata::geocoords::CSGeo cs;
  cs.ellipsoid("clrk66");
  cs.datumHoriz("NAD27");
  cs.datumVert("mean sea level");
  cs.initialize();

  const int numLocs = 17;
  const int spaceDim = 3;
  const double lonlatelev[] = {
    -118.560000,  32.550000,  -2450.00,
    -118.513208,  33.884888,  -1400.00,
    -118.520000,  34.120000,  -1400.00,
    -116.400000,  32.340000,  -1000.00,
    -118.337765,  34.095691,  -1770.00,
    -118.337765,  34.095691, -17700.00,
    -117.989344,  34.034148,  -3000.00,

    -125.000000,  35.000000,  -40000.0, // outside domain
    -125.000000,  35.000000,  -35000.0,
    -125.000000,  35.000000,  -28300.0,
    -125.000000,  35.000000,  -15000.0,
    -125.000000,  35.000000,  -4000.0,
    -125.000000,  35.000000,  0.0,

    -115.000000,  30.000000,  -800000.0, // outside domain
    -115.000000,  30.000000,  -4539.0,

    -117.989344,  34.034148,  5000.00, // above domain
    -117.989344,  34.034148,  -500000.0, // below domain
  };
  const double tolerance = 1.0e-06;

  db.open();
  { // all values
    const int querySize = 7;
    const char* queryNames[] = { 
      "moho-depth",
      "topo-elev",
      "vp-tag",
      "Basement-Depth",
      "vP",
      "DenSity",
      "VS"
    };
    const double values[] = {
      -27991.001953, -1115.499268,  2.0, -1326.415405,  5560.209473,  3133.403158,  3333.334131,
      //-27991.00,   -1115.50,      2.00,   -1326.42, 5540.545410,   3126.848633,   3323.004705,
      -27165.316406,   -56.893856,  2.0, -1431.710449,  4384.126953,  2741.375651,  2584.759474,
      -31178.105469,   489.975189,  2.0,    26.471289,  4142.553223,  2660.851074,  2398.752778,
      -34526.414062,   801.209961,  2.0,   631.073059,  5226.578125,  3022.192708,  3148.777736,
      -27857.322266,   106.671280,  3.0, -2361.386963,  4181.372070,  2673.790690,  2432.217302,
      -27857.322266,   106.671280,  0.0, -2361.386963,  6351.574219,  3397.191406,  3707.466394,
      -28512.111328,    93.515053,  2.0, -2860.919189,  4932.721191,  2924.240397,  2968.477965,

      -26312.804688, -50.465275, 1.0, -2875.716553, 7819.771973, 3886.590658, 4473.594442,
      -26312.804688, -50.465275, 1.0, -2875.716553, 7800.935059, 3880.311686, 4459.966373,
      -26312.804688, -50.465275, 0.0, -2875.716553, 6925.244140, 3588.414714, 3962.891997,
      -26312.804688, -50.465275, 0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,
      -26312.804688, -50.465275, 0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,
      -26312.804688, -50.465275, 0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,

      -26906.470703, 3.366069, 1.0, -973.515442, 7800.0, 3880.0, 4459.29424,
      -26906.470703, 3.366069, 2.0, -973.515442, 6642.105469, 3494.035156, 3834.988779,

      -28512.111328,    93.515053,  0.0, -2860.919189, 6649.152832, 3496.384277, 3838.102107,
      -28512.111328,    93.515053,  0.0, -2860.919189, 8159.479492, 3999.826497, 4751.5155415, 
    };
    const int flags[] = {
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,
      0, 0,
      0, 0
    };

    db.queryVals(queryNames, querySize);

    double data[querySize];

    for (int iLoc=0; iLoc < numLocs; ++iLoc) {
      int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
      CPPUNIT_ASSERT_EQUAL(flags[iLoc], err);

      for (int iVal=0; iVal < querySize; ++iVal) {
	const double dataE = values[iLoc*querySize+iVal];
	if (fabs(dataE) > tolerance)
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, data[iVal]/dataE, tolerance);
	else
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(dataE, data[iVal], tolerance);
      } // for
    } // for
  } // all values

  { // subset values
    const int querySize = 2;
    const char* queryNames[] = { 
      "DenSity",
      "vp-tag",
    };
    const double values[] = {
      3133.403158,   2.0,
      2741.375651,   2.0,
      2660.851074,   2.0,
      3022.192708,   2.0,
      2673.790690,   3.0,
      3397.191406,   0.0,
      2924.240397,   2.0,
      3886.590657,   1.0,
      3880.311686,   1.0,
      3588.414714,   0.0,
      3475.256510,   0.0,
      3475.256510,   0.0,
      3475.256510,   0.0,
      3880.000000,   1.0,
      3494.035156,   2.0,
      3496.384277,   0.0,
      3999.826497,   0.0,
    };
    const int flags[] = {
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,
      0, 0,
      0, 0
    };

    db.queryVals(queryNames, querySize);

    double data[querySize];

    for (int iLoc=0; iLoc < numLocs; ++iLoc) {
      int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
      CPPUNIT_ASSERT_EQUAL(flags[iLoc], err);
      
      for (int iVal=0; iVal < querySize; ++iVal) {
	const double dataE = values[iLoc*querySize+iVal];
	if (fabs(dataE) > tolerance)
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, data[iVal]/dataE, tolerance);
	else
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(dataE, data[iVal], tolerance);
      } // for
    } // for
  } // all values

  { // subset values
    const int querySize = 1;
    const char* queryNames[] = { 
      "vs",
    };
    const double values[] = {
      3333.334131,
      2584.759474,
      2398.752778,
      3148.777736,
      2432.217302,
      3707.466394,
      2968.477965,

      4473.594442,
      4459.966373,
      3962.891997,
      3810.172109,
      3810.172109,
      3810.172109,

      4459.29424,
      3834.988779,

      3838.102107,
      4751.5155415, 
    };
    const int flags[] = {
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,
      0, 0,
      0, 0
    };

    db.queryVals(queryNames, querySize);

    double data[querySize];

    for (int iLoc=0; iLoc < numLocs; ++iLoc) {
      int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
      CPPUNIT_ASSERT_EQUAL(flags[iLoc], err);
      
      for (int iVal=0; iVal < querySize; ++iVal) {
	const double dataE = values[iLoc*querySize+iVal];
	if (fabs(dataE) > tolerance)
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, data[iVal]/dataE, tolerance);
	else
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(dataE, data[iVal], tolerance);
      } // for
    } // for
  } // all values

  db.close();
} // testQuery

// ----------------------------------------------------------------------
// Test query() with squashing.
void
spatialdata::spatialdb::TestSCECCVMH::testQuerySquashed(void)
{ // testQuerySquashed
  SCECCVMH db;
  db.dataDir(SCECCVMH_DATADIR);

  spatialdata::geocoords::CSGeo cs;
  cs.ellipsoid("clrk66");
  cs.datumHoriz("NAD27");
  cs.datumVert("mean sea level");
  cs.initialize();

  const int numLocs = 17;
  const int spaceDim = 3;
  const double lonlatelev[] = {
    -118.560000,  32.550000,  -2450.00,
    -118.513208,  33.884888,  -1400.00+56.893856,
    -118.520000,  34.120000,  -1400.00-489.975189,
    -116.400000,  32.340000,  -1000.00-801.209961,
    -118.337765,  34.095691,  -1770.00-106.671280,
    -118.337765,  34.095691, -17700.00,
    -117.989344,  34.034148,  -3000.00,

    -125.000000,  35.000000,  -40000.0, // outside domain
    -125.000000,  35.000000,  -35000.0,
    -125.000000,  35.000000,  -28300.0,
    -125.000000,  35.000000,  -15000.0,
    -125.000000,  35.000000,  -4000.0,
    -125.000000,  35.000000,  0.0-50.465275,

    -115.000000,  30.000000,  -800000.0, // outside domain
    -115.000000,  30.000000,  -4539.0,

    -117.989344,  34.034148,  5000.00, // above domain
    -117.989344,  34.034148,  -500000.0, // below domain
  };
  const double tolerance = 1.0e-06;

  db.open();
  { // all values
    const int querySize = 7;
    const char* queryNames[] = { 
      "moho-depth",
      "topo-elev",
      "vp-tag",
      "Basement-Depth",
      "vP",
      "DenSity",
      "VS"
    };
    const double values[] = {
      -27991.001953, -1115.499268,  2.0, -1326.415405,  5560.209473,  3133.403158,  3333.334131,
      //-27991.00,   -1115.50,      2.00,   -1326.42, 5540.545410,   3126.848633,   3323.004705,
      -27165.316406,   -56.893856,  2.0, -1431.710449,  4384.126953,  2741.375651,  2584.759474,
      -31178.105469,   489.975189,  2.0,    26.471289,  4142.553223,  2660.851074,  2398.752778,
      -34526.414062,   801.209961,  2.0,   631.073059,  5226.578125,  3022.192708,  3148.777736,
      -27857.322266,   106.671280,  3.0, -2361.386963,  4181.372070,  2673.790690,  2432.217302,
      -27857.322266,   106.671280,  0.0, -2361.386963,  6351.574219,  3397.191406,  3707.466394,
      -28512.111328,    93.515053,  2.0, -2860.919189,  4932.721191,  2924.240397,  2968.477965,

      -26312.804688,   -50.465275,  1.0, -2875.716553, 7819.771973, 3886.590658, 4473.594442,
      -26312.804688,   -50.465275,  1.0, -2875.716553, 7800.935059, 3880.311686, 4459.966373,
      -26312.804688,   -50.465275,  0.0, -2875.716553, 6925.244140, 3588.414714, 3962.891997,
      -26312.804688,   -50.465275,  0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,
      -26312.804688,   -50.465275,  0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,
      -26312.804688,   -50.465275,  0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,

      -26906.470703,   3.36606908,  1.0,  -973.515442, 7800.0, 3880.0, 4459.29424,
      -26906.470703,   3.36606908,  2.0,  -973.515442, 6642.105469, 3494.035156, 3834.988779,

      -28512.111328,    93.515053,  0.0, -2860.919189, 6649.152832, 3496.384277, 3838.102107,
      -28512.111328,    93.515053,  0.0, -2860.919189, 8159.479492, 3999.826497, 4751.5155415, 
    };
    const int flags[] = {
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,
      0, 0,
      0, 0
    };

    db.squash(true);
    db.queryVals(queryNames, querySize);

    double data[querySize];

    for (int iLoc=0; iLoc < numLocs; ++iLoc) {
      int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
      CPPUNIT_ASSERT_EQUAL(flags[iLoc], err);

      for (int iVal=0; iVal < querySize; ++iVal) {
	const double dataE = values[iLoc*querySize+iVal];
	if (fabs(dataE) > tolerance)
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, data[iVal]/dataE, tolerance);
	else
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(dataE, data[iVal], tolerance);
      } // for
    } // for
  } // all values

  db.close();
} // testQuerySquashed
#endif

// ----------------------------------------------------------------------
// Test calcDensity()
void
spatialdata::spatialdb::TestSCECCVMH::testCalcDensity(void)
{ // testCalcDensity
  const int size = 10;
  const double vp[] = {
    -99999.00,
    5540.545410,
    4384.126953,
    4142.553223,
    5226.578125,
    4181.372070,
    6351.574219,
    4932.721191,
    1480.0,
    1860.0,
  };
  const double densityE[] = {
    -99999.00,
    3126.848633,
    2741.375488,
    2660.851074,
    3022.192871,
    2673.790527,
    3397.191406,
    2924.240234,
    1000.0,
    2000.0,
  };

  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i) {
    const double density = SCECCVMH::_calcDensity(vp[i]);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,
				 density/densityE[i], tolerance);
  } // for
} // testCalcDensity

// ----------------------------------------------------------------------
// Test calcVs()
void
spatialdata::spatialdb::TestSCECCVMH::testCalcVs(void)
{ // testCalcVs
  const int size = 10;
  const double vp[] = {
    -99999.00,
    5540.545410,
    4384.126953,
    4142.553223,
    5226.578125,
    4181.372070,
    6351.574219,
    4932.721191,
    1480.0,
    1860.0,
  };
  const double vsE[] = {
    -99999.00,
    3323.004705,
    2584.759846,
    2398.752778,
    3148.777937,
    2432.217302,
    3707.466393753004,
    2968.477865,
    0.0,
    431.0344827586207,
  };

  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i) {
    const double vs = SCECCVMH::_calcVs(vp[i]);
    if (fabs(vsE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,
				   vs/vsE[i], tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(vsE[i], vs, tolerance);
  } // for
} // testCalcVs


// End of file 