//
//  Book.hpp
//  CSCE315_Project_1
//
//  Created by Jared Wheeler on 1/25/17.
//  Copyright © 2017 Jared Wheeler. All rights reserved.
//

#ifndef Book_hpp
#define Book_hpp

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Book {
    string bookName;
    string isbn;
    string author;
    string required;
    int edition = 0;
    string condition;
    float cost = 0;
    int month, year;
public:
    Book(string i, string b) : isbn(i), bookName(b) {}
    void addAuthor (string);
    void addDate (int, int);
    void addEdition (int);
    void addCost (float);
    void addConditionType (string);
    void requiredOrNot(char);
    string getISBN() { return isbn; }
    string getBookName() { return bookName; }
    string getAuthor() { return author; }
    string getDate() { cout << month << "/" << year; return ""; }
    int getMonth() { return month; }
    int getYear() { return year; }
    string getEdition();
    float getCost() { return cost; }
    string getCondition() { return condition; }
    string getRequiredOrOptional() { return required; }
};

#endif /* Book_hpp */
