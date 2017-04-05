/*#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "/Users/jaredwheeler/Documents/CSCE 315 Homework/CSCE315_Team_Project_1/json-develop/src/json.hpp"
#include "Database.h"
using json = nlohmann::json;

//Database database;

void buildTable(json j){
    vector<string> v;
    string s;
    for (auto it = j.begin(); it != j.end(); it++) {
        s = it->dump();
        cout << "s dump: " << s << endl;
        v.push_back(s);
    }
    for (int i = 0; i < v.size() - 1; i++) {
        cout << i << ": " << v[i] << endl;
    }
}


json readJSON(){
    json j;
    std::string s;
    std::ifstream i("/Users/jaredwheeler/Documents/CSCE 315 Homework/CSCE315_Team_Project_1/yelp_dataset_challenge_round9/yelp_academic_dataset_review.json");
    if(i.is_open()) {
        std::getline(i, s);
        j = json::parse(s);
        buildTable(j);
    }
    return j;
}

int main(int argc, const char * argv[]) {
    json j = readJSON();
    
}
*/
