#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class student
{
public:
    string USN;
    string Name;
    string Branch;
    int Semester;
    string buffer;
    int count;

    int rrn_list[100];

    void read_data();
    void pack();
    void write_to_file();
    void unpack();
    void create_rrn();
    void search_by_rrn(int);
};
void student::read_data()
{
    cout << "\nUsn:";
    cin >> USN;
    cout << "\nName:";
    cin >> Name;
    cout << "\nBranch:";
    cin >> Branch;
    cout << "\nsemester:";
    cin >> Semester;
}

void student::pack()
{
    string sem;
    stringstream out;
    out << Semester;
    sem = out.str();
    buffer.erase();
    buffer = USN + '|' + Name + '|' + Branch + '|' + sem + '$' + '\n';
}

void student::write_to_file()
{
    int pos;
    fstream file;
    file.open("1.txt", ios::out | ios::app);
    pos = file.tellp();
    file << buffer;
    file.close();
    rrn_list[++count] = pos;
}

void student::unpack()
{
    string sem;
    int ch = 1, i = 0;
    USN.erase();
    while (buffer[i] != '|')
        USN += buffer[i++];

    Name.erase();
    i++;
    while (buffer[i] != '|')
        Name += buffer[i++];

    Branch.erase();
    i++;
    while (buffer[i] != '|')
        Branch += buffer[i++];

    sem.erase();
    i++;
    while (buffer[i] != '$')
        sem += buffer[i++];
    istringstream out(sem);
    out >> Semester;
}

void student::create_rrn()
{
    ifstream file;
    int pos;
    count = -1;
    file.open("1.txt", ios::in);
    while (!file.eof())
    {
        pos = file.tellg();
        buffer.erase();
        getline(file, buffer);
        rrn_list[++count] = pos;
    }
    file.close();
}

void student::search_by_rrn(int rrn)
{
    int pos = -1;
    fstream file;
    if (rrn > count)
        cout << "\n Not Found";
    else
    {
        buffer.erase();
        file.open("1.txt");
        pos = rrn_list[rrn];
        file.seekp(pos, ios::beg);
        getline(file, buffer);
        cout << "\n"
             << buffer << "\n";
    }
}

int main()
{
    int choice, rrn;
    student s1;

    s1.create_rrn();
    while (1)
    {
        cout << "\nMain Menu\n 1.Add \n\n 2.Search 3.EXIT\n\nEnter the choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Data\n";
            s1.read_data();
            s1.pack();
            s1.write_to_file();
            break;
        case 2:
            cout << "\n\nEnter the RRN";
            cin >> rrn;
            s1.search_by_rrn(rrn);
            break;
        case 3:
            return 0;
        default:
            cout << "\n\nWrong Choice";
            break;
        }
    }
    return 0;
}