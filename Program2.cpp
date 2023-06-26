#include <iostream>
#include <fstream>
#include <string.h>
#define SIZE 55
using namespace std;
char buffer[SIZE + 1];

class Student
{
    char usn[15];
    char name[20];
    char sem[5];
    char marks[10];

public:
    void getData();
    void putData();
    void pack();
    void unpack();
    void insert();
    void display();
    void modify(char *key);
    void search(char *key);
};

void Student::getData()
{
    cout << "Enter usn, name, sem, marks: \n";
    cin >> usn >> name >> sem >> marks;
}

void Student::putData()
{
    cout << usn << "\t" << name << "\t\t" << sem << "\t" << marks << endl;
}

void Student::pack()
{
    strcpy(buffer, usn);
    strcat(buffer, "|");
    strcat(buffer, name);
    strcat(buffer, "|");
    strcat(buffer, sem);
    strcat(buffer, "|");
    strcat(buffer, marks);
    while (strlen(buffer) < SIZE - 1)
    {
        strcat(buffer, "#");
    }                     // here len of buffer is SIZE - 1
    strcat(buffer, "\n"); // now len of buffer becomes = SIZE
}

void Student::unpack()
{
    char *p;
    p = strtok(buffer, "|");
    strcpy(usn, p);
    p = strtok(NULL, "|");
    strcpy(name, p);
    p = strtok(NULL, "|");
    strcpy(sem, p);
    p = strtok(NULL, "#");
    strcpy(marks, p);
}

void Student::insert()
{
    getData();
    pack(); // packs the data into buffer
    ofstream fout("record2.txt", ios::app);
    fout << buffer;
    fout.close();
}

void Student::display()
{
    ifstream fin("record2.txt");
    while (!fin.eof())
    {
        fin.getline(buffer, SIZE + 1, '\n');
        if (fin.fail())
            break;
        unpack();
        putData();
    }
    fin.close();
}

void Student::search(char *key)
{
    ifstream fin("record2.txt");
    int count = 0;
    while (!fin.eof())
    {
        fin.getline(buffer, SIZE + 1, '\n');
        if (fin.fail())
            break;
        unpack();
        if (strcmp(usn, key) == 0)
        {
            putData();
            count++;
        }
    }
    cout << "Total record2s found: " << count << endl;
    fin.close();
}

void Student::modify(char *key)
{
    ifstream fin("record2.txt");
    ofstream fout("temp.txt");
    int count = 0;
    while (!fin.eof())
    {
        fin.getline(buffer, SIZE + 1, '\n');
        if (fin.fail())
            break;
        unpack();
        if (strcmp(usn, key) == 0)
        {
            getData();
            count++;
        }
        pack();
        fout << buffer;
    }
    if (count == 0)
        cout << "USN not found." << endl;
    else
        cout << "Modified. " << endl;

    fin.close();
    fout.close();
    remove("record2.txt");
    rename("temp.txt", "record2.txt");
}

int main()
{
    int choice;
    Student s;
    char key[15];

    while (1)
    {
        cout << "1.Insert\n"
             << "2.Display\n"
             << "3.Search\n"
             << "4.Modify\n"
             << "5.Exit\n"
             << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            s.insert();
            cout << "Done!" << endl;
            break;
        case 2:
            cout << "The contents are: " << endl;
            s.display();
            cout << "Done!" << endl;
            break;
        case 3:
            cout << "Enter the key USN: ";
            cin >> key;
            s.search(key);
            cout << "Done!" << endl;
            break;
        case 4:
            cout << "Enter the USN to modify: ";
            cin >> key;
            s.modify(key);
            cout << "Done!" << endl;
            break;
        default:
            return 0;
        }
    }
}