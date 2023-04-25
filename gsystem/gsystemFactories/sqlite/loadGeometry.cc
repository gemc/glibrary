// gsystem
#include "systemSqliteFactory.h"

// glibrary
#include "gutilities.h"

// c++
#include <iostream>

void GSystemSQLiteFactory::loadGeometry(GSystem *system, int verbosity)
{
    if (db == nullptr) {
        initialize_sqlite_db(system, verbosity);
    }



//
//    if ( IN != nullptr) {
//
//        if (verbosity >= GVERBOSITY_SUMMARY) {
//            cout << GSYSTEMLOGHEADER << "Loading <text> geometry for <" << KWHT << system->getName() << RST << ">"
//                 << endl;
//        }
//
//        // loading volumes
//        while (!IN->eof()) {
//
//            string dbline;
//            getline(*IN, dbline);
//
//            if (!dbline.size())
//                continue;
//
//            // extract gvolume parameters
//            vector <string> gvolumePars = gutilities::getStringVectorFromStringWithDelimiter(dbline, "|");
//            system->addGVolume(gvolumePars, verbosity);
//        }
//
//        IN->close();
//    }
}

