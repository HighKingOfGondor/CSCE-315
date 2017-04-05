#ifndef Table_h
#define Table_h
#include "Record.h"

using namespace std;

class Table {
private:
    int numRows;
    int numCols;
    string table_key;
    vector<Record> records;
    vector<string> attribute_names;
public:
    Table();
    ~Table();
    vector<Record> getTableRecords();
    Table(vector<string> attributes);
    void addAttribute(string attribute);
    void deleteAttribute(string attribute);
    void insertRecord(Record newRecord);
    vector<string> getAttributes();
    int getSize();
    void setKey(string attribute);
    Table crossJoin(Table table1, Table table2);
    Table naturalJoin(Table table1, Table table2);
    int countNonNull(string attribute);
    string computeMin(string attribute);
    string computeMax(string attribute);
    string getKey();
    int getAttributeLocation(string attribute);
    Record& operator[](int location);
    bool operator==(Table &table);
    
    //added functions
    vector<string> returnAttributesNames() { return attribute_names; }
    vector<Record> returnRecords() { return records; }
};
#endif
