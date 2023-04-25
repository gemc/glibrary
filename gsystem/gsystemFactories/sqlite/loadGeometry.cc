// gsystem
#include "systemSqliteFactory.h"

// glibrary
#include "gutilities.h"

// c++
#include <iostream>
using std::to_string;


// SQLite will call this callback function for each record processed in
// each SELECT statement executed within the SQL argument.
// uncomment for debugging
static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void GSystemSQLiteFactory::loadGeometry(GSystem *system, int verbosity)
{
    if (db == nullptr) {
        initialize_sqlite_db(system, verbosity);
    }

    char *zErrMsg = 0;
    const char* data = "Callback function called";

    string sql_query = "SELECT * from geometry ;";
    //where system = '" + system_name;
//    sql_query += "' and variation = '" + variation ;
//    sql_query += "' and runno = " + to_string(runno) + ";";

    int rc = sqlite3_exec(db, sql_query.c_str(), callback, (void*)data, &zErrMsg);


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

