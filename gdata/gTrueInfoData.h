#ifndef GTRUEINFOHIT_H
#define GTRUEINFOHIT_H 1

#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;

// data for a single bu
class GTrueInfoData {
	
public:

	void includeVariable(string varName, float var);

private:

	// the data map are keyd with the variable name
	map<string, float> trueInfo ;
};


#endif
