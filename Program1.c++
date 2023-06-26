#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
class names
{
public:
    char name[255];
};
void revr(ofstream &out, char name[255])
{
    char *rev;
    rev = name + strlen(name) - 1;
    while (rev >= name)
    {
        out << *rev;
        rev--;
    }
}

void revs(char name[255])
{
    char *rev;
    rev = name + strlen(name) - 1;
    while (rev >= name)
    {
        cout << *rev;
        rev--;
    }
}
int main()
{

    names n[10];
    ofstream outf;
    ifstream in;
    int choice;
    while (1)
    {
        cout << "Enter: 1. For standard I/P, O/P \n 2. To read from file \n 3. Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int m;
            cout << "enter no. of names\n";
            cin >> m;
            for (int i = 0; i < m; i++)
            {
                cout << "\nenter the names\n";
                cin >> n[i].name;
                revs(n[i].name);
                cout << "\n";
            }
            cout << "\n";
            break;
        }
        case 2:
        {
            ofstream o;
            ifstream in;
            char sfile[10], dfile[10];
            char ch[10];
            cout << "Enter the input file :";
            cin >> sfile;
            cout << "Enter the outut file :";
            cin >> dfile;
            o.open(sfile, ios::out);
            int m;
            cout << "enter no. of names\n";
            cin >> m;
            for (int i = 0; i < m; i++)
            {
                cout << "\nenter the names\n";
                cin >> n[i].name;
                o << n[i].name << endl;
            }
            o.close();
            in.open(sfile, ios::in);
            ofstream outf(dfile, ios::out);
            while (in)
            {
                in.getline(ch, 255);
                if (in)
                    revr(outf, ch);
                outf << "\n";
            }
            cout << "\n";
            in.close();
            break;
        }
        case 3:
            exit(0);
        } // End of Switch
    }     // End of While
} // End of Main