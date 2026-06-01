
Student Management System – Beginner State
This program is at the Beginner State, exactly as the name suggests.
It doesn’t yet have powerful algorithms or strong input handling, so it can be broken easily.
Think of it as a baseline architecture — a foundation for future versions that will be more advanced and robust.

What This Program Contains

Menu‑Driven System
Student search (by name or ID) and display
Calculation of the average mark of 5 predefined students
Highest / Lowest mark display
Pass / Fail grading system (Grades: A, B, C, F)
Display of the student list
Prevention of duplicates by using a predefined dataset
Delete student function
Use of vector for dynamic data storage


🚫 What This Program Does Not Contain

Powerful algorithms
Powerful database
Strong admin authentication system
…and many other advanced features (yet!)

🧭 Step‑by‑Step Mind Map (Notes)


Initial Setup
Declare a struct and predefine 5 students with their marks.


"Student Management System" : {
    "Option A" : "Input Student Name and Display",
    "Option B" : "Calculate Average Mark of 5 Students",
    "Option C" : "Find Highest and Lowest Mark among Students"
}


Option A – Search Student
Originally: input a student’s name and display it back.

Modified: search for a student by name and display their mark.
added search by ID to make it more practical and accurate.

IDs prevent duplicate issues and make searches more reliable.

Option B – Average Marks

Originally: input marks for 5 students, calculate average, display result.

Modified: use predefined students instead of user input (to avoid beginner input errors).
Average mark is calculated and displayed automatically.

Option C – Highest / Lowest Marks

Function identifies the student with the highest and lowest marks.
Displays their names and marks.

Option D – Pass / Fail System

Based on predefined students.
If average ≥ 50 → Pass.
If average < 50 → Fail.
Expanded into a grading system (A, B, C, F).

Option E – Edit Student Data

Added a delete function: input a student ID, remove that student.
Student list moved to global scope for easier modification.

📝 Notes
This beginner version focuses on simplicity and flexibility.
It avoids complex data structures or authentication systems, but sets the stage for future improvements.
Upcoming versions will include:

More editing features (update marks/names).

Multi‑subject system.

File handling for persistent storage.



