#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

#define DATABASE_FILE "graph_database.txt"

const int MAX_PEOPLE = 100;
string names[MAX_PEOPLE];
bool adjMatrix[MAX_PEOPLE][MAX_PEOPLE] = {0};
int totalPeople = 0;

void showAdjMatrix()
{
    if (totalPeople == 0)
    {
        cout << "Belum ada data orang dalam jaringan.\n";
        return;
    }

    const int colWidth = 10;

    cout << setw(colWidth) << left << " ";
    for (int i = 0; i < totalPeople; i++)
    {
        cout << setw(colWidth) << left << names[i];
    }
    cout << "\n";

    cout << string((totalPeople + 1) * colWidth, '-') << "\n";

    for (int i = 0; i < totalPeople; i++)
    {
        cout << setw(colWidth) << left << names[i];
        for (int j = 0; j < totalPeople; j++)
        {
            cout << setw(colWidth) << left << (adjMatrix[i][j] ? "1" : "0");
        }
        cout << "\n";
    }
}

void outputMainMenu()
{
    cout << endl
         << "====== JARINGAN TEMAN ======" << endl;

    showAdjMatrix();

    cout << endl
         << "1. Tambah Orang" << endl
         << "2. Tambah Pertemanan" << endl
         << "3. Lihat Teman Seseorang" << endl
         << "4. Cek Pertemanan Langsung" << endl
         << "5. Temukan Jalur Pertemanan (DFS)" << endl
         << "0. Simpan dan Keluar" << endl
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
int searchPersonByName(string name)
{
    for (int i = 0; i < totalPeople; i++)
    {
        if (toLowerCase(names[i]) == toLowerCase(name))
        {
            return i;
        }
    }

    return -1;
}

void addPersonToNetwork(string name)
{
    if (searchPersonByName(name) != -1)
    {
        cout << name << " sudah ada dalam jaringan." << endl;
        return;
    }
    if (totalPeople >= MAX_PEOPLE)
    {
        cout << "Jumlah orang telah mencapai batas maksimal." << endl;
        return;
    }
    names[totalPeople++] = name;
    cout << name << " berhasil ditambahkan." << endl;
}

bool searchAndValidateTwoPeople(string name1, string name2, int *index1, int *index2, string errorMessage = "")
{
    if (!index1 || !index2)
        return false;

    *index1 = searchPersonByName(name1);

    if (*index1 == -1)
    {
        if (!empty(errorMessage))
            cout << errorMessage << ", ";
        cout << name1 << " tidak ditemukan." << endl;
        return false;
    }

    *index2 = searchPersonByName(name2);

    if (*index2 == -1)
    {
        if (!empty(errorMessage))
            cout << errorMessage << ", ";
        cout << name2 << " tidak ditemukan." << endl;
        return false;
    }

    return true;
}

void connectTwoPeople(string name1, string name2)
{
    if (toLowerCase(name1) == toLowerCase(name2))
    {
        cout << "Tidak dapat berteman dengan diri sendiri." << endl;
        return;
    }
    int index1;
    int index2;
    string errorMessage = "Tidak dapat menambahkan pertemanan";

    bool isFound = searchAndValidateTwoPeople(name1, name2, &index1, &index2, errorMessage);

    if (!isFound)
        return;

    if (adjMatrix[index1][index2] == 1 && adjMatrix[index2][index1] == 1)
    {
        cout << name1 << " dan " << name2 << " sudah berteman sebelumnya." << endl;
        return;
    }

    adjMatrix[index1][index2] = 1;
    adjMatrix[index2][index1] = 1;

    cout << "Pertemanan antara " << name1 << " dan " << name2 << " berhasil ditambahkan." << endl;
}

void showFriendList(string name)
{
    int index = searchPersonByName(name);

    if (index == -1)
    {
        cout << name << " tidak ditemukan." << endl;
        return;
    }

    string friends[MAX_PEOPLE];
    int totalFriends = 0;

    for (int j = 0; j < totalPeople; j++)
    {
        if (adjMatrix[index][j] == 1)
        {
            friends[totalFriends++] = names[j];
        }
    }

    if (totalFriends)
    {
        cout << "Teman-teman " << name << ":" << endl;

        for (int i = 0; i < totalFriends; i++)
        {
            cout << "- " << friends[i] << endl;
        }
    }
    else
    {
        cout << name << " tidak memiliki teman." << endl;
    }
}

void showConnectionStatus(string name1, string name2)
{
    if (toLowerCase(name1) == toLowerCase(name2))
    {
        cout << "Tidak dapat mengecek pertemanan dengan diri sendiri." << endl;
        return;
    }

    int index1;
    int index2;
    string errorMessage = "Tidak dapat mengecek pertemanan langsung";

    bool isFound = searchAndValidateTwoPeople(name1, name2, &index1, &index2, errorMessage);

    if (!isFound)
        return;

    cout << name1 << " dan " << name2;

    if (adjMatrix[index1][index2] == 1)
    {
        cout << " berteman langsung." << endl;
    }
    else
    {
        cout << " tidak berteman langsung." << endl;
    }
}

bool visited[MAX_PEOPLE];
int path[MAX_PEOPLE];
int pathIndex = 0;

void dfs(int current, int target, bool *found)
{
    visited[current] = true;
    path[pathIndex++] = current;

    if (current == target)
    {
        *found = true;
        return;
    }

    for (int i = 0; i < totalPeople; i++)
    {
        if (adjMatrix[current][i] && !visited[i])
        {
            dfs(i, target, found);
            if (*found)
                return;
        }
    }

    pathIndex--;
}

void initDFS()
{
    for (int i = 0; i < MAX_PEOPLE; i++)
    {
        visited[i] = false;
    }
    pathIndex = 0;
}

void findConnectionPath(string name1, string name2)
{
    if (toLowerCase(name1) == toLowerCase(name2))
    {
        cout << "Tidak dapat menemukan jalur pertemanan dengan diri sendiri." << endl;
        return;
    }

    int index1;
    int index2;
    string errorMessage = "Tidak dapat menemukan jalur pertemanan";

    bool isFound = searchAndValidateTwoPeople(name1, name2, &index1, &index2, errorMessage);

    if (!isFound)
        return;

    bool pathFound = false;

    initDFS();
    dfs(index1, index2, &pathFound);

    if (pathFound)
    {
        cout << "Jalur pertemanan ditemukan:" << endl;

        for (int i = 0; i < pathIndex; i++)
        {
            int nameIndex = path[i];
            cout << names[nameIndex];
            if (i != pathIndex - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "Tidak ditemukan jalur pertemanan" << endl;
    }
}
/* End Core Helper Functions */

/* Begin Core Functions */
void addPerson()
{
    string name = inputData("Masukkan nama orang");
    addPersonToNetwork(name);
}

void addFriendship()
{
    string name1 = inputData("Masukkan nama orang pertama");
    string name2 = inputData("Masukkan nama orang kedua");
    connectTwoPeople(name1, name2);
}

void showFriendsOfPerson()
{
    string name = inputData("Masukkan nama orang");
    showFriendList(name);
}

void showFriendshipStatus()
{
    string name1 = inputData("Masukkan nama orang pertama");
    string name2 = inputData("Masukkan nama orang kedua");
    showConnectionStatus(name1, name2);
}

void findFriendshipPath()
{
    string name1 = inputData("Masukkan nama asal");
    string name2 = inputData("Masukkan nama tujuan");
    findConnectionPath(name1, name2);
}

void loadDataFromFile()
{
    ifstream file(DATABASE_FILE);
    if (!file.is_open())
    {
        cout << "Tidak ada data tersimpan atau gagal membuka file." << endl;
        return;
    }

    file >> totalPeople;

    if (totalPeople > MAX_PEOPLE)
    {
        cout << "Data melebihi kapasitas maksimal. Load dibatalkan." << endl;
        file.close();
        return;
    }

    file.ignore();

    for (int i = 0; i < totalPeople; i++)
    {
        getline(file, names[i]);
    }

    for (int i = 0; i < totalPeople; i++)
    {
        for (int j = 0; j < totalPeople; j++)
        {
            int val;
            file >> val;
            adjMatrix[i][j] = (val == 1);
        }
    }

    file.close();
}

void saveDataToFile()
{
    ofstream file(DATABASE_FILE);
    if (!file.is_open())
    {
        cout << "Gagal menyimpan data ke file." << endl;
        return;
    }

    file << totalPeople << endl;

    for (int i = 0; i < totalPeople; i++)
    {
        file << names[i] << endl;
    }

    for (int i = 0; i < totalPeople; i++)
    {
        for (int j = 0; j < totalPeople; j++)
        {
            file << adjMatrix[i][j] << " ";
        }
        file << endl;
    }

    file.close();
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
            addPerson();
            break;
        case 2:
            addFriendship();
            break;
        case 3:
            showFriendsOfPerson();
            break;
        case 4:
            showFriendshipStatus();
            break;
        case 5:
            findFriendshipPath();
            break;
        case 0:
            cout << "Menyimpan data ke file..." << endl;

            saveDataToFile();

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