#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

#define DATABASE_FILE "tree_database.txt"

struct Node
{
    string word;
    string meaning;
    Node *left = NULL;
    Node *right = NULL;
};

Node *root = NULL;

void outputMainMenu()
{
    cout << endl
         << "======= KAMUS KATA SEDERHANA =======" << endl;

    cout << "1. Tambah Kata" << endl
         << "2. Cari Arti Kata" << endl
         << "3. Hapus Kata" << endl
         << "4. Tampilkan Semua Kata" << endl
         << "0. Keluar" << endl
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

int compareWords(const string &word1, const string &word2)
{
    string lower1 = toLowerCase(word1);
    string lower2 = toLowerCase(word2);

    int len = min(lower1.length(), lower2.length());

    for (int i = 0; i < len; ++i)
    {
        if (lower1[i] < lower2[i])
            return -1;
        else if (lower1[i] > lower2[i])
            return 1;
    }

    if (lower1.length() < lower2.length())
        return -1;
    else if (lower1.length() > lower2.length())
        return 1;

    return 0;
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

string inputWord(string label = "")
{
    try
    {
        string input = inputData(label);

        if (input.find(' ') != string::npos)
        {
            cout << "Mohon masukkan sebuah kata tanpa spasi." << endl;
            throw -1;
        }

        return input;
    }
    catch (...)
    {
        return inputWord(label);
    }
}

/* Begin Core Helper Functions */
Node *createWordNode()
{
    Node *newNode = new Node;
    newNode->word = inputWord("Masukkan kata");
    newNode->meaning = inputData("Masukkan arti");
    return newNode;
}

void addNodeToTree(Node **rootPtr, Node *newNode)
{
    if (*rootPtr == NULL)
    {
        *rootPtr = newNode;
    }
    else if (compareWords(newNode->word, (*rootPtr)->word) < 0)
    {
        addNodeToTree(&(*rootPtr)->left, newNode);
    }
    else if (compareWords(newNode->word, (*rootPtr)->word) > 0)
    {
        addNodeToTree(&(*rootPtr)->right, newNode);
    }
    else
    {
        cout << "Tidak dapat menambahkan kata. Kata sudah ditambahkan sebelumnya" << endl;
    }
}

void searchInTree(Node **rootPtr, string word)
{
    if (*rootPtr == NULL)
    {
        cout << "Kata " << word << " tidak ditemukan." << endl;
    }
    else if (compareWords(word, (*rootPtr)->word) < 0)
    {
        searchInTree(&(*rootPtr)->left, word);
    }
    else if (compareWords(word, (*rootPtr)->word) > 0)
    {
        searchInTree(&(*rootPtr)->right, word);
    }
    else
    {
        cout << "Arti dari '" << word << "': " << (*rootPtr)->meaning << endl;
    }
}

void inorderTraversal(Node **rootPtr)
{
    if (*rootPtr == NULL)
        return;

    inorderTraversal(&(*rootPtr)->left);
    cout << "- " << (*rootPtr)->word << ": " << (*rootPtr)->meaning << endl;
    inorderTraversal(&(*rootPtr)->right);
}

Node *findMin(Node *node)
{
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

Node *removeNode(Node *root, string word)
{
    if (root == NULL)
    {
        cout << "Kata '" << word << "' tidak ditemukan" << endl;
        return NULL;
    }

    int cmp = compareWords(word, root->word);

    if (cmp < 0)
    {
        root->left = removeNode(root->left, word);
    }
    else if (cmp > 0)
    {
        root->right = removeNode(root->right, word);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        else if (root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        else
        {
            Node *temp = findMin(root->right);
            root->word = temp->word;
            root->meaning = temp->meaning;
            root->right = removeNode(root->right, temp->word);
        }
    }

    cout << "Kata '" << word << "' berhasil dihapus dari kamus." << endl;
    return root;
}

void removeAllNodes(Node *&root)
{
    if (root == NULL)
        return;

    removeAllNodes(root->left);
    removeAllNodes(root->right);

    delete root;
    root = NULL;
}

/* End Core Helper Functions */

/* Begin Core Functions */
void addWord()
{
    Node *newNode = createWordNode();
    addNodeToTree(&root, newNode);
}

void searchMeaning()
{
    if (root == NULL)
    {
        cout << "Kamus masih kosong." << endl;
        return;
    }

    string word = inputWord("Masukkan kata yang ingin dicari");
    searchInTree(&root, word);
}

void removeWord()
{
    if (root == NULL)
    {
        cout << "Kamus masih kosong." << endl;
        return;
    }

    string word = inputWord("Masukkan kata yang ingin dihapus");
    root = removeNode(root, word);
}

void showAllWords()
{
    if (root == NULL)
    {
        cout << "Kamus masih kosong." << endl;
        return;
    }

    cout << endl
         << "===== Daftar Kata dalam Kamus =====" << endl;

    inorderTraversal(&root);
}

void clearTree()
{
    removeAllNodes(root);
}

void insertNode(Node *&root, string word, string meaning)
{
    if (root == NULL)
    {
        root = new Node{word, meaning};
    }
    else if (compareWords(word, root->word) < 0)
    {
        insertNode(root->left, word, meaning);
    }
    else if (compareWords(word, root->word) > 0)
    {
        insertNode(root->right, word, meaning);
    }
}

void loadDataFromFile()
{
    ifstream file(DATABASE_FILE);
    if (!file.is_open())
    {
        cerr << "Gagal membuka file untuk memuat data.\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != string::npos)
        {
            string word = line.substr(0, delimiterPos);
            string meaning = line.substr(delimiterPos + 1);
            insertNode(root, word, meaning);
        }
    }

    file.close();
}

void saveNodeToFile(Node *node, ofstream &file)
{
    if (node == NULL)
        return;

    file << node->word << '|' << node->meaning << '\n';

    saveNodeToFile(node->left, file);
    saveNodeToFile(node->right, file);
}

void saveDataToFile()
{
    ofstream file(DATABASE_FILE);
    if (!file.is_open())
    {
        cerr << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }

    saveNodeToFile(root, file);
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
            addWord();
            break;
        case 2:
            searchMeaning();
            break;
        case 3:
            removeWord();
            break;
        case 4:
            showAllWords();
            break;
        case 0:
            cout << "Menyimpan data ke file..." << endl;

            saveDataToFile();
            clearTree();

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