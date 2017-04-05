#include "Table.h"
#include <iostream>

Table::Table() {
    numRows = 0;
    numCols = 0;
}
Table::~Table(){
    while(records.size() > 0)  {
        records.erase(records.begin() + 0);
    }
}

vector<Record> Table::getTableRecords() {
    return records;
}

Table::Table(vector<string> attributes)  {
    numRows = 0;
    numCols = 0;
    for(int i = 0; i < attributes.size(); i++)  {
        numCols++;
        attribute_names.push_back(attributes.at(i));
    }
}

void Table::addAttribute(string attribute)  {
    int location = getAttributeLocation(attribute);
    if(location < 0)  {
        attribute_names.push_back(attribute);
        numCols++;
        for(int i = 0; i < records.size(); i++)  {
            records.at(i)[numCols-1] = "";
        }
    }
    else  {
        cout << "Duplicate attributed found. Duplicate not created." << endl;
    }
}

void Table::deleteAttribute(string attribute)  {
    int attribute_loc = getAttributeLocation(attribute);
    
    if(attribute_loc >= 0) {
        attribute_names.erase(attribute_names.begin() + attribute_loc);
        for(int i = 0; i < numRows; i++)  {
            Record curr_rec = records.at(i);
            curr_rec.deleteAttribute(attribute_loc);
        }
        numCols--;
    }
}

void Table::insertRecord(Record newRecord)  {
    records.push_back(newRecord);
    numRows++;
}

vector<string> Table::getAttributes()  {
    return attribute_names;
}

int Table::getSize()  {
    return numRows;
}

void Table::setKey(string attribute)  {
    bool key_set = false;
    int location = getAttributeLocation(attribute);
    if(location >= 0)  {
        table_key = attribute;
        key_set = true;
    }
    if(!key_set)  {
        cout << "Key not set" << endl;
    }
}

Table Table::crossJoin(Table table1, Table table2)  {
    //start with table1 attributes
    vector<string> combined_attributes = table1.attribute_names;
    //adds table2 attributes
    for(int i = 0; i < table2.attribute_names.size(); i++)  {
        combined_attributes.push_back(table2.attribute_names.at(i));
    }
    //creates table with all attributes
    Table combined_table(combined_attributes);
    
    //add all combinations of attributes
    for(int i = 0; i < table1.records.size(); i++)  {
        for(int x = 0; x< table2.records.size(); x++)  {
            /* start with record from table1 and add all */
            /*      attributes from table2 records       */
            Record new_record = table1.records.at(i);
            for(int y = 0; y < table2.records.at(x).size(); y++)  {
                string new_attribute = table2.records.at(x)[y];
                int size = new_record.size();
                new_record[size-1] = new_attribute;
            }
            combined_table.insertRecord(new_record);
        }
    }
    return table1;
}

Table Table::naturalJoin(Table table1, Table table2)  {
    string join_key = table2.getKey();
    if(join_key == "")  {
        cout << "Key not set for table2." << endl;
        /*                                   */
        /*   NOT SURE WHAT TO RETURN HERE    */
        /*                                   */
        Table empty_table;
        return empty_table;
    }
    int table1_location = table1.getAttributeLocation(join_key);
    int table2_location = table2.getAttributeLocation(join_key);
    
    if( (table1_location == -1) || (table2_location == -1) )  {
        cout << "Natural join not performed." << endl;
        /*                                   */
        /*   NOT SURE WHAT TO RETURN HERE    */
        /*                                   */
        Table empty_table;
        return empty_table;
    }
    vector<string> combined_attributes = table2.getAttributes();
    for(int i = 0; i < table1.numCols; i++)  {
        //dont want to include join_key attribute twice
        if(table1.getAttributes().at(i) != join_key)  {
            combined_attributes.push_back(table1.getAttributes().at(i));
        }
    }
    Table new_table(combined_attributes);
    //for each record in table2
    for(int i = 0; i < table2.numRows; i++)  {
        string curr_key_val = (table2[i])[table2_location];
        //find matching key values in table1
        for(int x = 0; x < table1.numRows; x++)  {
            if((table1[x])[table1_location] == curr_key_val)  {
                //make a new record in the new table
                Record new_record = table2[i];
                for(int y = 0; y < table1.numCols; y++)  {
                    if(y != table1_location)  {
                        new_record[new_record.size()-1] = (table1[x])[y];
                    }
                }
                new_table.insertRecord(new_record);
            }
        }
    }
    return new_table;
}

int Table::countNonNull(string attribute)  {
    int attribute_location = getAttributeLocation(attribute);
    if(attribute_location < 0)  {
        return attribute_location;
    }
    else  {
        int non_null_count = 0;
        for(int i = 0; i < records.size(); i++)  {
            if(records.at(i)[attribute_location] != "")  {
                non_null_count++;
            }
        }
        return non_null_count;
    }
}

string Table::computeMin(string attribute)  {
    //Find attribute location in table
    int attribute_loc = getAttributeLocation(attribute);
    if(attribute_loc == -1)  {
        cout << "No min returned." << endl;
        return "";
    }
    else  {
        //Set min to 1st val automatically
        string min = records.at(0)[attribute_loc];
        for(int i = 1; i < records.size(); i++)  {
            string compare_string = records.at(i)[attribute_loc];
            //compare returns negative when min > compare_string
            if(min.compare(compare_string) < 0)  {
                min = compare_string;
            }
        }
        return min;
    }
}

string Table::computeMax(string attribute)  {
    if(numRows <= 0)  {
        cout << "No records in table. Max not found." << endl;
        return "";
    }
    else  {
        //Find attribute location in table
        int attribute_loc = getAttributeLocation(attribute);
        if(attribute_loc == -1)  {
            cout << "No max returned." << endl;
            return "";
        }
        else  {
            //Set max to 1st val automatically
            string max = records.at(0)[attribute_loc];
            for(int i = 1; i < records.size(); i++)  {
                string compare_string = records.at(i)[attribute_loc];
                //compare returns positive when max < compare_string
                if(max.compare(compare_string) > 0)  {
                    max = compare_string;
                }
            }
            return max;
        } 
    }
}

string Table::getKey()  {
    return table_key;
}

int Table::getAttributeLocation(string attribute)  {
    int location = -1;
    for(int i = 0; i < attribute_names.size(); i++)  {
        if(attribute == attribute_names.at(i))  {
            location = i;
            break;
        }
    }
    if(location < 0)  {
        //cout << "Attribute " << attribute << " not found." << endl;
    }
    return location;
}

Record& Table::operator[](int location)  {
    return records.at(location);
}

bool Table::operator==(Table &table){
    if(this->numRows == table.numRows &&
       this->numCols == table.numCols &&
       this->table_key == table.table_key &&
       this->attribute_names == table.attribute_names){
        for(int i = 0; i < records.size(); i++)  {
            if(records.at(i) == table[i])  {}
            else {return false;}
        }
        return true;
    }
    return false;
}

