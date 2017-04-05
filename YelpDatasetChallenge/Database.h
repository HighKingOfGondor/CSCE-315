#ifndef Database_h
#define Database_h

#include "Table.h"

using namespace std;

class Database{
public:
    Database();
    ~Database();
    void addTable(Table table, string name);
    void deleteTable(string name);
    
    int getWeight(string s);
    vector<string> getTableNames();
    map<string, Table> getTables();
    Table Query(vector<string> select_arg, string from_arg, string where_arg);
    
    
private:
    map<string, Table> mapOfTables;
    std::vector<string> vecOfTableNames;
    Table findTable(string);
    vector<string> queryParser(string parse);
};

#endif /* Database_hpp */
