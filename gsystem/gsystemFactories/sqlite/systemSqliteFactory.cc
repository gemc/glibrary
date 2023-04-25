// string for gexit
#include "gutilities.h"
using namespace gutilities;

// gsystem
#include "systemSqliteFactory.h"

// c++
using namespace std;



GSystemSQLiteFactory::GSystemSQLiteFactory() {
	
}



void GSystemSQLiteFactory::initialize_sqlite_db(GSystem *system, int verbosity)
{
    system_name = system->getName();
    variation   = system->getVariation();
    runno       = system->getRunno();
    sqlite_file = system->getSqliteFile();

    // sqlite3_open_v2 will return SQLITE_OK (0) on success if the file exist (note: even if it's not an sql db)
    int rc = sqlite3_open_v2(sqlite_file.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);

    if( rc ) {
        cerr << GSYSTEMLOGHEADER << "Sqlite database " << sqlite_file << " not found " << endl;
        gexit(EC__GSETUPFILENOTOFOUND);

    } else {
        cout << GSYSTEMLOGHEADER << "Sqlite database >" <<  KMAG << sqlite_file << RST  << "< opened successfully" << endl;
    }


}

void GSystemSQLiteFactory::closeSystem() {
    sqlite3_close(db);
    possibleLocationOfFiles.clear();
    cout << GSYSTEMLOGHEADER << "Sqlite database >" <<  KMAG << sqlite_file << RST  << "<  closed successfully" << endl;

}
