//
//  Course.cpp
//  CSCE315_Project_1
//
//  Created by Jared Wheeler on 1/26/17.
//  Copyright © 2017 Jared Wheeler. All rights reserved.
//
#include <iostream>
#include "Course.hpp"
#include "Department.hpp"

void Course::cycleBooks() {
    //used to to cycle through the books vector
    for (auto book : books) {
        cout << "ISBN: " << book->getISBN() << endl;
        cout << "Book: " << book->getBookName() << endl;
        cout << "Author: " << book->getAuthor() << endl;
        cout << "Date: " << book->getDate() << endl;
        cout << "Cost: $" << book->getCost() << endl;
        cout << "Type: " << book->getCondition() << endl << endl;
    }
}

void Course::cycleSections() {
    //used to output the sections vector
    cout << "Sections of " << courseCode << ": " << endl;
    for (auto section : sections) {
        cout << section << endl;
    }
}

int Course::cycleBooksToGetMinCosts() {
    //used to calculate the min cost for the PM statement. Checks to see if the book is required, then
    //adds to the running total if it is.
    int minCosts = 0;
    for (auto book : books) {
        if(book->getRequiredOrOptional() == "Required") {
            minCosts = minCosts + book->getCost();
        }
    }
    return minCosts;
}
int Course::cycleBooksToGetMaxCosts() {
    //running total for all books in a department. Used for the PM statement.
    int maxCosts = 0;
    for (auto book : books) {
        maxCosts = maxCosts + book->getCost();
    }
    return maxCosts;
}


