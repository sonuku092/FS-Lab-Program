#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class primary_index
{
public:
    string usn_list[100];
    int address_list[100];
    int count;
    void create_primary_index();
    void insert();
    void remove(string);
    void search(string);
    int search_primary_index(string);
    string extract_usn(string);
    void sort_primary_index();
};

void primary_index::create_primary_index()
{
    fstream file;
    int pos;
    string buffer, usn;
    count = -1;
    file.open("hi1.txt", ios::in);
    while (!file.eof())
    {
        pos = file.tellg();
        buffer.erase();
        getline(file, buffer);
        if (buffer.empty())
            break;
        usn = extract_usn(buffer);
        usn_list[++count] = usn;
        address_list[count] = pos;
    }
    file.close();
    sort_primary_index();
}

void primary_index::insert()
{
    string usn, name, branch, sem, buffer;
    int semester, address, pos;
    fstream file;
    cout << "\nUSN:";
    cin >> usn;
    cout << "\nNAME:";
    cin >> name;
    cout << "\n BRANCH:";
    cin >> branch;
    cout << "\nSEMESTER:";
    cin >> semester;
    stringstream out;
    out << semester;
    sem = out.str();
    buffer.erase();
    buffer = usn + '|' + name + '|' + branch + '|' + sem + '$' + '\n';
    file.open("hi1.txt", ios::out | ios::app);
    pos = file.tellp();
    file << buffer;
    file.close();
    usn_list[++count] = usn;
    address_list[count] = pos;
    sort_primary_index();
}

string primary_index::extract_usn(string buffer)
{
    string usn;
    int i = 0;
    usn.erase();
    while (buffer[i] != '|')
        usn += buffer[i++];
    return usn;
}

int primary_index::search_primary_index(string key)
{
    int low = 0, high = count, mid = 0, flag = 0, pos;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (usn_list[mid] == key)
        {
            flag = 1;
            break;
        }
        if (usn_list[mid] > key)
            high = mid - 1;
        if (usn_list[mid] < key)
            low = mid + 1;
    }
    if (flag)
        return mid;
    else
        return -1;
}

void primary_index::search(string key)
{
    int pos = 0, address;
    string buffer;
    fstream file;
    buffer.erase();
    pos = search_primary_index(key);
    if (pos >= 0)
    {
        file.open("hi1.txt");
        address = address_list[pos];
        file.seekp(address, ios::beg);
        getline(file, buffer);
        cout << "\nFound the record\n"
             << buffer;
        file.close();
    }
    else
        cout << "\nNot found.";
}

void primary_index::remove(string key)
{
    int pos = 0;
    int address, i;
    char del_ch = '*';
    fstream file;
    pos = search_primary_index(key);
    if (pos >= 0)
    {
        file.open("hi1.txt");
        address = address_list[pos];
        file.seekp(address, ios::beg);

        file.put(del_ch);
        cout << "\nRecord deleted.";
        file.close();
        for (i = pos; i < count; i++)
        {
            usn_list[i] = usn_list[i + 1];
            address_list[i] = address_list[i + 1];
        }
        count--;
    }
    else
        cout << "Not found.\n";
}

void primary_index::sort_primary_index()
{
    int i, j, temp_address;
    string temp_usn;
    for (i = 0; i <= count; i++)
    {
        for (j = i + 1; j <= count; j++)
        {
            if (usn_list[i] > usn_list[j])
            {
                temp_usn = usn_list[i];
                usn_list[i] = usn_list[j];
                usn_list[j] = temp_usn;
                temp_address = address_list[i];
                address_list[i] = address_list[j];
                address_list[j] = temp_address;
            }
        }
    }
}

int main()
{
    int choice;
    string key;
    primary_index i1;
    i1.create_primary_index();
    while (1)
    {
        cout << "\nMAin menu\n1.ADD\n2.SEARCH\n";
        cout << "3.Delete\n4.Exit\nEnter your choice\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Data\n";
            i1.insert();
            break;
        case 2:
            cout << "Enter the usn to be searched\n";
            cin >> key;
            i1.search(key);
            break;
        case 3:
            cout << "Enter the usn to delete\n";
            cin >> key;
            i1.remove(key);
            break;
        case 4:
            return 0;
        default:
            cout << "Wrong choice\n";
        }
    }
    return 0;
}