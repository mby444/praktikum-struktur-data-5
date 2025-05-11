#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

#define DATABASE_FILE "searching_database.txt"

struct Book
{
    string isbn;
    string title;
    string author;
};

int booksCurrentSize = 0;
const int BOOKS_MAX_SIZE = 1000;
Book books[BOOKS_MAX_SIZE];

void outputMainMenu()
{
    cout << "==============================" << endl
         << "     LIBRARY BOOK FINDER      " << endl
         << "==============================" << endl

         << "1. Tambah Buku" << endl
         << "2. Tampilkan Semua Buku" << endl
         << "3. Cari Buku Berdasarkan ISBN" << endl
         << "4. Edit Buku Berdasarkan ISBN" << endl
         << "5. Hapus Buku Berdasarkan ISBN" << endl
         << "6. Muat Ulang Data dari File" << endl
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

long long toNumericISBN(const string &isbn)
{
    long long result = 0;
    int len = isbn.length();

    for (int i = 0; i < len; i++)
    {
        char c = isbn[i];

        if (i == len - 1 && c == 'X')
        {
            result = result * 10 + 10;
        }
        else if (i == len - 1 && c == 'x')
        {
            return -1;
        }
        else if (isdigit(c))
        {
            result = result * 10 + (c - '0');
        }
        else
        {
            return -1;
        }
    }

    return result;
}

int interpolationSearchISBN(const string &key, Book arr[], int n)
{
    int low = 0;
    int high = n - 1;

    long long keyVal = toNumericISBN(key);
    if (keyVal == -1)
        return -1;

    while (low <= high)
    {
        long long lowVal = toNumericISBN(arr[low].isbn);
        long long highVal = toNumericISBN(arr[high].isbn);

        if (lowVal == -1 || highVal == -1)
            return -1;

        if (keyVal < lowVal || keyVal > highVal)
            return -1;

        if (highVal == lowVal)
        {
            if (key == arr[low].isbn)
                return low;
            else
                return -1;
        }

        int pos = low + ((keyVal - lowVal) * (high - low)) / (highVal - lowVal);

        if (pos < low || pos > high || pos >= n || pos < 0)
            return -1;

        long long posVal = toNumericISBN(arr[pos].isbn);

        if (posVal == -1)
            return -1;

        if (key == arr[pos].isbn)
            return pos;
        else if (keyVal < posVal)
            high = pos - 1;
        else
            low = pos + 1;
    }

    return -1;
}

bool isValidISBN10(const string &isbn)
{
    if (isbn.length() != 10)
        return false;

    for (int i = 0; i < 9; ++i)
    {
        if (!isdigit(isbn[i]))
            return false;
    }

    if (!isdigit(isbn[9]) && isbn[9] != 'X')
        return false;

    return true;
}

bool isISBNExists(const string &isbn)
{
    return interpolationSearchISBN(isbn, books, booksCurrentSize) != -1;
}

string inputISBN(string label = "ISBN")
{
    try
    {
        string isbn;
        cout << label << " (ISBN-10)> ";
        getline(cin, isbn);

        isbn = toUpperCase(isbn);

        if (isbn.empty())
        {
            throw "Data tidak boleh kosong!";
        }

        if (!isValidISBN10(isbn))
        {
            throw "ISBN-10 tidak valid! Harus 10 karakter, hanya angka (kecuali karakter ke-10 bisa 'X').";
        }

        return isbn;
    }
    catch (const char *msg)
    {
        cout << "Error: " << msg << endl;
        return inputISBN(label);
    }
    catch (...)
    {
        cout << "Mohon masukkan ISBN yang benar!" << endl;
        return inputISBN(label);
    }
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

int compareISBN(const string &isbn1, const string &isbn2)
{
    int len1 = isbn1.length();
    int len2 = isbn2.length();
    int minLength = min(len1, len2);

    for (int i = 0; i < minLength; i++)
    {
        if (isbn1[i] < isbn2[i])
            return -1;
        else if (isbn1[i] > isbn2[i])
            return 1;
    }

    if (len1 < len2)
        return -1;
    else if (len1 > len2)
        return 1;

    return 0;
}

void merge(Book arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Book *L = new Book[n1];
    Book *R = new Book[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (compareISBN(L[i].isbn, R[j].isbn) <= 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Book arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* Begin Core Helper Functions */

void pushBookData(Book newBook)
{
    books[booksCurrentSize++] = newBook;
    mergeSort(books, 0, booksCurrentSize - 1);
}

void removeBookByIndex(int index)
{
    if (index < 0 || index >= booksCurrentSize)
    {
        cout << "Index tidak valid." << endl;
        return;
    }

    for (int i = index; i < booksCurrentSize - 1; ++i)
    {
        books[i] = books[i + 1];
    }

    booksCurrentSize--;
}

void showSearchedBook(Book book)
{
    cout << "Buku Ditemukan:" << endl
         << "ISBN: " << book.isbn << endl
         << "Judul: " << book.title << endl
         << "Penulis: " << book.author << endl
         << endl;
}

void showRelatedBooks(Book book)
{
    string output;
    bool found = false;

    for (int i = 0; i < booksCurrentSize; i++)
    {
        if (books[i].author == book.author && books[i].isbn != book.isbn)
        {
            found = true;
            output += "- ISBN " + books[i].isbn + " | " + "Judul: " + books[i].title + "\n";
        }
    }
    if (found)
    {
        cout << "Rekomendasi Buku dari Penulis yang Sama:" << endl;
        cout << output << endl;
    }
}

/* End Core Helper Functions */

/* Begin Core Functions */

/**
 * Alur Kerja:
 * - If booksCurrentSize >= BOOKS_MAX_SIZE; stop
 * Else:
 * - Input data buku
 * - Cari buku berdasarkan ISBN untuk memastikan ISBN belum ada pada array
 * - If Input ISBN sudah ada pada array; tampilkan pesan; ulangi input ISBN
 * - Simpan data buku ke dalam array
 * - Sortir ulang array berdasarkan ISBN
 */
void addBook()
{
    if (booksCurrentSize >= BOOKS_MAX_SIZE)
    {
        cout << "Kapasitas maksimum buku telah tercapai!" << endl;
        return;
    }

    Book newBook;

    while (true)
    {
        newBook.isbn = inputISBN("Masukkan ISBN");

        if (isISBNExists(newBook.isbn))
        {
            cout << "ISBN sudah ada dalam data!" << endl;
            continue;
        }
        break;
    }

    newBook.title = inputData("Masukkan Judul");
    newBook.author = inputData("Masukkan Penulis");

    pushBookData(newBook);

    cout << "Buku berhasil ditambahkan!" << endl;
}

/**
 * Alur Kerja:
 * - If booksCurrentSize <= 0; Tampilkan pesan bahwa data buku masih kosong; stop
 * Else:
 * - Tampilkan semua data buku dalam bentuk tabel
 */
void showAllBooks()
{
    cout << "--- Daftar Semua Buku ---" << endl;
    if (booksCurrentSize <= 0)
    {
        cout << "Data buku masih kosong" << endl;
        return;
    }

    cout << left << setw(15) << "ISBN"
         << " | " << setw(30) << "Judul"
         << " | " << setw(25) << "Penulis" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < booksCurrentSize; i++)
    {
        cout << left << setw(15) << books[i].isbn
             << " | " << setw(30) << books[i].title
             << " | " << setw(25) << books[i].author << endl;
    }
}

/**
 * Alur Kerja:
 * - Input ISBN
 * - Cari berdasarkan ISBN menggunakan interpolationSearch()
 * - If pencarian tidak ditemukan; tampilkan pesan; stop
 * Else:
 * - Tampilkan data buku yang ditemukan
 * - Tampilkan list buku dengan penulis yang sama dengan yang dicari
 */
void searchBook()
{
    if (!booksCurrentSize)
    {
        cout << "Data buku masih kosong" << endl;
        return;
    }

    cout << "--- Cari Buku Berdasarkan ISBN ---" << endl;

    string isbn = inputISBN("Masukkan ISBN yang dicari");
    int index = interpolationSearchISBN(isbn, books, booksCurrentSize);

    if (index == -1)
    {
        cout << "Buku dengan ISBN " << isbn << " tidak ditemukan" << endl;
        return;
    }

    Book book = books[index];
    showSearchedBook(book);
    showRelatedBooks(book);
}

void editBook()
{
    if (!booksCurrentSize)
    {
        cout << "Data buku masih kosong" << endl;
        return;
    }

    cout << "--- Edit Buku ---" << endl;

    string isbn = inputISBN("Masukkan ISBN yang ingin diedit");
    int index = interpolationSearchISBN(isbn, books, booksCurrentSize);

    if (index == -1)
    {
        cout << "Buku dengan ISBN " << isbn << " tidak ditemukan" << endl;
        return;
    }

    books[index].title = inputData("Masukkan Judul Baru");
    books[index].author = inputData("Masukkan Penulis Baru");

    cout << "Buku berhasil diperbarui" << endl;
}

void removeBook()
{
    if (!booksCurrentSize)
    {
        cout << "Data buku masih kosong" << endl;
        return;
    }

    cout << "--- Hapus Buku ---" << endl;

    string isbn = inputISBN("Masukkan ISBN yang ingin dihapus");
    int index = interpolationSearchISBN(isbn, books, booksCurrentSize);

    if (index == -1)
    {
        cout << "Buku dengan ISBN " << isbn << " tidak ditemukan" << endl;
        return;
    }

    string title = books[index].title;

    removeBookByIndex(index);
    cout << "Buku dengan judul '" << title << "' berhasil dihapus dari daftar." << endl;
}

void clearBooks()
{
    booksCurrentSize = 0;
}

void loadBooksFromFile()
{
    ifstream file(DATABASE_FILE);
    if (!file.is_open())
    {
        cout << "Gagal membuka file: " << DATABASE_FILE << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    while (getline(file, line))
    {
        lineNumber++;

        if (line.empty())
            continue;

        stringstream ss(line);
        string isbn, title, author;

        if (getline(ss, isbn, '|') && getline(ss, title, '|') && getline(ss, author))
        {
            if (booksCurrentSize < BOOKS_MAX_SIZE)
            {
                books[booksCurrentSize++] = {isbn, title, author};
            }
            else
            {
                cout << "Maksimum jumlah buku telah tercapai." << endl;
                break;
            }
        }
        else
        {
            cout << "Format baris tidak valid pada baris ke-" << lineNumber << endl;
        }
    }

    file.close();
    cout << "Berhasil memuat " << booksCurrentSize << " buku dari file." << endl;
}

void reloadBooksFromFile()
{
    clearBooks();
    loadBooksFromFile();
}

void saveBooksToFile()
{
    ofstream file(DATABASE_FILE);

    if (!file.is_open())
    {
        cerr << "Gagal membuka file untuk menulis." << endl;
        return;
    }

    for (int i = 0; i < booksCurrentSize; i++)
    {
        file << books[i].isbn << "|"
             << books[i].title << "|"
             << books[i].author << "\n";
    }

    file.close();
    cout << "Data buku berhasil disimpan ke " << DATABASE_FILE << endl;
}

/* End Core Functions */

int main()
{
    loadBooksFromFile();
    int option;

    do
    {
        outputMainMenu();
        option = inputOption();

        switch (option)
        {
        case 1:
            addBook();
            break;
        case 2:
            showAllBooks();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            editBook();
            break;
        case 5:
            removeBook();
            break;
        case 6:
            reloadBooksFromFile();
            break;
        case 0:
            cout << "Menyimpan data ke file..." << endl;

            saveBooksToFile();

            cout << "Berhasil menyimpan buku ke dalam file." << endl;
            cout << "Keluar dari program. Sampai jumpa!" << endl;
            break;
        default:
            cout << "Opsi " << option << " tidak ditemukan!" << endl;
            break;
        }
    } while (option != 0);

    return 0;
}
