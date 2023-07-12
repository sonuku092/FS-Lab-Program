#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class secondary_index
{
public:
    string Name_list[100];
    int Address_list[100];
    int count;
    void create_index();
    void insert();
    void remove(string);
    void delete_from_file(int);
    void search(string);
    int search_index(string);
    void read_from_file(int);
    string extract_Name(string);
    void sort_index();
};
void secondary_index::create_index()
{
    fstream file;
    int pos;
    string buffer, name;
    count = -1;
    file.open("record6.txt", ios::in);
    while (!file.eof())
    {
        pos = file.tellg();
        buffer.erase();
        getline(file, buffer);
        if (buffer.empty())
            break;
        if (buffer[0] == '*')
            continue;
        name = extract_Name(buffer);
        Name_list[++count] = name;
        Address_list[count] = pos;
    }
    file.close();
    sort_index();
    buffer.erase();
}

void secondary_index::insert()
{
    string USN, Name, Branch, sem, buffer;
    int semester, pos;
    fstream file;
    cout << "\n USN:";
    cin >> USN;
    cout << "\n Name:";
    cin >> Name;
    cout << "\nBranch:";
    cin >> Branch;
    cout << "\nSEMESTER:";
    cin >> semester;
    stringstream out;
    out << semester;
    sem = out.str();
    buffer = USN + '|' + Name + '|' + Branch + '|' + sem + '$' + '\n';
    file.open("record6.txt", ios::out | ios::app);
    pos = file.tellp();
    file << buffer;
    file.close();
    Name_list[++count] = Name;
    Address_list[count] = pos;
    sort_index();
}

void secondary_index::remove(string key)
{
    int pos = 0, t;
    string buffer;
    buffer.erase();
    pos = search_index(key);
    if (pos >= 0)
    {
        read_from_file(pos);
        delete_from_file(pos);
        t = pos;
        while (Name_list[++t] == key)
        {
            read_from_file(t);
            delete_from_file(t);
        }
        t = pos;
        while (Name_list[--t] == key)
        {
            read_from_file(t);
            delete_from_file(t);
        }
    }
    else
        cout << "\n\nNot found\n";
}

void secondary_index::delete_from_file(int pos)
{
    char del_ch = '*';
    int i, address;
    if (pos >= 0)
    {
        fstream file;
        file.open("1.txt");
        address = Address_list[pos];
        file.seekp(address, ios::beg);
        file.put(del_ch);
        cout << endl
             << "\n\nRecord deleted:";
        file.close();
    }
    for (int i = pos; i < count; i++)
    {
        Name_list[i] = Name_list[i + 1];
        Address_list[i] = Address_list[i + 1];
    }
    count--;
}

void secondary_index::search(string key)
{
    int pos = 0, t;
    string buffer;
    buffer.erase();
    pos = search_index(key);
    if (pos >= 0)
    {
        read_from_file(pos);
        t = pos;
        while (Name_list[++t] == key)
            read_from_file(t);
        t = pos;
        while (Name_list[--t] == key)
            read_from_file(t);
    }
    else
        cout << "\n"<< "Not found";
}

int secondary_index::search_index(string key)
{
    int low = 0, high = count, mid = 0, flag = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (Name_list[mid] == key)
        {
            flag = 1;
            break;
        }
        if (Name_list[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
        if (flag)
            return mid;
        else
            return -1;
    }
    return flag;
}

void secondary_index::read_from_file(int pos)
{
    int address;
    string buffer;
    fstream file;
    file.open("1.txt");
    address = Address_list[pos];
    file.seekp(address, ios::beg);
    getline(file, buffer);
    cout << endl
         << "Found the record:" << buffer;
    file.close();
}

string secondary_index::extract_Name(string buffer)
{
    string USN, Name;
    int i = 0;
    USN.erase();
    while (buffer[i] != '|')
        USN += buffer[i++];
    Name.erase();
    i++;
    while (buffer[i] != '|')
        Name += buffer[i++];
    return Name;
}

void secondary_index::sort_index()
{
    int i, j, temp_Address;
    string temp_Name;
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j <= count; j++)
        {
            if (Name_list[i] > Name_list[j])
            {
                temp_Name = Name_list[i];
                Name_list[i] = Name_list[j];
                Name_list[j] = temp_Name;
                temp_Address = Address_list[i];
                Address_list[i] = Address_list[j];
                Address_list[j] = temp_Address;
            } // End of if
        }     // End of Inner for
    }         // End of outer for
} // End of function

int main()
{
    int ch;
    string key;
    secondary_index i1;
    i1.create_index();
    while (1)
    {
        cout << "\nMain Menu\n1:Add\n2:Search\n3:Delete\n4:Exit\nEnter the choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Data \n";
            i1.insert();
            break;
        case 2:
            cout << "Enter the name\n";
            cin >> key;
            i1.search(key);
            break;
        case 3:
            cout << "Enter the Name";
            cin >> key;
            i1.remove(key);
            break;
        case 4:
            return 0;
        default:
            cout << "Wrong Choice!!!!!!!\n\n";
        }
    }
}
