#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
#include<iomanip> // for std::setprecision
using namespace std;


/* MIND MAP */

/*

-I implemented a GPA system to provide a more comprehensive evaluation of student performance,
 allowing for a more nuanced understanding of their academic standing beyond just letter grades.

- I decorated the console outputs with clear section headers and separators to enhance readability and user experience,
 making it easier for users to navigate through the information displayed.

- I rewrote the entire if else functions of the main() to switch cases for better organization and readability, 
allowing for clearer separation of different functionalities and easier maintenance of the code.

- I  Implemented a Ranking System which will display Top 5 Student and made it also a Sorting Option .

- I then created Exam Result Processing System which allows user not to just look but also export it .

- I created Multi-User log in system to improve Security with 3 roles.
Users are allocated to 3 roles which are Student , Teachers And Admins . Teachers and Students have limited functions and 
access. I had to modified each Option to check for current user's log in role after giving away every access.

- later, I planted a Scholarship Eligibility Checker for better performance and realistic program. 

- I implemented a delete user, display user, add user which based on roles and authentications only.

- Finally, I added a Report Card Generator to make it more fancier ! 



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

    virtual ~Person() {
        // No dynamic memory to clean up in this class, so the destructor can be empty
    };

};



class student : public Person { //inheritance : student class inherits from Person class
private: //ecapsulation : keep data private

    int id;
    double cs_mark;
    double math_mark;
    double english_mark;
    int attendance_record = 7 ; // New attribute for attendance record 
    double gpa; // New attribute for GPA
    
public: //encapsulation : provide public methods to access and modify private data

//Constructor to initialize student data

    student(int id, string name, int age, double cs, double math, double english, int attendance = 7)
        : id(id), Person(name, age), cs_mark(cs), math_mark(math), english_mark(english), attendance_record(attendance) {gpa = calculateGPA();} ; //Constructor to initialize student data, with default attendance of 7 days

//Deconstructor

    ~student() {
        // No dynamic memory to clean up in this class, so the destructor can be empty
    };


          //GPA Helper

    double marktoPoint(double mark) const {
        if(mark >= 70) {
            return 4.0;
        }else if(mark >= 60) {
            return 3.0;
        }else if(mark >= 30) {
            return 2.0;
        }else{
            return 0.0;
        };

    };

    double calculateGPA() const {
        double totalPoints = marktoPoint(cs_mark) + marktoPoint(math_mark) + marktoPoint(english_mark);
        return totalPoints / 3.0; // Average GPA across the three subjects
    };

    //Getter for GPA
    double getGPA() const {
        return gpa;
    };

    //Setter for GPA ( in case we want to recalculate GPA after updating marks )
    void upgradeGPA() {
        gpa = calculateGPA();
    };

    void setGPA(double newGPA) {
        gpa = newGPA;
    };



    void displayInfo() const override { //Polymorphism : override the base class displayInfo function to display student-specific information
        Person::displayInfo(); // Call base class function to display name and age
        cout << " ID : " << id << endl;
        cout << " Computer Science Mark : " << cs_mark << endl;
        cout << " Math Mark : " << math_mark << endl;
        cout << " English Mark : " << english_mark << endl;
        cout << " Attendance Record (Days Present) : " << attendance_record << endl;
        cout<< " Overall Average Mark : " << overallAverage() << endl;
        cout<<" Grade : " << GetGrade(overallAverage()) << endl;
        cout<<" GPA : " <<fixed<<setprecision(2)<<getGPA() << endl;
        cout<<endl; 
        cout<<" ============================== " <<endl;
    };

    //Getter & Setter functions for encapsulation

    int getID() const { return id ; }
    void setID(int newID) { id = newID; }

    string getName() const {return Person::getName(); }
    void setName(const string &newName) { Person::setName(newName);}

    double getCSMark() const { return cs_mark; }
    void setCSMark(double newCSMark) { cs_mark = newCSMark; upgradeGPA(); } // Recalculate GPA whenever marks are updated

    double getMathMark() const { return math_mark; }
    void setMathMark(double newMathMark) { math_mark = newMathMark; upgradeGPA(); } // Recalculate GPA whenever marks are updated

    double getEnglishMark() const { return english_mark; }
    void setEnglishMark(double newEnglishMark) { english_mark = newEnglishMark; upgradeGPA(); } // Recalculate GPA whenever marks are updated

    int getAttendanceRecord() const { return attendance_record; }
    void setAttendanceRecord(int newAttendance) { attendance_record = newAttendance; }


    //Helper function to get the average 
    double overallAverage() const{
        return (math_mark + cs_mark + english_mark) / 3.0 ;
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
    outFile <<"  | GPA : " << fixed << setprecision(2) << s.getGPA() << endl;
    outFile<<" --------------------------------------------- "
            << endl;
        
};


//Log in System

struct User {
    string username;
    string password;
    string role;
};

User currentuser; // store logged in user globally


bool login(const string &filename, const string &backupName) {

    ifstream inFile(filename);
    if(!inFile.is_open()) {
        cerr << " Error Opening Authentication File. "
            << "Trying Backup File... " <<endl;

        inFile.clear();
        inFile.open(backupName);
        if(!inFile.is_open()) {
            cerr << " No Backup File Found. Exiting... " <<endl;
            return false; // Exit the function if no backup file is found
        } else {
            cout << " Backup file loaded successfully. "<<endl;
        };
    };

    string username, password;
    cout<<" Enter Username (hint : users.txt) : " ;
    cin>> username;
    cout<<" Enter Password : " ;
    cin>> password;

    string line;

    while(getline(inFile, line)) { // Read the file
        stringstream ss(line); // Wrap the line in a stringstream to parse it easily
        string Fileuser, Filepass, Filerole;
        getline(ss, Fileuser, ','); // Extract the username from the line
        getline(ss, Filepass, ','); // Extract the password from the line
        getline(ss, Filerole, ','); // Extract the role from the line 
        if(username == Fileuser && password == Filepass) {
            cout<<" Login Successful. Welcome, "<<username<<" ! "<<endl;
            currentuser.username = Fileuser;
            currentuser.password = Filepass;
            currentuser.role = Filerole;
            return true;
        };

    };

    cout<<" Login Failed. Invalid username or password. "<<endl;
    return false;
    

};

//Registery

void registeruser(const string &filename , const string &backup_name) {
    if(currentuser.role!="admin") {
        cout<<" Only Admins Can register new user " <<endl;
        return;
    };

    ofstream outFile(filename, ios::app);
     if(!outFile) {
        cerr << "Error opening main user file!" << endl;
        return;
    }

    ofstream backupFile(backup_name, ios::app);
    if(!backupFile) {
        cerr << "Error opening backup user file!" << endl;
        return;
    }

        string newUser, newPass, newRole, auth ;
        cout<< " Enter New Username : " ;
        cin >> newUser;
        cout<<endl;
        cout<<" Enter User's Password : ";
        cin >> newPass;
        cout<<endl;
        cout<<" Enter the role for the user ( must be admin,teacher,student) : " ;
        cin>> newRole;
        cout<<endl;

        //Valide Role 
        if(newRole != "admin" && newRole != "teacher" && newRole != "student") {
            cout << "Invalid role. Must be admin, teacher, or student." << endl;
            return;
        };

        //Admin Authenticate
        cout<<" Enter Password of the admin to authenticate : " ;
        cin >> auth;
        cout<<endl;
        if(auth != currentuser.password) {
            cout << "Authentication failed. User not registered." << endl;
            return;
        };

        // Write new user to file
        outFile << newUser << "," << newPass << "," << newRole << endl;
        backupFile << newUser << "," << newPass << "," << newRole << endl;
        cout << "User registered successfully!" << endl;
    
};

//Role checker

bool hasrole( const string &required ){
    return currentuser.role == required ;
};

bool hasAnyrole( const vector<string> &roles ){
    for(const auto &r : roles ){
        if(currentuser.role == r) return true;
    }
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
                << S.getAttendanceRecord() << ","
                << fixed << setprecision(2) << S.getGPA() << endl;
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
                       << S.getAttendanceRecord() << ","
                       << S.getGPA() << endl;
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
        inFile.clear();
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
        getline(ss, temp, ','); double gpa = stod(temp);

        student s(id, name, age, cs, math, english, attendance); //create a student object with the extracted data
        s.upgradeGPA(); // Calculate and set GPA for the student object; 
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
        cout<<" Grade : "<<GetGrade(class_list[i].overallAverage())<<endl;
        cout<<" GPA : "<<fixed<<setprecision(2)<<class_list[i].getGPA()<<endl;
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
            cout<<" Grade : "<<GetGrade(class_list[i].overallAverage())<<endl;
            cout<<" GPA : "<<fixed<<setprecision(2)<<class_list[i].getGPA()<<endl;
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
        cout<<" GPA : "<<fixed<<setprecision(2)<<class_list[highestIndex].getGPA()<<endl;
    } else if(choice == 'L' || choice == 'l') {
        cout << "\nLowest Mark Student: " << endl;
        cout << "Name: " << class_list[lowestIndex].getName() << endl;
        cout << "Average Mark: " << class_list[lowestIndex].overallAverage() << endl;
        cout<<" GPA : "<<fixed<<setprecision(2)<<class_list[lowestIndex].getGPA()<<endl;
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
            cout<<" Studnet GPA : "<<fixed<<setprecision(2)<<it->getGPA()<<endl;

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
    cout<<" GPA : "<<newStudent.getGPA()<<endl;

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

    auto temp = class_list;
    sort(temp.begin() , temp.end() ,[](const student &a, const student &b ){
        return a.getID() < b.getID() ; //smaller one comes first rule 
    } );

    cout<<"Sorted By ID : "<< endl;
    for (auto &s : temp) {
        cout << "ID: " << s.getID() << " | Name: " << s.getName() << " | Overall Average Mark: " << s.overallAverage() << endl;
    };

};

//b, Sorting List by names

void SortByName() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };


    auto temp = class_list;
    sort(temp.begin() , temp.end() , [](const student &a , const student &b) {
        return a.getName() < b.getName(); 
    });

    cout<<" Sorted by Name : "<<endl ;
    for (auto &s : temp) {
        cout<<" Name : " << s.getName() <<" | ID : " << s.getID() <<" | Average Mark : " << s.overallAverage() <<endl;
    };

};

//c, Sorting List by Marks

void SortByMark() {

    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    auto temp = class_list;
    sort(temp.begin(), temp.end(), [](const student &a, const student &b) {
        return a.overallAverage() > b.overallAverage(); // descending order (highest first)
    });

    cout << "Sorted by Mark:" <<endl;
    for (auto &s : temp) {
        cout << "ID: " << s.getID() << " | Name: " << s.getName() << endl;
        cout<< " | Math : " << s.getMathMark() <<endl;
        cout<<" | Computer Science : "<< s.getCSMark() <<endl;
        cout<<" | English : "<< s.getEnglishMark() <<endl;
        cout<<" Overall Average Mark: " << s.overallAverage() << endl;
    };
};

//Sort by GPA

void SortbyGpa() {
    if(class_list.empty()) {
    cout << "No students in the system. Please add new students first." << endl;
    return;
    };

    auto temp = class_list;
    sort(temp.begin(), temp.end(), [](const student &a, const student &b) {
        return a.getGPA() > b.getGPA(); // descending order (highest first)
    });

    cout << "Sorted by GPA:" <<endl;
    for(auto &s : temp) {
        cout<<" GPA : " << s.getGPA() << endl;
        cout<<" ID : " << s.getID() << " | Name : " << s.getName() << endl;
        cout<<" | Math : " << s.getMathMark() <<endl;
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


// Ranking System (Top 5 Students)

void RankStudents() {
    if(class_list.empty()) {
        cout<<" No students in the system. Please add new students first." << endl;
        return;
    }else if(class_list.size() < 5) {
        cout<<" Not enough students to rank. At least 5 students are required." << endl;
        return;
    };

    // Sort students by combined marks (descending order)
    auto temp = class_list;
    sort(temp.begin(), temp.end(),[](const student &a, const student &b) {
        double totalA = a.getCSMark() + a.getMathMark() + a.getEnglishMark();
        double totalB = b.getCSMark() + b.getMathMark() + b.getEnglishMark();
        return totalA > totalB; //Hightest first
    } );

    cout<<"\n=============================="<<endl;
    cout<<"       Top 5 Students           " <<endl;
    cout<<"   (Ranked by Total Marks)      "<<endl;
    cout<<"================================"<<endl;

    //Display Top 5 student

    for(int i=0 ; i < 5 ; i++) {
        double totalMarks = temp[i].getCSMark() + temp[i].getMathMark() + temp[i].getEnglishMark();
        cout<<" Rank "<< i+1 <<" : "
            <<" | Name : " <<temp[i].getName()
            <<" | ID : " << temp[i].getID()
            <<" | Age : " << temp[i].getAge()
            <<" | GPA : " << fixed << setprecision(2) << temp[i].getGPA()
            <<" | Total Marks : " << totalMarks
            <<endl;
    };
};

//Exam Result Processing System

void ProcessExamResults() {
    if(class_list.empty()) {
        cout << "No students in the system. Please add new students first." << endl;
        return;
    };

    // Sort students by combined marks (descending order)
    auto temp = class_list;
    sort(temp.begin(), temp.end(),[](const student &a, const student &b) {
        double totalA = a.getCSMark() + a.getMathMark() + a.getEnglishMark();
        double totalB = b.getCSMark() + b.getMathMark() + b.getEnglishMark();
        return totalA > totalB; //Hightest first
    } );

    cout<<"\n=============================="<<endl;
    cout<<"    Exam Results Processed   " <<endl;
    cout<<"================================"<<endl;

    for(int i=0; i<temp.size(); i++) {
        double totalMarks = temp[i].getCSMark() + temp[i].getMathMark() + temp[i].getEnglishMark();
        cout<<" Rank "<< i+1 <<" : "
            <<" | Name : " <<temp[i].getName()
            <<" | ID : " << temp[i].getID()
            <<" | Age : " << temp[i].getAge()
            <<" | GPA : " << fixed << setprecision(2) << temp[i].getGPA()
            <<" | Total Marks : " << totalMarks
            <<" | Grade : " << GetGrade(temp[i].overallAverage())
            <<endl;
    };

    cout<<" Exam Results Processed and Displayed Successfully. "<<endl;
    cout<<" Ready to Export this into results.txt ? "<<endl;
    cout<<" (y/n) : " ;
    char exportChoice;
    cin>> exportChoice;

    switch(exportChoice) {
        case 'y':
        case 'Y': {
            ofstream outFile("results.txt");
            if(!outFile) {
                cerr << " Error Opening File for writing ! "<<endl;
                return ;
            };

            for(const auto &s : class_list) {
                exportsdata(s, outFile); // Use the friend function to export student data to file
            };

            outFile.close();
            cout<<" Exam Results Exported to 'results.txt' successfully. "<<endl;
            break;
        };
        case 'n':
        case 'N':
            cout<<" Export Cancelled. "<<endl;
            break;
        default:
            cout<<" Invalid Choice. Export Cancelled. "<<endl;
    }


};

//ScholarShip Checker 

void scholarchecker() {

    if(class_list.empty()) {
        cout<<" NO Student in the System to check ..." <<endl;
        return;
    };

    int searchid;
    cout<<" Enter Student ID to check : " <<endl;
    cin>>searchid;

    bool found = false;

    for(auto &s : class_list) {
        if(s.getID() == searchid ) {
            found = true ;
            s.displayInfo(); //show student info

            //check based on GPA
            if(s.getGPA() >= 3.5 ){
                cout<< " result :  Eligible for Scholarship " <<endl;
            }else{
                cout<<" result : Not Eligible for scholarship "<<endl;
            };

            cout<<"\n=================================="<<endl;
            break;

        };
    };

    if(!found){
        cout<< " Student Not Found " <<endl;
    };
};


//Display Users

void displayusers(const string &filename , const string &backupname ){
    auto showFile = [](const string &file) {
        ifstream inFile(file);
         if(!inFile) {
            cerr << "Could not open " << file << endl;
            return;
        };

        cout<<" Users From System " <<endl;
        string line;
        while(getline(inFile, line)) {
            stringstream ss(line);
            string username, password, role;
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, role, ',');
            cout << "Username: " << username << " | Role: " << role << endl;
        }
    };

    showFile(filename);

};

//Delete Users

void deleteusers(const string &filename , const string &backupname ) {
    if(currentuser.role != "admin") {
        cout << "Access denied. Only Admins can delete users." << endl;
        return;
    };

    vector<User> users;
    string line;

    ifstream inFile(filename);
    if(!inFile) {
        cerr << "Error opening " << filename << endl;
        return;
    };

    while(getline(inFile, line)){
        stringstream ss(line);

        string username, pass, role;
        getline(ss, username, ',');
        getline(ss, pass, ',');
        getline(ss, role, ',');
        users.push_back({username, pass, role});
    };

    inFile.close();

    string deluser;
    cout<<" Enter the username of the user you want to delete (will delete the first match) : " ;
    cin>>deluser;

    bool found = false;
    for(auto it = users.begin(); it != users.end(); ++it) {
        if(it->username == deluser) {
            if(it->role == "admin") {
                cout << "Cannot delete admin accounts!" << endl;
                return;
            }
            users.erase(it);
            found = true;
            cout << "User deleted successfully (first match)." << endl;
            break;
        };
    };

    if(!found){
        cout<<"Users not found"<<endl;
        return;
    };

    ofstream outFile(filename);
    ofstream backupFile(backupname);

    if(!outFile || !backupFile ) {
        cerr<<" Error Opening one or both Output File !" <<endl;
        return;
    };

      for(auto &u : users) {
        outFile   << u.username << "," << u.password << "," << u.role << endl;
        backupFile << u.username << "," << u.password << "," << u.role << endl;
    }

    outFile.close();
    backupFile.close();

};



//Student Report Card Generator

void ReportCard() {
    if(class_list.empty()){
        cout<<" No Student here to generate report card "<<endl;
        return;
    };

    int searchID;
    cout << "Enter Student ID to generate report card: ";
    cin >> searchID;

    bool found = false;
    for(auto &s : class_list) {
        if(s.getID() == searchID ) {
            found = true;

            cout << "\n======================================" << endl;
            cout << "           Student Report Card       " << endl;
            cout << "======================================" << endl;
            cout << " Name: " << s.getName() << endl;
            cout << " ID: " << s.getID() << endl;
            cout << " Age: " << s.getAge() << endl;
            cout << "--------------------------------------" << endl;
            cout << " Computer Science: " << s.getCSMark() << endl;
            cout << " Math: " << s.getMathMark() << endl;
            cout << " English: " << s.getEnglishMark() << endl;
            cout << "--------------------------------------" << endl;
            cout << " Overall Average: " << fixed << setprecision(2) << s.overallAverage() << endl;
            cout << " Grade: " << GetGrade(s.overallAverage()) << endl;
            cout << " GPA: " << fixed << setprecision(2) << s.getGPA() << endl;
            cout << " Attendance: " << s.getAttendanceRecord() << " days" << endl;
            cout << "======================================" << endl;
            break;

        }
    }

     if(!found) {
        cout << "Student not found." << endl;
    };

}








int main() {
    if (!login("users.txt", "users_backup.txt")) {
        return 0; // exit if login fails
    }

    LoadFromFile("students.txt", "students_backup.txt"); // Load existing student data

    char answer;
    bool keepRunning = true;

    cout << "\t\t\t==============================================================" << endl;
    cout << "\t\t\t             Welcome to Student Management Center    " << endl;
    cout << "\t\t\t==============================================================" << endl;
    cout << " \t\t\t This program helps manage student information." << endl;
    cout << " \t\t\t  Warning: Admin access only." << endl;
    cout << " \t\t\t Note: Use valid inputs to avoid unexpected behavior." << endl;
    cout << "\t\t\t --------------------------------------------------------------" << endl;
    cout << "\t\t\t                        Enjoy!                                " << endl;
    cout << "\t\t\t==============================================================" << endl;

    do {
        cout << "\n==============================================================" << endl;
        cout << "                    MAIN MENU OPTIONS                         " << endl;
        cout << "==============================================================" << endl;
        cout << " [a]   Search For a Student (Teachers and Admin)" << endl;
        cout << " [b]   See Average Marks of All Students (All Role)" << endl;
        cout << " [c]   Highest and Lowest Marks(All Roles)" << endl;
        cout << " [d]   Grade System (All Roles)" << endl;
        cout << " [e]   Edit Student Data (Admin and Terachers)" << endl;
        cout << " [f]   Student Information & Sorting (Teachers and Admin)" << endl;
        cout << " [g]   Manage Attendance(Teachers and Admins)" << endl;
        cout << " [h]   Process Exam Results(Teachers and Admin) " << endl;
        cout << " [i]   Scholarship Eligibility Checker (Teachers And Admin ) "<<endl;
        cout << " [j]   User Management System (Admin and Teachers) "<<endl;
        cout << " [o]  Exit Program" << endl;
        cout << "==============================================================" << endl;
        cout << " Enter Choice (a, b, c, ...): ";
        cin >> answer;

        switch(answer) {
            case 'a': {
                if(!hasAnyrole({"admin","teacher"})){
                    cout<<"Access Denied. Admins or Teacher Only "<<endl;
                    break;
                };

                cout << "\n------------------- SEARCH STUDENT -------------------" << endl;
                cout << " (a) Search by Name" << endl;
                cout << " (b) Search by ID" << endl;
                cout << " (c) Show Total Student List" << endl;
                cout << "------------------------------------------------------" << endl;
                cout << " Choice: ";
                char searchChoice;
                cin >> searchChoice;

                switch(searchChoice) {
                    case 'a': handleStudentName(); break;
                    case 'b': displayIDlist(); handleStudentID(); break;
                    case 'c': displayTotalStudents(); break;
                    default: cout << "  Invalid Choice." << endl;
                }
                keepRunning = askMenuOrExit();
                break;
            }

            case 'b':
                cout << "\n------------------- AVERAGE MARKS -------------------" << endl;
                handleAverageMarks();
                keepRunning = askMenuOrExit();
                break;

            case 'c':
                cout << "\n------------------- HIGH/LOW MARKS ------------------" << endl;
                High_Low_Students();
                keepRunning = askMenuOrExit();
                break;

            case 'd': {
                cout << "\n------------------- GRADE SYSTEM --------------------" << endl;
                cout << " (a) Normal Grade System (A, B, C, F)" << endl;
                cout << " (b) GPA System" << endl;
                cout << " (c) Ranking System ( Top 5 Students )" << endl;
                cout << "------------------------------------------------------" << endl;
                cout << " Choice: ";
                char gradeChoice;
                cin >> gradeChoice;

                switch(gradeChoice) {
                    case 'a': handleGrades(); 
                    break;
                    case 'b':
                        for(auto &s : class_list) {
                            cout << " Name: " << s.getName()
                                 << " | ID: " << s.getID()
                                 << " | GPA: " << fixed << setprecision(2) << s.getGPA() << endl;
                        }
        
                        break;
                    case 'c':
                        RankStudents();
                        break;
                    default: cout << " Invalid Choice." << endl;
                }
                keepRunning = askMenuOrExit();
                break;
            }

            case 'e': {

                cout << "\n------------------- EDIT STUDENT DATA ----------------" << endl;
                cout << " (a) Delete a Student by ID(Admins Only)" << endl;
                cout << " (b) Edit a Student's Information" << endl;
                cout << " (c) Add New Student" << endl;
                cout << "------------------------------------------------------" << endl;
                cout << " Choice: ";
                char editChoice;
                cin >> editChoice;

                switch(editChoice) {
                    case 'a': 
                    
                    if(!hasrole("admin")){
                    cout<<"Access Denied. Admins Only "<<endl;
                    break;
                    };
                    displayIDlist(); deleteStudentByID();
                    break;

                    case 'b': 

                    if(!hasAnyrole({"admin","teacher"})){
                    cout<<"Access Denied. Admins or Teacher Only "<<endl;
                    break;
                    };
                        cout << " (1) Update Student Name" << endl;
                        cout << " (2) Update Student Mark" << endl;
                        cout << " Choice: ";
                        int updateC;
                        cin >> updateC;
                        if(updateC == 1) { displayIDlist(); updateStudentName(); }
                        else if(updateC == 2) { displayIDlist(); updateStudentMark(); }
                        else cout << "  Invalid Choice." << endl;
                        break;
                    
                    case 'c':
                    
                    if(currentuser.role == "admin" || currentuser.role == "teacher") {
                                addNewStudent(); break;
                            } else {
                                cout << "Access denied. Only Admins or Teachers can add new students." << endl;
                            }
                            break;

                    default: cout << "  Invalid Choice." << endl;
                }
                keepRunning = askMenuOrExit();
                break;
            }

            case 'f': {

                if(!hasAnyrole({"admin","teacher"})){
                    cout<<"Access Denied. Admins or Teacher Only "<<endl;
                    break;
                };
                

                cout << "\n------------------- STUDENT INFORMATION --------------" << endl;
                cout << " (a) Sort by ID" << endl;
                cout << " (b) Sort by Name" << endl;
                cout << " (c) Sort by Mark" << endl;
                cout << " (d) Display without Sorting" << endl;
                cout << " (e) Export Student Information to File" << endl;
                cout << " (f) Sort by GPA" << endl;
                cout << " (g) Sort by Ranks" << endl;
                cout << " (h) Student Report Card Generator "<<endl;
                cout << "------------------------------------------------------" << endl;
                cout << " Choice: ";
                char infoChoice;
                cin >> infoChoice; 

                switch(infoChoice) {
                    case 'a': displayTotalStudents(); SortByID();; break;
                    case 'b': displayTotalStudents(); SortByName();  break;
                    case 'c': displayTotalStudents(); SortByMark();  break;
                    case 'd': displayStudentInfo(); displayTotalStudents(); break;
                    case 'e': displayIDlist(); ExportResults("results.txt");  break;
                    case 'f': displayTotalStudents(); SortbyGpa(); break;
                    case 'g': displayTotalStudents(); RankStudents(); break;
                    case 'h': displayIDlist(); ReportCard();  break;
                    default: cout << "  Invalid Choice." << endl;
                }
                keepRunning = askMenuOrExit();
                break;
            }

            case 'g': {

                if(!hasAnyrole({"admin","teacher"})){
                    cout<<"Access Denied. Admins or Teacher Only "<<endl;
                    break;
                };
                
                cout << "\n------------------- ATTENDANCE MANAGER ---------------" << endl;
                cout << " (a) Mark Attendance for a Student" << endl;
                cout << " (b) See Attendance Records for All Students" << endl;
                cout << "------------------------------------------------------" << endl;
                cout << " Choice: ";
                char opt;
                cin >> opt;

                switch(opt) {
                    case 'a': displayIDlist(); markAttendance();break;
                    case 'b': displayAttendance(); break;
                    default: cout << "  Invalid Choice." << endl;
                }
                keepRunning = askMenuOrExit();
                break;
            }

            case 'h':
                if(!hasAnyrole({"admin","teacher"})){
                    cout<<"Access Denied. Admins or Teacher Only "<<endl;
                    break;
                };
                
                cout << "\n------------------- EXAM RESULT PROCESSOR ---------------" << endl;
                ProcessExamResults();
                keepRunning = askMenuOrExit();
                break;

            case 'i' :
                if(!hasAnyrole({"admin","teacher"})){
                    cout<<"Access Denied. Admins or Teacher Only "<<endl;
                    break;
                };

                cout<<"\n------------ SCHOLARSHIP CHECKER -----------------"<<endl;
                displayIDlist();
                scholarchecker();
                keepRunning = askMenuOrExit();
                break;


            case 'j' :

                if(!hasAnyrole({"admin","teacher"})){
                    cout<<" Access Denied. Admins or Teacher only "<<endl;
                    break;
                };

                cout<<"\n------------ USER MANAGEMENT CENTRE --------------"<<endl;
                cout<<" [a] check userlist " <<endl;
                cout<<" [b] Add new User " <<endl;
                cout<<" [c] Delete User "<<endl;

                char usrchoice;
                cin>> usrchoice;

                switch(usrchoice){
                    case 'a' :
                    displayusers("users.txt","users_backup.txt");
                    
                    break;

                    case 'b' :
                    cout<<"\n--------- Register New User ------ "<<endl;
                    registeruser("users.txt","users_backup.txt");
                   
                    break;
                    
                    case 'c' :
                    cout<<"\n-------- DELETE USER ------------- "<<endl;
                    deleteusers("users.txt","users_backup.txt");
                
                    break;

                    default :
                    cout<<" Invalid Input "<<endl;
                    break;
                };
                keepRunning = askMenuOrExit();
                break;

            case 'o':
                keepRunning = false;
                cout << " Exiting..." << endl;
                break;

            default:
                cout << "  Invalid Input. Restarting..." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                keepRunning = true;
        }

    } while (keepRunning);

    SaveToFile("students.txt", "students_backup.txt"); // Save before exit
    cout << " Goodbye! All data saved safely." << endl;
    return 0;
};


