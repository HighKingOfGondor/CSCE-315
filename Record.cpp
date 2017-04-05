#include "Record.h"

Record::Record(int tupleSize){
    tuple = vector<string>(tupleSize,"");
}
Record::~Record(){
    
}
int Record::size(){
    return tuple.size();
}

void Record::set(int i, string att) {
    tuple[i] = att;
}

string Record::getAttributeStat(int i) {
    return tuple[i];
}

void Record::deleteAttribute(int location)  {
    if( location >= tuple.size() )  {
        cout << "User attempted to remove attribute from location " << location << ". Tuple size is " << tuple.size() << endl;
    }
    else {
        tuple.erase(tuple.begin() + location);
    }
}

string& Record::operator[](int index){
    return tuple[index];
}

bool Record::operator== (const Record &record){
    if(this->tuple == record.tuple){
        return true;
    }
    return false;
}
