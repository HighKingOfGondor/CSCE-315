#ifndef main_menu_h
#define main_menu_h
#include "Database.h"

void main_menu_select() {
    //the output of the main menu
    cout << "main menu..." << endl;
    cout << "Enter number as input. " << endl;
    cout << "1. Find a business " << endl;
    cout << "2. Find a review " << endl;
    cout << "3. Find a user " << endl;
}

void findBusinessOutput() {
    //query options
    cout << "You chose: Find a business. " << endl;
    cout << "Find business by: " << endl;
    cout << "1. Business reviews " << endl;
    cout << "2. Yelp business ID " << endl;
    cout << "3. City " << endl;
    cout << "4. Coordinates (finds the closest match) " << endl;
    cout << "5. Name of business " << endl;
    cout << "6. Business rating " << endl;
    cout << "7. State " << endl;
    cout << "8. Highest ratings in your city" << endl;
    cout << "9. Find number of business in your city " << endl;
    cout << "10. Find business by type " << endl;
    cout << "11. Find businesses that accept credit cards " << endl;
}

void findReviewOutput() {
    //query options
    cout << "You chose: Find a review. " << endl;
    cout << "Find review by: " << endl;
    cout << "1. Yelp business ID " << endl;
    cout << "2. User ID " << endl;
    cout << "3. Rating " << endl;
    cout << "4. Type " << endl;
    cout << "5. Review ID " << endl;
}

void findUserOutput() {
    //query options
    cout << "You chose: Find a user. " << endl;
    cout << "Find user by: " << endl;
    cout << "1. Average rating " << endl;
    cout << "2. Yelp user ID " << endl;
    cout << "3. User name " << endl;
}

void queryBusiness(Database* data, Table table, Table table2, string selection) {
    map<string, Table> map = data->getTables();
    if (selection == "1") { //find by business reviews
        string businessR;
        cout << "You've chosen to search for business reviews. " << endl;
        cout << "Input business to query: ";
        cin.ignore();
        getline(cin, businessR);
        string ad = "(name = " + businessR + ")";
        Table reviewQuery = data->Query({"name", "businessID"}, "business", ad);
        Record r = reviewQuery[0];
        string findad = "businessID = " + r[1];
        cout << r[1] << endl;
        Table reviewQuery2 = data->Query({"userID", "rating", "review"}, "review", findad);
        cout << "Businesses found: " << endl;
        vector<Record> addr = reviewQuery.getTableRecords();
        vector<string> atts = reviewQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cout << "Reviews for this business: " << endl;
        addr = reviewQuery2.getTableRecords();
        atts = reviewQuery2.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "2") { //find by yelp business ID
        //comparison doesnt work
        string bID;
        cout << "You've chosen to search by the Yelp business ID. " << endl;
        cout << "Input ID to query: ";
        cin.ignore();
        getline(cin, bID);
        string bbID = "businessID = " + bID;
        Table bIDQuery = data->Query({"businessID", "name", "rating"}, "business", bbID);
        cout << "Businesses found: " << endl;
        vector<Record> addr = bIDQuery.getTableRecords();
        vector<string> atts = bIDQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "3") { //find by city
        string city;
        cout << "You've chosen to search by city. " << endl;
        cout << "Input city to query: ";
        cin.ignore();
        getline(cin, city);
        string citys = "city = " + city;
        Table cityQuery = data->Query({"address", "name", "rating", "city", "state"}, "business", citys);
        cout << "Businesses found: " << endl;
        vector<Record> addr = cityQuery.getTableRecords();
        vector<string> atts = cityQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "4") { //find by coordinates
        float xc, yc, xcc, ycc, xcf, ycf, range;
        cout << "You've chosen to search by coordinates. " << endl;
        cout << "Input x-coordinates to query: ";
        cin >> xc;
        cout << "Input y-coordinates to query: ";
        cin >> yc;
        cout << "Enter range of search (enter a percentage as a decimal, i.e 5% is 0.05): ";
        cin >> range;
        xcc = xc - (xc * range);
        ycc = yc - (yc * range);
        xcf = xc + (xc * range);
        ycf = yc + (yc * range);
        string command = "(x-coordinate > " + to_string(xcc) + ") AND (x-coordinate < " + to_string(xcf) + ") AND (y-coordinate > " + to_string(ycc) + ") AND (y-coordinate < " + to_string(ycf) + ")";
        string command2 = "(y-coordinate > " + to_string(ycc) + ")";
        Table cQuery = data->Query({"address", "name", "city", "state"}, "business", command);
        cout << "Businesses found within 5% of : " << endl;
        vector<Record> addr = cQuery.getTableRecords();
        vector<string> atts = cQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl << endl;
            }
        }
        cin.ignore();
    } else if (selection == "5") { //find by business name
        //comparison doesnt work
        string bname;
        cout << "You've chosen to search by business name. " << endl;
        cout << "Input title to query: ";
        cin.ignore();
        getline(cin, bname);
        string businessName = "name = " + bname;
        Table bnameQuery = data->Query({"name", "address", "city", "state"}, "business", businessName);
        cout << "Businesses address found: " << endl;
        vector<Record> addr = bnameQuery.getTableRecords();
        vector<string> atts = bnameQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "6") { //find by rating
        string rated;
        cout << "You've chosen to search by rating. " << endl;
        cout << "Find businesses with rating better or equal to: ";
        cin.ignore();
        getline(cin, rated);
        string businessRated = "(rating > " + rated + ") AND (rating = " + rated + ")";
        Table ratedQuery = data->Query({"address", "city", "state", "name", "rating"}, "business", businessRated);
        cout << "Businesses found: " << endl;
        vector<Record> addr = ratedQuery.getTableRecords();
        vector<string> atts = ratedQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "7") { //find by state
        string st;
        cout << "You've chosen to search all businesses in a state." << endl;
        cout << "Input state to query (search by the acromem, i.e Texas is TX): ";
        cin.ignore();
        getline(cin, st);
        string searchSt = "state = ";
        searchSt.append(st);
        Table stateQuery = data->Query({"name", "address", "city", "state"}, "business", searchSt);
        cout << "Businesses address found: " << endl;
        vector<Record> addr = stateQuery.getTableRecords();
        vector<string> atts = stateQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "8") { //find by highest rated
        string hr;
        cout << "You've chosen to find the highest rated businesses in your city." << endl;
        cout << "Input city: ";
        cin.ignore();
        getline(cin, hr);
        string hrsearch = "city = " + hr;
        Table hrQuery = data->Query({"name", "address", "city", "state", "rating"}, "business", hrsearch);
        data->addTable(hrQuery, "hr");
        string max = hrQuery.computeMax("rating");
        hrsearch = "rating >= " + max;
        Table hrQuery2 = data->Query({"name", "address", "city", "state", "rating"}, "hr", hrsearch);
        cout << "Businesses address found: " << endl;
        vector<Record> addr = hrQuery2.getTableRecords();
        vector<string> atts = hrQuery2.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
    } else if (selection == "9") { //find number of business by city
        string findInCity;
        cout << "You've chosen to find how many businesses are in a selected city. " << endl;
        cout << "Input city: ";
        cin.ignore();
        getline(cin, findInCity);
        string find = "city = " + findInCity;
        Table findQuery = data->Query({"name", "address", "city", "state", "rating"}, "business", find);
        cout << "There are: " << findQuery.countNonNull("name") << " businesses in this city" << endl;
    } else if (selection == "10") { //find by type
        string type, city;
        cout << "You've chosen to find a particular type of business. " << endl;
        cout << "Input type: ";
        cin.ignore();
        getline(cin, type);
        string stringFindInCity = "((descriptor1 = " + type + ") OR (descriptor2 = " + type + "))";
        Table findType = data->Query({"name", "address", "city", "state", "descriptor1", "descriptor2"}, "business", stringFindInCity);
        cout << "Businesses found: " << endl;
        vector<Record> addr = findType.getTableRecords();
        vector<string> atts = findType.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
    } else if (selection == "11") {
        cout << "You've chosen to find businesses that accept credit cards. " << endl;
        string card = "BusinessAcceptsCreditCards = True";
        Table cardQuery = data->Query({"name", "address", "city", "state", "rating", "BusinessAcceptsCreditCards"}, "business", card);
        cout << "Businesses found: " << endl;
        vector<Record> addr = cardQuery.getTableRecords();
        vector<string> atts = cardQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
    }
}

void queryReviews(Database* data, Table table, string selection) {
    if (selection == "1") { //find by business ID
        string bID;
        cout << "You've chosen to search by business ID " << endl;
        cout << "Input ID to query: ";
        cin.ignore();
        getline(cin, bID);
        string busID = "businessID = " + bID;
        Table bIDQuery = data->Query({"businessID", "reviewPosted", "userID", "rating", "review", "type", "reviewID"}, "review", busID);
        cout << "Reviews found: " << endl;
        vector<Record> addr = bIDQuery.getTableRecords();
        vector<string> atts = bIDQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr.size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "2") { //find by user ID
        string uID;
        cout << "You've chosen to search by User ID " << endl;
        cout << "Input ID to query: ";
        cin.ignore();
        getline(cin, uID);
        string userID = "userID = " + uID;
        Table uIDQuery = data->Query({"businessID", "reviewPosted", "userID", "rating", "review", "type", "reviewID"}, "review", userID);
        cout << "Reviews found: " << endl;
        vector<Record> addr = uIDQuery.getTableRecords();
        vector<string> atts = uIDQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr.size(); j++) {
                cout << atts[j] << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "3") { //find by rating (higher or equal)
        string rate;
        cout << "You've chosen to search by rating " << endl;
        cout << "Find reviews with ratings better than or equal to: ";
        cin.ignore();
        getline(cin, rate);
        string rating = "(rating > " + rate + ") AND (rating = " + rate + ")";
        Table ratingsQuery = data->Query({"businessID", "reviewPosted", "userID", "rating", "review", "type", "reviewID"}, "review", rating);
        cout << "Reviews found: " << endl;
        vector<Record> addr = ratingsQuery.getTableRecords();
        vector<string> atts = ratingsQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < atts.size(); j++) {
                cout << atts[j] << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "4") { //find by review type
        string type;
        cout << "You've chosen to search by review type " << endl;
        cout << "Input type: ";
        cin.ignore();
        getline(cin, type);
        string reviewType = "type = " + type;
        Table typeQuery = data->Query({"businessID", "reviewPosted", "userID", "rating", "review", "type", "reviewID"}, "review", reviewType);
        cout << "Reviews found: " << endl;
        vector<Record> addr = typeQuery.getTableRecords();
        vector<string> atts = typeQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < atts.size(); j++) {
                cout << atts[j] << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "5") { //find by review ID
        string revID;
        cout << "You've chosen to search by review ID " << endl;
        cout << "Input review ID to query: ";
        cin.ignore();
        getline(cin, revID);
        string reviewID = "reviewID = " + revID;
        Table revIDQuery = data->Query({"businessID", "reviewPosted", "userID", "rating", "review", "type", "reviewID"}, "review", reviewID);
        cout << "Reviews found: " << endl;
        vector<Record> addr = revIDQuery.getTableRecords();
        vector<string> atts = revIDQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < atts.size(); j++) {
                cout << atts[j] << addr[i].getAttributeStat(j) << endl;
            }
        }
    }
}

void queryUsers(Database* data, Table table, string selection) {
    map<string, Table> map = data->getTables();
    if (selection == "1") { //find by rating
        string userR;
        cout << "You've chosen to search for average user rating " << endl;
        cout << "Input rating to search for: ";
        cin.ignore();
        getline(cin, userR);
        Table reviewQuery = data->Query({"averageRating", "user", "type", "userID", "accountCreated", "friends"}, "users", "averageRating = userR");
        cout << "Users found: " << endl;
        vector<Record> addr = reviewQuery.getTableRecords();
        vector<string> atts = reviewQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "2") { //find by user ID
        string uID;
        cout << "You've chosen to search by the Yelp user ID. " << endl;
        cout << "Input ID to query: ";
        cin.ignore();
        getline(cin, uID);
        Table uIDQuery = data->Query({"averageRating", "user", "type", "userID", "accountCreated", "friends"}, "users", "userID = uID");
        cout << "Users found: " << endl;
        vector<Record> addr = uIDQuery.getTableRecords();
        vector<string> atts = uIDQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    } else if (selection == "3") { //find by user name
        string uID;
        cout << "You've chosen to search by the user name. " << endl;
        cout << "Input user to query: ";
        cin.ignore();
        getline(cin, uID);
        Table uIDQuery = data->Query({"averageRating", "user", "type", "userID", "accountCreated", "friends"}, "users", "user = userName");
        cout << "Users found: " << endl;
        vector<Record> addr = uIDQuery.getTableRecords();
        vector<string> atts = uIDQuery.getAttributes();
        for (int i = 0; i < addr.size(); i++) {
            for (int j = 0; j < addr[i].size(); j++) {
                cout << atts[j] << ": " << addr[i].getAttributeStat(j) << endl;
            }
        }
        cin.ignore();
    }
}

void main_menu(Database* database) {
    string input;
    map<string, Table> databaseTables = database->getTables();
    Table business = databaseTables.find("business")->second;
    Table reviews = databaseTables.find("review")->second;
    Table users = databaseTables.find("user")->second;
    
    cout << "Welcome the the Yelp dataset challenge database. " << endl;
    main_menu_select();
    while (getline(cin, input) && (input != "quit" || input != "q" )) {
        if (input == "1") { //business search
            string select;
            findBusinessOutput();
            cin >> select;
            queryBusiness(database, business, reviews, select);
        } else if (input == "2") { //review search
            string select;
            findReviewOutput();
            cin >> select;
            queryReviews(database, reviews, select);
        } else if (input == "3") { //user search
            string select;
            findUserOutput();
            cin >> select;
            queryUsers(database, users, select);
        } else {
            cout << "Input not valid. Please choose one of the options displayed by number. " << endl;
            main_menu_select();
        }
        
    }
}

#endif
