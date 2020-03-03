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

/** @file libsrc/spatialdb/SimpleIO.hh
 *
 * @brief C++ abstract base class for I/O of data for simple spatial database.
 */

#if !defined(spatialdata_spatialdb_simpleio_hh)
#define spatialdata_spatialdb_simpleio_hh

#include "spatialdbfwd.hh" // forward declarations
#include "spatialdata/geocoords/geocoordsfwd.hh" // forward declarations

#include <string> // HASA std::string

/// C++ manager for simple spatial database.
class spatialdata::spatialdb::SimpleIO { // class SimpleIO
public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor.
    SimpleIO(void);

    /// Default destructor.
    virtual ~SimpleIO(void);

    // Using default copy constructor

    /** Clone object.
     *
     * @returns Pointer copy of this.
     */
    virtual SimpleIO* clone(void) const = 0;

    /** Set filename for database.
     *
     * @param filename Filename of database
     */
    void setFilename(const char* filename);

    /** Get filename for database.
     *
     * @returns Filename of database
     */
    const char* getFilename(void) const;

    /** Read the database.
     *
     * @param pData Database data
     * @param ppCS Pointer to coordinate system
     */
    virtual void read(SimpleDBData* pData,
                      spatialdata::geocoords::CoordSys** ppCS) = 0;

    /** Write the database.
     *
     * @param data Database data
     * @param pCS Pointer to coordinate system
     */
    virtual void write(const SimpleDBData& data,
                       const spatialdata::geocoords::CoordSys* pCS) = 0;

protected:

    // PROTECTED METHODS //////////////////////////////////////////////////

    /** Check compatibility of topology and spatial distribution.
     *
     * Currently, this compatiblity check only involves making sure
     * there are enough number of points to perform the interpolation
     * corresponding to the topology of the spatial distribution. It
     * does not check the actual topology of the distribution.
     *
     * @param data Database data
     * @param pCS Pointer to coordinate system
     */
    static void checkCompatibility(const SimpleDBData& data,
                                   const spatialdata::geocoords::CoordSys* pCS);

    /** Convert values to SI units.
     *
     * @param data Database data
     */
    static void convertToSI(SimpleDBData* const data);

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    const SimpleIO& operator=(const SimpleIO& data); ///< Not implemented

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    /** Filename of database */
    std::string _filename;

}; // class SimpleIO

#include "SimpleIO.icc"

#endif // spatialdata_spatialdb_simpleio_hh

// End of file
