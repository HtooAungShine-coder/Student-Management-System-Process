
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


//MIND MAP 

/*

Option A : Build functions to search students by name or ID and display their marks.
Option B : Automatically calculate average marks whenever the student list changes (add/update/delete).
Option C : Implement a function to identify and display the student with the highest and lowest marks.
Option D : Grade system based on marks (A/B/C/F).
Option E : Edit student data (delete existing student, update marks or names, add new student).
Option F : Student Information (e.g., sort by ID, Name, or Marks & Display Total Students).
Option G : Extend student struct to support multiple subjects (e.g., Math, English, Science) and calculate averages per subject.
Option Out : Exist the Program 

[Multi-Subject Mark System] :
- Each student stores marks for multiple subjects.
- Functions calculate per-subject averages and overall averages.
- Sorting and grade system can be extended to multi-subject context.

[Auto Average Calculation] :
- Average marks are recalculated automatically after any modification (add, update, delete).
- Prevents outdated results and keeps system dynamic.


Tracking ;

-Firstly, I will implement a function to ask wether user wants to go back to menu or exit after each operation.
So that user can decide to continue or exit after each operation , It was in previous version but it was reused in a wrong way and pontentially caused some bugs. 
I will fix it and use it properly in this version.

-Secondly, I updated the option in the Option E 
to edit student datas (name and mark) by ID, and also which is one of the most important features in a student management system.

-Later, I made a option to exist the program in the main menu, so that user can exit whenever they want
 without having to go through the menu again and again after each operation.

-Then, I added a new feature to add new student to the system, which is also one of the most important features in a student management system.
but however , for the lack of static database currently , the change may not be permanent and may be lost after the program is closed,
but it is still a good practice to implement this feature for future improvements and for the purpose of completeness of the system. 
And the average mark function is set to automatically calculate the average mark of "all" students in the system,
so that it can be dynamic and always up to date whenever there is a change in the student list.

-I made a search function reusable which can be used to search student by name and ID for better maintainability and 
to avoid code duplication, which is a good practice in programming.

-I added a new feature to display total number of students in the system, tied to Option A and Option F,
so that user can see the total number of students in the system whenever they want,
which is also a good practice in a student management system.

-I Upgraded Option F by addding Sorting Alogrithm (using Library for time-saving and maintainbility)

[[Multi - Subject System ]]

-I upgraded the studentlist class to have multiple subject's marks and also upgraded Vector Student List's Data.
-I upgraded and modified required Functions and Features affected by the Addition of Multi-Subject System.

-Finally, I fixed Menu Aesthetic a bit and added the " There is no Student Left " alarm system incase some user deleted all students in necessary functions and features.


*/

//===================================//


//Intermediate Level Student Management System


class studentlist{
public:

    int id;
    string full_name;
    double cs_mark;
    double math_mark;
    double english_mark;

    //Helper function to get the average 
    double overallAverage() const{
        return (math_mark + cs_mark + english_mark) /3.0 ;
    };


};


//Predefined Global Student List
    vector<studentlist> class_list = {
        {334, "Alice",  80, 40, 80},
        {225, "Bob", 20, 90, 80},
        {316, "Charles",  10, 2, 90},
        {307, "Diana", 78, 65, 90},
        {788, "Edward",  55, 76, 90}
    };




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
        return false ; // Exit the program
    }else{
        cout<<"Invalid InPut."<<endl;
        cout<<"Exiting..."<<endl;
        exit(0); // Exit the program immediately
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





int main() {

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
    cout<<"\t\t\t Warning : This Program is in Beginner-Intermediate State. "<<endl;
    cout<<"\t\t\t [ which means it may have some bugs and limited features. ] " <<endl;
    cout<<"\t\t\t Note : Please Use Valid Inputs to Avoid Unexpected Behavior. "<<endl;

    cout<<"\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"\t\t\t                      Enjoy !" <<endl;

        do{

            cout<<"\n=================================================="<<endl;
            cout<< "=========    Student Management Menu    ========" <<endl;
            cout<< "\n=============================================== " <<endl;
            cout<<"[a] Search For a Student." <<endl;
            cout<<"[b] see average of students "<<endl;
            cout<<"[c] look highest and lowest mark among students "<<endl;
            cout<<"[d] see Grades (Pass/Fail) "<<endl;
            cout<<"[e] Edit Student Datas "<<endl;
            cout<<"[f] see Student Information "<<endl;
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
                }else{
                cout<<" Invalid Input ." <<endl;
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

    return 0;
};




   
