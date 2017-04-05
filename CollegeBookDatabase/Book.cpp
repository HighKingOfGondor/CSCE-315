//
//  Book.cpp
//  CSCE315_Project_1
//
//  Created by Jared Wheeler on 1/25/17.
//  Copyright © 2017 Jared Wheeler. All rights reserved.
//

#include "Book.hpp"

void Book::addAuthor(string a) {
    author = a;
}
void Book::addDate(int m, int y) {
    month = m;
    year = y;
}
void Book::addEdition(int e) {
    edition = e;
}
void Book::addCost(float c) {
    cost = c;
}
void Book::addConditionType(string c) {
    condition = c;
}
string Book::getEdition() {
    switch (edition) {
        case 1: cout << edition << "st"; break;
        case 2: cout << edition << "nd"; break;
        case 3: cout << edition << "rd"; break;
        default: cout << edition << "th"; break;
    }
    return "";
}
void Book::requiredOrNot(char r) {
    switch (r) {
        case 'R': required = "Required"; break;
        case 'O': required = "Optional"; break;
        default: cout << "Input not valid. Either try using capitals, or false input." << endl;
            break;
    }
}
