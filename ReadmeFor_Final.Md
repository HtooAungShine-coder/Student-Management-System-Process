🎓 Student Management System
I have finally developed a C++ console application for managing student records, grades, attendance, and user authentication.
 Built with Object-Oriented Programming principles including Inheritance, Polymorphism, Encapsulation, and Friend Functions.

---

## 📋 Table of Contents
* [Features](#-features)
* [System Design](#-system-design)
  * [Process Workflow](#process-workflow)
  * [System Architecture](#system-architecture)
* [Code Architecture](#-code-architecture)
  * [Class Hierarchy](#class-hierarchy)
  * [File Organization](#file-organization)
* [User Roles & Permissions](#-user-roles--permissions)
* [File Specifications](#-file-specifications)
* [Getting Started](#-getting-started)
  * [Prerequisites](#prerequisites)
  * [Compilation & Execution](#compilation--execution)
* [Menu Navigation Structure](#-menu-navigation-structure)

---

## ✨ Features

| Feature | Description |
| :--- | :--- |
| **📈 GPA & Grading** | Automated 4.0 scale GPA calculation across 3 core subjects alongside letter grade mapping (A, B, C, F). |
| **🏆 Ranking & Sorting** | Real-time Top 5 student ranking with dynamic sorting configurations (by ID, Name, Marks, or GPA). |
| **🔐 Multi-User Auth** | Secure, role-based authentication separating workflows for **Admins**, **Teachers**, and **Students**. |
| **📅 Attendance Engine** | Integrated tracker to mark, store, and display cumulative student attendance metrics. |
| **💰 Scholarship Evaluator** | Algorithmic eligibility checker flags students maintaining a $\text{GPA} \ge 3.5$. |
| **🖨️ Report Generator** | Formatted command-line report cards and automated bulk export of processing results to `results.txt`. |
| **🛡️ Fault Tolerance** | Dynamic text-file storage architecture featuring automated data persistence and real-time backup redundancy. |

---

## 🧠 System Design

### Process Workflow
```dayman
[Start] ──> [Login Screen] ──> [Load Data From File]
                                      │
                                      ▼
                             [Main Menu Interface] ◄───┐
                                      │                │
                        ┌─────────────┴─────────────┐  │
                        ▼                           ▼  │
               [Execute Operations]         [Render Outputs]
               (CRUD, Sort, Filter)         (Console/Export)
                        │                              │
                        └─────────────┬─────────────┘  │
                                      ▼                │
                             [Auto-Save & Backup] ─────┘
                                      │
                                      ▼
                                   [Exit]
System ArchitectureCode snippet┌───────────────────────────────────────────────────────────────────────────┐
│                            PRESENTATION LAYER                             │
│       [Console I/O Engine]   [Menu Subsystem]   [iomanip Formatters]       │
├───────────────────────────────────────────────────────────────────────────┤
│                            BUSINESS LOGIC LAYER                           │
│       [Person Base Class]     [Student Derived]     [GPA/Grade Matrix]    │
│       [Attendance Engine]     [Scholarship Unit]    [Exam Processor]      │
├───────────────────────────────────────────────────────────────────────────┤
│                           AUTHENTICATION LAYER                            │
│       [Login System]         [Role Validator]      [User CRUD Matrix]     │
├───────────────────────────────────────────────────────────────────────────┤
│                                DATA LAYER                                 │
│  Main Data:     [students.txt]                 [users.txt]                │
│  Redundancy:    [students_backup.txt]          [users_backup.txt]         │
│  Exports:       [results.txt]                                             │
└───────────────────────────────────────────────────────────────────────────┘
📁 Code ArchitectureClass HierarchyCode snippet               ┌─────────────────────────────────┐
               │         Person (Abstract)       │
               ├─────────────────────────────────┤
               │ # full_name: string             │
               │ # age: int                      │
               ├─────────────────────────────────┤
               │ + virtual displayInfo(): void =0│
               │ + virtual ~Person()             │
               └────────────────┬────────────────┘
                                │
                        Public Inheritance
                                │
                                ▼
               ┌─────────────────────────────────┐
               │             Student             │
               ├─────────────────────────────────┤
               │ - id: int                       │
               │ - cs_mark, math_mark, eng: double│
               │ - attendance_record: int        │
               │ - gpa: double                   │
               ├─────────────────────────────────┤
               │ + displayInfo() override        │
               │ + calculateGPA(): void          │
               │ + overallAverage(): double      │
               └────────────────┬────────────────┘
                                │
                         Grants Access To
                                │
                                ▼
               ┌─────────────────────────────────┐
               │    friend void exportsdata()    │
               └─────────────────────────────────┘
File OrganizationThe monolithic implementation is structured across highly-cohesive logical segments:Preprocessor Context & State: Core headers (<fstream>, <vector>, <algorithm>) alongside global session variables (currentUser, class_list).Authentication Subsystem: User structural schemas linked with algorithmic safety guards checking structural role hierarchies.File I/O Engine: Dual-stream synchronization routines outputting state snapshots to secondary hardware backups concurrently.Analytical Modules: Granular functional components processing search lookups, class statistical boundaries, report generation, and sorting pipelines.👤 User Roles & PermissionsFeatureAdminTeacherStudentSearch Profiles✅✅❌View Metrics & Averages✅✅✅Access Grade/GPA Tooling✅✅✅Modify Records / Add Students✅✅❌Purge Records (Delete)✅❌❌Attendance Tracking✅✅❌User Management Operations✅❌❌📂 File SpecificationsThe system relies on structured Comma-Separated Values (CSV) schemas stored in flat .txt formats:students.txt / students_backup.txtCode snippet<ID>,<Name>,<Age>,<CS_Mark>,<Math_Mark>,<English_Mark>,<Attendance>,<GPA>
101,Alice Smith,18,85.5,92.0,78.5,7,3.67
102,Bob Jones,19,65.0,70.5,55.0,7,2.33
users.txt / users_backup.txtCode snippet<Username>,<Password>,<Role>
admin,admin123,admin
teacher1,pass456,teacher
student1,pass789,student
🛠️ Getting StartedPrerequisitesA C++11 compliant compiler (g++ 4.8.1+ or clang 3.3+)Standard Command Line / Terminal InterfaceCompilation & ExecutionClone or download the source code file (Advanced.cpp).Generate an initial validation profile by creating a file named users.txt in the same directory, containing:Code snippetadmin,admin123,admin
Compile via your terminal terminal application:Bashg++ -o student_system Advanced.cpp -std=c++11
Initialize the environment binary:Bash./student_system
🎮 Menu Navigation StructurePlaintext[a] Search For a Student
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
    ├── (a) Delete a Student by ID [Admin Only]
    ├── (b) Edit a Student's Information
    │   ├── (1) Update Student Name
    │   └── (2) Update Student Mark
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
[h] Process Exam Results ──> (Auto-exports to results.txt)
[i] Scholarship Eligibility Checker
[j] User Management System
    ├── (a) Check User List
    ├── (b) Register New User [Admin Only]
    └── (c) Delete User       [Admin Only]
[o] Exit Program
🛡️ OOP Principles DemonstratedInheritance: Concrete implementation extending specialized attributes from an abstract base (student : public Person).Polymorphism: Utilizing runtime dynamic binding via virtual member overrides to display specialized class logs dynamically.Encapsulation: Absolute protection of internal structural data using restrictive access specifiers combined with validated accessors and mutators.Friend Functions: Utilizing explicit scope bypass rules (friend void exportsdata()) to bridge clean interactions between class components and I/O streams safely.
