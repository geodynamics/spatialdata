// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "utilsfwd.hh"

#include <string> // HASA std::string

/// C++ object for reading/writing points to/from stdin/stdout.
class spatialdata::utils::PointsStream { // class PointsStream
    friend class TestPointsStream;

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor
    PointsStream(void);

    /// Default destructor
    ~PointsStream(void);

    /** Set comment flag.
     *
     * @param flag String identifying comments.
     */
    void setCommentFlag(const char* flag);

    /** Get comment flag.
     *
     * @returns String identifying comments.
     */
    const char* getCommentFlag(void) const;

    /** Set field width.
     *
     * @returns Width of field.
     */
    void setFieldWidth(const size_t width);

    /** Get field width.
     *
     * @returns Width of field.
     */
    size_t getFieldWidth(void) const;

    /** Set precision.
     *
     * @returns Precision.
     */
    void setPrecision(const size_t value);

    /** Get precision.
     *
     * @returns Precision.
     */
    size_t getPrecision(void) const;

    /** Set name of file.
     *
     * If no filename is supplied, stdin/stdout is used.
     *
     * @param filename Name of file
     */
    void setFilename(const char* filename);

    /** Get name of fle.
     *
     * If no filename is supplied, stdin/stdout is used.
     *
     * @returns Name of file
     */
    const char* getFilename(void) const;

    /** Read points from stdin.
     *
     * @param ppPoints Pointer to array of points
     * @param pNumPts Pointer to number of points
     * @param pNumDims Pointer to number of dimensions
     */
    void read(double** ppPoints,
              size_t* pNumPts,
              size_t* pNumDims) const;

    /** Write points to stdout.
     *
     * @param pPoints Array of points
     * @param numPts Number of points
     * @param numDims Number of dimensions
     */
    void write(const double* pPoints,
               const size_t numPts,
               const size_t numDims) const;

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    PointsStream(const PointsStream& p); ///< Not implemented
    const PointsStream& operator=(const PointsStream& p); ///< Not implemented

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    std::string _filename; ///< Name of file for input/output
    std::string _commentFlag; ///< String identifying comments in input
    size_t _fieldWidth; ///< Width of field in output
    size_t _precision; ///< Precision in floating point output

}; // class PointsStream

#include "PointsStream.icc" // inline methods

// End of file
