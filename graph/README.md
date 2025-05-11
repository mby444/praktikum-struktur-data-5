# **Friendship Network**

---

### 🔁 **Menu Utama (Looping Program)**

Setiap iterasi, user disuguhkan menu:

```
====== JARINGAN TEMAN ======
1. Tambah Orang
2. Tambah Pertemanan
3. Lihat Teman Seseorang
4. Cek Pertemanan Langsung
5. Temukan Jalur Pertemanan (DFS)
6. Keluar
Pilih:
```

---

### 1. **Tambah Orang**

- **Input:** Nama orang (misal: `Alice`)
- **Proses:** Tambahkan `graph["Alice"] = {};` jika belum ada.
- **Output:** Konfirmasi "Orang berhasil ditambahkan."

---

### 2. **Tambah Pertemanan**

- **Input:** Dua nama orang (misal: `Alice`, `Bob`)
- **Proses:** Tambahkan pertemanan dua arah:

  ```cpp
  graph["Alice"].push_back("Bob");
  graph["Bob"].push_back("Alice");
  ```

- **Output:** "Pertemanan berhasil ditambahkan."

---

### 3. **Lihat Teman Seseorang**

- **Input:** Nama orang.
- **Proses:** Loop pada `graph[nama]` dan tampilkan semua teman.
- **Output:**

  ```
  Teman-teman Alice:
  - Bob
  - Charlie
  ```

---

### 4. **Cek Pertemanan Langsung**

- **Input:** Dua nama (misal: `Alice`, `Charlie`)
- **Proses:** Cek apakah `Charlie` ada di dalam `graph["Alice"]`.
- **Output:**

  - Jika ya: "Alice dan Charlie adalah teman langsung."
  - Jika tidak: "Mereka tidak berteman langsung."

---

### 5. **Temukan Jalur Pertemanan (DFS)**

- **Input:** Dua nama (asal dan tujuan).
- **Proses:**

  - Gunakan DFS rekursif dari asal → tujuan.
  - Simpan jalur sementara (`string path[]`) dan tandai kunjungan (`Visited visited[]`).

- **Output:**

  - Jika ditemukan: tampilkan semua nama dalam jalur.
  - Jika tidak: "Tidak ditemukan jalur pertemanan."

---

### 6. **Keluar**

- Menghentikan program.

---

## 🖥️ Contoh Tampilan Terminal

```
====== JARINGAN TEMAN ======
1. Tambah Orang
2. Tambah Pertemanan
3. Lihat Teman Seseorang
4. Cek Pertemanan Langsung
5. Temukan Jalur Pertemanan (DFS)
6. Keluar
Pilih: 1

Masukkan nama orang: Alice
>> Alice berhasil ditambahkan.

====== JARINGAN TEMAN ======
Pilih: 1
Masukkan nama orang: Bob
>> Bob berhasil ditambahkan.

Pilih: 2
Masukkan nama orang pertama: Alice
Masukkan nama orang kedua : Bob
>> Pertemanan antara Alice dan Bob berhasil ditambahkan.

Pilih: 3
Masukkan nama orang: Alice
Teman-teman Alice:
- Bob

Pilih: 4
Masukkan nama pertama : Alice
Masukkan nama kedua   : Charlie
>> Alice dan Charlie tidak berteman langsung.

Pilih: 5
Masukkan nama asal    : Alice
Masukkan nama tujuan  : Bob
Jalur pertemanan ditemukan:
Alice -> Bob

Pilih: 6
Terima kasih telah menggunakan Jaringan Teman!
```
