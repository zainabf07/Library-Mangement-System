#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

// Constants
const int MAX_NAME_LENGTH = 50;
const char student_file[] = "students.txt";
const char book_file[] = "books.txt";
const int ISSUE_PERIOD = 7; 
const double FINE_PER_DAY = 1.0;


// Structures
struct Student {
    int roll;
    char name[MAX_NAME_LENGTH];
    double balance;
    int issued_book_index; // Index of the book issued by the student (-1 if no book issued)
    time_t issue_date;
};

struct Book {
    char title[MAX_NAME_LENGTH];
    char author[MAX_NAME_LENGTH];
    int isbn;
    bool available;
    time_t due_date;
};

// Function prototypes
void create_account();
void display(int roll);
void deposit_amount(int roll, double amount);
void issue_item(int roll);
void return_item(int roll, int isbn);
void display_sorted();
int find_student(int roll);
int find_book(int isbn);
void add_book();
void edit_book();
void view_books();
void save_students();
void remove_book();
void load_students();
void save_books();
void load_books();
void calculate_fine(int roll, int isbn);

// Global variables
Student students[100];
int student_count = 0;
Book books[100];
int book_count = 0;

int main() {
    load_students();
    load_books();
    
    cout<<" ************************************************************* ";
    cout << " Welcome to Library Management System " << endl;

    int main_option = -1; // Main menu option
    bool is_admin;
    string password;

    while (main_option != 0) {
        cout << "\nLogin as:\n1. Admin\n2. Student\n0. Exit\n";
        cout << "Enter your option: ";
        cin >> main_option;

        if (main_option == 0) {
            break;
        }

        is_admin = (main_option == 1);

        cout << "Enter password: ";
        cin >> password;

        if (password == "password") { // Simple password for demonstration
            if (is_admin) {
                int admin_option = -1; // Admin menu option
                while (admin_option != 0) {
                	cout<<" ************************************************************* ";
                    cout << "\nAdmin options:\n1. Add book\n2. Edit book\n3. View book status\n4. View enrolled students\n5. View student balance\n6. Remove book\n0. Logout\n";
                    cout << "Enter your option: ";
                    cin >> admin_option;

                    switch (admin_option) {
                        case 1: add_book(); break;
                        case 2: edit_book(); break;
                        case 3: view_books(); break;
                        case 4: display_sorted(); break;
                        case 5: {
                            int roll;
                            cout << "Enter student roll number: ";
                            cin >> roll;
                            display(roll);
                            break;
                        }
                        case 6: remove_book(); break;
                        case 0: cout << "Logging out as Admin.\n"; break;
                        default: cout << "Invalid option!\n"; break;
                    }
                }
            } else {
                int student_option = -1; // Student menu option
                int roll;

                cout << "Enter your roll number: ";
                cin >> roll;

                int index = find_student(roll);
                if (index == -1) {
                    cout << "Student not found. Create an account? (1. Yes / 2. No): ";
                    int create_account_option;
                    cin >> create_account_option;
                    if (create_account_option == 1) {
                        create_account();
                    }
                } else {
                    while (student_option != 0) {
                    	cout<<" ************************************************************* ";
                        cout << "\nStudent options:\n1. View balance\n2. Deposit amount\n3. Issue item\n4. Return item\n0. Logout\n";
                        cout << "Enter your option: ";
                        cin >> student_option;

                        switch (student_option) {
                            case 1: display(roll); break;
                            case 2: {
                                double amount;
                                cout << "Enter the amount to deposit: ";
                                cin >> amount;
                                deposit_amount(roll, amount);
                                break;
                            }
                            case 3: issue_item(roll); break;
                            case 4: {
                                int isbn;
                                cout << "Enter the ISBN of the book to return: ";
                                cin >> isbn;
                                return_item(roll, isbn);
                                break;
                            }
                            case 0: cout << "Logging out as Student.\n"; break;
                            default: cout << "Invalid option!\n"; break;
                        }
                    }
                }
            }
        } else {
            cout << "Incorrect password.\n";
        }
    }

    save_students();
    save_books();

    return 0;
}

void create_account() {
    if (student_count >= 100) {
        cout << "Student limit reached. Cannot create more accounts.\n";
        return;
    }

    int roll;
    cout << "Enter roll number : ";
    cin >> roll;

    if (find_student(roll) != -1) {
        cout << "Account already exists for this roll number.\n";
        return;
    }

    students[student_count].roll = roll;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(students[student_count].name, MAX_NAME_LENGTH);

    double initial_deposit;
    cout << "Enter initial deposit amount ($50 minimum): ";
    cin >> initial_deposit;

    if (initial_deposit < 50) {
        cout << "Initial deposit must be at least $50.\n";
        return;
    }

    students[student_count].balance = initial_deposit - 20 - 30; // Account opening and security deposit
    student_count++;
}

void display(int roll) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Roll No: " << students[index].roll << endl;
    cout << "Name: " << students[index].name << endl;
    cout << "Balance: $" << fixed << setprecision(2) << students[index].balance << endl;
}

void deposit_amount(int roll, double amount) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    students[index].balance += amount;
    cout << "New balance: $" << fixed << setprecision(2) << students[index].balance << endl;
}

void issue_item(int roll) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Available books:\n";
    for (int i = 0; i < book_count; i++) {
        if (books[i].available) {
            cout << i + 1 << ". " << books[i].title << " by " << books[i].author << " (ISBN: " << books[i].isbn << ")\n";
        }
    }

    int choice;
    cout << "Enter the number of the book you want to issue (0 to cancel): ";
    cin >> choice;

    if (choice == 0 || choice > book_count || !books[choice - 1].available) {
        cout << "Invalid choice or book unavailable.\n";
        return;
    }

    if (students[index].balance >= 2) {
        books[choice - 1].available = false;
        students[index].balance -= 2;
        time_t now = time(0);
        books[choice - 1].due_date = now + (ISSUE_PERIOD * 24 * 60 * 60); // Calculate due date
        students[index].issued_book_index = choice - 1;
        students[index].issue_date = now;
        cout << "Book issued successfully. New balance: $" << fixed << setprecision(2) << students[index].balance << endl;
        cout << "Due date: " << ctime(&books[choice - 1].due_date);
    } else {
        cout << "Cannot issue the book. Insufficient balance.\n";
    }
}

void display_sorted() {
    for (int i = 0; i < student_count; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].roll > students[j].roll) {
                swap(students[i], students[j]);
            }
        }
    }

    for (int i = 0; i < student_count; i++) {
        cout << students[i].roll << " - " << students[i].name << " - Balance: $" << fixed << setprecision(2) << students[i].balance << endl;
    }
}

int find_student(int roll) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll == roll) {
            return i;
        }
    }
    return -1;
}

int find_book(int isbn) {
    for (int i = 0; i < book_count; i++) {
        if (books[i].isbn == isbn) {
            return i;
        }
    }
    return -1;
}

void add_book() {
    if (book_count >= 100) {
        cout << "Book limit reached. Cannot add more books.\n";
        return;
    }
    cout << "Enter book title: ";
    cin.ignore();
    cin.getline(books[book_count].title, MAX_NAME_LENGTH);

    cout << "Enter book author: ";
    cin.getline(books[book_count].author, MAX_NAME_LENGTH);

    int isbn;
    cout << "Enter book ISBN: ";
    cin >> isbn;

    if (find_book(isbn) != -1) {
        cout << "A book with this ISBN already exists.\n";
        return;
    }

    books[book_count].isbn = isbn;
    books[book_count].available = true;
    book_count++;
}

void edit_book() {
    int isbn;
    cout << "Enter book ISBN to edit: ";
    cin >> isbn;
    int index = find_book(isbn);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    cout << "Current book title: " << books[index].title << endl;
    cout << "Enter new book title: ";
    cin.ignore();
    cin.getline(books[index].title, MAX_NAME_LENGTH);

    cout << "Current book author: " << books[index].author << endl;
    cout << "Enter new book author: ";
    cin.getline(books[index].author, MAX_NAME_LENGTH);

    cout << "Book details updated.\n";
}

void view_books() {
    for (int i = 0; i < book_count; i++) {
        cout << "Title: " << books[i].title << endl;
        cout << "Author: " << books[i].author << endl;
        cout << "ISBN: " << books[i].isbn << endl;
        cout << "Available: " << (books[i].available ? "Yes" : "No") << endl << endl;
    }
}

void save_students() {
    ofstream stud(student_file);
    if (!stud) {
        cout << "Error opening " << student_file << " for writing.\n";
        return;
    }
    stud << student_count << "\n";
    for (int i = 0; i < student_count; i++) {
        stud << students[i].roll << "\n"
             << students[i].name << "\n"
             << students[i].balance << "\n";
    }
    stud.close();
}


void load_students() {
    ifstream load(student_file);
    if (!load) {
        cout << "Error opening " << student_file << " for reading. Starting with no students.\n";
        return;
    }
    load >> student_count;
    load.ignore();
    for (int i = 0; i < student_count; i++) {
        load >> students[i].roll;
        load.ignore();
        load.getline(students[i].name, MAX_NAME_LENGTH);
        load >> students[i].balance;
        load.ignore();
    }
    load.close();
   
}


void save_books() {
    ofstream book(book_file);
    if (!book) {
        cout << "Error opening " << book_file << " for writing.\n";
        return;
    }
    book << book_count << "\n";
    for (int i = 0; i < book_count; i++) {
        book << books[i].title << "\n"
             << books[i].author << "\n"
             << books[i].isbn << "\n"
             << books[i].available << "\n";
    }
    book.close();

}

void remove_book() {
    int isbn;
    cout << "Enter the ISBN of the book to remove: ";
    cin >> isbn;

    int index = find_book(isbn);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }
    // Shift all books after the found book to the left
    for (int i = index; i < book_count - 1; i++) {
        books[i] = books[i + 1];
    }
    book_count--;

    cout << "Book removed successfully.\n";
}


void load_books() {
    ifstream load(book_file);
    if (!load) {
        cout << "Error opening " << book_file << " for reading. Starting with default books.\n";
        return;
    }
    load >> book_count;
    load.ignore();
    for (int i = 0; i < book_count; i++) {
        load.getline(books[i].title, MAX_NAME_LENGTH);
        load.getline(books[i].author, MAX_NAME_LENGTH);
        load >> books[i].isbn;
        load >> books[i].available;
        load.ignore();
    }
    load.close();
    
}

void calculate_fine(int roll, int isbn) {
    int student_index = find_student(roll);
    int book_index = find_book(isbn);

    if (student_index == -1 || book_index == -1) {
        cout << "Invalid student or book.\n";
        return;
    }

    time_t now = time(0);
    double fine = 0.0;

    if (now > books[book_index].due_date) {
        int overdue_days = ((now - books[book_index].due_date) / (24 * 60 * 60));
        fine = overdue_days * FINE_PER_DAY;
        students[student_index].balance -= fine;
        cout << "Book is overdue by " << overdue_days << " days. Fine imposed: $" << fixed << setprecision(2) << fine << ". New balance: $" << students[student_index].balance << endl;
    }
}


void return_item(int roll, int isbn) {
    int student_index = find_student(roll);
    int book_index = find_book(isbn);

    if (student_index == -1) {
        cout << "Student not found.\n";
        return;
    }

    if (book_index == -1) {
        cout << "Book not found.\n";
        return;
    }

    if (books[book_index].available) {
        cout << "Book is not currently issued.\n";
        return;
    }

    time_t now = time(0);
    if (now > books[book_index].due_date) {
        calculate_fine(roll, isbn);
    }

    books[book_index].available = true;
    books[book_index].due_date = 0;
    cout << "Book returned successfully.\n";
}
