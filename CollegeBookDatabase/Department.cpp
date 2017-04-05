//
//  Department.cpp
//  CSCE315_Project_1
//
//  Created by Jared Wheeler on 2/1/17.
//  Copyright © 2017 Jared Wheeler. All rights reserved.
//

#include "Department.hpp"

void Department::addCourse(Course* crse) {
    courses.push_back(crse);
}
Course* Department::getCourse(int courseCode) {
    for (auto course : courses) {
        if (courseCode == course->getCourseCode()) {
            return course;
        }
    }
    return NULL;
}

void Department::cycleCourses() {
    //used to output all courses in the department
    for (auto course : courses) {
        cout << course->getCourseCode() << ", ";
    }
}
void Department::cycleCoursesToGetAllBooks() {
    //used to output the vector of books in for each course
    for (auto course : courses) {
        course->cycleBooks();
    }
}
void Department::cycleCoursesToGetBookCosts() {
    //uses the Min and Max functions in Course.cpp to calcuate the running totals for the given department.
    //This does not return the totals for the books, only outputting them.
    float minimumCosts = 0;
    float maximumCosts = 0;
    for (auto course : courses) {
        minimumCosts = minimumCosts + course->cycleBooksToGetMinCosts();
        maximumCosts = maximumCosts + course->cycleBooksToGetMaxCosts();
    }
    cout << "Maximum costs for all required and optional books in the department: $" << maximumCosts << endl;
    cout << "Minimum costs for all required books in the department: $" << minimumCosts << endl;
}


