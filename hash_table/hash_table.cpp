#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

#define DATABASE_FILE "hash_table_database.txt"

struct Student
{
    string name = "";
    string email = "";
    Student *next = NULL;
};

const int TABLE_SIZE = 20;
Student *hashTable[TABLE_SIZE] = {NULL};

void outputMainMenu()
{
    cout << "=========== Student Email Directory ===========" << endl
         << "[1] Tambah Mahasiswa" << endl
         << "[2] Cari Email" << endl
         << "[3] Hapus Mahasiswa" << endl
         << "[4] Lihat Semua" << endl
         << "[0] Keluar" << endl
         << endl;
}

char toUpperChar(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}

char toLowerChar(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

string toUpperCase(const string &input)
{
    string result = "";
    for (int i = 0; input[i] != '\0'; ++i)
    {
        result += toUpperChar(input[i]);
    }
    return result;
}

string toLowerCase(const string &input)
{
    string result = "";
    for (int i = 0; input[i] != '\0'; ++i)
    {
        result += toLowerChar(input[i]);
    }
    return result;
}

int inputOption()
{
    try
    {
        string input;
        cout << "> ";
        getline(cin, input);
        return stoi(input);
    }
    catch (...)
    {
        cout << "Mohon masukkan bilangan bulat!" << endl;
        return inputOption();
    }
}

string inputData(string label = "")
{
    try
    {
        string input;
        cout << label << "> ";
        getline(cin, input);

        if (input.empty())
        {
            throw "Data tidak boleh kosong!";
        }

        return input;
    }
    catch (...)
    {
        cout << "Mohon masukkan data yang benar!" << endl;
        return inputData(label);
    }
}

/* Begin Core Helper Functions */

bool isDataEmpty()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i] != NULL)
        {
            return false;
        }
    }
    return true;
}

Student *createStudent()
{
    Student *newStudent = new Student;
    newStudent->name = inputData("Masukkan Nama");
    newStudent->email = inputData("Masukkan Email");
    newStudent->next = NULL;

    return newStudent;
}

int getHashValue(string name)
{
    int hash = 0;
    int prime = 31;

    for (int i = 0; i < name.length(); i++)
    {
        hash = (hash * prime + int(name[i])) % TABLE_SIZE;
    }

    return hash;
}

void addStudentNode(int index, Student *newStudent)
{
    Student **headPtr = &hashTable[index];

    if (*headPtr == NULL)
    {
        *headPtr = newStudent;
        cout << "Data mahasiswa berhasil ditambahkan ke slot [" << index << "]" << endl;
    }
    else
    {
        cout << "Terjadi tabrakan hash di slot [" << index << "], menggunakan chaining." << endl;

        newStudent->next = *headPtr;
        *headPtr = newStudent;

        cout << "Data berhasil ditambahkan ke dalam linked list slot [" << index << "]." << endl;
    }
}

string searchEmailByName(int index, string name)
{
    Student **headPtr = &hashTable[index];
    bool found = false;
    string email = "";

    if (*headPtr != NULL)
    {
        Student *temp = *headPtr;

        while (temp->next != NULL && temp->name != name)
        {
            temp = temp->next;
        }

        found = temp->name == name;
        email = temp->email;
    }

    if (found)
    {
        cout << "Email ditemukan: " << email << endl;
    }
    else
    {
        cout << "Data tidak ditemukan." << endl;
    }

    return email;
}

void removeDataByName(int index, string name)
{
    Student **headPtr = &hashTable[index];
    Student *temp = *headPtr;

    if (*headPtr == NULL)
    {
        cout << "Data tidak ditemukan, tidak dapat dihapus." << endl;
    }
    else if ((*headPtr)->name == name)
    {
        Student *del = *headPtr;
        *headPtr = (*headPtr)->next;
        delete del;
        cout << "Data dengan nama " << name << " berhasil dihapus dari slot [" << index << "]." << endl;
    }
    else if (temp->next == NULL)
    {
        if (temp->name == name)
        {
            Student *del = *headPtr;
            *headPtr = NULL;
            delete del;
            cout << "Data dengan nama " << name << " berhasil dihapus dari slot [" << index << "]." << endl;
        }
        else
        {
            cout << "Data tidak ditemukan, tidak dapat dihapus." << endl;
        }
    }
    else
    {
        while (temp->next->next != NULL && temp->next->name != name)
        {
            temp = temp->next;
        }

        if (temp->next->name == name)
        {
            Student *del = temp->next;
            temp->next = del->next;
            delete del;
            cout << "Data dengan nama " << name << " berhasil dihapus dari slot [" << index << "]." << endl;
        }
        else
        {
            cout << "Data tidak ditemukan, tidak dapat dihapus." << endl;
        }
    }
}

void printLinkedList(int index)
{
    Student *temp = hashTable[index];

    cout << "[" << index << "] ";

    if (temp == NULL)
    {
        cout << "(kosong)" << endl;
    }
    else
    {
        while (temp != NULL)
        {
            cout << "\n      -> Nama : " << temp->name
                 << "\n         Email: " << temp->email << endl;
            temp = temp->next;
        }
    }
}

void clearLinkedList(int index)
{
    Student **headPtr = &hashTable[index];
    Student *current = *headPtr;

    while (current != NULL)
    {
        Student *temp = current;
        current = current->next;
        delete temp;
    }

    *headPtr = NULL;
}

/* End Core Helper Functions */

/* Begin Core Functions */

void addStudent()
{
    Student *newStudent = createStudent();
    int index = getHashValue(newStudent->name);
    addStudentNode(index, newStudent);
}

void searchEmail()
{
    if (isDataEmpty())
    {
        cout << "Data mahasiswa masih kosong" << endl;
        return;
    }

    string name = inputData("Masukkan Nama");
    int index = getHashValue(name);
    searchEmailByName(index, name);
}

void removeStudent()
{
    if (isDataEmpty())
    {
        cout << "Data mahasiswa masih kosong" << endl;
        return;
    }

    string name = inputData("Masukkan Nama");
    int index = getHashValue(name);
    removeDataByName(index, name);
}

void showAllData()
{
    if (isDataEmpty())
    {
        cout << "Data mahasiswa masih kosong.\n";
        return;
    }

    cout << "\n=========== Isi Hash Table ===========\n";

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printLinkedList(i);
    }
    cout << endl
         << endl;
}

void clearAllData()
{
    if (isDataEmpty())
        return;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        clearLinkedList(i);
    }
}

void insertStudent(string name, string email)
{
    int index = getHashValue(name);
    Student *newStudent = new Student;
    newStudent->name = name;
    newStudent->email = email;
    newStudent->next = hashTable[index];
    hashTable[index] = newStudent;
}

void loadDataFromFile()
{
    ifstream inFile(DATABASE_FILE);
    if (!inFile)
    {
        cout << "File tidak ditemukan. Tidak ada data yang dimuat.\n";
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string name, email;

        if (getline(ss, name, ',') && getline(ss, email))
        {
            insertStudent(name, email);
        }
    }

    inFile.close();
    cout << "Data berhasil dimuat dari file.\n";
}

void saveDataToFile()
{
    ofstream outFile(DATABASE_FILE);
    if (!outFile)
    {
        cout << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }

    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        Student *current = hashTable[i];
        while (current != NULL)
        {
            outFile << current->name << "," << current->email << "\n";
            current = current->next;
        }
    }

    outFile.close();
    cout << "Data berhasil disimpan ke file.\n";
}

/* End Core Functions */

int main()
{
    loadDataFromFile();
    int option;

    do
    {
        outputMainMenu();
        option = inputOption();

        switch (option)
        {
        case 1:
            addStudent();
            break;
        case 2:
            searchEmail();
            break;
        case 3:
            removeStudent();
            break;
        case 4:
            showAllData();
            break;
        case 0:
            cout << "Menyimpan data ke file..." << endl;

            saveDataToFile();
            clearAllData();

            cout << "Berhasil menyimpan data ke dalam file." << endl;
            cout << "Keluar dari program. Sampai jumpa!" << endl;
            break;
        default:
            cout << "Opsi " << option << " tidak ditemukan!" << endl;
            break;
        }
    } while (option != 0);
    return 0;
}
