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

#include "TestConverter.hh" // Implementation of class methods

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/CSGeoLocal.hh" // USES CSGeoLocal

#include "catch2/catch_test_macros.hpp"

namespace spatialdata {
    namespace geocoords {
        class TestConverter_Cases;
    } // geocoords
} // spatialdata

class spatialdata::geocoords::TestConverter_Cases {
public:

    // Factory methods
    static
    TestConverter_Data* NAD27ToWGS84(void);

    static
    TestConverter_Data* WGS84ToNAD27(void);

    static
    TestConverter_Data* WGS84ToECEF(void);

    static
    TestConverter_Data* WGS84ToUTMLocal(void);

    static
    TestConverter_Data* XYZToXYZ(void);

    static
    TestConverter_Data* Units(void);

};

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestConverter::testConstructor", "[TestConverter]") {
    spatialdata::geocoords::TestConverter::testConstructor();
}

TEST_CASE("TestConverter::NAD27ToWGS84", "[TestConverter]") {
    spatialdata::geocoords::TestConverter(spatialdata::geocoords::TestConverter_Cases::NAD27ToWGS84()).testConvert();
}
TEST_CASE("TestConverter::WGS84ToNAD27", "[TestConverter]") {
    spatialdata::geocoords::TestConverter(spatialdata::geocoords::TestConverter_Cases::WGS84ToNAD27()).testConvert();
}
TEST_CASE("TestConverter::WGS84ToUTMLocal", "[TestConverter]") {
    spatialdata::geocoords::TestConverter(spatialdata::geocoords::TestConverter_Cases::WGS84ToUTMLocal()).testConvert();
}
TEST_CASE("TestConverter::WGS84ToECEF", "[TestConverter]") {
    spatialdata::geocoords::TestConverter(spatialdata::geocoords::TestConverter_Cases::WGS84ToECEF()).testConvert();
}
TEST_CASE("TestConverter::XYZToXYZ", "[TestConverter]") {
    spatialdata::geocoords::TestConverter(spatialdata::geocoords::TestConverter_Cases::XYZToXYZ()).testConvert();
}
TEST_CASE("TestConverter::Units", "[TestConverter]") {
    spatialdata::geocoords::TestConverter(spatialdata::geocoords::TestConverter_Cases::Units()).testConvert();
}

// ------------------------------------------------------------------------------------------------
spatialdata::geocoords::TestConverter_Data*
spatialdata::geocoords::TestConverter_Cases::NAD27ToWGS84(void) {
    TestConverter_Data* data = new TestConverter_Data();assert(data);

    data->numPoints = 6;
    data->spaceDim = 3;

    static CSGeo csNAD27;
    csNAD27.setString("+proj=longlat +datum=NAD27");
    csNAD27.setSpaceDim(data->spaceDim);
    data->csSrc = &csNAD27;

    static CSGeo csWGS84;
    csWGS84.setString("+proj=longlat +datum=WGS84");
    csWGS84.setSpaceDim(data->spaceDim);
    data->csDest = &csWGS84;

    static const double coordsLonLatNAD27[6*3] = {
        -1.150000000000e+02,  3.900000000000e+01,  1.200000000000e+01,
        -1.203425320000e+02,  4.323423000000e+01,  1.010000000000e+01,
        -1.213425320000e+02,  4.523423000000e+01,  3.600000000000e+00,
        -1.153425320000e+02,  3.623423000000e+01,  7.200000000000e+00,
        -1.103425320000e+02,  3.923423000000e+01,  1.233000000000e+02,
        -1.073425320000e+02,  3.323423000000e+01,  3.460000000000e+01,
    };
    data->coordsSrc = coordsLonLatNAD27;

    static const double coordsLonLatWGS84[6*3] = {
        -1.150008507633e+02,  3.899994227695e+01,  1.200000018017e+01,
        -1.203436181122e+02,  4.323409740913e+01,  1.010000021373e+01,
        -1.213437106276e+02,  4.523406963911e+01,  3.600000226768e+00,
        -1.153433730158e+02,  3.623419630177e+01,  7.200000158508e+00,
        -1.103432442395e+02,  3.923419970866e+01,  1.233000001811e+02,
        -1.073431211987e+02,  3.323430190358e+01,  3.460000013495e+01,
    };
    data->coordsDest = coordsLonLatWGS84;

    return data;
} // NAD27ToWGS84


// ------------------------------------------------------------------------------------------------
spatialdata::geocoords::TestConverter_Data*
spatialdata::geocoords::TestConverter_Cases::WGS84ToNAD27(void) {
    TestConverter_Data* data = new TestConverter_Data();assert(data);

    data->numPoints = 6;
    data->spaceDim = 3;

    static CSGeo csWGS84;
    csWGS84.setString("+proj=longlat +datum=WGS84");
    csWGS84.setSpaceDim(data->spaceDim);
    data->csSrc = &csWGS84;

    static CSGeo csNAD27;
    csNAD27.setString("EPSG:4267"); // NAD27, latitude/longitude
    csNAD27.setSpaceDim(data->spaceDim);
    data->csDest = &csNAD27;

    static const double coordsLonLatWGS84[6*3] = {
        -1.150008507633e+02,  3.899994227695e+01,  1.200000018017e+01,
        -1.203436181122e+02,  4.323409740913e+01,  1.010000021373e+01,
        -1.213437106276e+02,  4.523406963911e+01,  3.600000226768e+00,
        -1.153433730158e+02,  3.623419630177e+01,  7.200000158508e+00,
        -1.103432442395e+02,  3.923419970866e+01,  1.233000001811e+02,
        -1.073431211987e+02,  3.323430190358e+01,  3.460000013495e+01,
    };
    data->coordsSrc = coordsLonLatWGS84;

    static const double coordsLatLonNAD27[6*3] = {
        3.900000000000e+01,  -1.150000000000e+02,  1.200000000000e+01,
        4.323423000000e+01,  -1.203425320000e+02,  1.010000000000e+01,
        4.523423000000e+01,  -1.213425320000e+02,  3.600000000000e+00,
        3.623423000000e+01,  -1.153425320000e+02,  7.200000000000e+00,
        3.923423000000e+01,  -1.103425320000e+02,  1.233000000000e+02,
        3.323423000000e+01,  -1.073425320000e+02,  3.460000000000e+01,
    };
    data->coordsDest = coordsLatLonNAD27;

    return data;
} // WGS84ToNAD27


// ------------------------------------------------------------------------------------------------
spatialdata::geocoords::TestConverter_Data*
spatialdata::geocoords::TestConverter_Cases::WGS84ToUTMLocal(void) {
    TestConverter_Data* data = new TestConverter_Data();assert(data);

    data->numPoints = 6;
    data->spaceDim = 3;

    static CSGeo csWGS84;
    csWGS84.setString("EPSG:4326"); // WGS84
    csWGS84.setSpaceDim(data->spaceDim);
    data->csSrc = &csWGS84;

    static CSGeoLocal csLocal;
    csLocal.setString("EPSG:32611"); // WGS84 UTM Zone 11N
    csLocal.setSpaceDim(data->spaceDim);
    csLocal.setLocal(500000.0, 3750000.0, 30.0);
    data->csDest = &csLocal;

    static const double coordsLatLonWGS84[6*3] = {
        34.0,  -115.0,  12.0,
        34.2,  -119.6,   10.1,
        35.8,  -117.2,    3.6,
        34.9,  -115.8,    7.2,
        32.0,  -118.3,  123.3,
        33.89036522863132,  -117.0,   34.6,
    };
    data->coordsSrc = coordsLatLonWGS84;

    static const double coordsUTMLocal[6*3] = {
        +152983.836,  104443.885,  12.0,
        -226168.561,  -87405.953,  10.1,
        -121542.068,  174375.157,   3.6,
        +38643.9012,  152342.458,   7.2,
        -1931.97409, -242246.929, 123.3,
        0.0, 0.0,  34.6,
    };
    data->coordsDest = coordsUTMLocal;

    return data;
} // WGS84ToUTMLocal


// ------------------------------------------------------------------------------------------------
spatialdata::geocoords::TestConverter_Data*
spatialdata::geocoords::TestConverter_Cases::WGS84ToECEF(void) {
    TestConverter_Data* data = new TestConverter_Data();assert(data);

    data->numPoints = 6;
    data->spaceDim = 3;

    static CSGeo csWGS84;
    csWGS84.setString("EPSG:4326"); // WGS84, latitude/longitude
    csWGS84.setSpaceDim(data->spaceDim);
    data->csSrc = &csWGS84;

    static CSGeo csECEF;
    csECEF.setString("+proj=geocent +datum=WGS84");
    csECEF.setSpaceDim(data->spaceDim);
    data->csDest = &csECEF;

    static const double coordsLatLonWGS84[6*3] = {
        3.899994227695e+01, -1.150008507633e+02,  -8.950827822595e+00,
        4.323409740913e+01, -1.203436181122e+02,  -9.225051786848e+00,
        4.523406963911e+01, -1.213437106276e+02,  -1.651562577217e+01,
        3.623419630177e+01, -1.153433730158e+02,  -2.018008883950e+01,
        3.923419970866e+01, -1.103432442395e+02,   1.046766831825e+02,
        3.323430190358e+01, -1.073431211987e+02,   1.087924313666e+01,
    };
    data->coordsSrc = coordsLatLonWGS84;

    static const double coordsECEF[6*3] = {
        -2.097658330155e+06, -4.498268420315e+06,  3.992306409748e+06,
        -2.351216279957e+06, -4.016601774689e+06,  4.346479509353e+06,
        -2.340325349141e+06, -3.842552160654e+06,  4.505693105857e+06,
        -2.204701624283e+06, -4.654958696636e+06,  3.749172150551e+06,
        -1.719793652503e+06, -4.638444207813e+06,  4.012555773384e+06,
        -1.591903914839e+06, -5.097499656067e+06,  3.475728975021e+06,
    };
    data->coordsDest = coordsECEF;

    return data;
} // WGS84ToECEF


// ------------------------------------------------------------------------------------------------
spatialdata::geocoords::TestConverter_Data*
spatialdata::geocoords::TestConverter_Cases::XYZToXYZ(void) {
    TestConverter_Data* data = new TestConverter_Data();assert(data);

    data->numPoints = 3;
    data->spaceDim = 3;

    static CSGeo csMeter;
    csMeter.setString("+proj=tmerc +datum=WGS84 +lon_0=-122.6765 +lat_0=45.5231 +k=0.9996 +units=m +vunits=m");
    csMeter.setSpaceDim(data->spaceDim);
    data->csSrc = &csMeter;

    static CSGeo csKilometer;
    csKilometer.setString("+proj=tmerc +datum=WGS84 +lon_0=-122.6765 +lat_0=45.5231 +k=0.9996 +units=km +vunits=km");
    csKilometer.setSpaceDim(data->spaceDim);
    data->csDest = &csKilometer;

    static const double coordsMeter[3*3] = {
        1.0e+2, -5.0e+2, 1.0e+1,
        4.0e+3, -1.5e+3, 1.0e+2,
        -5.0e+4, +2.0e+4, 2.5e+3,
    };
    data->coordsSrc = coordsMeter;

    static const double coordsKilometer[3*3] = {
        1.0e-1, -5.0e-1, 1.0e-2,
        4.0e+0, -1.5e+0, 1.0e-1,
        -5.0e+1, +2.0e+1, 2.5e+0,
    };
    data->coordsDest = coordsKilometer;

    return data;
} // XYZToXYZ


// ------------------------------------------------------------------------------------------------
spatialdata::geocoords::TestConverter_Data*
spatialdata::geocoords::TestConverter_Cases::Units(void) {
    TestConverter_Data* data = new TestConverter_Data();assert(data);

    data->numPoints = 6;
    data->spaceDim = 3;

    static CSCart csMeter;
    csMeter.setToMeters(1.0);
    csMeter.setSpaceDim(data->spaceDim);
    data->csSrc = &csMeter;

    static CSCart csKilometer;
    csKilometer.setToMeters(1.0e+3);
    csKilometer.setSpaceDim(data->spaceDim);
    data->csDest = &csKilometer;

    static const double coordsMeter[6*3] = {
        -1.284640402306e+06,  1.064304544651e+05, -1.314223695069e+05,
        -1.617989794608e+06,  6.524818197004e+05, -2.429529262194e+05,
        -1.637488936912e+06,  8.852730256936e+05, -2.774331769932e+05,
        -1.362847273019e+06, -1.913287267184e+05, -1.500646038350e+05,
        -8.881745594215e+05,  7.658679840913e+04, -6.239198222893e+04,
        -6.825105930858e+05, -6.111332576090e+05, -6.615476230714e+04,
    };
    data->coordsSrc = coordsMeter;

    static const double coordsKilometer[6*3] = {
        -1.284640402306e+03,  1.064304544651e+02, -1.314223695069e+02,
        -1.617989794608e+03,  6.524818197004e+02, -2.429529262194e+02,
        -1.637488936912e+03,  8.852730256936e+02, -2.774331769932e+02,
        -1.362847273019e+03, -1.913287267184e+02, -1.500646038350e+02,
        -8.881745594215e+02,  7.658679840913e+01, -6.239198222893e+01,
        -6.825105930858e+02, -6.111332576090e+02, -6.615476230714e+01,
    };
    data->coordsDest = coordsKilometer;

    return data;
} // Units


// End of file
