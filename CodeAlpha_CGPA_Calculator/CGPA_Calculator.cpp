#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
struct Course {
    string name;
    double grade;
    double credits;
};
int main() {
    int semesters;
    cout << "Enter number of semesters: ";
    if (!(cin >> semesters) || semesters <= 0) {
        cout << "Invalid number of semesters.\n";
        return 0;
    }
    double overallGradePoints = 0.0;
    double overallCredits = 0.0;
    cout << fixed << setprecision(2);
    for (int s = 1; s <= semesters; s++) {
        int n;
        cout << "\nEnter number of courses in semester "
             << s << ": ";

        if (!(cin >> n) || n <= 0) {
            cout << "Invalid number of courses.\n";
            return 0;
        }

        vector<Course> courses(n);
        double totalGradePoints = 0.0;
        double totalCredits = 0.0;

        for (int i = 0; i < n; i++) {
            cout << "\nCourse " << i + 1 << ":\n";

            cout << "Enter course name (use _ instead of spaces): ";
            cin >> courses[i].name;

            cout << "Enter grade: ";
            if (!(cin >> courses[i].grade) ||
                courses[i].grade < 0) {
                cout << "Invalid grade.\n";
                return 0;
            }

            cout << "Enter credit hours: ";
            if (!(cin >> courses[i].credits) ||
                courses[i].credits <= 0) {
                cout << "Invalid credit hours.\n";
                return 0;
            }

            totalGradePoints +=
                courses[i].grade * courses[i].credits;

            totalCredits += courses[i].credits;
        }

        double semesterGPA = totalGradePoints / totalCredits;

        cout << "\n--- Semester " << s << " Results ---\n";
        cout << left << setw(20) << "Course"
             << setw(12) << "Grade"
             << setw(12) << "Credits"
             << "Grade Points\n";

        for (int i = 0; i < n; i++) {
            cout << left << setw(20) << courses[i].name
                 << setw(12) << courses[i].grade
                 << setw(12) << courses[i].credits
                 << courses[i].grade * courses[i].credits
                 << '\n';
        }

        cout << "\nTotal Credits: " << totalCredits;
        cout << "\nTotal Grade Points: " << totalGradePoints;
        cout << "\nSemester GPA: " << semesterGPA << '\n';

        overallGradePoints += totalGradePoints;
        overallCredits += totalCredits;
    }

    double cgpa = overallGradePoints / overallCredits;

    cout << "\nFINAL RESULT\n";
    cout << "Total Credits: " << overallCredits << '\n';
    cout << "Total Grade Points: " << overallGradePoints << '\n';
    cout << "Overall CGPA: " << cgpa << '\n';

    return 0;
}