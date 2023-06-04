#include<bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

COORD coord = {0, 0};
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void password()
{
    char n[20], ch;
    int i = 0, j;
    gotoxy(1, 10);
    cout << "Enter Your Password";
    gotoxy(30, 10);
    j = 30;
    while ((ch = getch()) != '\r')
    {
        gotoxy(j, 10);
        cout << "*";
        j++;
        n[i] = ch;
        i++;
    }
    n[i] = '\0';
    if (strcmp(n, "2023") == 0)
    {
        cout << "\n\n\n The Password Is Correct \n";
    }
    else
    {
        cout << "\n\n Invalid Password , Try Again !!";
        getch();
        exit(1);
    }
}

// Date Class
class Date
{
private:
    int dd, mm, yy;

public:
    Date()
    {
        dd = 1, mm = 1, yy = 2018;
    }
    void setDate()
    {
        cout << "Enter Date : ";
        cin >> dd;
        cout << "Enter month : ";
        cin >> mm;
        cout << "Enter Year : ";
        cin >> yy;
    }
    void showDate()
    {
        cout << dd << "/" << mm << "/" << yy;
    }
};

// Menu Section
class Menu
{
public:
    void mainMenu();
    void studentMenu();
    void bookMenu();
    void issueBook();
    void returnBook();
};

void Menu::mainMenu()
{
    gotoxy(30,1);
    cout << "========================================================" << endl;
    gotoxy(53,2);
    cout<<"Main Menu"<<endl;
    gotoxy(30,3);
    cout << "========================================================" << endl;
    gotoxy(32,4);
    cout << "1. Student Menu " << endl;
    gotoxy(32,5);
    cout << "2. Book Menu " << endl;
    gotoxy(32,6);
    cout << "3. Issue Book " << endl;
    gotoxy(32,7);
    cout << "4. Return Book " << endl;
    gotoxy(32,8);
    cout << "5. Exit " << endl;
}

void Menu::studentMenu()
{
    gotoxy(30,1);
    cout << "========================================================" << endl;
    gotoxy(53,2);
    cout<<"Student Menu "<<endl;
    gotoxy(30,3);
    cout << "========================================================" << endl;
    gotoxy(33,4);
    cout << "1. New Entry " << endl;
    gotoxy(33,5);
    cout << "2. Modify Entry " << endl;
    gotoxy(33,6);
    cout << "3. Search Entry " << endl;
    gotoxy(33,7);
    cout << "4. Delete Entry " << endl;
    gotoxy(33,8);
    cout << "5. View All Entry " << endl;
    gotoxy(33,9);
    cout << "6. Go Back To Previous Menu " << endl;
}

void Menu::bookMenu()
{
    gotoxy(30,1);
    cout << "========================================================" << endl;
    gotoxy(53,2);
    cout<<"Book Menu "<<endl;
    gotoxy(30,3);
    cout << "========================================================" << endl;
    gotoxy(33,4);
    cout << "1. New Entry " << endl;
    gotoxy(33,5);
    cout << "2. Modify Entry " << endl;
    gotoxy(33,6);
    cout << "3. Search Entry " << endl;
    gotoxy(33,7);
    cout << "4. Delete Entry " << endl;
    gotoxy(33,8);
    cout << "5. View All Entry " << endl;
    gotoxy(33,9);
    cout << "6. Go Back To Previous Menu " << endl;
}

// Data Section
class BookData
{
private:
public:
    char title[25], author[15], publisher[20];
    int status;
    float price;
    int issuedRollNo;
    Date issueDate;
    Date returnDate;
    BookData()
    {
        status = 0;
        issuedRollNo = -9999;
    }
};

class StudentData
{
public:
    int rollNo, status;
    char name[20], address[40], branch[15], bookTitle[20];
    StudentData()
    {
        status = 0;
    }
};

// Book Section
class Book
{
public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllBookDetails();
};

void Book::inputDetails()
{
    fstream file;
    file.open("bookDatabase.dat", ios::out | ios::binary | ios::app);
    if (!file)
    {
        cerr << "Unable to open file" << endl;
        return;
    }

    BookData book;
    cout << "Enter Book Title : ";
    fflush(stdin);
    gets(book.title);
    cout << "Enter Book Author : ";
    fflush(stdin);
    gets(book.author);
    cout << "Enter Book Publisher : ";
    fflush(stdin);
    gets(book.publisher);
    cout << "Enter Book Price : ";
    cin >> book.price;

    file.write((char *)&book, sizeof(BookData));
    file.close();
    gotoxy(60,16);
    cout<<"Book Added Successfully !!";
}

void Book::modifyDetails()
{
    fstream file;
    file.open("bookDatabase.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!file)
    {
        cerr << "Unable to open file" << endl;
        return;
    }
    file.seekg(0, ios::beg);

    BookData book;
    char title[25];
    cout << "Enter The Title Of Book You Want To Modify: ";
    fflush(stdin);
    gets(title);

    while (file.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
        {
            int position = (-1) * sizeof(BookData);
            file.seekp(position, ios::cur);

            cout << "Enter New Book Title: ";
            fflush(stdin);
            gets(book.title);

            cout << "Enter New Author's Name: ";
            fflush(stdin);
            gets(book.author);

            cout << "Enter New Book Publisher: ";
            fflush(stdin);
            gets(book.publisher);

            cout << "Enter New Book Price: ";
            cin >> book.price;

            file.write((char*)&book , sizeof(BookData));
            file.close();
            cout << "Record Updated";
            return;
        }
    }
    cout << "Book Not Found";
    return;
}

void Book::searchDetails()
{
    fstream file;
    file.open("bookDatabase.dat", ios::in | ios::binary);
    if (!file)
    {
        cout << "Unable To Open File!" << endl;
        return;
    }

    BookData book;
    char title[25];
    cout << "Enter The Title Of Book You Want To Search: ";
    fflush(stdin);
    gets(title);

    while (file.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
        {
            cout << "Book Title : " << book.title << endl;
            cout << "Book Author : " << book.author << endl;
            cout << "Book Publisher : " << book.publisher << endl;
            cout << "Book Price : " << book.price << endl;
            if (book.status == 1)
            {
                cout << "Issued Status : " << book.issuedRollNo << endl;
                cout << "Issued Date : ";
                book.issueDate.showDate();
                cout << endl;
                cout << "Return Date : ";
                book.returnDate.showDate();
                cout << endl;
            }
            else
            {
                cout << "Issued Status : None" << endl;
            }
            cin.get();
            return;
        }
    }
    cout << "Book Not Found " << endl;
    file.close();
    return;
}

void Book::deleteDetails()
{
    fstream file, temp;
    file.open("bookDatabase.dat", ios::in | ios::binary);
    temp.open("temp.dat", ios::binary | ios::out);
    if (!file)
    {
        cout << "Unable To Open File!" << endl;
        return;
    }

    char title[25];
    int flag = 0;
    cout << "Enter The Book Title To Remove : ";
    fflush(stdin);
    gets(title);

    BookData book;
    while (file.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title))
        {
            flag++;
            continue;
        }
        temp.write((char *)&book, sizeof(BookData));
    }
    file.close();
    temp.close();
    remove("bookDatabase.dat");
    rename("temp.dat", "bookDatabase.dat");

    if (flag == 1)
        cout << "Record Deleted";
    else
        cout << "Record Not Found";
    return;
}

void Book::viewAllBookDetails()
{
    fstream file;
    file.open("bookDatabase.dat", ios::in | ios::binary);
    if (!file)
    {
        cout << "Unable To Open File!" << endl;
        return;
    }

    BookData book;
    int choice = 1;
    while (file.read((char *)&book, sizeof(BookData)) && choice)
    {
        system("cls");
        cout << "Book Title : " << book.title << endl;
        cout << "Book Author : " << book.author << endl;
        cout << "Book Publisher : " << book.publisher << endl;
        cout << "Book Price : " << book.price << endl;
        if (book.status == 1)
        {
            cout << "Issued Status : " << book.issuedRollNo << endl;
            cout << "Issued Date : ";
            book.issueDate.showDate();
            cout << endl;
            cout << "Return Date : ";
            book.returnDate.showDate();
            cout << endl;
        }
        else
        {
            cout << "Issued Status : None" << endl;
        }
        cout << "Press 1 To View The Next Book Else Press 0 : ";
        cin >> choice;
    }
    file.close();
    return;
}

// Student Section
class Student
{
public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllStudentDetails();
};

void Student::inputDetails()
{
    fstream file;
    file.open("studentDatabase.dat", ios::out | ios::binary | ios::app);
    if (!file)
    {
        cerr << "Unable to open file" << endl;
        return;
    }

    StudentData student;
    cout << "Enter Student Roll No. : ";
    cin >> student.rollNo;
    cout << "Enter Student Name : ";
    fflush(stdin);
    gets(student.name);
    cout << "Enter Student Branch : ";
    fflush(stdin);
    gets(student.branch);
    cout << "Enter Student Address : ";
    fflush(stdin);
    gets(student.address);
    

    file.write((char *)&student, sizeof(StudentData));
    file.close();
    gotoxy(60,16);
    cout<<"Student Added Successfully !!";
}

void Student::modifyDetails()
{
    fstream file;
    file.open("studentDatabase.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!file)
    {
        cerr << "Unable to open file" << endl;
        return;
    }
    file.seekg(0, ios::beg);

    int roll;
    cout << "Enter The RollNo. Of Student You Want To Modify: ";
    cin >> roll;

    StudentData student;
    while (file.read((char *)&student, sizeof(StudentData)))
    {
        if (roll == student.rollNo)
        {
            int position = (-1) * sizeof(StudentData);
            file.seekp(position, ios::cur);

            cout << "Enter Student Roll No.: ";
            cin >> student.rollNo;
            cout << "Enter New Student Name: ";
            fflush(stdin);
            gets(student.name);
            cout << "Enter New Student Branch: ";
            fflush(stdin);
            gets(student.branch);
            cout << "Enter New Student Address: ";
            fflush(stdin);
            gets(student.address);

            file.write((char*)&student , sizeof(StudentData));
            file.close();
            cout << "Record Updated";
            return;
        }
    }
    cout << "Roll Number Not Found";
    return;
}

void Student::searchDetails()
{
    fstream file;
    file.open("studentDatabase.dat", ios::in | ios::binary);
    if (!file)
    {
        cout << "Unable To Open File!" << endl;
        return;
    }

    StudentData student;
    int roll;
    cout << "Enter The RollNo. Of Student You Want To Search: ";
    cin >> roll;

    while (file.read((char *)&student, sizeof(StudentData)))
    {
        if (roll == student.rollNo)
        {
            cout << "Record Found !!" << endl;
            cout << "Student RollNo. : " << student.rollNo << endl;
            cout << "Student Name : " << student.name << endl;
            cout << "Student Branch : " << student.branch << endl;
            cout << "Student Address : " << student.address << endl;
            if (student.status == 1)
            {
                cout << "Issued Book Name : " << student.bookTitle << endl;
            }
            else
            {
                cout << "No Book Issued For This Roll Number :" << endl;
            }
            cin.get();
            return;
        }
    }
    cout << "Student Not Found " << endl;
    file.close();
    return;
}

void Student::deleteDetails()
{
    fstream file, temp;
    file.open("studentDatabase.dat", ios::in | ios::binary);
    temp.open("temp.dat", ios::binary | ios::out);
    if (!file)
    {
        cout << "Unable To Open File!" << endl;
        return;
    }

    int roll;
    int flag = 0;
    cout << "Enter The Student Roll Number To Remove : ";
    cin >> roll;

    StudentData student;
    while (file.read((char *)&student, sizeof(StudentData)))
    {
        if (student.rollNo == roll)
        {
            flag++;
            continue;
        }
        temp.write((char *)&student, sizeof(StudentData));
    }
    file.close();
    temp.close();
    remove("studentDatabase.dat");
    rename("temp.dat", "studentDatabase.dat");

    if (flag == 1)
        cout << "Record Deleted";
    else
        cout << "Roll Number Not Found";
    return;
}

void Student::viewAllStudentDetails()
{
    fstream file;
    file.open("studentDatabase.dat", ios::in | ios::binary);
    if (!file)
    {
        cout << "Unable To Open File!" << endl;
        return;
    }

    StudentData student;
    int choice = 1;
    while (file.read((char *)&student, sizeof(StudentData)) && choice)
    {
        system("cls");
        cout << "Student RollNo. : " << student.rollNo << endl;
        cout << "Student Name : " << student.name << endl;
        cout << "Student Branch : " << student.branch << endl;
        cout << "Student Address : " << student.address << endl;
        if (student.status == 1)
        {
            cout << "Issued Book Name is : " << student.bookTitle << endl;
        }
        else
        {
            cout << "No Book Is Issued For This Roll Number : " << endl;
        }
        cout << "Press 1 To View The Next Student Else Press 0 : ";
        cin >> choice;
    }
    file.close();
    return;
}

// Book Issue/Return Section
void Menu::issueBook()
{
    fstream sp, bp;
    sp.open("studentDatabase.dat", ios::in | ios::out | ios::ate | ios::binary);
    bp.open("bookDatabase.dat", ios::in | ios::out | ios::ate | ios::binary);
    sp.seekg(0, ios::beg);
    bp.seekg(0, ios::beg);

    int roll, flagS = 0, flagB = 0, position;
    char title[30];
    StudentData student;
    BookData book;

    cout << "Enter Student's Roll No. To Issue Book : ";
    cin >> roll;

    while (sp.read((char *)&student, sizeof(StudentData)))
    {
        if (student.rollNo == roll)
        {
            position = (-1) * sizeof(StudentData);
            sp.seekp(position, ios::cur);
            flagS++;
            break;
        }
    }

    if (flagS != 1)
    {
        cout << "Record Not Found";
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }

    cout << "Enter Book Title You Want To Issue : ";
    fflush(stdin);
    gets(title);

    while (bp.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
        {
            position = (-1) * sizeof(BookData);
            bp.seekp(position, ios::cur);
            flagB++;
            break;
        }
    }
    if (flagB != 1)
    {
        cout << "Record Not Found";
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }

    if (student.status != 1 && book.status != 1)
    {
        strcpy(student.bookTitle, title);
        student.status = 1;
        book.status = 1;
        book.issuedRollNo = student.rollNo;
        gotoxy(6,3);
        cout<<"Issue Date "<<endl;
        book.issueDate.setDate();
        gotoxy(6,7);
        cout<<"Return Date "<<endl;
        book.returnDate.setDate();
        sp.write((char *)&student, sizeof(StudentData));
        bp.write((char *)&book, sizeof(BookData));
        sp.close();
        bp.close();
        gotoxy(60,10);
        cout<<"Book Issued Successfully !!"<<endl;
    }
    else
    {
        if (student.status == 1)
        {
            cout << "Student Account Is Already Full !" << endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
        else
        {
            cout << "Book Is Already Issued !" << endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
    }
}

void Menu::returnBook()
{
    fstream sp, bp;
    sp.open("studentDatabase.dat", ios::in | ios::out | ios::ate | ios::binary);
    bp.open("bookDatabase.dat", ios::in | ios::out | ios::ate | ios::binary);
    sp.seekg(0, ios::beg);
    bp.seekg(0, ios::beg);

    int roll, flagS = 0, flagB = 0, position;
    char title[30];
    StudentData student;
    BookData book;

    gotoxy(50,3);
    cout << "Enter Student's Roll No. To Return Book : ";
    gotoxy(50,4);
    cin >> roll;

    while (sp.read((char *)&student, sizeof(StudentData)))
    {
        if (student.rollNo == roll)
        {
            position = (-1) * sizeof(StudentData);
            sp.seekp(position, ios::cur);
            flagS++;
            break;
        }
    }

    if (flagS != 1)
    {
        cout << "Record Not Found";
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }

    while (bp.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, student.bookTitle) == 0)
        {
            position = (-1) * sizeof(BookData);
            bp.seekp(position, ios::cur);
            flagB++;
            break;
        }
    }

    if (flagB != 1)
    {
        cout << "Record Not Found";
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }

    if (student.status == 1 && book.status == 1)
    {
        student.status = 0;
        book.status = 0;
        book.issuedRollNo = -9999;
        sp.write((char *)&student, sizeof(StudentData));
        bp.write((char *)&book, sizeof(BookData));
        sp.close();
        bp.close();
        gotoxy(60,10);
        cout<<"Book Returned Successfully !!"<<endl;
    }
    else
    {
        if (student.status == 0)
        {
            cout << "Student Account Is Already Full !" << endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
        else
        {
            cout << "Book Is Already Issued !" << endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
    }
}

// Main Function
int main()
{
    system("Color 17");
    Menu menu;
    Student s1;
    Book b1;
    int choice = 0;
    // password();
    while (choice != 5)
    {
        system("cls");
        menu.mainMenu();
        gotoxy(15,10);
        cout << "Enter Your Choice : " << endl;
        gotoxy(15,11);
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            menu.studentMenu();
            gotoxy(15,10);
            cout << "Enter Your Choice :" << endl;
            gotoxy(15,11);
            cin >> choice;
            switch (choice)
            {
            case 1:
                s1.inputDetails();
                break;
            case 2:
                s1.modifyDetails();
                break;
            case 3:
                s1.searchDetails();
                break;
            case 4:
                s1.deleteDetails();
                break;
            case 5:
                s1.viewAllStudentDetails();
                choice=1;
                break;
            case 6:
                break;
            default:
                gotoxy(50,13);
                cout << "Wrong Choice Input !!!" << endl;
            }
            break;
        }

        case 2:
        {
            system("cls");
            menu.bookMenu();
            gotoxy(15,10);
            cout << "Enter Your Choice :" << endl;
            gotoxy(15,11);
            cin >> choice;
            switch (choice)
            {
            case 1:
                b1.inputDetails();
                break;
            case 2:
                b1.modifyDetails();
                break;
            case 3:
                b1.searchDetails();
                break;
            case 4:
                b1.deleteDetails();
                break;
            case 5:
                b1.viewAllBookDetails();
                choice=1;
                break;
            case 6:
                break;
            default:
                gotoxy(50,13);
                cout << "Wrong Choice Input !!!" << endl;
            }
            break;
        }

        case 3:
            system("cls");
            menu.issueBook();
            break;

        case 4:
            system("cls");
            menu.returnBook();
            break;

        case 5:
            system("cls");
            gotoxy(60,13);
            cout << "Thank You !!!";
            break;

        default:
            gotoxy(50,13);
            cout << "Please Enter Correct Input !!";
            break;
        } // switch
        getch();
    }     // while
    return 0;
}