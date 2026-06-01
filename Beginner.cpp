#include<iostream>
#include<vector>
#include<string>
using namespace std;


//MIND MAP 

/*

Declare a struct and Predefined 5 Student with their marks.
[
    "Student Management System" : {
        "Option A" : "Input Student Name and Display",
        "Option B" : "Calculate Average Mark of 5 Students",
        "Option C" : "Find Highest and Lowest Mark among Students"
    }
]

Option A : Build a simple function to input a student's name and display it back to the user.
Option B : Create a function that allows the user to input marks for 5 students, calculates the average, and displays it.
Option C : Implement a function that takes a list of students with their marks and identifies the student with the highest and lowest marks,
 then displays their names and marks.

[PASS/FAIL SYSTEM] :
Use Predefined 5 Student.
- If the average mark is 50 or above, display "Pass".
- If the average mark is below 50, display "Fail".

Note : I modifed Option B to use predefined students instead of user 
input for marks, to keep it simple and
avoid potential input errors in the beginner state.
And I added a new Option D for the Grade System 
(Pass/Fail) based on the average mark of the predefined students.
I modifed Option A to search for a student by name and display their mark, 
instead of just displaying the name input by the user, to make it more meaningful and interactive.

[Search Student by Id] :

I updated the predefined students database to include an ID field, 
and I can implement a search function that allows the user to input a student ID and retrieves the corresponding student's name and mark.
This will enhance the functionality of Option A and provide a more practical use case for managing student information.
And because of the database , this will prevent potential issues with duplicate names or ID and make the search more accurate and efficient.

[Delete Student Function] :

Now I will implement a delete function that allows the user to input a student ID and removes the corresponding student from the predefined list.
I updated the predefined students database to Global scope without a predefined function so that it can be accessed and modified by the delete function.
It is better due to its flexibility and simplicity in this beginner state, allowing for easy management of the student list without the need for complex data structures or additional classes.

Finally, I will add a new Option E for editing student data,
which includes the delete function as a starting point, and I can expand it in the future to include more editing features
like updating marks or names.


*/





//===================================//


//Beginner State 


class studentlist{
public:

    int id;
    string full_name;
    double mark;
};


//Predefined Global Student List
    vector<studentlist> class_list = {
        {334, "Alice", 88},
        {225, "Bob", 99},
        {316, "Charles", 22},
        {307, "Diana", 33},
        {788, "Edward", 88}
    };




//Option A : search student 


//by name and display their mark
void handleStudentName() {

    string searchName;

    cout<<" Enter Student Name to search : " <<endl;
    cin.ignore(1000,'\n');
    getline(cin, searchName);

    bool found = false;
    for(auto &s : class_list) {
         /* iterate through the predefined students to
          find the one matching the input name */

        if(s.full_name == searchName) {
            cout<<" Student Found : "<<s.full_name<<endl;
            cout<<" Mark : "<<s.mark<<endl;
            found = true;
            break;
        };
    };

    if(!found) {
         cout<<" Student Not Found. "<<endl;
    };


};

//display ID list 
int displayIDlist() {

    cout<<" Student ID List : "<<endl;
    for(auto &s : class_list) {
        cout<<" ID : "<<s.id<<endl;
    }
    return 0;
};


//by ID and display their mark
void handleStudentID() {
    int searchID;

    cout<<" Enter Student ID to search : " <<endl;
    cin>> searchID;

    bool found = false;
    for(auto &s : class_list) {
         /* iterate through the predefined students to
          find the one matching the input ID */

        if(s.id == searchID) {
            cout<<" Student Found : "<<s.full_name<<endl;
            cout<<" Mark : "<<s.mark<<endl;
            found = true;
            break;
        }
        if(!found) {
            cout<<" Student Not Found. "<<endl;
        }
    };

};



//Average Mark of 5 student : Option B

void handleAverageMarks() {

    double total_marks = 0;

    cout<<" Average Mark Calculation for 5 Students "<<endl;

    for(int i=0; i < class_list.size(); i++) {
      cout<<i+1<<". "<<class_list[i].full_name
      <<" (Current Mark: "<<class_list[i].mark<<")"<<endl;
        total_marks += class_list[i].mark;
    }; //Calculate total marks

    //Display


    cout<<"\n==================="<<endl;
    cout<<"  5 Student Entered  "<<endl;
    cout<<"======================="<<endl;

    double Average = total_marks / class_list.size();
    cout<<"-------------------------"<<endl;
    cout<< " Average Mark  " << Average <<endl;
};



//Option C : Find Highest and Lowest Mark among Students


void High_Low_Students() {

    int highestIndex=0;
    int lowestIndex=0;

    for(int i=1; i<class_list.size(); i++) {
        if(class_list[i].mark > class_list[highestIndex].mark) {
            highestIndex= i;
        }
        if(class_list[i].mark < class_list[lowestIndex].mark) {
            lowestIndex= i;
        }
    }

    char choice;
    cout<<"\nDo you wanna see (H)ighest or (L)owest? ";
    cin>> choice;

    if(choice == 'H' || choice == 'h' ) {
        cout<<" \nHighest Mark Student : " <<endl;
        cout<<" Name : "<<class_list[highestIndex].full_name<<endl;
          cout << "Mark: " << class_list[highestIndex].mark << endl;
    } else if(choice == 'L' || choice == 'l') {
        cout << "\nLowest Mark Student: " << endl;
        cout << "Name: " << class_list[lowestIndex].full_name << endl;
        cout << "Mark: " << class_list[lowestIndex].mark << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
};


//Option D : Grade System (Pass/Fail)

string GetGrade(double mark) {
    if(mark >= 80 ){
        return "A" ;
    }else if(mark >= 70 ){
        return "B" ;
    }else if(mark >= 60 ){
        return "C" ;
    }else{
        return "F" ;
    };
};


void handleGrades() {

    cout<<"\n==================="<<endl;
    cout<<"  Student Grades  "<<endl;
    cout<<"======================="<<endl;

   for(int i=0; i<class_list.size(); i++) {
        cout<<i + 1<<". "<<class_list[i].full_name
        <<"'s Grade :: " << GetGrade(class_list[i].mark)<<endl;

        if(GetGrade(class_list[i].mark) == "F") {
            cout<<" Note : "<<class_list[i].full_name<<" has failed. "<<endl;
        }else if(GetGrade(class_list[i].mark) == "A" || GetGrade(class_list[i].mark) == "B" || GetGrade(class_list[i].mark) == "C") {
            cout<<" Note : "<<class_list[i].full_name<<" has passed. "<<endl;
        };
   }
};


//Option E : Edit Student Datas

//delete 
void deleteStudentByID() {
    int deleteID;
    cout<<" Enter Student ID to delete : " ;
    cin>> deleteID;

    bool found = false;
    for(auto it = class_list.begin(); it != class_list.end(); ++it) {
        if(it->id == deleteID) {
            cout<<" Studend Found : "<<it->full_name<<endl;
            cout<<" Student Mark : "<<it->mark<<endl;
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

        }else if(!found) {
            cout<<" Student Not Found. "<<endl;
        };
    };
};

int main() {

    studentlist student_info;
    char answer;
    char yn;
    bool keepRunning = true ; //Control flag for the loop
      
    cout<<"\n==============================================="<<endl;
    cout<<"| Welcome to Student Management Center For Admins |"<<endl;
    cout<<"==============================================="<<endl;

    cout<<" This is a simple program to manage student information. "<<endl;
    cout<<" Warning : This program is for Admins only. "<<endl;
    cout<< " Warning : This Program is in Beginner State. "<<endl;
    cout<< " [ which means it may have some bugs and limited features. ] " <<endl;
    cout<<" Note : Please Use Valid Inputs to Avoid Unexpected Behavior. "<<endl;

    cout<<" Enjoy !"<<endl;

    do{
        cout<< "=============Student Management Menu=============" <<endl;
        cout<< " \n=============================================== " <<endl;
        cout<<"write 'a' to Search For a Student." <<endl;
        cout<<" Write 'b' to see or edit average of 5 students "<<endl;
        cout<<"Write 'c' to look highest and lowest mark among students "<<endl;
        cout<<"Write 'd' to see Grades (Pass/Fail) "<<endl;
        cout<<"Write 'e' to Edit Student Datas "<<endl;
        cout<<"Write 'f' to Exit "<<endl;

        cout<<" Choice : ";
        cin>>answer;


        if(answer == 'a' ) {
          
            cout<<"\n==================="<<endl;
            cout<<"  Search Student  "<<endl;
            cout<<"======================="<<endl;

            cout<<"Do you wanna search by Name or ID ? ( a or b) ?"<<endl;
            cout<<" (a) Name "<<endl;
            cout<<" (b) ID "<<endl;
            cout<<" Choice : ";
            char searchChoice;
            cin>> searchChoice;

            if(searchChoice == 'a'){
                handleStudentName();
            }else if(searchChoice == 'b') {
                displayIDlist();
                handleStudentID();  
            }else{
                cout<<" Invalid Choice. "<<endl;
                cout<<" Returning to Main Menu... "<<endl;
            };

            cout<<endl;
            cout<<" Go back to menu y/n ? " <<endl;
            cin>>yn;

            if(yn == 'y' || yn == 'Y'){
                keepRunning = true;
            }else if(yn == 'n' || yn == 'N'){
                keepRunning = false;
                cout<<"Exiting..."<<endl;
            }else{
                cout<<"Invalid InPut."<<endl;
                cout<<"Exiting..."<<endl;
            };

            cout<<endl;
            cout<<endl;
        
        }else if(answer == 'b') {
            handleAverageMarks();
            
            cout<<endl;
            cout<<" Go back to menu y/n ? " <<endl;
            cin>>yn;

            if(yn == 'y' || yn == 'Y'){
                keepRunning = true;
            }else if(yn == 'n' || yn == 'N'){
                keepRunning = false;
                cout<<"Exiting..."<<endl;
            }else{
                cout<<"Invalid InPut."<<endl;
                cout<<"Exiting..."<<endl;
            };

            cout<<endl;
            cout<<endl;
        
        }else if(answer == 'c' ){
            High_Low_Students();

            cout<<endl;
            cout<<" Go back to menu y/n ? " <<endl;
            cin>>yn;

            if(yn == 'y' || yn == 'Y'){
                keepRunning = true;
            }else if(yn == 'n' || yn == 'N'){
                keepRunning = false;
                cout<<"Exiting..."<<endl;
            }else{
                cout<<"Invalid InPut."<<endl;
                cout<<"Exiting..."<<endl;
            };

            cout<<endl;
            cout<<endl;
            
        }else if(answer == 'd' ) {
            handleGrades();

            cout<<endl;
            cout<<" Go back to menu y/n ? " <<endl;
            cin>>yn;

            if(yn == 'y' || yn == 'Y'){
                keepRunning = true;
            }else if(yn == 'n' || yn == 'N'){
                keepRunning = false;
                cout<<"Exiting..."<<endl;
            }else{
                cout<<"Invalid InPut."<<endl;
                cout<<"Exiting..."<<endl;
            };

            cout<<endl;
            cout<<endl;
        }else if(answer == 'e') {
            cout<<"\n==================="<<endl;
            cout<<"  Edit Student Datas "<<endl;
            cout<<"======================="<<endl;

            cout<<" What Do you wanna do ? "<<endl;
            cout<<" (a) Delete a Student by ID. "<<endl;
            cout<<" (more features coming soon...) "<<endl;
            cout<<" Choice : ";
            char editChoice;
            cin>> editChoice;

            if(editChoice == 'a') {
                displayIDlist();
                deleteStudentByID();
                cout<<endl;
                cout<<" Go back to menu y/n ? " <<endl;
                cin>>yn;

                if(yn == 'y' || yn == 'Y'){
                    keepRunning = true;
                }else if(yn == 'n' || yn == 'N'){
                    keepRunning = false;
                    cout<<"Exiting..."<<endl;
                }else{
                    cout<<"Invalid InPut."<<endl;
                    cout<<"Exiting..."<<endl;
                };

                cout<<endl;
                cout<<endl;

            }else{
                cout<<" Invalid Choice. "<<endl;
                cout<<endl;
                cout<<" Go back to menu y/n ? " <<endl;
                cin>>yn;

                if(yn == 'y' || yn == 'Y'){
                    keepRunning = true;
                }else if(yn == 'n' || yn == 'N'){
                    keepRunning = false;
                    cout<<"Exiting..."<<endl;
                }else{
                    cout<<"Invalid InPut."<<endl;
                    cout<<"Exiting..."<<endl;
                };

                cout<<endl;
                cout<<endl;
            };

        }else if(answer == 'f' || answer == 'F') {
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


   

