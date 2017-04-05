#ifndef Record_hpp
#define Record_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <regex>

using namespace std;

class Record {
    vector<string> tuple;
public:
    Record(int tupleSize);
    ~Record();
    int size();
    void set(int, string);
    string getAttributeStat(int);
    void deleteAttribute(int location);
    string& operator[] (int index);
    bool operator== (const Record &record);
};

#endif /* Record_hpp */
