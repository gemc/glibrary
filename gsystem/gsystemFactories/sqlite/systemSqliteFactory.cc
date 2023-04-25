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
    variation = system->getVariation();
    runno = system->getRunno();

    string db_filename = system->getName();

    int rc = sqlite3_open(db_filename.c_str(), &db);

    if( rc ) {
        cerr << GSYSTEMLOGHEADER << "Sqlite database " << db_filename << " not found " << endl;
        gexit(EC__GSETUPFILENOTOFOUND);

    } else {
        cout << GSYSTEMLOGHEADER << "Sqlite database >" <<  KMAG << db_filename << RST  << "< opened successfully" << endl;
    }


    //sqlite3_close(db);


}

void GSystemSQLiteFactory::closeSystem() {
    sqlite3_close(db);
    possibleLocationOfFiles.clear();
    cout << GSYSTEMLOGHEADER << "Sqlite database " <<  KMAG << RST  << "closed successfully" << endl;

}
