// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/muparser/muparserfwd.hh
 *
 * @brief Forward declarations for mu::parser object.
 *
 * Including this header file eliminates the need to use separate
 * forward declarations.
 */

#if !defined(spatialdata_muparser_muparserfwd_hh)
#define spatialdata_muparser_muparserfwd_hh

#define MUP_BASETYPE double

namespace mu {
    class Parser;

    typedef MUP_BASETYPE value_type;

} // mu

#endif // spatialdata_muparser_muparserfwd_hh

// End of file
