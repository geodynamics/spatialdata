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

/** @file libsrc/spatialdb/TimeHistory.h
 *
 * @brief C++ object for time dependence in spatial databases. Time
 * history is applied independently of the spatial variation.
 */

#if !defined(spatialdata_spatialdb_timehistory_hh)
#define spatialdata_spatialdb_timehistory_hh

#include "spatialdbfwd.hh"

#include <string> // HASA std::string

/// C++ object for time dependence in spatial databases.
class spatialdata::spatialdb::TimeHistory { // class TimeHistory
    friend class TestTimeHistory;

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor.
    TimeHistory(void);

    /** Constructor with label.
     *
     * @param label Label for database
     */
    TimeHistory(const char* label);

    /// Default destructor.
    ~TimeHistory(void);

    /** Set label of time history.
     *
     * @param label Label for time history.
     */
    void label(const char* label);

    /** Get label of time history.
     *
     * @returns Label for time history.
     */
    const char* label(void) const;

    /** Set filename for time history.
     *
     * @param name Name of file.
     */
    void filename(const char* name);

    /** Set filename for time history.
     *
     * @return Name of file.
     */
    const char* filename(void);

    /// Open the time history and prepare for querying.
    void open(void);

    /// Close the time history.
    void close(void);

    /** Query the database.
     *
     * @pre Must call open() before query()
     *
     * @param value Value in time history.
     * @param t Time for query.
     *
     * @returns 0 on success, 1 on failure (i.e., could not interpolate)
     */
    int query(double* value,
              const double t);

    /** Query the database.
     *
     * @pre Must call open() before query()
     *
     * @param value Value in time history.
     * @param t Time for query.
     *
     * @returns 0 on success, 1 on failure (i.e., could not interpolate)
     */
    int query(float* value,
              const float t);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    std::string _label; ///< Label of time history.
    std::string _filename; ///< Name of time history file
    double* _time; ///< Time stamps for points in time history.
    double* _amplitude; ///< Amplitude at points in time history.
    size_t _npts; ///< Number of points in time history.
    size_t _ilower; ///< Current index for point preceding current time.

private:

    // NOT IMPLEMENTED ////////////////////////////////////////////////////

    TimeHistory(const TimeHistory&); ///< Not implemented
    const TimeHistory& operator=(const TimeHistory&); ///< Not implemented

}; // class TimeHistory

#include "TimeHistory.icc" // inline methods

#endif // spatialdata_spatialdb_timehistory_hh

// End of file
