//
//  Course.hpp
//  CSCE315_Project_1
//
//  Created by Jared Wheeler on 1/26/17.
//  Copyright © 2017 Jared Wheeler. All rights reserved.
//

#ifndef Course_hpp
#define Course_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "Book.hpp"
#include "Department.hpp"
using namespace std;

class Course {
private:
    int courseCode;
    string courseName;
    vector<Book*> books;
    vector<int> sections;
public:
    Course(int ccode, string cname) : courseCode(ccode), courseName(cname) {};
    void addBook(Book* b) { books.push_back(b); }
    void addSection(int i) { sections.push_back(i); }
    int getCourseCode() { return courseCode; }
    void cycleBooks();
    void cycleSections();
    int cycleBooksToGetMinCosts();
    int cycleBooksToGetMaxCosts();
};

#endif /* Course_hpp */
