# **Dictionary App**

---

### 1. **Struktur Data: Node BST**

Setiap entri kamus disimpan dalam node BST:

```cpp
struct Node {
    string word;       // Kata
    string meaning;    // Artinya
    Node *left;        // Subpohon kiri (kata lebih kecil secara alfabet)
    Node *right;       // Subpohon kanan (kata lebih besar secara alfabet)
};
```

### 2. **Fungsi Tambah Kata**

- Pengguna memasukkan kata dan artinya.
- Program akan menambahkan node ke BST sesuai urutan alfabet:

  - Jika `word` < `node->word`, masuk ke kiri.
  - Jika `word` > `node->word`, masuk ke kanan.

### 3. **Fungsi Cari Kata**

- Program melakukan pencarian berdasarkan input.
- Perbandingan alfabet digunakan:

  - Jika `word` == `node->word` → tampilkan arti.
  - Jika lebih kecil → cari di kiri.
  - Jika lebih besar → cari di kanan.

### 4. **Fungsi Hapus Kata**

- Jika kata ditemukan:

  - Jika node tidak punya anak → hapus langsung.
  - Jika satu anak → sambungkan ke anaknya.
  - Jika dua anak → ganti dengan penerus in-order (min node dari subtree kanan), lalu hapus node tersebut.

### 5. **Fungsi Tampilkan Semua Kata**

- Gunakan **in-order traversal**:

  - Kunjungi kiri → cetak node → kunjungi kanan.

- Menampilkan kata dalam urutan alfabet.

### 6. **Loop Menu**

- Program berjalan dalam loop hingga pengguna memilih keluar.

---

## **Contoh Tampilan Terminal**

```
======= KAMUS KATA SEDERHANA =======
1. Tambah Kata
2. Cari Arti Kata
3. Hapus Kata
4. Tampilkan Semua Kata
5. Keluar
Pilih: 1

Masukkan kata: Apel
Masukkan arti: Buah berwarna merah atau hijau
>> Kata berhasil ditambahkan.

======= KAMUS KATA SEDERHANA =======
1. Tambah Kata
2. Cari Arti Kata
3. Hapus Kata
4. Tampilkan Semua Kata
5. Keluar
Pilih: 1

Masukkan kata: Buku
Masukkan arti: Kumpulan halaman dengan tulisan
>> Kata berhasil ditambahkan.

======= KAMUS KATA SEDERHANA =======
1. Tambah Kata
2. Cari Arti Kata
3. Hapus Kata
4. Tampilkan Semua Kata
5. Keluar
Pilih: 2

Masukkan kata yang ingin dicari: Apel
>> Arti dari 'Apel': Buah berwarna merah atau hijau

======= KAMUS KATA SEDERHANA =======
1. Tambah Kata
2. Cari Arti Kata
3. Hapus Kata
4. Tampilkan Semua Kata
5. Keluar
Pilih: 4

===== Daftar Kata dalam Kamus =====
- Apel: Buah berwarna merah atau hijau
- Buku: Kumpulan halaman dengan tulisan

======= KAMUS KATA SEDERHANA =======
1. Tambah Kata
2. Cari Arti Kata
3. Hapus Kata
4. Tampilkan Semua Kata
5. Keluar
Pilih: 3

Masukkan kata yang ingin dihapus: Apel
>> Kata 'Apel' berhasil dihapus dari kamus.

======= KAMUS KATA SEDERHANA =======
1. Tambah Kata
2. Cari Arti Kata
3. Hapus Kata
4. Tampilkan Semua Kata
5. Keluar
Pilih: 5

>> Terima kasih telah menggunakan Kamus Kata Sederhana!
```
