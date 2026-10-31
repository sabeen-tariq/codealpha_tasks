#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int numCourses;
    cout << "=== CODEALPHA CGPA CALCULATOR ===" << endl;
    cout << "Enter the total number of courses taken: ";
    cin >> numCourses;

    double totalCredits = 0;
    double totalGradePoints = 0;

    for (int i = 1; i <= numCourses; i++) {
        string courseName;
        double credits, gradePoint;

        cout << "\n--- Course " << i << " ---" << endl;
        cout << "Enter course name: ";
        cin >> courseName;
        cout << "Enter credit hours for " << courseName << ": ";
        cin >> credits;
        cout << "Enter grade points obtained (e.g., 4.0, 3.7, 3.0): ";
        cin >> gradePoint;

        totalCredits += credits;
        totalGradePoints += (gradePoint * credits);
    }

    if (totalCredits == 0) {
        cout << "\nError: Total credit hours cannot be zero!" << endl;
    } else {
        double cgpa = totalGradePoints / totalCredits;
        cout << "\n=================================" << endl;
        cout << "          RESULT SUMMARY         " << endl;
        cout << "=================================" << endl;
        cout << "Total Credit Hours : " << totalCredits << endl;
        cout << "Total Grade Points : " << totalGradePoints << endl;
        cout << fixed << setprecision(2);
        cout << "Final Semester CGPA: " << cgpa << endl;
        cout << "=================================" << endl;
    }

    return 0;
}        


