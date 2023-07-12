#include <iostream>
#include <fstream>
#include <string.h>
// #include<conio.h>
using namespace std;

int main()
{

    int i, n;
    char name[20], name2[20];
    ofstream fout;
    ifstream fin1, fin2;
    // clrscr();

    fout.open("record7a.txt");
    cout << "Enter the no of names to enter in record1: ";
    cin >> n;
    cout << "Enter " << n << " names in ascending order: \n";
    for (i = 0; i < n; i++)
    {
        cin >> name;
        fout << name << endl;
    }
    fout.close();
    fout.open("record7b.txt");
    cout << "Enter the no of names to enter in record2: ";
    cin >> n;
    cout << "Enter " << n << " names in ascending order: \n";
    for (i = 0; i < n; i++)
    {
        cin >> name;
        fout << name << endl;
    }

    fout.close();
    fin1.open("record7a.txt");
    fin2.open("record7b.txt");
    fout.open("output.txt");
    fin1 >> name;
    fin2 >> name2;
    while (!fin1.eof() && !fin2.eof())
    {
        if (strcmp(name, name2) == 0)
        {
            fout << name << endl;
            cout << name << endl;
            fin1 >> name;
            fin2 >> name2;
        }
        else if (strcmp(name, name2) < 0)
        {
            fin1 >> name;
        }
        else
        {

            fin2 >> name2;
        }
    }

    fin1.close();
    fin2.close();
    fout.close();
    cout << "Done!";
    // getch();
    return 0;
}