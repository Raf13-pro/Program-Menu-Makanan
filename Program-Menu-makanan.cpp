#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream> // Untuk file handling

using namespace std;

// Struktur untuk menu makanan
struct MenuItem {
    string nama;
    int harga;
};

// Daftar menu
vector<MenuItem> makananUtama = {
    {"Nasi Goreng Biasa", 13000},
    {"Nasi Goreng Spesial", 16000},
    {"Mie Goreng Biasa", 13000},
    {"Mie Rebus Biasa", 13000},
    {"Mie Goreng Telur", 16000},
    {"Kwetiau Goreng", 16000},
    {"Kwetiau Rebus", 16000}
};

vector<MenuItem> minuman = {
    {"Teh Manis/Tawar", 2000},
    {"Es Teh Manis/Tawar", 4000},
    {"Jeruk Panas", 4000},
    {"Es Jeruk", 6000},
    {"Kopi Panas", 3000},
    {"Es Kopi", 5000}
};

vector<MenuItem> tambahan = {
    {"Gorengan", 2000},
    {"Kerupuk", 2000},
    {"Bawang Boreng", 2000}
};

// Fungsi untuk menampilkan menu
void tampilkanMenu(const vector<MenuItem>& menu, const string& kategori) {
    cout << "=== " << kategori << " ===\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        cout << i + 1 << ". " << setw(20) << left << menu[i].nama
             << "Rp " << menu[i].harga << endl;
    }
    cout << endl;
}

// Fungsi untuk memilih item dari menu
vector<MenuItem> pilihBeberapaItem(const vector<MenuItem>& menu) {
    vector<MenuItem> pesanan;
    int pilihan;
    cout << "Masukkan nomor menu yang ingin dipilih (0 untuk selesai): ";
    while (true) {
        cin >> pilihan;
        if (pilihan == 0) {
            break; // Selesai memilih
        } else if (pilihan > 0 && pilihan <= menu.size()) {
            pesanan.push_back(menu[pilihan - 1]);
            cout << "Item '" << menu[pilihan - 1].nama << "' ditambahkan.\n";
        } else {
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    }
    return pesanan;
}

// Fungsi untuk menyimpan pesanan ke file CSV
void simpanKeCSV(const vector<MenuItem>& pesanan, int totalHarga, const string& namaFile, const string& namaPemesan) {
    ofstream file(namaFile);
    if (!file) {
        cerr << "Gagal membuka file untuk menulis.\n";
        return;
    }

    // Menulis header
    file << "Nama Pemesan," << namaPemesan << "\n";
    file << "Nama Item,Harga\n";

    // Menulis data pesanan
    for (const auto& item : pesanan) {
        file << item.nama << "," << item.harga << "\n";
    }

    // Menulis total harga
    file << "Total Harga," << totalHarga << "\n";

    file.close();
    cout << "Pesanan berhasil disimpan ke file '" << namaFile << "'\n";
}

int main() {
    vector<MenuItem> pesanan;	 // Menyimpan semua pesanan pengguna
    char pilihanLanjut;
    string namaPemesan;

    //Input nama pemesan
    cout << "Selamat datang di NAGASI (Nasi Goreng Gacor Asli} !\n";
    cout << "Silakan masukkan nama Anda: ";
    getline(cin, namaPemesan);

    do {
        system("cls");	 // Membersihkan layar (gunakan "clear" di Linux/Mac)

        // Menampilkan semua menu
        tampilkanMenu(makananUtama, "Makanan Utama");
        tampilkanMenu(minuman, "Minuman");
        tampilkanMenu(tambahan, "Tambahan");

        // Memilih kategori
        int kategori;
        cout << "Pilih kategori (1. Makanan Utama, 2. Minuman, 3. Tambahan): ";
        cin >> kategori;

        vector<MenuItem> pilihanPesanan;
        if (kategori == 1) {
            tampilkanMenu(makananUtama, "Makanan Utama");
            pilihanPesanan = pilihBeberapaItem(makananUtama);
        } else if (kategori == 2) {
            tampilkanMenu(minuman, "Minuman");
            pilihanPesanan = pilihBeberapaItem(minuman);
        } else if (kategori == 3) {
            tampilkanMenu(tambahan, "Tambahan");
            pilihanPesanan = pilihBeberapaItem(tambahan);
        } else {
            cout << "Kategori tidak valid.\n";
        }

        // Menambahkan pilihan ke daftar pesanan utama
        pesanan.insert(pesanan.end(), pilihanPesanan.begin(), pilihanPesanan.end());

        // Menanyakan apakah ingin memesan lagi
        cout << "\nIngin memesan lagi? (y/n): ";
        cin >> pilihanLanjut;

    } while (pilihanLanjut == 'y' || pilihanLanjut == 'Y');

    // Menampilkan pesanan akhir
    system("cls");	 // Membersihkan layar (gunakan "clear" di Linux/Mac)
    cout << "=== Pesanan Anda ===\n";
    cout << "Nama Pemesan: " << namaPemesan << endl;
    int totalHarga = 0;
    for (const auto& item : pesanan) {
        cout << "-" << setw(20) << left << item.nama
             << "Rp" << item.harga << endl;
        totalHarga += item.harga;
    }
    cout << "Total Harga: Rp " << totalHarga << endl;

    // Menyimpan pesanan ke file CSV
    string namaFile = "pesanan.csv";
    simpanKeCSV(pesanan, totalHarga, namaFile, namaPemesan);

    cout << "Terima kasih telah memesan, " << namaPemesan << "!\n";

    return 0;
}
