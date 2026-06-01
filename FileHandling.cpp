#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
using namespace std;


/* MIND MAP */

/* 

-I first create SaveToFile and LoadFromFile functions to handle file operations for saving and loading student data.
These functions use ofstream and ifstream to write to and read from a text file, respectively.

-Then I call these functions at necessary points in the program, 
such as loading existing data at the start of the program and
saving data after any modifications (like adding, editing, or deleting students).

-I edited Vector of studentlist objects to not hold any student data in memory because The File Based Data Base is here.

[[ Attendance Records ]]

-I added a new attribute attendance_record to the studentlist class to keep track of the number of days a student has been present.

-Default is 7 because I assume the class has already attended 7 days before the program starts, 
and we will mark attendance for each student from that point onward.

-Then I created two new functions, markAttendance and displayAttendance,
 to handle attendance marking and displaying attendance records for all students.

-markAttendance function prompts the user to enter a student ID, finds the corresponding student in the class_list,
 and increments their attendance_record by 1 each time attendance is marked.

-displayAttendance function iterates through the class_list and displays each student's name along with their
 attendance record (number of days present).

[[ Simple Log In System ]]


-I create a log in file to authenticate predefined user before they can access the student management system.

-Then I create a login function that reads the username and password from the file and compares it with the user input.

-If the credentials match, the user is granted access to the system; otherwise, an error message is displayed and the program exits.

[[Exporting results ]]

-I added a new function ExportResults that allows the user to export a specific student's information,
 including their ID, name, average mark, grade, attendance record, and individual subject marks, to a text file named "results.txt".

-It use append mode to ensure that new results are added to the file without overwriting existing data.

[[File Error Handling]]

-I already implemented basic error handling for file operations in the SaveToFile and LoadFromFile functions,
such as checking if the file was opened successfully and displaying an error message if it fails.

[[Backup File]]

-I can implement a backup system for students and users data 
by creating a copy of the student data file.

-I ended up modifying the SaveToFile and LoadFromFile functions to also handle backup files. 
When saving, it writes to both the main data file and a backup file. 
When loading, it first tries to load from the main data file,
and if that fails (e.g., due to file corruption or deletion), it attempts to load from the backup file.
Same goes as users data file for log in system,
 I also create a backup file for users data and modify the login function to try loading from the backup file 
 if the main users data file cannot be opened.

*/



//File-Based Student Management System for Admins



class studentlist{
public:

    int id;
    string full_name;
    double cs_mark;
    double math_mark;
    double english_mark;
    int attendance_record = 7 ; // New attribute for attendance record 

    //Helper function to get the average 
    double overallAverage() const{
        return (math_mark + cs_mark + english_mark) /3.0 ;
    };


};

//Log in System

bool login(const string &filename, const string &backupName) {

    ifstream inFile(filename);
    if(!inFile.is_open()) {
        cerr << " Error Opening Authentication File. "
            << "Trying Backup File... " <<endl;


        inFile.open(backupName);
        if(!inFile.is_open()) {
            cerr << " No Backup File Found. Exiting... " <<endl;
            return false; // Exit the function if no backup file is found
        } else {
            cout << " Backup file loaded successfully. "<<endl;
        };
    };

    string username, password;
    cout<<" Enter Username (hint : Admin) : " ;
    cin>> username;
    cout<<" Enter Password (hint : 11501) : " ;
    cin>> password;

    string line;

    getline(inFile, line); // Read the first line of the file
    stringstream ss(line); // Wrap the line in a stringstream to parse it easily
    string Fileuser, Filepass;
    getline(ss, Fileuser, ','); // Extract the username from the line
    getline(ss, Filepass, ','); // Extract the password from the line

    if(username == Fileuser && password == Filepass) {
        cout<<" Login Successful. Welcome, "<<username<<" ! "<<endl;
        return true;
    };

    cout<<" Login Failed. Invalid username or password. "<<endl;
    return false;


};





//Predefined Global Student List
    vector<studentlist> class_list ;

//Save to File

void SaveToFile(const string &filename, const string &backupName) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error Opening File for wiriting ! " << endl;
        return ;
    };

    for(auto &S : class_list) {
        outFile << S.id << ","
                << S.full_name << ","
                << S.cs_mark << "," 
                << S.math_mark << ","
                << S.english_mark << ","
                << S.attendance_record << endl;
    };

    outFile.close();
    cout<<" Student Datas Saved to 'The Data Base' successfully. "<<endl;

    // Always also save to backup file
    ofstream backupFile(backupName);
    if (!backupFile.is_open()) {
        cerr << "Error: Could not open backup file " << backupName << " for writing." << endl;
    } else {
        for (auto &S : class_list) {
            backupFile << S.id << ","
                       << S.full_name << ","
                       << S.cs_mark << ","
                       << S.math_mark << ","
                       << S.english_mark << ","
                       << S.attendance_record << endl;
        };
        backupFile.close();
    };

};

//Load From File

void LoadFromFile(const string &filename, const string &backupName) {
    ifstream inFile(filename); //open the file for reading

    if(!inFile.is_open()) { //check if file exists and opened successfully
        cerr << "No Existing File Found. Starting fresh. "
                << " trying backup file... " <<endl;

        inFile.open(backupName); // Try to open the backup file
        if(!inFile.is_open()) {
            cerr << " No Backup File Found. Starting with an empty student list. "<<endl;
            return; // Exit the function if no backup file is found
        } else {
            cout << " Backup file loaded successfully. "<<endl;
        };
    };

    class_list.clear(); // Reset current lsit to avoid duplicate entries when loading 
    studentlist s; //temporary student object to hold data while reading from file
    string line ; //variable to hold each line read from the file

    while (getline(inFile, line)) { //read file line by line in 'Line' variable 
        stringstream ss(line); //Warp line in stringstream to parse it easily
        string temp; //temporary variable to hold parsed data

        //Extract Values separated by commas

        getline(ss, temp, ','); s.id = stoi(temp); //convert string to int and assign to student id
        getline(ss, s.full_name, ','); //name as string
        getline(ss, temp, ','); s.cs_mark = stod(temp); //convert string to double and assign to cs_mark
        getline(ss, temp, ','); s.math_mark = stod(temp); //convert string to double and assign to math_mark
        getline(ss, temp, ','); s.english_mark = stod(temp); //convert string to double and assign to english_mark
        getline(ss, temp, ','); s.attendance_record = stoi(temp); 

        class_list.push_back(s); //add the student object to the global class list
    };

    inFile.close(); //close the file after reading
    cout<<"\t\t\t Student Datas Loaded from 'The Data Base' successfully. "<<endl;
};


//BACK UP FILE SYSTEM FOR STUDENTS AND USERS DATA IMPLEMENTED IN LoadFromFile,SaveToFile FUNCTIONS ABOVE.
//ALSO FOR SIMPLICITY, I ASSUME THE BACKUP FILES ARE MANUALLY CREATED AND MAINTAINED BY THE USER,
//AND THEY ARE IN THE SAME FORMAT AS THE MAIN DATA FILES (students.txt and users.txt) 
//TO ENSURE COMPATIBILITY WITH THE EXISTING LOAD AND SAVE FUNCTIONS.

//ALSO CREATED FOR USERS DATA BACKUP, BUT SINCE THIS PROGRAM IS FOR ADMINS ONLY, I ASSUME THERE IS ONLY ONE ADMIN USER,
//BUT THE BACKUP SYSTEM FOR USERS DATA IS AS CRITICAL AS THE STUDENTS DATA BACKUP,
//SO IT CAN STILL BE USEFUL IN CASE OF FILE CORRUPTION OR ACCIDENTAL DELETION OF THE USERS DATA FILE.


//Option A : search student 

//reusable function to search student by name and ID, which can be used in both search and edit options
//Id

void searchStudentByID(int Id) {
  for(int i=0 ; i < class_list.size() ; i++) {
    if(class_list[i].id == Id) {
        cout<<" Student found = "<<class_list[i].full_name<<endl;
        cout<<" Id : "<<class_list[i].id<<endl;
        cout<<" Mark : "<<class_list[i].overallAverage()<<endl;
        return ;
        };
    } ;
    cout<<" Student Not Found. "<<endl;
    return ;
};

//Name

void searchStudentByName(string name) {
    for (int i=0 ; i < class_list.size() ; i++) {
        if(class_list[i].full_name == name) {
            cout<<" Student found = "<<class_list[i].full_name<<endl;
            cout<<" Id : "<<class_list[i].id<<endl;
            cout<<" Overall Mark : "<<class_list[i].overallAverage()<<endl;
            return ; // Return the index of the found student
        };
    };
    cout<<" Student Not Found. "<<endl;
    return ; // Return -1 if student not found
};


//by name and display their mark
void handleStudentName() {

    string searchName;

    cout<<" Enter Student Name to search : " <<endl;
    cin.ignore(1000, '\n');
    getline(cin, searchName);
    
    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    searchStudentByName(searchName);



};

//display ID list 
int displayIDlist() {

    cout<<" Student ID List : "<<endl;
    for(auto &s : class_list) {
        cout<<" ID : "<<s.id<<endl;
    }
    return 0;

}


//by ID and display their mark
void handleStudentID() {
    int searchID;

    cout<<" Enter Student ID to search : " <<endl;
    cin>> searchID;

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    searchStudentByID(searchID);


};

//Total Student Displayment

void displayTotalStudents() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    cout << "\n===================" << endl;
    cout << "  Total Students   " << endl;
    cout << "===================" << endl;
    cout << " Number of Students: " << class_list.size() << endl;
};



//Average Mark of All student : Option B

void handleAverageMarks() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    double total_math = 0, total_english =0, total_cs = 0 ;

    for(auto &s : class_list) {
        total_math += s.math_mark;
        total_cs += s.cs_mark;
        total_english += s.english_mark;
    };

    cout<<"\n=============================="<<endl;
    cout<<" | Average marks of All Student | "<<endl;
    cout<<"================================="<<endl;

    cout<<"Math Average : "<<  total_math / class_list.size() << endl;
    cout<<"Computer Science Average : " << total_cs / class_list.size() <<endl;
    cout<<"English Average :"<< total_english / class_list.size() <<endl;

    cout<<" ================================= "<<endl;

    cout<<" Overall Average (ALL SUBJECT) : " << (total_cs + total_math + total_english) / (class_list.size() *3.0)<<endl;
};


//Option C : Find Highest and Lowest Mark among Students


void High_Low_Students() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    int highestIndex=0;
    int lowestIndex=0;

    for(int i=1; i<class_list.size(); i++) {
        if(class_list[i].overallAverage() > class_list[highestIndex].overallAverage()) {
            highestIndex= i;
        }
        if(class_list[i].overallAverage() < class_list[lowestIndex].overallAverage()) {
            lowestIndex= i;
        }
    }

    char choice;
    cout<<"\nDo you wanna see (H)ighest or (L)owest? ";
    cin>> choice;

    if(choice == 'H' || choice == 'h' ) {
        cout<<" \nHighest Mark Student : " <<endl;
        cout<<" Name : "<<class_list[highestIndex].full_name<<endl;
        cout << "Average Mark: " << class_list[highestIndex].overallAverage() << endl;
    } else if(choice == 'L' || choice == 'l') {
        cout << "\nLowest Mark Student: " << endl;
        cout << "Name: " << class_list[lowestIndex].full_name << endl;
        cout << "Average Mark: " << class_list[lowestIndex].overallAverage() << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
};


//Option D : Grade System (Pass/Fail)

string GetGrade(double mark) {
    if(mark >= 70 ){
        return "A" ;
    }else if(mark >= 60 ){
        return "B" ;
    }else if(mark >= 30 ){
        return "C" ;
    }else{
        return "F" ;
    };
};


void handleGrades() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    cout<<"\n==================="<<endl;
    cout<<"  Student Grades  "<<endl;
    cout<<"======================="<<endl;

   for(int i=0; i<class_list.size(); i++) {
        cout<<i + 1<<". "<<class_list[i].full_name
        <<"'s Grade :: " << GetGrade(class_list[i].overallAverage())<<endl;


        if(GetGrade(class_list[i].overallAverage()) == "F") {
            cout<<" Note : "<<class_list[i].full_name<<" has failed. "<<endl;
        }else if(GetGrade(class_list[i].overallAverage()) == "A" || GetGrade(class_list[i].overallAverage()) == "B" || GetGrade(class_list[i].overallAverage()) == "C") {
            cout<<" State : "<<class_list[i].full_name<<" has passed. "<<endl;
        };
    };
};

//Ask For Main Menu or Exit after each operation
bool askMenuOrExit() {
    char yn;
    cout<<endl;
    cout<<" Go back to menu y/n ? " <<endl;
    cin>>yn;

    if(yn == 'y' || yn == 'Y'){
        return true; // Go back to menu
    }else if(yn == 'n' || yn == 'N'){
        cout<<"Exiting..."<<endl;
        SaveToFile("students.txt", "students_backup.txt"); // Save student data to file before exiting the program
        return false ; // Exit the program
    }else{
        cout<<"Invalid InPut."<<endl;
        cout << "Invalid input. Returning to main menu..." << endl;
        return true; // Don’t kill program, just go back
    };
};

//Option E : Edit Student Datas

//delete 
void deleteStudentByID() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };


    int deleteID;
    cout<<" Enter Student ID to delete : " ;
    cin>> deleteID;

    bool found = false;
    for(auto it = class_list.begin(); it != class_list.end(); ++it) {
        if(it->id == deleteID) {
            cout<<" Studend Found : "<<it->full_name<<endl;
            cout<<" Student Overall Average Mark : "<<it->overallAverage()<<endl;
            found = true;
            cout<<" Are you sure you want to delete this student? (y/n) : ";
            char confirm;
            cin >> confirm;
            if(confirm =='y'){
                class_list.erase(it);
                cout<<" Student Deleted. "<<endl;
                break;
            }else{
                cout<<" Deletion Cancelled. "<<endl;
                break;
            };

        }; 
    };

    if(found) {
        SaveToFile("students.txt","students_backup.txt"); // Save the updated student list to file after deletion
    };

    if(!found) {
            cout<<" Student Not Found. "<<endl;
        };
};


//Update Student Name by ID
void updateStudentName() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    int updateID;
    cout<< " Enter Student ID to update name : " ;
    cin>> updateID;

    bool found = false;
    for (auto &s : class_list) {
        if (s.id == updateID) {
            cout<< " Current Name : " << s.full_name << endl;
            cout<< " Enter New Name : " ;
            cin.ignore(1000, '\n');
            string newName;
            getline(cin, newName);
            s.full_name = newName;
            cout<< " Name Updated. "<<endl;
            cout<< " Updated Name : " << s.full_name << endl;
            cout<<" ID : " << s.id << endl;
            found = true;
            break;
        };
    };

    if(found) {
        SaveToFile("students.txt", "students_backup.txt");
    };

    if (!found) {
        cout<< " Student not found. "<<endl;
    };
};

//Update Student Mark by ID
void updateStudentMark() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };


    int updateID;
    cout<< " Enter Student ID to update mark : " ;
    cin>> updateID;

    bool found = false;
    for (auto &s : class_list) {
        if (s.id == updateID) {
            cout<<" Which Subject ? "<<endl;
            cout<<" 1) Math "<<endl;
            cout<<" 2) Computer Science"<<endl;
            cout<<" 3) English"<<endl;

            int choice;
            cin >> choice ;

            double newMark;
            cout<<" Enter New Mark : ";
            cin>> newMark;

            if(choice ==1 ) s.math_mark = newMark;
            else if(choice ==2 ) s.cs_mark = newMark;
            else if(choice==3 ) s.english_mark = newMark;
            else cout<< " Invalid Choice "<<endl;

            found = true;
            break;
        };
    };

    if(found) {
        SaveToFile("students.txt", "students_backup.txt"); 
    };

    if (!found) {
        cout<< " Student not found. "<<endl;
    };
};

//Add New Student 

void addNewStudent() {
    int newID;
    string newName;
    double newCs, newmath, newEnglish ;

    cout<< " Enter New Student ID : " ;
    cin>> newID;
    //prevent duplicate ID
    for(auto &s : class_list) {
        if(s.id == newID) {
            cout<<" ID already exists. Please enter a unique ID. "<<endl;
            return;
        }
    };
    cout<< " Enter New Student Name : " ;
    cin.ignore(1000, '\n');
    getline(cin, newName);
    cout<< " Enter Computer Science Mark : " ;
    cin>> newCs;
    cout<<" Enter Math Mark : ";
    cin>>newmath;
    cout<<" Enter English Mark : ";
    cin>>newEnglish;

    studentlist newStudent = {newID, newName, newCs, newmath, newEnglish};
    class_list.push_back(newStudent);
    SaveToFile("students.txt", "students_backup.txt"); // Save the updated student list to file after adding new student
    cout<< " New Student Added. "<<endl;

    cout<<" Display New Student Informations : "<<endl;
    cout<<" ID : "<<newStudent.id<<endl;
    cout<<" Name : "<<newStudent.full_name<<endl;
    cout<<" Average Mark : "<<newStudent.overallAverage()<<endl;

    cout<< " New Student's Grade : " << GetGrade(newStudent.overallAverage()) << endl;
    cout<<" ================================ "<<endl;
};


//Option F : Student Information (e.g., sort by ID, Name, or Marks & Display Total Students List).

//d, Display Total Student List without Sorting
void displayStudentInfo() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };


    cout<<"\n==================="<<endl;
    cout<<"  Student List  "<<endl;
    cout<<"======================="<<endl;

    for(int i=0; i<class_list.size(); i++) {
    cout<<i+1<<". "<<class_list[i].full_name<<endl;
    cout<<" ID : "<<class_list[i].id<<endl;
    cout<<" Overall Average : "<<class_list[i].overallAverage()<<endl;
    cout<<" Math Mark : " <<class_list[i].math_mark<<endl;
    cout<<" Computer Science Mark : "<<class_list[i].cs_mark<<endl;
    cout<<" English Mark : "<<class_list[i].english_mark<<endl;
    cout<<" Grade : "<<GetGrade(class_list[i].overallAverage())<<endl;
    cout<<" ----------------------- "<<endl;
    };
};

//a, Sorting List by Id

void SortByID() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };


    sort(class_list.begin() , class_list.end() ,[](const studentlist &a, const studentlist &b ){
        return a.id < b.id ; //smaller one comes first rule 
    } );

    cout<<"Sorted By ID : "<< endl;
    for (auto &s : class_list) {
        cout << "ID: " << s.id << " | Name: " << s.full_name << " | Overall Average Mark: " << s.overallAverage() << endl;
    };

};

//b, Sorting List by names

void SortByName() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };


    sort(class_list.begin() , class_list.end() , [](const studentlist &a , const studentlist &b) {
        return a.full_name < b.full_name; 
    });

    cout<<" Sorted by Name : "<<endl ;
    for (auto &s : class_list) {
        cout<<" Name : " << s.full_name <<" | ID : " << s.id <<" | Average Mark : " << s.overallAverage() <<endl;
    };

};

//c, Sorting List by Marks

void SortByMark() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    sort(class_list.begin(), class_list.end(), [](const studentlist &a, const studentlist &b) {
        return a.overallAverage() > b.overallAverage(); // descending order (highest first)
    });

    cout << "Sorted by Mark:" <<endl;
    for (auto &s : class_list) {
        cout << "ID: " << s.id << " | Name: " << s.full_name << endl;
        cout<< " | Math : " << s.math_mark <<endl;
        cout<<" | Computer Science : "<< s.cs_mark <<endl;
        cout<<" | English : "<< s.english_mark <<endl;
        cout<<" Overall Average Mark: " << s.overallAverage() << endl;
    };
};


//Attendence Function 

void markAttendance() {

    if(class_list.empty()){
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    int studentID;
    cout<<" Enter Student ID to mark attendance : "<<endl;
    cin >> studentID;

    bool found=false;
    for( auto &s : class_list) {
        if(s.id == studentID) {
            s.attendance_record += 1; // Increment attendance record by 1 for each attendance marking
            cout<<" Attendance marked for "<<s.full_name 
            << "Total Day Present : " << s.attendance_record << endl;
            SaveToFile("students.txt", "students_backup.txt");
            found = true;
            break;
        };
    };

    if(!found) {
        cout<<" Student Not Found. "  <<endl;
    };

};

//displayment

void displayAttendance() {
    cout<<"\t\t\t===================="<<endl;
    cout<<"\t\t\t Attendance record  "<<endl;
    cout<<"\t\t\t===================="<<endl;

    if(class_list.empty()) {
        cout<<"No students in the system. Please add new students first."<<endl;
        return;
    };

    for(auto &s : class_list) {
        cout<<" ID : " <<s.id <<" Name : "<<s.full_name
        <<" | Days Present : "<<s.attendance_record <<endl;
    };
};


void ExportResults(const string &filename) {

    if(class_list.empty()) {
        cout << "No students in the system. Please add new students first." << endl;
        return;
    };

    int studentId;
    cout<<" Enter Student ID to export results : " <<endl;
    cin>> studentId;

    bool found = false;
    for(const auto &s : class_list) {
        if(s.id == studentId) {
            ofstream outFile(filename, ios::app); // Open file in append mode to add results without overwriting existing data
            if(!outFile) {
                cerr << " Error Opening File for writing ! "<<endl;
                return ;
            };

            outFile<<"\t\t\t  Student Result Exported : "<<endl;
            outFile << "ID: " << s.id <<endl;
            outFile << " | Name: "<< s.full_name<<endl; 
            outFile <<"  | Overall Average Mark: " << s.overallAverage() <<endl;
            outFile <<"  | Grade : " << GetGrade(s.overallAverage()) <<endl;
            outFile <<"  | Attendance : " << s.attendance_record << endl;
            outFile <<"  | Math : " << s.math_mark << endl;
            outFile <<"  | Computer Science : " << s.cs_mark << endl;
            outFile <<"  | English : " << s.english_mark << endl;
            outFile <<" --------------------------------------------- "
                    << endl;

            outFile.close();
            cout<<" Student Results Exported to 'results.txt' successfully. "<<endl;
            found = true;
            break;
        };

    };

    if(!found) {
        cout<<" Student Not Found. "<<endl;
    };
};

int main() {

    if (!login("users.txt", "users_backup.txt")) {
        return 0; // exit if login fails
    };

    LoadFromFile("students.txt", "students_backup.txt"); // Load existing student data from 
    //file at the start of the program

    studentlist student_info;
    char answer;
    char yn;
    bool keepRunning = true ; //Control flag for the loop
      
    cout<<"\t\t\t================================================"<<endl;
    cout<<"\t\t\t|                                                 |"<<endl;
    cout<<"\t\t\t| Welcome to Student Management Center For Admins |"<<endl;
    cout<<"\t\t\t|                                                 |"<<endl;
    cout<<"\t\t\t================================================="<<endl;

    cout<<"\t\t\t This is a simple program to manage student information. "<<endl;
    cout<<"\t\t\t Warning : This program is for Admins only. "<<endl;
    cout<<"\t\t\t Warning : This Program is in Upper Intermediate State. "<<endl;
    cout<<"\t\t\t [ which means it may have some bugs and limited features. ] " <<endl;
    cout<<"\t\t\t Note : Please Use Valid Inputs to Avoid Unexpected Behavior. "<<endl;

    cout<<"\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"\t\t\t                      Enjoy !" <<endl;

        do{

            cout<<"\n=================================================="<<endl;
            cout<< "=========    Student Management Menu    ========" <<endl;
            cout<< "\n=============================================== " <<endl;
            cout<<"[a] Search For a Student." <<endl;
            cout<<"[b] See average marks of all students "<<endl;
            cout<<"[c] Look highest and lowest mark among students "<<endl;
            cout<<"[d] See Grades (Pass/Fail) "<<endl;
            cout<<"[e] Edit Student Datas "<<endl;
            cout<<"[f] See Student Information "<<endl;
            cout<<"[g] Manage Attendance "<<endl;
            cout<<"[o] Exit "<<endl;

            cout<<"===================================="<<endl;
            cout<<"(Only write (a, b, c, d, ... ) Only)"<<endl;
            cout<<" Choice : ";
            cin>>answer;


        if(answer == 'a' ) {
            
            cout<<"\n==================="<<endl;
            cout<<"  Search Student  "<<endl;
            cout<<"======================="<<endl;

            cout<<"Do you wanna search by Name or ID ? ( a or b) ?"<<endl;
            cout<<" (a) Name "<<endl;
            cout<<" (b) ID "<<endl;
            cout<<" (c) Total Student List "<<endl;
            cout<<" Choice : ";
            char searchChoice;
            cin>> searchChoice;

            if(searchChoice == 'a'){
                handleStudentName();
                keepRunning = askMenuOrExit();

            }else if(searchChoice == 'b') {
                displayIDlist();
                handleStudentID(); 
                keepRunning = askMenuOrExit(); 
            }else if(searchChoice == 'c') {
                displayTotalStudents();
                keepRunning = askMenuOrExit();
            }
            else{
                cout<<" Invalid Choice. "<<endl;
                cout<<" Returning to Main Menu... "<<endl;
                keepRunning = true;
            };

                
            
        }else if(answer == 'b') {

            handleAverageMarks();
            keepRunning = askMenuOrExit();

        }else if(answer == 'c' ){

            High_Low_Students();
            keepRunning = askMenuOrExit();
                
        }else if(answer == 'd' ) {

            handleGrades();
            keepRunning = askMenuOrExit();

        }else if(answer == 'e') {

            cout<<"\n==================="<<endl;
            cout<<"  Edit Student Datas "<<endl;
            cout<<"======================="<<endl;

            cout<<" What Do you wanna do ? "<<endl;
            cout<<" (a) Delete a Student by ID. "<<endl;
            cout<<" (b) Edit a Student's Information. "<<endl;
            cout<<" (c) Add New Student. "<<endl;
            cout<<" Choice : ";
            char editChoice;
            cin>> editChoice;

                if(editChoice == 'a') {
                    displayIDlist();
                    deleteStudentByID();
                    keepRunning = askMenuOrExit();

                }else if(editChoice == 'b') {
                    cout<<" (1) Update a student's name. "<<endl;
                    cout<< "(2) Update a student's mark. "<<endl;
                    cout<<" Choice : " ;
                    int updateC;
                    cin>> updateC;

                    if(updateC == 1) {
                        cout<<" Update Student Name "<<endl;
                        displayIDlist();
                        updateStudentName();
                        keepRunning = askMenuOrExit();
                    };
                    if(updateC == 2) {
                        cout<<" Update Student Mark "<<endl;
                        displayIDlist();
                        updateStudentMark();
                        keepRunning = askMenuOrExit();
                    }else{
                        cout<<" Invalid Choice. "<<endl;
                        keepRunning = askMenuOrExit();
                    };

                } else if(editChoice == 'c') {
                    addNewStudent();
                    keepRunning = askMenuOrExit();
                }else{
                    cout<<" Invalid Choice. "<<endl;
                    keepRunning = askMenuOrExit();
                };


        }else if(answer == 'f' ) {
            cout<<"\n==================="<<endl;
            cout<<"  Student Information  "<<endl;
            cout<<"======================="<<endl;


            cout<<" a) Sorting List by ID "<<endl;
            cout<<" b) Sorting List by Name "<<endl;
            cout<<" c) Sorting List by Mark "<<endl;
            cout<<" d) Display without Sorting "<<endl;
            cout<<" e) export Student Information to File "<<endl;
            cout<<" choice : " ;

            char infoChoice;
            cin>> infoChoice;

                if(infoChoice == 'd') {
                        
                displayStudentInfo();
                displayTotalStudents();
                keepRunning = askMenuOrExit();
                }else if(infoChoice == 'a') {

                displayTotalStudents();
                SortByID();
                keepRunning = askMenuOrExit();
                }else if(infoChoice == 'b') {

                displayTotalStudents();
                SortByName();
                keepRunning=askMenuOrExit();
                }else if(infoChoice == 'c') {

                displayTotalStudents();
                SortByMark();
                keepRunning=askMenuOrExit();
                }else if(infoChoice == 'e') {
                
                displayIDlist();
                ExportResults("results.txt");
                keepRunning = askMenuOrExit();
                }else{
                cout<<" Invalid Input ." <<endl;
                keepRunning=askMenuOrExit();
            };
        }else if(answer == 'g') {
            cout<<" Attendance Manager Menu "<<endl;
            cout<<"========================="<<endl;

            cout<<"[a] Mark Attendance record for a student "<<endl;
            cout<<"[b] See Attendance record for all students "<<endl;
            cout<<" [ Invalid Input = Ban ] " <<endl;

            char opt;
            cout<<" Choice : "<<endl;
            cin>>opt;

            if(opt == 'a' || opt == 'A'){
                displayIDlist();
                markAttendance();
                keepRunning=askMenuOrExit();
            }else if(opt == 'b' || opt == 'B'){
                displayAttendance();
                keepRunning=askMenuOrExit();
            }else{
                cout<<"Invalid Input >>> " <<endl;
                keepRunning=askMenuOrExit();
            };
        }
        else if(answer == 'o' ) {
            keepRunning = false;
            cout<<"Exiting..."<<endl;
        }else{
            cout<<" Invalid Input. " <<endl;
            cout<<" Restarting... " <<endl;
            cout<<" __________________ " <<endl;

            cin.clear();
            cin.ignore(1000, '\n');

            keepRunning = true;
        };
        
    } while (keepRunning);

    SaveToFile("students.txt", "students_backup.txt"); // Save student data to file before exiting the program

    cout << "Goodbye! All data saved safely." << endl;

    
    return 0;
}




   
