//
//  main.cpp
//  CSCE315_Project_1
//
//  Created by Jared Wheeler on 1/24/17.
//  Copyright © 2017 Jared Wheeler. All rights reserved.
//

#include <iostream>
#include <map>
#include "Book.hpp"
#include "Course.hpp"
#include "Department.hpp"
using namespace std;

//helper function to make sure IBSN is valid
bool checkISBN(string);

int main() {
    try {
        
        string selectOption;
        map<string, Book*> map1;
        map<string, Department*> map2;
        
        //Here is the main menu. It will give the user the possible options
        //The user will input a string, and a chain of if-else statements will
        //handle the selection.
        cout << "Main Menu" << endl;
        cout << "Use the provided key in order to preform an operation. " << endl;
        cout << "B: Creates a book. Input ISBN and book name. " << endl;
        cout << "D: Set already defined book characteristics. " << endl;
        cout << "M: Defines book cost. " << endl;
        cout << "C: Defines a course. " << endl;
        cout << "A: Assigns a defined book to a defined class. " << endl;
        cout << "GC: Print the books required and optional for all sections of a given course" << endl;
        cout << "GS: Print the books required and optional for a given section of a course" << endl;
        cout << "GB: Print all information known about a particular book. " << endl;
        cout << "PB: Print a list of all books that are defined. " << endl;
        cout << "PC: Print a list of all courses that are defined. " << endl;
        cout << "PY: Print all books with known publication dates in the given month/year or later." << endl;
        cout << "PD: Print the list of all books used in a department, given by department code. Do not list by section." << endl;
        cout << "PM: Print the average minimum and maximum costs of all books in a department." << endl;
        cout << "RD: Re-print the main menu. " << endl;
        while (cin) {
            cin >> selectOption;
            if (selectOption == "B") {
                //This if-statement adds a book to the database. It takes user input
                //then creates a new Book object that is added to the map. I choose
                //to use the ISBN that the user inputs as the key of the map. This
                //way there is no extra input needed, and each book will have a unique
                //IBSN, so there should be no dupes or clashes.
                cout << "Input ISBN followed by the name of the book: ";
                string bookName;
                string isbnB;
                cin >> isbnB;
                if (checkISBN(isbnB) == false) {
                    cout << "Input not valid. IBSN is only digits and 13 digit long. " << endl;
                } else {
                    getline(cin, bookName);
                    while (bookName == "") {
                        cout << "Book name not received. Please re-enter the book name: ";
                        getline(cin, bookName);
                    }
                    map1.insert(pair<string, Book*>(isbnB, new Book(isbnB, bookName)));
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "D") {
                //The user can search the map for a book to add information too.
                //Like the main menu, this will be handled with if-else statements.
                //The IBSN that the user enters will be used to search the map to
                //find the correct class instance.
                string selectD;
                string isbnD;
                cout << "Enter ISBN from book: ";
                cin >> isbnD;
                cout << "A: Add the author of a book. " << endl;
                cout << "E: Add the edition of a book. " << endl;
                cout << "D: Add the date of publication (MM/YYYY)." << endl;
                cout << "Use these options with the value following. " << endl;
                cin >> selectD;
                map<string, Book*>::iterator it = map1.find(isbnD);
                //if the book is not located in the map, reject and return to main menu
                if (map1.find(isbnD) == map1.end()) {
                    cout << "Book not found. " << endl;
                } else {
                    if (selectD == "A") {
                        string author;
                        cout << "Enter author's name: ";
                        cin.ignore();
                        getline(cin, author);
                        cout << endl;
                        it->second->addAuthor(author);
                    }
                    else if (selectD == "E") {
                        int edition;
                        cout << "Enter the book edition: ";
                        cin >> edition;
                        //error case handling
                        if (edition > 30) {
                            cout << "Unlikely input. Input not registed. " << endl;
                        } else {
                            cout << endl;
                            it->second->addEdition(edition);
                        }
                    }
                    else if (selectD == "D") {
                        int month, year;
                        cout << "Enter the date of the book publication (Format: MM/YYYY): ";
                        cin >> month;
                        if (cin.get() != '/' ) // make sure there is a slash between DD and MM
                        {
                            std::cout << "expected /\n";
                            return 1;
                        }
                        cin >> year;
                        //error case handling
                        if (month > 12 || month < 1 || year > 2017) {
                            cout << "Input not valid. There are only 12 months in a year. Future books not accepted." << endl;
                        } else {
                            cout << endl;
                            it->second->addDate(month, year);
                        }
                    }
                    else {
                        cout << "Input not valid. Either try using capitals, or false input." << endl;
                    }
                    cout << "Returning to main menu... " << endl;
                }
            }
            else if (selectOption == "M") {
                string isbnM;
                float cost;
                cout << "Enter the ISBN of the book: ";
                cin >> isbnM;
                cout << "Enter the cost of the book: ";
                cin >> cost;
                char newOrUsedOrRentOrElectronic;
                cout << "U: Book is used. " << endl;
                cout << "N: Book is new. " << endl;
                cout << "R: Book is a rental. " << endl;
                cout << "E: Book is electronic. " << endl;
                cin >> newOrUsedOrRentOrElectronic;
                map1.find(isbnM)->second->addCost(cost);
                //This part will ask the user to set the condition of the book
                //It does this by getting the key (isbn) from the input, then using
                //that key to find the correct book. Using the second element in the
                //map we can add the condition to the function associated with the Book class
                switch (newOrUsedOrRentOrElectronic) {
                    case 'U': map1.find(isbnM)->second->addConditionType("Used");
                        break;
                    case 'N': map1.find(isbnM)->second->addConditionType("New");
                        break;
                    case 'R': map1.find(isbnM)->second->addConditionType("Rental");
                        break;
                    case 'E': map1.find(isbnM)->second->addConditionType("Electronic");
                        break;
                    default:
                        cout << "Input not valid. Either try using capitals, or false input." << endl;
                        break;
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "C") {
                cout << "Input Department code of the class: ";
                string departmentCode;
                int courseCode;
                string courseName;
                cin >> departmentCode;
                cout << "Enter the three digit course code: ";
                cin >> courseCode;
                if (courseCode > 999 || courseCode < 100) {
                    cout << "Input not valid. Input only three numbers. " << endl;
                } else {
                    cout << "Enter the name of the course: ";
                    cin.ignore();
                    getline(cin, courseName);
                    //Inputs the course to a vector in the Department class.
                    map2.insert(pair<string, Department*> (departmentCode, new Department(departmentCode)));
                    map<string, Department*>::iterator it = map2.find(departmentCode);
                    it->second->addCourse(new Course (courseCode, courseName));
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "A") {
                string isbnA;
                string dCode;
                char requiredOrOp;
                int cCode;
                int section;
                cout << "Enter the ISBN of the book that needs to be added: ";
                cin >> isbnA;
                cout << "Enter the department code of the course, followed by the course code and three digit section number: ";
                cin >> dCode;
                cin >> cCode;
                cin >> section;
                cout << "Is this book required? (Y/N): ";
                cin >> requiredOrOp;
                //if the user enters y, then the book will be sent to the requiredOrOptional function in the book class
                if (requiredOrOp == 'R') {
                    requiredOrOp = 'R';
                } else {
                    //if the user fails to input y, input will be treated as 'n'
                    requiredOrOp = 'O';
                }
                if (section > 999 || section < 100) {
                    cout << "Input not valid. Input only three numbers. " << endl;
                } else {
                    //This will first add to the book class whether or not the book is required.
                    map1.find(isbnA)->second->requiredOrNot(requiredOrOp);
                    map<string, Department*>::iterator it = map2.find(dCode);
                    //Then the program can add the book to the correct course instance. After a book is added to a course,
                    //it cannot be edited unless it is reassigned.
                    if (dCode == it->second->getDepartment()) {
                        //this will add the book and section to vectors in specific course instance
                        it->second->getCourse(cCode)->addSection(section);
                        it->second->getCourse(cCode)->addBook(map1.find(isbnA)->second);
                    }
                    else {
                        cout << "That course is not in the system. " << endl;
                    }
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "GC") {
                string dCode;
                int cCode;
                cout << "Enter department code and course number: ";
                cin >> dCode >> cCode;
                if (map2.find(dCode) == map2.end()) {
                    cout << "Department code not found." << endl;
                } else {
                    map<string, Department*>::iterator it = map2.find(dCode);
                    cout << endl << "Books in course: " << endl;
                    it->second->getCourse(cCode)->cycleBooks();
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "GS") {
                string dCode;
                int cCode;
                int section;
                cout << "Enter department code, course number, and section number: ";
                cin >> dCode >> cCode >> section;
                map<string, Department*>::iterator it = map2.find(dCode);
                //error case, if the input is not found, send the user back to the main menu.
                if (map2.find(dCode) == map2.end()) {
                    cout << "Department code not found." << endl;
                } else {
                    //prints out the vector of books associated with a course instance
                    cout << endl << "Books in course: " << endl;
                    it->second->getCourse(cCode)->cycleBooks();
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            //Find and print out the user inputted book from map1
            else if (selectOption == "GB") {
                string isbnGB;
                cout << "Enter ISBN of book to display information: ";
                cin >> isbnGB;
                map<string, Book*>::iterator it = map1.find(isbnGB);
                if(map1.find(isbnGB) == map1.end()) {
                    cout << "Book not found. " << endl;
                } else {
                    cout << "ISBN: " << it->second->getISBN() << endl;
                    cout << "Name: " << it->second->getBookName() << endl;
                    cout << "Author: " << it->second->getAuthor() << endl;
                    cout << "Edition: " << it->second->getEdition() << endl;
                    cout << "Publication Date: " << it->second->getDate() << endl;
                    cout << "Cost: " << it->second->getCost() << endl;
                    cout << "Type: " << it->second->getCondition() << endl;
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "PB") {
                cout << "All books in the database... " << endl;
                //Prints out all entries in the book class.
                for(auto it = map1.cbegin(); it != map1.cend(); ++it)
                {
                    //the key is the isbn, so that will function as the isbn print
                    cout << "ISBN: " << it->first << endl;
                    cout << "Book Name: " << it->second->getBookName() << endl;
                    cout << "Author: " << it-> second->getAuthor() << endl;
                    cout << "Date: " << it->second->getDate() << endl << endl;
                }
                cout << endl << "Returning to main menu... ";
            }
            else if (selectOption == "PC") {
                cout << "All courses in the database..." << endl;
                for(auto it = map2.cbegin(); it != map2.cend(); ++it)
                {
                    //Prints out the entire courses vector in the Department class.
                    cout << it->second->getDepartment() << " ";
                    it->second->cycleCourses();
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "PY") {
                int month, year;
                cout << "Enter the date (MM/YYYY): " << endl;
                cin >> month;
                if (cin.get() != '/' ) // make sure there is a slash between DD and MM
                {
                    std::cout << "expected /\n";
                    return 1;
                }
                cin >> year;
                cout << "Book publication dates in the database... " << endl;
                for(auto it = map1.cbegin(); it != map1.cend(); ++it)
                {
                    //This algorithm will check every book in map1 and retrieve the date. If a month is returned, then
                    //there is a valid entry to check. This will then print out every book from the input and later.
                    if (it->second->getMonth() != 0 && it->second->getMonth() >= month && it->second->getYear() >= year) {
                        cout << it->first << " " << it->second->getBookName() << "\t" << it->second->getDate() << endl;
                    }
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "PD") {
                string departmentCode;
                cout << "Enter the department code: ";
                cin >> departmentCode;
                if(map2.find(departmentCode) == map2.end()) {
                    cout << "No department found. " << endl;
                } else {
                    //This alogorithm will check through a vector of vectors within the map.
                    //It will first check the courses vector, and then all of the books in the vectors within that course
                    //instance. The courses vector lies within the Department class and the books vector in the Course class
                    map<string, Department*>::iterator it = map2.find(departmentCode);
                    it->second->cycleCoursesToGetAllBooks();
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "PM") {
                string departmentCode;
                cout << "Enter the department code: ";
                cin >> departmentCode;
                //error handling. If there is not a matching Department instance, reject.
                if(map2.find(departmentCode) == map2.end()) {
                    cout << "No department found. " << endl;
                } else {
                    //Iterator will find the instance of the departmentCode input in map2
                    //cycleCoursesToGetBookCosts() is a multi-class function. It links to two functions
                    //in the Course class with similar name. Those two functions will examine the book
                    //vector, and use the getCosts() function to retrieve the cost of each book, if there is one.
                    //These values shall then be returned to the Department class, which will get the next element of the
                    //courses vectors and look through that course's book vector as well. Repeat until all courses in the
                    //course vector have been examined.
                    //This is a high run time alogorithm and can slow the program down if there is a large database.
                    map<string, Department*>::iterator it = map2.find(departmentCode);
                    //cycleCoursesToGetBookCosts function will do the printing to the output screen for main() instead.
                    it->second->cycleCoursesToGetBookCosts();
                    //Only one cost can be assigned to each book instance. Since this is the case, the program
                    //has nothing to compare the costs too. Instead, the algorithm will determine if a book is
                    //optional or required. If required, then it will count toward both min and max cost. If it is
                    //optional, it will only count towards the max cost of the department.
                }
                cout << endl << "Returning to main menu... " << endl;
            }
            else if (selectOption == "RD") {
                cout << "Main Menu" << endl;
                cout << "Use the provided key in order to preform an operation. " << endl;
                cout << "B: Creates a book. Input ISBN and book name. " << endl;
                cout << "D: Set already defined book characteristics. " << endl;
                cout << "M: Defines book cost. " << endl;
                cout << "C: Defines a course. " << endl;
                cout << "A: Assigns a defined book to a defined class. " << endl;
                cout << "GC: Print the books required and optional for all sections of a given course" << endl;
                cout << "GS: Print the books required and optional for a given section of a course" << endl;
                cout << "GB: Print all information known about a particular book. " << endl;
                cout << "PB: Print a list of all books that are defined. " << endl;
                cout << "PC: Print a list of all courses that are defined. " << endl;
                cout << "PY: Print all books with known publication dates in the given month/year or later." << endl;
                cout << "PD: Print the list of all books used in a department, given by department code. Do not list by section." << endl;
                cout << "PM: Print the average minimum and maximum costs of all books in a department." << endl;
                cout << "RD: Re-print the main menu. " << endl;
            }
            else {
                cout << "Input not valid. Either try using capitals, or false input." << endl;
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Exception thrown: " << &e << endl;
    }
}

bool checkISBN (string ibsn) {
    bool hasOnlyDigits = (ibsn.find_first_not_of( "0123456789" ) == string::npos);
    if (ibsn.length() != 13) {
        hasOnlyDigits = false;
    }
    return hasOnlyDigits;
}
