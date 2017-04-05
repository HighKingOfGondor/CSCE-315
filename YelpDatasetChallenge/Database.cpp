#include "Database.h"

using namespace std;
Database::Database(){
    
}
Database::~Database(){
    
}
void Database::addTable(Table table, string name){
    //mapOfTables.insert(pair<string,Table *>(name, &table));
    mapOfTables[name] = table;
    vecOfTableNames.push_back(name);
    
}
void Database::deleteTable(string name){
    mapOfTables.erase(name);
    for (int i = 0; i < vecOfTableNames.size() - 1; i++) {
        if (vecOfTableNames[i] == name) {
            vecOfTableNames.erase(vecOfTableNames.begin() + i);
        }
    }
}
vector<string> Database::getTableNames(){
    return vecOfTableNames;
}
map<string, Table> Database::getTables(){
    return mapOfTables;
}
int Database::getWeight(string s) {
    if(s == "NOT"){
        return 2;
    } else if (s == "=" || s == "<>" || s == ">" || s == "<" || s == ">=" || s == "<=" || s == "AND" || s == "OR"){
        //cout << s << endl;
        return 1;
    } else{
        return 0;
    }
}
Table Database::Query(vector<string> select_arg, string from_arg, string where_arg){
    Table oldTable = findTable(from_arg);
    Table newTable;
    vector<string> parsedQuery;
    if(select_arg[0] == "*"){
        for(auto i : oldTable.getAttributes()){
            newTable.addAttribute(i);
        }
    }else{
        for (auto i : select_arg) {
            newTable.addAttribute(i);
        }
    }
    
    parsedQuery = queryParser(where_arg);
    
    for(int i = 0; i<oldTable.getSize(); ++i){
        vector<string> currTableQuery;
        stack<string> attributeNames;
        string right, left;
        for(string s : parsedQuery){
            if (s == "="){
                right = attributeNames.top();
                attributeNames.pop();
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string(left == right));
            }
            else if(s == "<>"){
                right = attributeNames.top();
                attributeNames.pop();
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string(left != right));
            }
            else if(s == ">"){
                right = attributeNames.top();
                attributeNames.pop();
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string(left > right));
            }
            else if(s == "<"){
                right = attributeNames.top();
                attributeNames.pop();
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string(left < right));
            }
            else if(s == ">="){
                right = attributeNames.top();
                attributeNames.pop();
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string(left >= right));
            }
            else if(s == "<="){
                right = attributeNames.top();
                attributeNames.pop();
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string(left <= right));
            }
            else if(s == "AND"){
                right = attributeNames.top();
                attributeNames.pop();
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string((left == "1") && (right == "1")));
            }
            else if(s == "OR"){
                right = attributeNames.top();
                attributeNames.pop();
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string((left == "1") || (right == "1")));
            }
            else if(s == "NOT"){
                left = attributeNames.top();
                attributeNames.pop();
                attributeNames.push(to_string(left == "0"));
            }
            else{
                if(oldTable.getAttributeLocation(s) < 0){
                    attributeNames.push(s);
                }else{
                    int loc = oldTable.getAttributeLocation(s);
                    attributeNames.push((oldTable[i])[loc]);
                }
            }
            
            
        }
        if(attributeNames.top() == "1"){
            Record new_rec(select_arg.size());
            for(int j = 0; j < select_arg.size(); j++)  {
                new_rec[j] = (oldTable[i])[oldTable.getAttributeLocation(select_arg.at(j))];
            }
            newTable.insertRecord(new_rec);
        }
        
    }
    return newTable;
}

Table Database::findTable(string tableName){
    Table newTable;
    newTable = mapOfTables.find(tableName)->second;
    return newTable;
}

vector<string> Database::queryParser(string parser){
    //string parser = "(tab1 < a)"; // AND (tab1 >= (tab1 = z))
    stringstream command(parser);
    stack<string> middleStack;
    vector<string> postfixVector;
    string individualCommand;
    int weight;
    
    int k = 0;
    while(command >> individualCommand){
        //cout << individualCommand << endl;
        
        for(char c : individualCommand){
            if(c == '('){
                middleStack.push("(");
            }
        }
        /*if (individualCommand.at(0) == '('){
         middleStack.push("(");
         }     */
        
        weight = getWeight(individualCommand);
        if(weight == 0){
            int rightParenthCount = 0;
            int leftParenthCount = 0;
            //found a operand, table
            for(char c : individualCommand){
                if(c == '('){
                    ++rightParenthCount;
                }
            }
            for(char c : individualCommand){
                if(c == ')'){
                    ++leftParenthCount;
                }
            }
            if(individualCommand.at(0) == '('){
                postfixVector.push_back(individualCommand.substr(rightParenthCount));
            } else if(individualCommand.back() == ')'){
                postfixVector.push_back(individualCommand.substr(0,individualCommand.find(")")));
            }else{
                postfixVector.push_back(individualCommand);
            }
        }
        else{
            //found operation, <= NOT >...etc...
            if(middleStack.empty()){
                middleStack.push(individualCommand);
            }
            else{
                while(!middleStack.empty() && middleStack.top() != "(" && weight <= getWeight(middleStack.top())){
                    postfixVector.push_back(middleStack.top());
                    middleStack.pop();
                }
                middleStack.push(individualCommand);
            }
        }
        for(char c : individualCommand){
            if(c == ')'){
                while(!middleStack.empty() && middleStack.top() != "("){
                    postfixVector.push_back(middleStack.top());
                    middleStack.pop();
                }
                if(!middleStack.empty()){
                    middleStack.pop(); // may need to change this to just pop once
                }
                continue;
            }
        }
        /*if(individualCommand.back() == ')'){
         while(!middleStack.empty() && middleStack.top() != "("){
         postfixVector.push_back(middleStack.top());
         middleStack.pop();
         }
         if(!middleStack.empty()){
         middleStack.pop(); // may need to change this to just pop once
         }
         continue;
         }*/
    }
    while(!middleStack.empty()){
        postfixVector.push_back(middleStack.top());
        middleStack.pop();
    }
    
    return postfixVector;
}

