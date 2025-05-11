# **Student Email Directory**

---

## ⚙️ **Tujuan Proyek**

Membuat program yang dapat:

- Menambahkan data mahasiswa (nama + email).
- Menyimpan data dalam hash table menggunakan chaining saat terjadi collision.
- Mencari email berdasarkan nama.
- Menghapus data mahasiswa.
- Menampilkan seluruh data dalam hash table.

---

## 🔄 **Alur Kerja Detail + Tampilan Terminal**

---

### 🟩 1. Tampilan Menu Utama

```bash
=========== Student Email Directory ===========
[1] Tambah Mahasiswa
[2] Cari Email
[3] Hapus Mahasiswa
[4] Lihat Semua
[0] Keluar
Pilih menu:
```

---

### 🟦 2. Tambah Mahasiswa (Insert)

Saat pengguna memilih opsi `[1]`:

```bash
Masukkan Nama : Andi
Masukkan Email: andi@student.unesa.ac.id
```

➡️ Hash function menghitung indeks:

```cpp
index = hash("Andi") % SIZE;
```

Jika index kosong:

```bash
Data berhasil ditambahkan ke slot [2].
```

Jika slot sudah terisi (collision), maka data dimasukkan ke linked list (chaining):

```bash
Terjadi tabrakan hash di slot [2], menggunakan chaining.
Data berhasil ditambahkan ke dalam linked list slot [2].
```

---

### 🟦 3. Cari Email Mahasiswa

Saat memilih opsi `[2]`:

```bash
Masukkan Nama : Andi
```

➡️ Program hash nama → cari di linked list:

```bash
Email ditemukan: andi@student.unesa.ac.id
```

Jika tidak ditemukan:

```bash
Data tidak ditemukan.
```

---

### 🟦 4. Hapus Mahasiswa

Memilih `[3]`:

```bash
Masukkan Nama : Andi
```

➡️ Hash nama → cari di linked list → hapus node:

```bash
Data dengan nama Andi berhasil dihapus dari slot [2].
```

Jika tidak ditemukan:

```bash
Data tidak ditemukan, tidak dapat dihapus.
```

---

### 🟦 5. Lihat Semua Data

Memilih `[4]`:

```bash
=== Isi Hash Table ===
[0] -> (kosong)
[1] -> Nama: Dita | Email: dita@student.unesa.ac.id
[2] -> Nama: Aldi | Email: aldi@student.unesa.ac.id
     -> Nama: Andi | Email: andi@student.unesa.ac.id
[3] -> (kosong)
...
[9] -> (kosong)
```

---

### 🟥 6. Keluar

Memilih `[0]`:

```bash
Terima kasih telah menggunakan Student Email Directory!
```

---

## 🔐 **Penanganan Collision**

Jika `hash("Aldi") % SIZE == hash("Andi") % SIZE`, maka:

- Slot sudah berisi node `Andi`.
- Node baru `Aldi` akan ditambahkan ke linked list di slot tersebut (chaining).

---

## 📘 Catatan Teknis:

- **Struktur Data**:

  - Hash Table: array dari pointer ke linked list.
  - Node Linked List: menyimpan `nama`, `email`, dan pointer ke node selanjutnya.

- **Hash Function**: bisa memakai jumlah ASCII dari nama % ukuran tabel.
