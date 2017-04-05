//
//  Department.hpp
//  CSCE315_Project_1
//
//  Created by Jared Wheeler on 2/1/17.
//  Copyright © 2017 Jared Wheeler. All rights reserved.
//

#ifndef Department_hpp
#define Department_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "Course.hpp"
using namespace std;

class Course;
class Department {
private:
    vector<Course*> courses;
    string departmentCode;
public:
    Department(string dc) : departmentCode(dc) {};
    void addCourse(Course*);
    Course* getCourse(int);
    string getDepartment() { return departmentCode; }
    void cycleCourses();
    void cycleCoursesToGetAllBooks();
    void cycleCoursesToGetBookCosts();
};

#endif /* Department_hpp */
