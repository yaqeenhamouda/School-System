# Student Management System Using Binary Search Tree

## Overview

This project implements a **Student Management System** in C using a **Binary Search Tree (BST)** to manage student records efficiently. Each student record includes:

- **Student ID**
- **Class ID**
- **Name**
- **Address (City)**
- **Date of Enrollment**

The system provides functionality to insert, update, delete, search, print, and save student records.

## Features

- Insert new student record.
- Update existing student information.
- Print all student records sorted alphabetically by student name.
- Search for students based on city (address).
- Search for students based on class ID.
- Delete student record by ID.
- Save all student records to a text file (`students.txt`).
- Automatically load student records from the file on startup.

## Menu Options

Upon execution, the program will display the following menu:

1- Insert new student 2- Update information for student 3- Print All Students 4- Search City 5- Search Class 6- Delete Student 7- Save Students in file 8- Exit


## Data Format (students.txt)

The student data is saved and read from `students.txt` in the following format:

Id IdClass Name Address DateEnrollment


## Core Functions

- `Read()`: Load student records from file into a binary search tree.
- `Insert()`: Insert a student into the BST based on student ID.
- `Delete()`: Remove a student record from the BST by ID.
- `Find()`: Search for a student using student ID.
- `InsertByName()`: Insert a student into a secondary tree sorted by student name.
- `SortByName()`: Sort the original tree by names and generate a new tree.
- `Print()`: Display all student records sorted by name.
- `SearchCity()`: Find students from a specific city.
- `SearchClass()`: Find students enrolled in a specific class.
- `PrintFile()`: Save the tree to `students.txt` file.

## Compilation

To compile the code:

```bash
gcc your_code_filename.c -o student_system
 

