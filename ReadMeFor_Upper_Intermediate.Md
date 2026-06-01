📘 Student Management System – Upper Intermediate State
This program represents the Upper Intermediate Level of the Student Management System project.

It builds upon the Beginner and Intermediate versions by introducing file persistence, editing capabilities, and richer features.

While still not a full database system, it now saves and reloads student data across program runs, making it far more practical.


Required files :
students.txt , users.txt ,results.txt , students_backup.txt & users_backup.txt
have to be in your computer ( download mine ) if you want to run this program.



✅ What This Program Contains :

All baseline features from the Intermediate version

Focusing on File Handling by :
 Save student data to a file and reload it after restarting
 Log in System using File
 Attendance records using File 
 Update/Delete/Edit Students' Data is now persistence due to File Data Base
 Append Mode for effectiveness
 Backup File System
 Exporting results into a text file 
 File Error Handling 




🚫 What This Program Does Not Contain
Advanced algorithms (e.g., complex search or ranking)

Powerful database integration (still file‑based only)

Strong admin authentication system

Robust input validation and error handling


🧭 Step‑by‑Step Mind Map (Notes)


"Student Management System - Upper Intermediate" : {
    Primary Log in System <New>
    "Option A" : "Search Student by Name or ID",
    "Option B" : "Calculate Average Marks (auto)",
    "Option C" : "Find Highest and Lowest Marks",
    "Option D" : "Grade System (A/B/C/F)",
    "Option E" : "Edit Student Data (Delete/Update/Add) ", // Persistance <Upgraded>
    "Option G" : "Manage Attendance " <New>
    "Option F" : "Student Information (Sort by ID, Name, Marks, Attendance Record & Display Total Students)", //Persistance <Upgraded>

    "Option Out" : "Exit the Program"
}


🔍 Feature Breakdown


Option A – Search Student
Search by Name or ID
Displays student details including marks and averages
Reusable search functions improve maintainability

Option B – Average Marks
Automatically recalculated whenever the student list changes
Results are always dynamic and up to date

Option C – Highest / Lowest Marks
Identifies and displays the student with the highest and lowest averages
extended to multi‑subject context

Option D – Grade System
Assigns grades (A/B/C/F) based on averages
Displays pass/fail status
extended to multi‑subject context

Option E – Edit Student Data
Delete student by ID
Update student’s name or marks
Add new student (with duplicate ID prevention)
File auto‑update after every change

Option F – Student Information
Display all students with details
Sort students by ID, Name, or Marks using std::sort
Display total number of students
extended to multi‑subject context

<Persistence>
SaveToFile: Writes all student data into students.txt (CSV format)
LoadFromFile: Reads student data back into memory at program start
Ensures data survives across program runs


Option Out – Exit
Cleanly exits the program

📝 Notes
This intermediate version focuses on persistence and usability.
It introduces file handling, editing, sorting, and dynamic averages, while laying the groundwork for future advanced features.

Future versions will include:

OOP Level Integration

More advanced algorithms

Stronger input validation and error handling

Admin authentication system

Database integration
