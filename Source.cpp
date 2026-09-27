#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA   // information for student
{
    string firstName;  // fristname
    string lastName;   // lastname

    #ifdef PRE_RELEASE
    string email;
    #endif
}; 

int main()
{
    #ifdef PRE_RELEASE
    cout << "Running PreRelease version." << endl;
    #else
    cout << "Running Standard version." << endl;
    #endif
    vector<STUDENT_DATA> students;  

    #ifdef PRE_RELEASE
    ifstream inputFile("StudentData_Emails.txt");
    #else
    ifstream inputFile("StudentData.txt");
    #endif

    if (!inputFile.is_open())   // check if the file opens successfully
    {
        cout << "Unable to open StudentData.txt" << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line)) // read the file one line at a time
    {
        size_t commaPosition = line.find(','); // find comma separating last name and first name

        if (commaPosition != string::npos)
        {
            STUDENT_DATA student; // creates new student object

            student.lastName = line.substr(0, commaPosition);

#ifdef PRE_RELEASE
            // Find the second comma between the first name and email
            size_t secondCommaPosition = line.find(',', commaPosition + 1);

            // Get the first name between the first and second comma
            student.firstName = line.substr(commaPosition + 1,
                secondCommaPosition - commaPosition - 1);

            // Get the email after the second comma
            student.email = line.substr(secondCommaPosition + 1);
#else
            // Standard version only contains last name and first name
            student.firstName = line.substr(commaPosition + 1);
#endif

            // Remove the space after the comma
            if (!student.firstName.empty() && student.firstName[0] == ' ')
            {
                student.firstName.erase(0, 1);
            }

            students.push_back(student); // add the student object to vector
        }
    }

    inputFile.close();  // close the file
    #ifdef _DEBUG

    // Print student information only when compiled in Debug mode
    cout << "Student Information:" << endl;
    for (const STUDENT_DATA& student : students)
    {
        cout << student.lastName << ", " << student.firstName;

#ifdef PRE_RELEASE
        cout << ", " << student.email;
#endif

        cout << endl;
    }

    #endif 

    return 0;
}