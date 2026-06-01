#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
using namespace std;


/* MIND MAP */

/*

1. New Class Design : 
   - Person (Base Class)
     - Attributes: full_name, age
     - Methods: getName(), getAge(), setName(), setAge(), displayInfo() [virtual]
   - Student (Derived Class)
     - Attributes: id, cs_mark, math_mark, english_mark, attendance_record
     - Methods: displayInfo() [override], getters and setters for all attributes, overallAverage(), friend function exportsdata()

2.Origirnal Functions : 
    - login(filename, backupName): Handles user authentication by reading credentials from a file.
    - SaveToFile(filename, backupName): Saves the current student list to a file and a backup file.
    - LoadFromFile(filename, backupName): Loads student data from a file or backup file into the global student list.
    - searchStudentByID(Id): Searches for a student by ID and displays their information.
    - searchStudentByName(name): Searches for a student by name and displays their information.
    - displayIDlist(): Displays a list of all student IDs.
    - handleStudentName(): Handles searching for a student by name and displaying their information.
    - handleStudentID(): Handles searching for a student by ID and displaying their information.
    - displayTotalStudents(): Displays the total number of students in the system.
    - handleAverageMarks(): Calculates and displays the average marks for all students in each subject and overall.
    - High_Low_Students(): Finds and displays the students with the highest and lowest average marks.
    - GetGrade(mark): Returns the grade (A, B, C, F) based on the average mark.
    - handleGrades(): Displays each student's grade based on their average mark.
    - askMenuOrExit(): Asks the user if they want to return to the menu or exit after an operation.
    - deleteStudentByID(): Deletes a student from the list based on their ID after confirmation.
    - updateStudentName(): Updates a student's name based on their ID.
    - updateStudentMark(): Updates a student's mark in a specific subject based on their ID.
    - addNewStudent(): Adds a new student to the list with all required information.
    - displayStudentInfo(): Displays detailed information for all students in the list using polymorphism.
    - SortByID(), SortByName(), SortByMark(): Sorts the student list by ID, name, or average mark respectively and displays it.
    - markAttendance(): Marks attendance for a student by incrementing their attendance record based on their ID.
    - displayAttendance(): Displays the attendance record for all students in the list.
    - ExportResults(filename): Exports a specific student's results to a file based on their ID.

** OOP Concepts Implementation : 

- Encapsulation:I modified all student attributes to be private and provided public getter and setter methods for each attribute.
This way, the internal state of the student objects is protected from direct access and can
only be modified through controlled methods, ensuring data integrity and security.


-Then , I used the getter and setter methods in all functions that need to access or modify student data, such as search,
 edit, and display functions. This ensures that all interactions with student data go through the defined interface, 
 maintaining encapsulation throughout the program.

- After that, I created a base class called Person with protected attributes for full name and age, and a virtual displayInfo() method.

- I then modified the student class to be a derived class called student that inherits from Person and 
adds additional attributes for ID, marks, and attendance, as well as an overridden displayInfo()
 method to display student-specific information.

- I also implemented polymorphism by using the virtual displayInfo() method in the Person class and overriding it in the student class.
This allows me to call displayInfo() on a student object and have it execute the student-specific version of the method, 
which displays all relevant information about the student, including their name, age, ID, marks, attendance, and grade.
I used this polymorphic displayInfo() method in the displayStudentInfo() function to show detailed information for all students in the list,
and in the exportsdata() friend function to export student information to a file in a consistent format.



























*/





string GetGrade(double mark); //Function prototype for grade calculation function, which is used in multiple places in the program


class Person {
protected: //inheritance : base class with protected members to allow access in derived classes

    string full_name;
    int age;


public:

    Person(string name, int age) : full_name(name), age(age) {} ;  
    string getName() const { return full_name; }
    int getAge() const { return age; }

    void setName(const string &newName) { full_name = newName; }
    void setAge(int newAge) { age = newAge; }

    virtual void displayInfo() const {
        cout << " Name : " << full_name << endl;
        cout << " Age : " << age << endl;
    }; //Polymorphism : virtual function to allow overriding in derived classes for specific display of student information
};


class student : public Person { //inheritance : student class inherits from Person class
private: //ecapsulation : keep data private

    int id;
    double cs_mark;
    double math_mark;
    double english_mark;
    int attendance_record = 7 ; // New attribute for attendance record 

public: //encapsulation : provide public methods to access and modify private data

//Constructor to initialize student data

    student(int id, string name, int age, double cs, double math, double english, int attendance = 7)
        : id(id), Person(name, age), cs_mark(cs), math_mark(math), english_mark(english), attendance_record(attendance) {};

//Deconstructor

    ~student() {
        // No dynamic memory to clean up in this class, so the destructor can be empty
    };

    void displayInfo() const override { //Polymorphism : override the base class displayInfo function to display student-specific information
        Person::displayInfo(); // Call base class function to display name and age
        cout << " ID : " << id << endl;
        cout<<" Name : " << getName() <<endl;
        cout<< " Age : " << getAge() <<endl;
        cout << " Computer Science Mark : " << cs_mark << endl;
        cout << " Math Mark : " << math_mark << endl;
        cout << " English Mark : " << english_mark << endl;
        cout << " Attendance Record (Days Present) : " << attendance_record << endl;
        cout<< " Overall Average Mark : " << overallAverage() << endl;
        cout<<" Grade : " << GetGrade(overallAverage()) << endl;
        cout<<endl;
        cout<<" ============================== " <<endl;
    };

    //Getter & Setter functions for encapsulation

    int getID() const { return id ; }
    void setID(int newID) { id = newID; }

    string getName() const {return Person::getName(); }
    void setName(const string &newName) { Person::setName(newName);}

    double getCSMark() const { return cs_mark; }
    void setCSMark(double newCSMark) { cs_mark = newCSMark; }

    double getMathMark() const { return math_mark; }
    void setMathMark(double newMathMark) { math_mark = newMathMark; }

    double getEnglishMark() const { return english_mark; }
    void setEnglishMark(double newEnglishMark) { english_mark = newEnglishMark; }

    int getAttendanceRecord() const { return attendance_record; }
    void setAttendanceRecord(int newAttendance) { attendance_record = newAttendance; }


    //Helper function to get the average 
    double overallAverage() const{
        return (math_mark + cs_mark + english_mark) /3.0 ;
    };

    friend void exportsdata(const student &s, ofstream &outFile);
     //Friend function to allow access to private members of student class for exporting data to file
};

void exportsdata(const student &s, ofstream &outFile) {
    outFile<<"\t\t\t  Student Result Exported : "<<endl;
    outFile << "ID: " << s.getID() <<endl;
    outFile << " | Name: "<< s.getName()<<endl; 
    outFile << " | Age : " << s.getAge() <<endl;
    outFile <<"  | Overall Average Mark: " << s.overallAverage() <<endl;
    outFile <<"  | Grade : " << GetGrade(s.overallAverage()) <<endl;
    outFile <<"  | Attendance : " << s.getAttendanceRecord() << endl;
    outFile <<"  | Math : " << s.getMathMark() << endl;
    outFile <<"  | Computer Science : " << s.getCSMark() << endl;
    outFile <<"  | English : " << s.getEnglishMark() << endl;
    outFile<<" --------------------------------------------- "
            << endl;
        
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
    vector<student> class_list ;

//Save to File

void SaveToFile(const string &filename, const string &backupName) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error Opening File for wiriting ! " << endl;
        return ;
    };

    for(auto &S : class_list) {
        outFile << S.getID() << ","
                << S.getName() << ","
                << S.getAge() << ","
                << S.getCSMark() << "," 
                << S.getMathMark() << ","
                << S.getEnglishMark() << ","
                << S.getAttendanceRecord() << endl;
    };

    outFile.close();
    cout<<" Student Datas Saved to 'The Data Base' successfully. "<<endl;

    // Always also save to backup file
    ofstream backupFile(backupName);
    if (!backupFile.is_open()) {
        cerr << "Error: Could not open backup file " << backupName << " for writing." << endl;
    } else {
        for (auto &S : class_list) {
            backupFile << S.getID() << ","
                       << S.getName() << ","
                       << S.getAge() << ","
                       << S.getCSMark() << ","
                       << S.getMathMark() << ","
                       << S.getEnglishMark() << ","
                       << S.getAttendanceRecord() << endl;
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
    string line ; //variable to hold each line read from the file

    while (getline(inFile, line)) { //read file line by line in 'Line' variable 
        stringstream ss(line); //Warp line in stringstream to parse it easily
        string temp, name; //temporary variable to hold parsed data
        int id, attendance ;
        double cs, math, english ;

        //Extract Values separated by commas

        getline(ss, temp, ','); id = stoi(temp); //convert string to int and assign to student id
        getline(ss, name, ','); //name as string
        getline(ss, temp, ','); int age = stoi(temp);
        getline(ss, temp, ','); cs= stod(temp); //convert string to double and assign to cs_mark
        getline(ss, temp, ','); math= stod(temp); //convert string to double and assign to math_mark
        getline(ss, temp, ','); english = stod(temp); //convert string to double and assign to english_mark
        getline(ss, temp, ','); attendance = stoi(temp); 

        student s(id, name, age, cs, math, english, attendance); //create a student object with the extracted data
        class_list.push_back(s); //add the student object to the global class list
    };

    inFile.close(); //close the file after reading
    cout<<"\t\t\t Student Datas Loaded from 'The Data Base' successfully. "<<endl;
};


//Option A : search student 

//reusable function to search student by name and ID, which can be used in both search and edit options
//Id

void searchStudentByID(int Id) {
  for(int i=0 ; i < class_list.size() ; i++) {
    if(class_list[i].getID() == Id) {
        cout<<" Student found = "<<class_list[i].getName()<<endl;
        cout<<" Age : "<<class_list[i].getAge()<<endl;
        cout<<" Id : "<<class_list[i].getID()<<endl;
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
        if(class_list[i].getName() == name) {
            cout<<" Student found = "<<class_list[i].getName()<<endl;
            cout<<" Age : "<<class_list[i].getAge()<<endl;
            cout<<" Id : "<<class_list[i].getID()<<endl;
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

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    };


    cout<<" Student ID List : "<<endl;
    for(auto &s : class_list) {
        cout<<" ID : "<<s.getID()<<endl;
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
        total_math += s.getMathMark();
        total_cs += s.getCSMark();
        total_english += s.getEnglishMark();
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
        cout<<" Name : "<<class_list[highestIndex].getName()<<endl;
        cout << "Average Mark: " << class_list[highestIndex].overallAverage() << endl;
    } else if(choice == 'L' || choice == 'l') {
        cout << "\nLowest Mark Student: " << endl;
        cout << "Name: " << class_list[lowestIndex].getName() << endl;
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
        cout<<i + 1<<". "<<class_list[i].getName()
        <<"'s Grade :: " << GetGrade(class_list[i].overallAverage())<<endl;


        if(GetGrade(class_list[i].overallAverage()) == "F") {
            cout<<" Note : "<<class_list[i].getName()<<" has failed. "<<endl;
        }else if(GetGrade(class_list[i].overallAverage()) == "A" || GetGrade(class_list[i].overallAverage()) == "B" || GetGrade(class_list[i].overallAverage()) == "C") {
            cout<<" State : "<<class_list[i].getName()<<" has passed. "<<endl;
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
        if(it->getID() == deleteID) {
            cout<<" Studend Found : "<<it->getName()<<endl;
            cout<<" Student Overall Average Mark : "<<it->overallAverage()<<endl;
            cout<<" Student Grade : "<<GetGrade(it->overallAverage())<<endl;
            cout<<" Student Attendance Record : "<<it->getAttendanceRecord()<<endl;
            cout<<" Student Age : "<<it->getAge()<<endl;
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
        if (s.getID() == updateID) {
            cout<< " Current Name : " << s.getName() << endl;
            cout<< " Enter New Name : " ;
            cin.ignore(1000, '\n');
            string newName;
            getline(cin, newName);
            s.setName(newName);
            cout<< " Name Updated. "<<endl;
            cout<< " Updated Name : " << s.getName() << endl;
            cout<<" ID : " << s.getID() << endl;
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
        if (s.getID() == updateID) {
            cout<<" Which Subject ? "<<endl;
            cout<<" 1) Math "<<endl;
            cout<<" 2) Computer Science"<<endl;
            cout<<" 3) English"<<endl;

            int choice;
            cin >> choice ;

            double newMark;
            cout<<" Enter New Mark : ";
            cin>> newMark;

            if(choice ==1 ) s.setMathMark(newMark);
            else if(choice ==2 ) s.setCSMark(newMark);
            else if(choice==3 ) s.setEnglishMark(newMark);
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
    int newAge;
    string newName;
    double newCs, newmath, newEnglish ;

    cout<< " Enter New Student ID : " ;
    cin>> newID;
    //prevent duplicate ID
    for(auto &s : class_list) {
        if(s.getID() == newID) {
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
    cout<<" Enter Student Age : ";
    cin>>newAge;

    student newStudent (newID, newName, newAge, newCs, newmath, newEnglish);
    class_list.push_back(newStudent);
    SaveToFile("students.txt", "students_backup.txt"); // Save the updated student list to file after adding new student
    cout<< " New Student Added. "<<endl;

    cout<<" Display New Student Informations : "<<endl;
    cout<<" ID : "<<newStudent.getID()<<endl;
    cout<<" Name : "<<newStudent.getName()<<endl;
    cout<<" Age : "<<newStudent.getAge()<<endl;
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

    //Polymorphism : using the displayInfo function of the student class to display all relevant information of each student in the list
    for ( auto &s : class_list) {
        s.displayInfo();
    }
    cout<<" ----------------------- "<<endl;
};


//a, Sorting List by Id

void SortByID() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };


    sort(class_list.begin() , class_list.end() ,[](const student &a, const student &b ){
        return a.getID() < b.getID() ; //smaller one comes first rule 
    } );

    cout<<"Sorted By ID : "<< endl;
    for (auto &s : class_list) {
        cout << "ID: " << s.getID() << " | Name: " << s.getName() << " | Overall Average Mark: " << s.overallAverage() << endl;
    };

};

//b, Sorting List by names

void SortByName() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };


    sort(class_list.begin() , class_list.end() , [](const student &a , const student &b) {
        return a.getName() < b.getName(); 
    });

    cout<<" Sorted by Name : "<<endl ;
    for (auto &s : class_list) {
        cout<<" Name : " << s.getName() <<" | ID : " << s.getID() <<" | Average Mark : " << s.overallAverage() <<endl;
    };

};

//c, Sorting List by Marks

void SortByMark() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    sort(class_list.begin(), class_list.end(), [](const student &a, const student &b) {
        return a.overallAverage() > b.overallAverage(); // descending order (highest first)
    });

    cout << "Sorted by Mark:" <<endl;
    for (auto &s : class_list) {
        cout << "ID: " << s.getID() << " | Name: " << s.getName() << endl;
        cout<< " | Math : " << s.getMathMark() <<endl;
        cout<<" | Computer Science : "<< s.getCSMark() <<endl;
        cout<<" | English : "<< s.getEnglishMark() <<endl;
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
        if(s.getID() == studentID) {
            s.setAttendanceRecord(s.getAttendanceRecord() + 1); // Increment attendance record by 1 for each attendance marking
            cout<<" Attendance marked for "<<s.getName() 
            << "Total Day Present : " << s.getAttendanceRecord() << endl;
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
        cout<<" ID : " <<s.getID() <<" Name : "<<s.getName()
        <<" | Days Present : "<<s.getAttendanceRecord() <<endl;
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
        if(s.getID() == studentId) {
            ofstream outFile(filename, ios::app); // Open file in append mode to add results without overwriting existing data
            if(!outFile) {
                cerr << " Error Opening File for writing ! "<<endl;
                return ;
            };

            exportsdata(s, outFile); // Use the friend function to export student data to file

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

