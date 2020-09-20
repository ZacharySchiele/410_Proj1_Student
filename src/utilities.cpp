
/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

vector<process_stats> stats;
bool cpuSort (process_stats x, process_stats y){
	return (x.cpu_time < y.cpu_time);
}

bool processSort (process_stats x, process_stats y){
	return (x.process_number < y.process_number);
}

bool startSort (process_stats x, process_stats y){
	return (x.start_time < y.start_time);
}

bool ioSort (process_stats x, process_stats y){
	return (x.io_time < y.io_time);
}

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile

int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	stats.clear();
	ifstream infile;
	infile.open(filename);

	if (!infile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	string line;

	if (ignoreFirstRow == true){
		getline(infile, line);
	}

	while (getline(infile, line)){
		stringstream stream(line);
		process_stats stat;
		string s1;
		string s2;
		string s3;
		string s4;
		getline(stream, s1, ',');
		getline(stream, s2, ',');
		getline(stream, s3, ',');
		getline(stream, s4, ',');

		if (s1.length() < 1 || s2.length() < 1 || s3.length() < 1 || s4.length() < 1) continue;

		stat.process_number = stoi(s1);
		stat.start_time = stoi(s2);
		stat.cpu_time = stoi(s3);
		stat.io_time = stoi(s4);

		stats.push_back(stat);
	}

	infile.close();

	return SUCCESS;
}




//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder){

		case IO_TIME:
			sort(stats.begin(), stats.end(), ioSort);
			break;

		case START_TIME:
			sort(stats.begin(), stats.end(), startSort);
			break;

		case CPU_TIME:
			sort(stats.begin(), stats.end(), cpuSort);
			break;

		case PROCESS_NUMBER:
			sort(stats.begin(), stats.end(), processSort);
			break;

			}
}

process_stats getNext() {

	process_stats myFirst;
	myFirst = stats.front();
	stats.erase(stats.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}
