#include "/Users/jaredwheeler/Documents/CSCE 315 Homework/CSCE315_Team_Project_1/json-develop/src/json.hpp"
#include "main_menu.h"

using json = nlohmann::json;

vector<string> convertToString(json j) {
    string s;
    vector<string> v;
    for (auto it = j.begin(); it != j.end(); it++) {
        s = it->dump();
        v.push_back(s);
    }
    return v;
}

Table* buildBusinessRecords(vector<vector<string>> v) {
    vector<Record> records;
    //extra records is herre because of the extra column abrastion. We do not want the data
    //out of order. We will combine both vectors when the vectors after completion.
    int recordSize = 12;
    
    Table* bTable = new Table({"address", "BusinessAcceptsCreditCards", "businessID", "descriptor1", "descriptor2", "hours", "city", "x-coordinate", "y-coordinate", "name", "rating", "state", "type"});
    
    for (int i = 0; i < v.size(); i++) {
        vector<string> recordData = {};
        Record* r = new Record(recordSize);
        for (int j = 0; j < v[i].size(); j++) {
            
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\"' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\:' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\'' ), v[i][j].end());
            //v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\,' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\[' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\]' ), v[i][j].end());
            //v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\-' ), v[i][j].end());
            switch (j) {
                case 0:
                    recordData.push_back(v[i][j]);
                    break;
                case 1: {
                    for(string::iterator it = v[i][j].begin(); it != v[i][j].end(); ++it) {
                        if(*it == ',')
                            *it = ' ';
                    }
                    string cards = "BusinessAcceptsCreditCards";
                    stringstream stream(v[i][j]);
                    string word;
                    while (stream >> word) {
                        if (word == cards) {
                            stream >> word;
                            break;
                        }
                    }
                    recordData.push_back(word);
                    break;
                }
                case 2:
                    recordData.push_back(v[i][j]);
                    break;
                case 3: {
                    stringstream stream(v[i][j]);
                    string word;
                    stream >> word;
                    recordData.push_back(word);
                    stream >> word;
                    recordData.push_back(word);
                    break;
                }
                case 4:
                    recordData.push_back(v[i][j]);
                    break;
                case 5:
                    recordData.push_back(v[i][j]);
                    break;
                case 7:
                    recordData.push_back(v[i][j]);
                    break;
                case 8:
                    recordData.push_back(v[i][j]);
                    break;
                case 9:
                    recordData.push_back(v[i][j]);
                    break;
                case 13:
                    recordData.push_back(v[i][j]);
                    break;
                case 14:
                    recordData.push_back(v[i][j]);
                    break;
                case 15:
                    recordData.push_back(v[i][j]);
                    break;
                default:
                    break;
            }
        }
        for (int k = 0; k < recordSize; k++) {
            r->set(k, recordData[k]);
        }
        records.push_back(*r);
    }
    for (int l = 0; l < records.size(); l++) {
        bTable->insertRecord(records[l]);
    }
    bTable->setKey("businessID");
    return bTable;
}

Table* buildUserRecords(vector<vector<string>> v){
    vector<Record> records;
    //extra records is herre because of the extra column abrastion. We do not want the data
    //out of order. We will combine both vectors when the vectors after completion.
    int recordSize = 6;
    
    Table* bTable = new Table({"averageRating", "user", "type", "userID", "accountCreated", "friends"});
    
    for (int i = 0; i < v.size(); i++) {
        vector<string> recordData = {};
        Record* r = new Record(recordSize);
        for (int j = 0; j < v[i].size(); j++) {
            
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\"' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\:' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\'' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\,' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\[' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\]' ), v[i][j].end());
            
            switch (j)
            {
                case 0:
                    recordData.push_back(v[i][j]);
                    break;
                case 15:
                    recordData.push_back(v[i][j]);
                    break;
                case 16:
                    recordData.push_back(v[i][j]);
                    break;
                case 19:
                    recordData.push_back(v[i][j]);
                    break;
                case 20:
                    recordData.push_back(v[i][j]);
                    break;
                case 21:
                    recordData.push_back(v[i][j]);
                    break;
                default:
                    break;
            }
        }
        for (int k = 0; k < recordSize; k++) {
            r->set(k, recordData[k]);
        }
        records.push_back(*r);
    }
    for (int l = 0; l < records.size(); l++) {
        bTable->insertRecord(records[l]);
    }
    bTable->setKey("user");
    return bTable;
}

Table* buildReviewRecords(vector<vector<string>> v){
    vector<Record> records;
    //extra records is herre because of the extra column abrastion. We do not want the data
    //out of order. We will combine both vectors when the vectors after completion.
    int recordSize = 7;
    
    Table* bTable = new Table({"businessID", "reviewPosted", "userID", "rating", "review", "type", "reviewID"});
    
    for (int i = 0; i < v.size(); i++) {
        vector<string> recordData = {};
        Record* r = new Record(recordSize);
        for (int j = 0; j < v[i].size(); j++) {
            
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\"' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\:' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\'' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\,' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\[' ), v[i][j].end());
            v[i][j].erase(remove(v[i][j].begin(), v[i][j].end(), '\]' ), v[i][j].end());
            
            switch (j)
            {
                case 0:
                    recordData.push_back(v[i][j]);
                    break;
                case 2:
                    recordData.push_back(v[i][j]);
                    break;
                case 4:
                    recordData.push_back(v[i][j]);
                    break;
                case 5:
                    recordData.push_back(v[i][j]);
                    break;
                case 6:
                    recordData.push_back(v[i][j]);
                    break;
                case 7:
                    recordData.push_back(v[i][j]);
                    break;
                case 9:
                    recordData.push_back(v[i][j]);
                    break;
                default:
                    break;
            }
        }
        for (int k = 0; k < recordSize; k++) {
            r->set(k, recordData[k]);
        }
        records.push_back(*r);
    }
    for (int l = 0; l < records.size(); l++) {
        bTable->insertRecord(records[l]);
    }
    bTable->setKey("rating");
    return bTable;
}

//takes the input
vector<vector<string>> readBusJSON(string str, int numRecords){
    int k = 0;
    json j;
    std::string s;
    std::ifstream i(str);
    vector<vector<string>> vvec;
    if(i.is_open()) {
        while(getline(i,s) && k < numRecords){
            k++;
            vector<string> vec;
            j = json::parse(s);
            vec = convertToString(j);
            vvec.push_back(vec);
        }
    }
    return vvec;
}

int main(int argc, const char * argv[]) {
    Database* database = new Database();
    
    string businessFile = "/yelp_dataset_challenge_round9/yelp_academic_dataset_business.json";
    string userFile = "/yelp_dataset_challenge_round9/yelp_academic_dataset_user.json";
    string reviewFile = "/yelp_dataset_challenge_round9/yelp_academic_dataset_review.json";
    
    vector<vector<string>> businessVec = readBusJSON(businessFile, 50);
    vector<vector<string>> userVec = readBusJSON(userFile, 100);
    vector<vector<string>> reviewVec = readBusJSON(reviewFile, 500);
    
    Table* businessTable = new Table();
    Table* userTable = new Table();
    Table* reviewTable = new Table();
    
    businessTable = buildBusinessRecords(businessVec);
    userTable = buildUserRecords(userVec);
    reviewTable = buildReviewRecords(reviewVec);
    
    //easy test records
    Record* r = new Record(13);
    r->set(0, "1020 Grassland Lane");
    r->set(1, "True");
    r->set(2, "1337");
    r->set(3, "Phones");
    r->set(4, "Gadgets");
    r->set(5, "Monday 110-210,Tuesday 110-210,Wednesday 110-210,Thursday 110-210,Friday 110-220,Saturday 100-220,Sunday 110-180");
    r->set(6, "Austin");
    r->set(7, "33");
    r->set(8, "111");
    r->set(9, "TMobile");
    r->set(10, "5.0");
    r->set(11, "TX");
    r->set(12, "business");
    Record* r2 = new Record(7);
    r2->set(0, "1337");
    r2->set(1, "01-01-2017");
    r2->set(2, "1338");
    r2->set(3, "5.0");
    r2->set(4, "blah blah blah");
    r2->set(5, "review");
    r2->set(6, "1339");
    businessTable->insertRecord(*r);
    reviewTable->insertRecord(*r2);
    
    database->addTable(*businessTable, "business");
    database->addTable(*userTable, "user");
    database->addTable(*reviewTable, "review");
    
    main_menu(database);
    
    return 0;
}
