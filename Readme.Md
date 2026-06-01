🎓 Student Management System
I have finally developed a C++ console application for managing student records, grades, attendance, and user authentication.
 Built with Object-Oriented Programming principles including Inheritance, Polymorphism, Encapsulation, and Friend Functions.

📋 Table of Contents
Features
Mind Map
System Architecture
Code Structure
Class Hierarchy
File Formats
User Roles & Permissions
Compilation & Execution
Menu Navigation
Data Flow

✨ Features

Feature	Description
GPA System	4.0 scale GPA calculation per student across 3 subjects
Grade System	Letter grades (A, B, C, F) based on overall average
Ranking System	Top 5 students ranked by total marks
Sorting Options	Sort by ID, Name, Marks, or GPA
Exam Result Processor	Process, display, and export exam results to file
Multi-User Login	Role-based authentication (Admin, Teacher, Student)
Attendance Manager	Mark and track daily attendance per student
Scholarship Checker	Eligibility check based on GPA ≥ 3.5
User Management	Add, display, and delete users (Admin only)
Report Card Generator	Formatted console report cards per student
File Persistence	Auto-save/load with main file + backup redundancy
Data Export	Export individual or bulk student results to results.txt

🧠 Mind Map
table
┌─────────────────────────────────────────────────────────────────────────┐
│                    STUDENT MANAGEMENT SYSTEM                            │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌──────────────┐      ┌──────────────┐      ┌──────────────┐       │
│  │   LOGIN      │─────▶│  ROLE CHECK  │─────▶│  MAIN MENU   │       │
│  │  (users.txt) │      │              │      │              │       │
│  └──────────────┘      └──────────────┘      └──────┬───────┘       │
│                                                     │                 │
│           ┌─────────────────────────────────────────┘                 │
│           │                                                           │
│     ┌─────┴─────┬──────────┬──────────┬──────────┬──────────┐      │
│     │           │          │          │          │          │      │
│     ▼           ▼          ▼          ▼          ▼          ▼      │
│ ┌───────┐  ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐ │
│ │Search │  │Average │ │High/   │ │Grade   │ │Edit    │ │Student │ │
│ │Student│  │Marks   │ │Low     │ │System  │ │Data    │ │Info &  │ │
│ │       │  │        │ │Marks   │ │        │ │        │ │Sorting │ │
│ └───┬───┘  └───┬────┘ └───┬────┘ └───┬────┘ └───┬────┘ └───┬────┘ │
│     │          │          │          │          │          │        │
│     ▼          ▼          ▼          ▼          ▼          ▼        │
│ ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐│
│ │By Name │ │Math    │ │Highest │ │Letter  │ │Delete  │ │Sort by ││
│ │By ID   │ │CS      │ │Lowest  │ │Grades  │ │Update  │ │ID/Name ││
│ │Total   │ │English │ │        │ │Pass/Fail│ │Add New │ │Mark/GPA││
│ │List    │ │Overall │ │        │ │GPA View│ │        │ │Display ││
│ └────────┘ └────────┘ └────────┘ └────────┘ └────────┘ └────────┘│
│                                                                         │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐            │
│  │Attendance│  │Exam      │  │Scholarship│  │User      │            │
│  │Manager   │  │Processor │  │Checker   │  │Management│            │
│  └────┬─────┘  └────┬─────┘  └────┬─────┘  └────┬─────┘            │
│       │             │             │             │                      │
│       ▼             ▼             ▼             ▼                      │
│  ┌────────┐   ┌────────┐  ┌────────┐  ┌────────┐                  │
│  │Mark    │   │Process │  │Check   │  │Display │                  │
│  │Display │   │Export  │  │Eligible│  │Register│                  │
│  │        │   │        │  │        │  │Delete  │                  │
│  └────────┘   └────────┘  └────────┘  └────────┘                  │
│                                                                         │
│  ┌─────────────────────────────────────────────────────────────┐     │
│  │              REPORT CARD GENERATOR (Per Student)            │     │
│  └─────────────────────────────────────────────────────────────┘     │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘


🏗️ System Architecture
table
┌─────────────────────────────────────────────────────────────────┐
│                         PRESENTATION LAYER                        │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────────┐  │
│  │ Console I/O │  │ Menu System │  │ Formatted Output (iomanip)│  │
│  └─────────────┘  └─────────────┘  └─────────────────────────┘  │
├─────────────────────────────────────────────────────────────────┤
│                         BUSINESS LOGIC LAYER                    │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────────┐  │
│  │  Student    │  │   Person    │  │   GPA/Grade Calculator  │  │
│  │  (derived)  │  │  (base)     │  │   Ranking/Sorting       │  │
│  └─────────────┘  └─────────────┘  └─────────────────────────┘  │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────────┐  │
│  │  Attendance │  │  Scholarship│  │   Exam Result Processor │  │
│  │  Manager    │  │  Checker    │  │                         │  │
│  └─────────────┘  └─────────────┘  └─────────────────────────┘  │
├─────────────────────────────────────────────────────────────────┤
│                         AUTHENTICATION LAYER                    │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────────┐  │
│  │   Login     │  │ Role-Based  │  │   User Management       │  │
│  │   System    │  │   Access    │  │   (CRUD operations)     │  │
│  └─────────────┘  └─────────────┘  └─────────────────────────┘  │
├─────────────────────────────────────────────────────────────────┤
│                         DATA LAYER                              │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────────┐  │
│  │ students.txt│  │  users.txt  │  │      results.txt        │  │
│  │(main data)  │  │(auth data)  │  │    (export target)      │  │
│  └─────────────┘  └─────────────┘  └─────────────────────────┘  │
│  ┌─────────────┐  ┌─────────────┐                                │
│  │students_    │  │  users_     │                                │
│  │backup.txt   │  │ backup.txt  │   ← Redundancy / Failover      │
│  └─────────────┘  └─────────────┘                                │
└─────────────────────────────────────────────────────────────────┘

📁 Code Structure

table
Advanced.cpp
│
├── PREPROCESSOR & HEADERS
│   ├── iostream, fstream, string, vector, algorithm
│   ├── sstream, iomanip
│   └── using namespace std;
│
├── GLOBAL DECLARATIONS
│   ├── string GetGrade(double mark);     // Function prototype
│   ├── vector<student> class_list;       // Global student database
│   └── User currentuser;                 // Global session holder
│
├── CLASS HIERARCHY
│   ├── class Person (BASE)
│   │   ├── protected: full_name, age
│   │   ├── Constructor, Getters/Setters
│   │   ├── virtual displayInfo()
│   │   └── virtual ~Person()
│   │
│   └── class student : public Person (DERIVED)
│       ├── private: id, cs_mark, math_mark, english_mark,
│       │            attendance_record, gpa
│       ├── Constructor with GPA auto-calculation
│       ├── marktoPoint() → GPA helper
│       ├── calculateGPA() → 4.0 scale logic
│       ├── upgradeGPA() / setGPA() / getGPA()
│       ├── displayInfo() OVERRIDE (polymorphism)
│       ├── Getters & Setters (with GPA auto-update on marks)
│       ├── overallAverage() helper
│       └── friend void exportsdata(...)
│
├── AUTHENTICATION MODULE
│   ├── struct User { username, password, role }
│   ├── bool login(filename, backupName)
│   ├── void registeruser(filename, backup_name)
│   ├── bool hasrole(required)
│   ├── bool hasAnyrole(vector<roles>)
│   ├── void displayusers(filename, backupname)
│   └── void deleteusers(filename, backupname)
│
├── FILE I/O MODULE
│   ├── void SaveToFile(filename, backupName)
│   ├── void LoadFromFile(filename, backupName)
│   └── void exportsdata(student, ofstream) [friend function]
│
├── SEARCH MODULE
│   ├── void searchStudentByID(int id)
│   ├── void searchStudentByName(string name)
│   ├── void handleStudentName()
│   ├── void handleStudentID()
│   └── int displayIDlist()
│
├── STATISTICS MODULE
│   ├── void handleAverageMarks()
│   ├── void High_Low_Students()
│   └── void displayTotalStudents()
│
├── GRADING MODULE
│   ├── string GetGrade(double mark)
│   └── void handleGrades()
│
├── EDITING MODULE
│   ├── void deleteStudentByID()
│   ├── void updateStudentName()
│   ├── void updateStudentMark()
│   └── void addNewStudent()
│
├── SORTING & DISPLAY MODULE
│   ├── void displayStudentInfo()
│   ├── void SortByID()
│   ├── void SortByName()
│   ├── void SortByMark()
│   └── void SortbyGpa()
│
├── ATTENDANCE MODULE
│   ├── void markAttendance()
│   └── void displayAttendance()
│
├── EXPORT MODULE
│   └── void ExportResults(filename)
│
├── RANKING MODULE
│   ├── void RankStudents()
│   └── void ProcessExamResults()
│
├── SCHOLARSHIP MODULE
│   └── void scholarchecker()
│
├── REPORT CARD MODULE
│   └── void ReportCard()
│
├── UTILITY MODULE
│   └── bool askMenuOrExit()
│
└── MAIN DRIVER
    ├── login() → LoadFromFile()
    ├── Welcome Banner
    ├── do-while Menu Loop
    │   ├── switch(answer) → 10 main cases (a-j, o)
    │   ├── Role validation per case
    │   ├── Nested switches for sub-menus
    │   └── askMenuOrExit() per operation
    └── SaveToFile() on exit
    
🧬 Class Hierarchy

                    ┌─────────────┐
                    │   Person    │
                    │  (Abstract) │
                    ├─────────────┤
                    │ - full_name │
                    │ - age       │
                    ├─────────────┤
                    │ + getName() │
                    │ + getAge()  │
                    │ + setName() │
                    │ + setAge()  │
                    │ + display() │◄── virtual
                    │ + ~Person() │◄── virtual
                    └──────┬──────┘
                           │ public inheritance
                           ▼
                    ┌─────────────┐
                    │   student   │
                    ├─────────────┤
                    │ - id        │
                    │ - cs_mark   │
                    │ - math_mark │
                    │ - eng_mark  │
                    │ - attendance│
                    │ - gpa       │
                    ├─────────────┤
                    │ + getID()   │
                    │ + getGPA()  │
                    │ + setMarks()│◄── triggers upgradeGPA()
                    │ + display() │◄── override
                    │ + overall() │
                    │ + marktoPt()│
                    │ + calcGPA() │
                    └─────────────┘
                           │
                           │ friend
                           ▼
                    ┌─────────────┐
                    │ exportsdata │
                    └─────────────┘

📂 File Formats
students.txt / students_backup.txt

<ID>,<Name>,<Age>,<CS>,<Math>,<English>,<Attendance>,<GPA>
Example:
plain
101,Alice Smith,18,85.5,92.0,78.5,7,3.67
102,Bob Jones,19,65.0,70.5,55.0,7,2.33
users.txt / users_backup.txt
plain
<Username>,<Password>,<Role>
Example:
plain
admin,admin123,admin
teacher1,pass456,teacher
student1,pass789,student
results.txt (Generated Export)
plain
			  Student Result Exported :
ID: 101
 | Name: Alice Smith
 | Age : 18
  | Overall Average Mark: 85.33
  | Grade : A
  | Attendance : 7
  | Math : 92.0
  | Computer Science : 85.5
  | English : 78.5
  | GPA : 3.67
 ---------------------------------------------
👤 User Roles & Permissions
Table
Feature	Admin	Teacher	Student
Search Student	✅	✅	❌
View Averages	✅	✅	✅
High/Low Marks	✅	✅	✅
Grade System	✅	✅	✅
Edit Student Data	✅	✅*	❌
Sort/Display Info	✅	✅	❌
Attendance	✅	✅	❌
Exam Results	✅	✅	❌
Scholarship Check	✅	✅	❌
User Management	✅	✅	❌
Report Card	✅	✅	❌
*Teachers can update marks and add students, but some admin-only restrictions apply to deletion.
🖥️ Compilation & Execution
Compile
bash
g++ -o student_system Advanced.cpp -std=c++11
Run
bash
./student_system
Prerequisites
C++11 compatible compiler (g++, clang++)
Terminal/Console with monospace font for best formatting
Create users.txt before first run:
plain
admin,admin123,admin
🎮 Menu Navigation
plain
[a] Search For a Student
    ├── (a) Search by Name
    ├── (b) Search by ID
    └── (c) Show Total Student List

[b] See Average Marks of All Students

[c] Highest and Lowest Marks
    └── (H)ighest / (L)owest

[d] Grade System
    ├── (a) Normal Grade System (A, B, C, F)
    ├── (b) GPA System
    └── (c) Ranking System (Top 5)

[e] Edit Student Data
    ├── (a) Delete a Student by ID  [Admin Only]
    ├── (b) Edit a Student's Information
    │       ├── (1) Update Student Name
    │       └── (2) Update Student Mark
    └── (c) Add New Student

[f] Student Information & Sorting
    ├── (a) Sort by ID
    ├── (b) Sort by Name
    ├── (c) Sort by Mark
    ├── (d) Display without Sorting
    ├── (e) Export to File
    ├── (f) Sort by GPA
    ├── (g) Sort by Ranks
    └── (h) Report Card Generator

[g] Manage Attendance
    ├── (a) Mark Attendance
    └── (b) See Attendance Records

[h] Process Exam Results
    └── Auto-export prompt to results.txt

[i] Scholarship Eligibility Checker

[j] User Management System
    ├── (a) Check User List
    ├── (b) Register New User  [Admin Only]
    └── (c) Delete User        [Admin Only]

[o] Exit Program

🔄 Data Flow

table
┌──────────┐     ┌──────────┐     ┌──────────┐
│  Start   │────▶│  Login   │────▶│ Load Data│
└──────────┘     └──────────┘     └────┬─────┘
                                       │
                    ┌──────────────────┘
                    ▼
            ┌──────────────┐
            │  Main Menu   │◄────────────────┐
            └──────┬───────┘                 │
                   │                         │
         ┌────────┴────────┐                │
         ▼                 ▼                │
   ┌──────────┐     ┌──────────┐            │
   │ Operation│     │  Display │            │
   │ (CRUD)   │     │  Output  │            │
   └────┬─────┘     └──────────┘            │
        │                                   │
        ▼                                   │
   ┌──────────┐                             │
   │ Save to  │─────────────────────────────┘
   │   File   │
   └────┬─────┘
        │
        ▼
   ┌──────────┐
   │   Exit   │
   └──────────┘

🛡️ OOP Principles Demonstrated

Principle	Implementation
Inheritance	class student : public Person
Polymorphism	virtual void displayInfo() overridden in student
Encapsulation	Private members with public getters/setters
Abstraction	Person as base class; user interacts via menus
Friend Function	exportsdata() accesses private student data for file export

📝 Notes
Backup Redundancy: Every write operation saves to both main and backup files.
GPA Auto-Calculation: Updating any subject mark automatically recalculates GPA.
Stream Safety: File streams are explicitly closed after operations.
Input Sanitization: cin.ignore() and cin.clear() used to handle invalid menu inputs.
Global State: currentuser and class_list are global for simplicity in a single-file academic project.
Built for academic purposes. Pure C++ with no external dependencies.
