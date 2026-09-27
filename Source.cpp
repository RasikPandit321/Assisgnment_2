#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA   // information for student
{
    string firstName;  // fristname
    string lastName;   // lastname
}; 

int main()
{
    vector<STUDENT_DATA> students;  

    ifstream inputFile("StudentData.txt");  // open the student data for reading

    if (!inputFile.is_open())   // check if the file opens successfully
    {
        cout << "Unable to open StudentData.txt" << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line))  // read the file one line at a time
    {
        size_t commaPosition = line.find(','); // find comma seperating the last name and first name

        if (commaPosition != string::npos)
        {
            STUDENT_DATA student;  // creates new student object 

            student.lastName = line.substr(0, commaPosition);  // seperate last name and first name
            student.firstName = line.substr(commaPosition + 1);

            // Remove the space after the comma
            if (!student.firstName.empty() && student.firstName[0] == ' ')
            {
                student.firstName.erase(0, 1);
            }

            students.push_back(student);  // add the student object to vector
        }
    }

    inputFile.close();  // close the file
    #ifdef _DEBUG

    // Print student information only when compiled in Debug mode
    cout << "Student Information:" << endl;

    for (const STUDENT_DATA& student : students)
    {
        cout << student.lastName << ", " << student.firstName << endl;
    }

    #endif 

    return 0;
}