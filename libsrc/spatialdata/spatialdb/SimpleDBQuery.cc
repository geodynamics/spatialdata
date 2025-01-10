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

#include "SpatialDB.hh" // USES SimpleDB
#include "SimpleDB.hh" // USES SimpleDB
#include "SimpleDBQuery.hh" // implementation of class methods

#include "SimpleDBData.hh" // USEs SimpleDBData

#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include "Exception.hh" // USES OutOfBounds

#include <math.h> // USES MAXFLOAT
#if !defined(MAXFLOAT)
#define MAXFLOAT 1e+30
#endif

#include <cstring> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <cassert> // USES assert()
#include <sstream> // USES std::ostringsgream
#include <algorithm> // USES std::fill(), std::lower_bound(), std::distance()

// ----------------------------------------------------------------------
// Default constructor.
spatialdata::spatialdb::SimpleDBQuery::SimpleDBQuery(const SimpleDB& db) :
    _queryType(SimpleDB::LINEAR),
    _db(db),
    _converter(new spatialdata::geocoords::Converter),
    _queryValues(NULL),
    _querySize(0) {}


// ----------------------------------------------------------------------
// Default destructor.
spatialdata::spatialdb::SimpleDBQuery::~SimpleDBQuery(void) {
    deallocate();
    delete _converter;_converter = NULL;
} // destructor


// ----------------------------------------------------------------------
// Deallocate data structures.
void
spatialdata::spatialdb::SimpleDBQuery::deallocate(void) {
    delete[] _queryValues;_queryValues = NULL;
    _querySize = 0;
    _nearest.resize(0);
} // deallocate


// ----------------------------------------------------------------------
// Set query type.
void
spatialdata::spatialdb::SimpleDBQuery::setQueryType(const SimpleDB::QueryEnum value) {
    _queryType = value;
} // setQueryType


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SimpleDBQuery::setQueryValues(const char* const* names,
                                                      const size_t numVals) {
    assert(_db._data);
    if (0 == numVals) {
        std::ostringstream msg;
        msg << "Number of values for query in spatial database " << _db.getDescription()
            << "\n must be positive.\n";
        throw std::invalid_argument(msg.str());
    } // if
    assert(names && 0 < numVals);

    _querySize = numVals;
    delete[] _queryValues;_queryValues = new size_t[numVals];
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        size_t iName = 0;
        const size_t numNames = _db._data->getNumValues();
        while (iName < numNames) {
            if (0 == strcasecmp(names[iVal], _db._data->getName(iName))) {
                break;
            }
            ++iName;
        } // while
        if (iName >= numNames) {
            std::ostringstream msg;
            msg << "Could not find value '" << names[iVal] << "' in spatial database '"
                << _db.getDescription() << "'. Available values are:";
            for (size_t iName = 0; iName < numNames; ++iName) {
                msg << "\n  " << _db._data->getName(iName);
            }
            msg << "\n";
            throw std::out_of_range(msg.str());
        } // if
        _queryValues[iVal] = iName;
    } // for
} // setQueryVals


// ----------------------------------------------------------------------
// Query the database.
void
spatialdata::spatialdb::SimpleDBQuery::query(double* vals,
                                             const size_t numVals,
                                             const double* coords,
                                             const size_t numDims,
                                             const spatialdata::geocoords::CoordSys* pCSQuery) {
    assert(0 != coords);

    if (0 == _querySize) {
        std::ostringstream msg;
        msg << "Values to be returned by spatial database " << _db.getDescription() << "\n"
            << "have not been set. Please call setQueryValues() before query().\n";
        throw std::logic_error(msg.str());
    } // if
    else if (numVals != _querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << _db.getDescription() << "\n"
            << "(" << _querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::invalid_argument(msg.str());
    } // if

    const size_t numLocs = 1;
    _q[0] = 0.0;
    _q[1] = 0.0;
    _q[2] = 0.0;
    for (size_t i = 0; i < numDims; ++i) {
        _q[i] = coords[i];
    } // for
    assert(_converter);
    _converter->convert(_q, numLocs, numDims, _db._cs, pCSQuery);

    switch (_queryType) {
    case SimpleDB::LINEAR:
        _queryLinear(vals, numVals);
        break;
    case SimpleDB::NEAREST:
        _queryNearest(vals, numVals);
        break;
    default:
        throw std::logic_error("Could not find requested query type.");
    } // switch
} // query


// ----------------------------------------------------------------------
// Query database using nearest neighbor algorithm.
void
spatialdata::spatialdb::SimpleDBQuery::_queryNearest(double* vals,
                                                     const size_t numVals) {
    assert( (0 < numVals && vals) ||
            (0 == numVals && !vals) );
    assert(_db._data);
    assert(numVals == _querySize);

    size_t iNear = 0;
    const size_t spaceDim = _db._data->getSpaceDim();
    double pt[3];
    _setPoint3(pt, _db._data->getCoordinates(iNear), spaceDim);
    double nearDist = _distSquared(_q, pt);

    const size_t numLocs = _db._data->getNumLocs();
    for (size_t iLoc = 1; iLoc < numLocs; ++iLoc) {
        _setPoint3(pt, _db._data->getCoordinates(iLoc), spaceDim);
        const double dist = _distSquared(_q, pt);
        if (dist < nearDist) {
            nearDist = dist;
            iNear = iLoc;
        } // if
    } // for

    const double* nearVals = _db._data->getData(iNear);
    const size_t querySize = _querySize;
    for (size_t iVal = 0; iVal < querySize; ++iVal) {
        vals[iVal] = nearVals[_queryValues[iVal]];
    }
} // _queryNearest


// ----------------------------------------------------------------------
// Query database using linear interpolation algorithm.
void
spatialdata::spatialdb::SimpleDBQuery::_queryLinear(double* vals,
                                                    const size_t numVals) {
    assert( (0 < numVals && vals) ||
            (0 == numVals && !vals) );
    assert(_db._data);
    assert(numVals == _querySize);

    if (0 == _db._data->getDataDim()) {
        const int index = 0;
        const double* nearVals = _db._data->getData(index);
        const size_t querySize = _querySize;
        for (size_t iVal = 0; iVal < querySize; ++iVal) {
            vals[iVal] = nearVals[_queryValues[iVal]];
        }
    } else { // else
        // Find nearest locations in database
        _findNearest();

        // Get interpolation weights
        std::vector<WtStruct> weights;
        _getWeights(&weights);

        // Interpolate values
        const size_t numWts = weights.size();
        const size_t querySize = _querySize;
        for (size_t iVal = 0; iVal < querySize; ++iVal) {
            double val = 0;
            for (size_t iWt = 0; iWt < numWts; ++iWt) {
                const size_t iLoc = _nearest[weights[iWt].nearIndex];
                const double* locVals = _db._data->getData(iLoc);
                val += weights[iWt].wt * locVals[_queryValues[iVal]];
            } // for
            vals[iVal] = val;
        } // for
    } // else
} // _queryLinear


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findNearest(void) {
    assert(_db._data);

    const size_t maxnear = 100;
    const size_t numLocs = _db._data->getNumLocs();
    const size_t nearSize = (numLocs < maxnear) ? numLocs : maxnear;
    _nearest.resize(nearSize);
    std::fill(_nearest.begin(), _nearest.end(), -1);

    std::vector<double> nearestDist(nearSize);
    std::fill(nearestDist.begin(), nearestDist.end(), MAXFLOAT);

    // find closest nearSize points
    double pt[3];
    const size_t spaceDim = _db._data->getSpaceDim();
    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        // use square of distance to find closest
        _setPoint3(pt, _db._data->getCoordinates(iLoc), spaceDim);
        const double dist2 = _distSquared(_q, pt);

        // find place in nearest list if it exists
        const std::vector<double>::iterator pNearDist =
            std::lower_bound(nearestDist.begin(), nearestDist.end(), dist2);
        if (dist2 <= *pNearDist) { // if found place in nearest list
#if !defined(_RWSTD_NO_CLASS_PARTIAL_SPEC)
            size_t index = std::distance(nearestDist.begin(), pNearDist);
#else
            size_t index = 0;
            std::distance(nearestDist.begin(), pNearDist, index);
#endif

            // move values to allow insertion of current
            for (size_t moveIndex = nearSize-1; moveIndex > index; --moveIndex) {
                nearestDist[moveIndex] = nearestDist[moveIndex-1];
                _nearest[moveIndex] = _nearest[moveIndex-1];
            } // for
            if (index < nearSize) {
                // insert current
                nearestDist[index] = dist2;
                _nearest[index] = iLoc;
            } // if
        } // if
    } // for
} // _findNearest


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_getWeights(std::vector<WtStruct>* pWeights) {
    assert(_db._data);
    assert(pWeights);

    /* Start with nearest point. Add next nearest points as necessary
     * to obtain appropriate interpolation. For example, adding 1 point
     * results in linear interpolation, adding 2 results in areal
     * interpolation, etc.
     */
    const size_t dataDim = _db._data->getDataDim();
    if (0 == dataDim) {
        const int numWts = 1;
        pWeights->resize(numWts);
        _findPointPt(pWeights);
    } else if (1 == dataDim) {
        const int numWts = 2;
        pWeights->resize(numWts);
        _findPointPt(pWeights);
        _findLinePt(pWeights);
    } else if (2 == dataDim) {
        const int numWts = 3;
        pWeights->resize(numWts);
        _findPointPt(pWeights);
        _findLinePt(pWeights);
        _findAreaPt(pWeights);
    } else if (3 == dataDim) {
        const int numWts = 4;
        pWeights->resize(numWts);
        _findPointPt(pWeights);
        _findLinePt(pWeights);
        _findAreaPt(pWeights);
        _findVolumePt(pWeights);
    } else {
        throw std::logic_error("Could not set weights for unknown data dimension.");
    } // if/else
} // _getWeights


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findPointPt(std::vector<WtStruct>* pWeights) {
    assert(_db._data);
    assert(pWeights);

    (*pWeights)[0].wt = 1.0;
    (*pWeights)[0].nearIndex = 0;
} // _findPointPt


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findLinePt(std::vector<WtStruct>* pWeights) {
    assert(_db._data);
    assert(pWeights);

    const size_t spaceDim = _db._data->getSpaceDim();

    // best case is to use next nearest pt
    const size_t nearIndexA = (*pWeights)[0].nearIndex;
    size_t nearIndexB = nearIndexA + 1;

    const size_t locIndexA = _nearest[nearIndexA];
    double ptA[3];
    assert(locIndexA >= 0);
    _setPoint3(ptA, _db._data->getCoordinates(locIndexA), spaceDim);

    double wtA = 0;
    double wtB = 0;
    double ptB[3];

    // find nearest pt where we can interpolate
    const size_t nearSize = _nearest.size();
    while (nearIndexB < nearSize) {
        const size_t locIndexB = _nearest[nearIndexB];
        _setPoint3(ptB, _db._data->getCoordinates(locIndexB), spaceDim);

        // wtA = DotProduct(pb, ab) / DotProduct(ab, ab)
        // wtB = DotProduct(ap, ab) / DotProduct(ab, ab)
        const double abX = ptB[0] - ptA[0];
        const double abY = ptB[1] - ptA[1];
        const double abZ = ptB[2] - ptA[2];
        const double abdotab = abX*abX + abY*abY + abZ*abZ;
        const double pbdotab = (ptB[0]-_q[0])*abX + (ptB[1]-_q[1])*abY + (ptB[2]-_q[2])*abZ;
        const double apdotab = (_q[0]-ptA[0])*abX + (_q[1]-ptA[1])*abY + (_q[2]-ptA[2])*abZ;
        wtA = pbdotab / abdotab;
        wtB = apdotab / abdotab;

        const double tolerance = 1e-06;
        if (( wtA >= -tolerance) &&
            ( wtB >= -tolerance) ) {
            // found 2nd point if weights are positive within tolerance level
            // (i.e. interpolation, not extrapolation)
            break;
        }
        ++nearIndexB;
    } // while
    if (nearIndexB >= nearSize) {
        throw OutOfBounds("Could not find points for linear interpolation.");
    }
    (*pWeights)[0].wt = wtA;
    (*pWeights)[1].wt = wtB;
    (*pWeights)[1].nearIndex = nearIndexB;
} // _findLinePt


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findAreaPt(std::vector<WtStruct>* pWeights) { // _findAreaPt
    assert(_db._data);
    assert(pWeights);

    const size_t spaceDim = _db._data->getSpaceDim();

    // best case is to use next nearest pt
    const size_t nearIndexA = (*pWeights)[0].nearIndex;
    const size_t locIndexA = _nearest[nearIndexA];
    double ptA[3];
    _setPoint3(ptA, _db._data->getCoordinates(locIndexA), spaceDim);

    const size_t nearIndexB = (*pWeights)[1].nearIndex;
    const size_t locIndexB = _nearest[nearIndexB];
    double ptB[3];
    _setPoint3(ptB, _db._data->getCoordinates(locIndexB), spaceDim);

    double wtA = 0;
    double wtB = 0;
    double wtC = 0;
    double ptC[3];

    // find nearest pt where we can interpolate
    const size_t nearSize = _nearest.size();
    size_t nearIndexC = nearIndexB + 1;
    while (nearIndexC < nearSize) {
        const size_t locIndexC = _nearest[nearIndexC];
        _setPoint3(ptC, _db._data->getCoordinates(locIndexC), spaceDim);

        double areaABC = 0;
        double dirABC[3];
        _area(&areaABC, dirABC, ptA, ptB, ptC);

#if 0
        // Alternate method of determining collinearity.
        // Compute unit vectors AB and AC, then compute the dot product.
        // If the absolute value of the dot product is somewhat less than 1,
        // the points are not collinear.
        double vecAB[3];
        double vecAC[3];
        double magAB = 0.0;
        double magAC = 0.0;
        for (int iDir = 0; iDir < numCoords; ++iDir) {
            vecAB[iDir] = ptA[iDir] - ptB[iDir];
            vecAC[iDir] = ptA[iDir] - ptC[iDir];
            magAB += vecAB[iDir] * vecAB[iDir];
            magAC += vecAC[iDir] * vecAC[iDir];
        } // for
        magAB = sqrt(magAB);
        magAC = sqrt(magAC);
        double abdotac = 0.0;
        for (int iDir = 0; iDir < numCoords; ++iDir) {
            abdotac += (vecAB[iDir]/magAB) * (vecAC[iDir]/magAC);
        } // for

        const double tolerance = 0.98;
        if (fabs(abdotac) < tolerance) {
#else
        // make sure A,B,C are not collinear by checking if area of
        // triangle ABC is not a tiny fraction of the distance AB

        // length(ab)^2
        const double ab2 =
            pow(ptA[0]-ptB[0], 2) +
            pow(ptA[1]-ptB[1], 2) +
            pow(ptA[2]-ptB[2], 2);

        const double tolerance = 1.0e-06;
        if (areaABC > tolerance*ab2) {
#endif
            // project P onto abc plane
            double qProj[3];
            const double qmod = dirABC[0]*_q[0] + dirABC[1]*_q[1] + dirABC[2]*_q[2];
            qProj[0] = _q[0] - dirABC[0]*qmod;
            qProj[1] = _q[1] - dirABC[1]*qmod;
            qProj[2] = _q[2] - dirABC[2]*qmod;

            // wtA = areaBCQ / areaABC * DotProduct(dirBCQ, dirABC);
            double areaBCQ = 0;
            double dirBCQ[3];
            _area(&areaBCQ, dirBCQ, ptB, ptC, qProj);
            wtA = areaBCQ/areaABC * (dirBCQ[0]*dirABC[0] +
                                     dirBCQ[1]*dirABC[1] +
                                     dirBCQ[2]*dirABC[2]);

            // wtB = areaCAQ / areaABC * DotProduct(dirCAQ, dirABC);
            double areaCAQ = 0;
            double dirCAQ[3];
            _area(&areaCAQ, dirCAQ, ptC, ptA, qProj);
            wtB = areaCAQ/areaABC * (dirCAQ[0]*dirABC[0] +
                                     dirCAQ[1]*dirABC[1] +
                                     dirCAQ[2]*dirABC[2]);

            // wtC = areaABQ / areaABC * DotProduct(dirABQ, dirABC);
            double areaABQ = 0;
            double dirABQ[3];
            _area(&areaABQ, dirABQ, ptA, ptB, qProj);
            wtC = areaABQ/areaABC * (dirABQ[0]*dirABC[0] +
                                     dirABQ[1]*dirABC[1] +
                                     dirABQ[2]*dirABC[2]);

            const double tolerance = 1e-06;
            if (( wtA >= -tolerance) &&
                ( wtB >= -tolerance) &&
                ( wtC >= -tolerance) ) {
                // found 3rd point if weights are positive within tolerance level
                // (i.e. interpolation, not extrapolation)
                break;
            }
        } // if
        ++nearIndexC;
    } // while
    if (nearIndexC >= nearSize) {
        throw OutOfBounds("Could not find points for areal interpolation.");
    }
    (*pWeights)[0].wt = wtA;
    (*pWeights)[1].wt = wtB;
    (*pWeights)[2].wt = wtC;
    (*pWeights)[2].nearIndex = nearIndexC;
} // _findAreaPt


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findVolumePt(std::vector<WtStruct>* pWeights) {
    assert(_db._data);
    assert(pWeights);

    // best case is to use next nearest pt

    const size_t spaceDim = _db._data->getSpaceDim();

    const size_t nearIndexA = (*pWeights)[0].nearIndex;
    const size_t locIndexA = _nearest[nearIndexA];
    double ptA[3];
    _setPoint3(ptA, _db._data->getCoordinates(locIndexA), spaceDim);

    const size_t nearIndexB = (*pWeights)[1].nearIndex;
    const size_t locIndexB = _nearest[nearIndexB];
    double ptB[3];
    _setPoint3(ptB, _db._data->getCoordinates(locIndexB), spaceDim);

    const size_t nearIndexC = (*pWeights)[2].nearIndex;
    const size_t locIndexC = _nearest[nearIndexC];
    double ptC[3];
    _setPoint3(ptC, _db._data->getCoordinates(locIndexC), spaceDim);

    double wtA = 0;
    double wtB = 0;
    double wtC = 0;
    double wtD = 0;
    double ptD[3];

    // find nearest pt where we can interpolate
    const size_t nearSize = _nearest.size();
    size_t nearIndexD = nearIndexC + 1;
    while (nearIndexD < nearSize) {
        const size_t locIndexD = _nearest[nearIndexD];
        _setPoint3(ptD, _db._data->getCoordinates(locIndexD), spaceDim);

        // make sure A,B,C,D are not coplanar by checking if volume of
        // tetrahedron ABCD is not a tiny fraction of the distance AB

        // volume abcd
        const double abcd = _volume(ptA, ptB, ptC, ptD);

        // ab = length(ab)
        const double ab3 =
            pow(pow(ptA[0] - ptB[0], 2) +
                pow(ptA[1] - ptB[1], 2) +
                pow(ptA[2] - ptB[2], 2), 3);

        const double tolerance = 1.0e-06;
        if (fabs(abcd) > tolerance*ab3) {
            // volume pbcd
            const double pbcd = _volume(_q, ptB, ptC, ptD);
            // wtA = vol(pbcd)/vol(abcd)
            wtA = pbcd / abcd;

            // volume apcd
            const double apcd = _volume(ptA, _q, ptC, ptD);
            // wtB = vol(apcd)/vol(abcd)
            wtB = apcd / abcd;

            // volume abpd
            const double abpd = _volume(ptA, ptB, _q, ptD);
            // wtC = vol(abpd)/vol(abcd)
            wtC = abpd / abcd;

            // volume abcp
            const double abcp = _volume(ptA, ptB, ptC, _q);
            // wtD = vol(abcp)/vol(abcd)
            wtD = abcp / abcd;

            const double tolerance = 1e-06;
            if (( wtA >= -tolerance) &&
                ( wtB >= -tolerance) &&
                ( wtC >= -tolerance) &&
                ( wtD >= -tolerance) ) {
                // found 4th point if weights are positive within tolerance level
                // (i.e. interpolation, not extrapolation)
                break;
            }
        } // if
        ++nearIndexD;
    } // while
    if (nearIndexD >= nearSize) {
        throw OutOfBounds("Could not find points for volumetric interpolation.");
    }
    (*pWeights)[0].wt = wtA;
    (*pWeights)[1].wt = wtB;
    (*pWeights)[2].wt = wtC;
    (*pWeights)[3].wt = wtD;
    (*pWeights)[3].nearIndex = nearIndexD;
} // _findVolumePt


// ----------------------------------------------------------------------
// Set coordiantes of point in 3-D space using coordinates in
// current coordinate system.
void
spatialdata::spatialdb::SimpleDBQuery::_setPoint3(double pt3[3],
                                                  const double* pt,
                                                  const size_t spaceDim) {
    pt3[0] = 0.0;
    pt3[1] = 0.0;
    pt3[2] = 0.0;
    memcpy(pt3, pt, spaceDim*sizeof(double));
} // _setPoint3


// ----------------------------------------------------------------------
// Compute square of distance between points A and B.
double
spatialdata::spatialdb::SimpleDBQuery::_distSquared(const double a[3],
                                                    const double b[3]) {
    const double abX = b[0]-a[0];
    const double abY = b[1]-a[1];
    const double abZ = b[2]-a[2];
    const double dist2 = abX*abX + abY*abY + abZ*abZ;
    return dist2;
} // _distSquared


// ----------------------------------------------------------------------
/* Compute area and "direction" of triangle abc. Direction is vector
 * normal to triangular surface.
 */
void
spatialdata::spatialdb::SimpleDBQuery::_area(double* pArea,
                                             double dir[3],
                                             const double* a,
                                             const double* b,
                                             const double* c) {
    assert(pArea);
    assert(dir);

    // AB
    const double abX = b[0] - a[0];
    const double abY = b[1] - a[1];
    const double abZ = b[2] - a[2];

    // AC
    const double acX = c[0] - a[0];
    const double acY = c[1] - a[1];
    const double acZ = c[2] - a[2];

    dir[0] = abY*acZ - abZ*acY;
    dir[1] = abZ*acX - abX*acZ;
    dir[2] = abX*acY - abY*acX;

    *pArea = sqrt(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2]);
    if (0 != *pArea) {
        dir[0] /= *pArea;
        dir[1] /= *pArea;
        dir[2] /= *pArea;
    } // if
    *pArea *= 0.5;
} // _area


// ----------------------------------------------------------------------
double
spatialdata::spatialdb::SimpleDBQuery::_volume(const double a[3],
                                               const double b[3],
                                               const double c[3],
                                               const double d[3]) {
    /* Compute volume of tetrahedral defined by four points. */
    // _volume
    const double det1 =
        b[0] * (c[1]*d[2] - c[2]*d[1]) +
        b[1] * (c[2]*d[0] - c[0]*d[2]) +
        b[2] * (c[0]*d[1] - c[1]*d[0]);
    const double det2 =
        -c[0] * (d[1]*a[2] - d[2]*a[1]) -
        c[1] * (d[2]*a[0] - d[0]*a[2]) -
        c[2] * (d[0]*a[1] - d[1]*a[0]);
    const double det3 =
        d[0] * (a[1]*b[2] - a[2]*b[1]) +
        d[1] * (a[2]*b[0] - a[0]*b[2]) +
        d[2] * (a[0]*b[1] - a[1]*b[0]);
    const double det4 =
        -a[0] * (b[1]*c[2] - b[2]*c[1]) -
        a[1] * (b[2]*c[0] - b[0]*c[2]) -
        a[2] * (b[0]*c[1] - b[1]*c[0]);
    return (det1 + det2 + det3 + det4) / 6.0;
} // _volume


// End of file
