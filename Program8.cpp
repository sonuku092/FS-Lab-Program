#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
// Record specification
class record
{
public:
    char name[20];
    char usn[20];
} rec[20];

int no;
fstream file[8];
// The first 8 files
char fname[8][8] = {"l.txt", "2.txt", "3.txt", "4.txt", "5.txt", "6.txt", "7.txt", "8.txt"};

void merge_file(char *file1, char *file2, char *filename)
{
    record recrd[20];
    int k;
    k = 0;
    fstream f1, f2;
    f1.open(file1, ios::in); // open the first file
    f2.open(file2, ios::in); // open the second file
    while (!f1.eof())        // Unpack and retrieve first file
    {
        f1.getline(recrd[k].name, 20, '|');
        f1.getline(recrd[k++].usn, 20, '\n');
    }
    while (!f2.eof()) // Unpack and retrieve second file
    {
        f2.getline(recrd[k].name, 20, '|');
        f2.getline(recrd[k++].usn, 20, '\n');
    }
    record temp;
    int t, y;
    for (t = 0; t < k - 2; t++) // Sort the retrieved records
        for (y = 0; y < k - t - 2; y++)
            if (strcmp(recrd[y].name, recrd[y + 1].name) > 0)
            {
                temp = recrd[y];
                recrd[y] = recrd[y + 1];
                recrd[y + 1] = temp;
            }
    fstream temp1;
    temp1.open(filename, ios::out); // Open the file to be packed into
    for (t = 1; t < k - 1; t++)     // Pack the sorted records onto the file
        temp1 << recrd[t].name << "|" << recrd[t].usn << "\n";
    f1.close();
    f2.close();
    temp1.close();
    return;
}

void kwaymerge()
{
    char filename[7][20] = {"ll.txt", "22.txt", "33.txt", "44.txt", "lll.txt", "222.txt", "llll.txt"};
    int i;
    int k;
    k = 0;
    for (i = 0; i < 8; i += 2) // Merge and sort the 8 original files onto
    {                          // the four files indicated {ll.txt,22.txt….}
        merge_file(fname[i], fname[i + 1], filename[k++]);
    }
    k = 4;
    for (i = 0; i < 4; i += 2) // Merge and sort the four files onto lll.txt and 222.txt
    {
        merge_file(filename[i], filename[i + 1], filename[k++]);
    }
    // Merge and sort the two files onto the llll.txt file
    merge_file(filename[4], filename[5], filename[6]);
    return;
}

int main()
{
    int i;
    cout << "Enter the no. of records : ";
    cin >> no;
    cout << "\nEnter the details : \n";
    for (i = 0; i < 8; i++) // Create 8 files to store the split data
        file[i].open(fname[i], ios::out);
    for (i = 0; i < no; i++) // Split and pack data onto the files
    {
        cout << "Name :";
        cin >> rec[i].name;
        cout << "USN : ";
        cin >> rec[i].usn;
        file[i % 8] << rec[i].name << '|' << rec[i].usn << "\n";
    }
    for (i = 0; i < 8; i++)
        file[i].close();
    kwaymerge(); // Merge
    fstream result;
    result.open("llll.txt", ios::in);
    cout << "\nSorted Records : \n";
    char name[20], usn[20];
    for (i = 0; i < no; i++) // Unpack the sorted records and dispL
    {
        result.getline(name, 20, '|');
        result.getline(usn, 20, '\n');
        cout << "\nName : " << name << "\nUSN : " << usn << "\n";
    }
    return 0;
}