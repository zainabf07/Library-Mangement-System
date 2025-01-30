# Library-Mangement-System
# Abstract
The Library Management System (LMS) is a software solution for managing student accounts and library resources. It allows students to create accounts, view balances, deposit funds, issue books and return book while administrators can add, edit, and manage books and student records. The system tracks book availability and charges students a fee (2$) for each issued book. Data is stored in external text files for persistence. With a simple interface and secure login, the system enhances library management by improving efficiency and user experience.
# Introduction
The Library Management System (LMS) is a software application designed to automate and simplify the management of library resources and student interactions. 
## Students Function:
1. Create an account
2. View balance
3. Deposit amount
4. Add amount
5. Issue an item
6. Return item

Account management: The system supports up to 100 students, who pay $20 for account opening and $30 as a security deposit. Students can issue any book for $2 for a 7-day period. Fines are imposed for late returns as per the specified rules.

Data storage: The system uses 2D arrays to store the details of students and books. Initially, 15 books are stored in the library. Each student account contains the roll number, balance, and first name.
## Admin Functions:
1. Add a book to the system 
2. Edit the details of the books
3. Find student
4. Find Book
5. Remove Book
6. View the status of books
7. View enrolled students
8. View student balance
9. Fine Calculation

The system stores data in external files, ensuring persistence across sessions and promoting smooth operations.
The motivation behind developing this project is to address the challenges faced by traditional manual library systems, such as time-consuming record-keeping, inefficient tracking of book availability, and the complexity of managing student transactions. By automating these tasks, E-LMS reduces human error and improves overall operational efficiency.
In terms of its importance, the project plays a crucial role in modernizing library management processes. It enhances user experience by providing an accessible, user-friendly interface for students and administrators, making it easier to manage resources and interact with the library system. In industry practice, systems like E-LMS are vital for institutions to handle large volumes of users and materials efficiently. Additionally, it contributes to the advancement of knowledge by promoting digital solutions for educational and public libraries, aligning with the increasing demand for technology integration in everyday processes.
# Problem Statements
The current manual process of managing library operations such as book records, student accounts, book lending, and fine calculation is inefficient, prone to errors, and time-consuming. To address these issues, this project implements a digital Library Management System (E-LMS) that provides the following solutions:
1.  Efficient Book Management: The system maintains a digital record of books, allowing admins to add, edit, view, and remove books with ease. It tracks book availability in real time.
2. 	Student Account Management: Students can create accounts, view balances, deposit funds, and manage their library transactions conveniently.
3. 	Automated Book Issuance and Return: The system automates the book lending process, ensuring proper balance deductions, due-date tracking, and overdue fine calculations.
4.  Streamlined Administration: Admins can oversee book records, manage students, and ensure smooth library operations with minimal manual effort.
This project eliminates the challenges of a manual system, ensuring accuracy, convenience, and better resource management in library operations.
# Objectives
1.	Automate library operations, including book addition, removal, issuance, and return.
2.	Enable students to manage accounts, view balances, deposit funds, and track issued items.
3.	Implement overdue fine calculation and automatic balance updates.
4.	Provide secure admin controls for managing students, books, and library operations.
5.	Ensure data persistence using file storage and prevent duplicate entries.
6.	Offer sorting and reporting features for efficient record management and decision-making.
7.	Create a user-friendly interface for seamless interaction.
# Results
To achieve the objectives, the following steps will be implemented:
1.  Student Management: Enable account creation, balance updates, and display using unique roll numbers.
2.  Book Management: Add, edit, view, and remove books identified by ISBN, with real-time availability tracking.
3. 	Issuance and Returns: Allow book issuance with balance checks, track due dates, and calculate fines for overdue returns.
4. 	Data Persistence: Use file storage to save and load student and book data, ensuring reliability across sessions.
5. 	Sorting and Reports: Provide sorted student records and reports on book availability and fines.
6. 	Admin Security: Implement password-protected admin access for sensitive operations.
7.  User Interface: Design a user-friendly, menu-driven interface with clear prompts and error handling.
These methods ensure streamlined library operations, accurate data management, and enhanced user experience.
