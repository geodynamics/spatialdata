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
#include <portinfo>

#include "catch2/catch_session.hpp"

#include <Python.h>

namespace pylith {
    namespace testing {
        class TestDriver;
    }
}

// ------------------------------------------------------------------------------------------------
class pylith::testing::TestDriver {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor.
    TestDriver(void);

    /** Run test application.
     * @param argc[in] Number of arguments passed.
     * @param argv[in] Array of input arguments.
     *
     * @returns 1 if errors were detected, 0 otherwise.
     */
    int run(int argc,
            char* argv[]);

    // NOT IMPLEMENTED ////////////////////////////////////////////////////////////////////////////
private:

    TestDriver(const TestDriver&); ///< Not implemented
    const TestDriver& operator=(const TestDriver&); ///< Not implemented

};

// ------------------------------------------------------------------------------------------------
// Constructor
pylith::testing::TestDriver::TestDriver(void) { }


// ---------------------------------------------------------------------------------------------------------------------
// Run info application.
int
pylith::testing::TestDriver::run(int argc,
                                 char* argv[]) {
    Catch::Session session;

    std::string infoJournalArgs;
    std::string debugJournalArgs;
    auto cli = session.cli();
    session.cli(cli);
    int returnCode = session.applyCommandLine(argc, argv);
    if (returnCode) {
        return returnCode;
    } // if

    // Initialize Python (needed for journals).
    Py_Initialize();

    int result = session.run();

    // Finalize Python
    Py_Finalize();

    return result;
} // run


// ------------------------------------------------------------------------------------------------
int
main(int argc,
     char* argv[]) {
    return pylith::testing::TestDriver().run(argc, argv);
} // main


// End of file
