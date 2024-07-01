// ProjectTwo.cpp 
// By Dathan Pompa
// 6/30/2024
// Class: CS 300
//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
// Creating course structure
struct Course {
    string courseNum;
    string title;
    vector<string> prereqs;
};

// Function to load data from file into the data structure
map<string, Course> loadCourses(const string& fileName) {
    map<string, Course> courses;

    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "There was a problem loading data from file." << fileName << endl;
        return courses;
    }
    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        Course course;
        string prereq;

        getline(stream, course.courseNum, ',');
        getline(stream, course.title, ',');

        while (getline(stream, prereq, ',')) {
            course.prereqs.push_back(prereq);
        }
        courses[course.courseNum] = course;
    }
    file.close();
    cout << "Successfully loaded courses!\n";
    return courses;
}

// Function to print the course list in alphanumeric order
void printCourseList(const map<string, Course>& courses) {

    if (courses.empty()) {
        cout << "You have not loaded any courses yet, Please load the data structure first." << endl;
        return;
    }
    cout << "Here is a sample schedule: \n\n";
    vector<string> coursesNums;
    for (const auto& pair : courses) {
        coursesNums.push_back(pair.first);
    }
    sort(coursesNums.begin(), coursesNums.end());

    for (const auto& courseNum : coursesNums) {
        cout << courseNum << ": " << courses.at(courseNum).title << endl;
    }
}

// Function to convert string to uppercase
string upperCaseMe(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Function to print information about a specific course
void printCourseInfo(const map<string, Course>& courses, const string& courseNum) {

    if (courses.empty()) {
        cout << "You have not loaded any courses yet, Please load the data structure first." << endl;
        return;
    }
    //Converts input to uppercase
    string upperCourseNum = upperCaseMe(courseNum);
    auto it = courses.find(upperCourseNum);
    if (it != courses.end()) {
        const Course& course = it->second;
        cout << course.courseNum << ", " << course.title << endl;
        cout << "Prerequisites: ";
        // If prerequisite is empty, displays none
        if (course.prereqs.empty()) {
            cout << "None";
        } else {
            // Else it prints a comma after the first prereq if there is more than 2
            for (size_t i = 0; i < course.prereqs.size(); i++) {
                cout << course.prereqs[i];
                if (i < course.prereqs.size() - 1) {
                    cout << ", ";
                }
            }
        }
        cout << endl;
    }
    else {
        cerr << "That course is not in the system" << endl;
    }
}

// Function to display menu options
static void Menu() {
    cout << "\n1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit\n";
    cout << "\nWhat would you like to do? ";
}
int main() {
    cout << "Welcome to the course planner.\n";

    map<string, Course> courses;
    
    string fileName;

    char choice;

    while (true) {
        Menu();
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "Please enter the file you want to load";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, fileName);
            courses = loadCourses(fileName);
            break;
        case '2':
            printCourseList(courses);
            break;
        case '3':
        {
            string courseNum;
            cout << "What course do you want to know about? ";
            cin >> courseNum;
            printCourseInfo(courses, courseNum);
            break;
        }
        case '9':
            cout << "Thank you for using the course planner!\n";
            return 0;
        default:
            cerr << choice << " is not a valid option." << endl;
        }
    }
    return 0;
}