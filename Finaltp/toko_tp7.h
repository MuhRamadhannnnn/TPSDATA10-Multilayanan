#ifndef TOKO_TP7_H
#define TOKO_TP7_H

#include <iostream>
#include <string>
#include <fstream>

#include "linkedlist.h"

using namespace std;

#define MENU_DIR "menu_toko/"

struct Menutoko {
    int isimenu;
    string pesanan[50];
    int harga[50];
    int jumlahpesanan;
    Menutoko() { jumlahpesanan = 0; }
    char lagi;
    int pilihsearching;
    int pilihmenu;
};

struct Restoran {
    string nama;
    float rating;
    string jenismakanan;
};

struct DataMakanan {
    string nama;
    int harga;
    string jenis;
    string restoran;
};

class PesananRating {
private:
    Restoran daftarRestoran[10];
    int jumlahRestoran;

    void sortByRating() {
        for (int i = 0; i < jumlahRestoran - 1; i++) {
            for (int j = 0; j < jumlahRestoran - i - 1; j++) {
                if (daftarRestoran[j].rating > daftarRestoran[j + 1].rating) {
                    Restoran temp = daftarRestoran[j];
                    daftarRestoran[j] = daftarRestoran[j + 1];
                    daftarRestoran[j + 1] = temp;
                }
            }
        }
    }

public:
    PesananRating() {
        jumlahRestoran = 10;

        daftarRestoran[0].nama = "Bebek Madura Sambal Hitam";
        daftarRestoran[0].rating = 4.0;
        daftarRestoran[0].jenismakanan = "Bebek";
        daftarRestoran[1].nama = "Bebek Goreng Haji Slamet";
        daftarRestoran[1].rating = 4.1;
        daftarRestoran[1].jenismakanan = "Bebek";
        daftarRestoran[2].nama = "Mie Pedas Badai";
        daftarRestoran[2].rating = 4.2;
        daftarRestoran[2].jenismakanan = "Mie";
        daftarRestoran[3].nama = "Bakso Beranak Jaya";
        daftarRestoran[3].rating = 4.3;
        daftarRestoran[3].jenismakanan = "Bakso";
        daftarRestoran[4].nama = "Bakso Pak Kumis";
        daftarRestoran[4].rating = 4.4;
        daftarRestoran[4].jenismakanan = "Bakso";
        daftarRestoran[5].nama = "Ayam Geprek Sambal Korek";
        daftarRestoran[5].rating = 4.5;
        daftarRestoran[5].jenismakanan = "Ayam";
        daftarRestoran[6].nama = "Martabak Bangka 77";
        daftarRestoran[6].rating = 4.6;
        daftarRestoran[6].jenismakanan = "Martabak";
        daftarRestoran[7].nama = "Martabak Legend";
        daftarRestoran[7].rating = 4.7;
        daftarRestoran[7].jenismakanan = "Martabak";
        daftarRestoran[8].nama = "Ayam Geprek Bangjo";
        daftarRestoran[8].rating = 4.8;
        daftarRestoran[8].jenismakanan = "Ayam";
        daftarRestoran[9].nama = "Mie Gacoan";
        daftarRestoran[9].rating = 4.9;
        daftarRestoran[9].jenismakanan = "Mie";

        sortByRating();
    }

    void cariRestoranByRating() {
        float targetRating;
        cout << "\n=== Pencarian Restoran Berdasarkan Rating (Binary Search) ===\n";
        cout << "Masukkan rating minimum (1.0 - 5.0): ";
        cin >> targetRating;

        int left = 0, right = jumlahRestoran - 1;
        int startIndex = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (daftarRestoran[mid].rating >= targetRating) {
                startIndex = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (startIndex != -1) {
            cout << "\n=== Restoran dengan Rating >= " << targetRating << " ===\n";
            int counter = 1;
            for (int i = startIndex; i < jumlahRestoran; i++) {
                cout << counter << ". " << daftarRestoran[i].nama
                     << " - Rating: " << daftarRestoran[i].rating
                     << " - Jenis: " << daftarRestoran[i].jenismakanan << endl;
                counter++;
            }
        } else {
            cout << "Tidak ada restoran dengan rating >= " << targetRating << endl;
        }
    }
};

class PesananHarga {
private:
    DataMakanan daftarMakanan[18];
    int jumlahMakanan;

public:
    PesananHarga() {
        jumlahMakanan = 18;

        daftarMakanan[0].nama = "Ayam Geprek";
        daftarMakanan[0].harga = 18000;
        daftarMakanan[0].jenis = "Ayam";
        daftarMakanan[0].restoran = "Ayam Geprek Bangjo";
        daftarMakanan[1].nama = "Ayam Geprek Keju";
        daftarMakanan[1].harga = 22000;
        daftarMakanan[1].jenis = "Ayam";
        daftarMakanan[1].restoran = "Ayam Geprek Bangjo";
        daftarMakanan[2].nama = "Ayam Geprek Sambel Korek";
        daftarMakanan[2].harga = 19000;
        daftarMakanan[2].jenis = "Ayam";
        daftarMakanan[2].restoran = "Ayam Geprek Sambal Korek";
        daftarMakanan[3].nama = "Ayam Geprek Original";
        daftarMakanan[3].harga = 17000;
        daftarMakanan[3].jenis = "Ayam";
        daftarMakanan[3].restoran = "Ayam Geprek Sambal Korek";
        daftarMakanan[4].nama = "Martabak Manis";
        daftarMakanan[4].harga = 25000;
        daftarMakanan[4].jenis = "Martabak";
        daftarMakanan[4].restoran = "Martabak Legend";
        daftarMakanan[5].nama = "Martabak Telur";
        daftarMakanan[5].harga = 30000;
        daftarMakanan[5].jenis = "Martabak";
        daftarMakanan[5].restoran = "Martabak Legend";
        daftarMakanan[6].nama = "Martabak Cokelat Keju";
        daftarMakanan[6].harga = 26000;
        daftarMakanan[6].jenis = "Martabak";
        daftarMakanan[6].restoran = "Martabak Bangka 77";
        daftarMakanan[7].nama = "Martabak Telur Spesial";
        daftarMakanan[7].harga = 32000;
        daftarMakanan[7].jenis = "Martabak";
        daftarMakanan[7].restoran = "Martabak Bangka 77";
        daftarMakanan[8].nama = "Bakso Urat";
        daftarMakanan[8].harga = 25000;
        daftarMakanan[8].jenis = "Bakso";
        daftarMakanan[8].restoran = "Bakso Pak Kumis";
        daftarMakanan[9].nama = "Mie Ayam";
        daftarMakanan[9].harga = 20000;
        daftarMakanan[9].jenis = "Bakso";
        daftarMakanan[9].restoran = "Bakso Pak Kumis";
        daftarMakanan[10].nama = "Bakso Beranak";
        daftarMakanan[10].harga = 28000;
        daftarMakanan[10].jenis = "Bakso";
        daftarMakanan[10].restoran = "Bakso Beranak Jaya";
        daftarMakanan[11].nama = "Bakso Mercon";
        daftarMakanan[11].harga = 25000;
        daftarMakanan[11].jenis = "Bakso";
        daftarMakanan[11].restoran = "Bakso Beranak Jaya";
        daftarMakanan[12].nama = "Mie Hompimpa";
        daftarMakanan[12].harga = 17000;
        daftarMakanan[12].jenis = "Mie";
        daftarMakanan[12].restoran = "Mie Gacoan";
        daftarMakanan[13].nama = "Mie Suit";
        daftarMakanan[13].harga = 17000;
        daftarMakanan[13].jenis = "Mie";
        daftarMakanan[13].restoran = "Mie Gacoan";
        daftarMakanan[14].nama = "Mie Badai Level 3";
        daftarMakanan[14].harga = 18000;
        daftarMakanan[14].jenis = "Mie";
        daftarMakanan[14].restoran = "Mie Pedas Badai";
        daftarMakanan[15].nama = "Mie Goreng Pedas";
        daftarMakanan[15].harga = 16000;
        daftarMakanan[15].jenis = "Mie";
        daftarMakanan[15].restoran = "Mie Pedas Badai";
        daftarMakanan[16].nama = "Bebek Goreng Original";
        daftarMakanan[16].harga = 30000;
        daftarMakanan[16].jenis = "Bebek";
        daftarMakanan[16].restoran = "Bebek Goreng Haji Slamet";
        daftarMakanan[17].nama = "Bebek Bakar";
        daftarMakanan[17].harga = 32000;
        daftarMakanan[17].jenis = "Bebek";
        daftarMakanan[17].restoran = "Bebek Goreng Haji Slamet";
    }

    void cariMakananByHarga() {
        int hargaMin, hargaMax;
        cout << "\n=== Pencarian Makanan Berdasarkan Harga (Linear Search) ===\n";
        cout << "Masukkan harga minimum: Rp ";
        cin >> hargaMin;
        cout << "Masukkan harga maksimum: Rp ";
        cin >> hargaMax;

        DataMakanan hasil[18];
        int jumlahHasil = 0;

        for (int i = 0; i < jumlahMakanan; i++) {
            if (daftarMakanan[i].harga >= hargaMin && daftarMakanan[i].harga <= hargaMax) {
                hasil[jumlahHasil] = daftarMakanan[i];
                jumlahHasil++;
            }
        }

        if (jumlahHasil > 0) {
            cout << "\n=== Makanan dengan Harga Rp " << hargaMin << " - Rp " << hargaMax << " ===\n";
            for (int i = 0; i < jumlahHasil; i++) {
                cout << i + 1 << ". " << hasil[i].nama
                     << " - Rp " << hasil[i].harga
                     << " (" << hasil[i].restoran << ")" << endl;
            }
        } else {
            cout << "Tidak ada makanan dalam range harga tersebut.\n";
        }
    }
};

class PesananJenis {
private:
    DataMakanan daftarMakanan[18];
    int jumlahMakanan;

public:
    PesananJenis() {
        jumlahMakanan = 18;

        daftarMakanan[0].nama = "Ayam Geprek";
        daftarMakanan[0].harga = 18000;
        daftarMakanan[0].jenis = "Ayam";
        daftarMakanan[0].restoran = "Ayam Geprek Bangjo";
        daftarMakanan[1].nama = "Ayam Geprek Keju";
        daftarMakanan[1].harga = 22000;
        daftarMakanan[1].jenis = "Ayam";
        daftarMakanan[1].restoran = "Ayam Geprek Bangjo";
        daftarMakanan[2].nama = "Ayam Geprek Sambel Korek";
        daftarMakanan[2].harga = 19000;
        daftarMakanan[2].jenis = "Ayam";
        daftarMakanan[2].restoran = "Ayam Geprek Sambal Korek";
        daftarMakanan[3].nama = "Ayam Geprek Original";
        daftarMakanan[3].harga = 17000;
        daftarMakanan[3].jenis = "Ayam";
        daftarMakanan[3].restoran = "Ayam Geprek Sambal Korek";
        daftarMakanan[4].nama = "Martabak Manis";
        daftarMakanan[4].harga = 25000;
        daftarMakanan[4].jenis = "Martabak";
        daftarMakanan[4].restoran = "Martabak Legend";
        daftarMakanan[5].nama = "Martabak Telur";
        daftarMakanan[5].harga = 30000;
        daftarMakanan[5].jenis = "Martabak";
        daftarMakanan[5].restoran = "Martabak Legend";
        daftarMakanan[6].nama = "Martabak Cokelat Keju";
        daftarMakanan[6].harga = 26000;
        daftarMakanan[6].jenis = "Martabak";
        daftarMakanan[6].restoran = "Martabak Bangka 77";
        daftarMakanan[7].nama = "Martabak Telur Spesial";
        daftarMakanan[7].harga = 32000;
        daftarMakanan[7].jenis = "Martabak";
        daftarMakanan[7].restoran = "Martabak Bangka 77";
        daftarMakanan[8].nama = "Bakso Urat";
        daftarMakanan[8].harga = 25000;
        daftarMakanan[8].jenis = "Bakso";
        daftarMakanan[8].restoran = "Bakso Pak Kumis";
        daftarMakanan[9].nama = "Mie Ayam";
        daftarMakanan[9].harga = 20000;
        daftarMakanan[9].jenis = "Bakso";
        daftarMakanan[9].restoran = "Bakso Pak Kumis";
        daftarMakanan[10].nama = "Bakso Beranak";
        daftarMakanan[10].harga = 28000;
        daftarMakanan[10].jenis = "Bakso";
        daftarMakanan[10].restoran = "Bakso Beranak Jaya";
        daftarMakanan[11].nama = "Bakso Mercon";
        daftarMakanan[11].harga = 25000;
        daftarMakanan[11].jenis = "Bakso";
        daftarMakanan[11].restoran = "Bakso Beranak Jaya";
        daftarMakanan[12].nama = "Mie Hompimpa";
        daftarMakanan[12].harga = 17000;
        daftarMakanan[12].jenis = "Mie";
        daftarMakanan[12].restoran = "Mie Gacoan";
        daftarMakanan[13].nama = "Mie Suit";
        daftarMakanan[13].harga = 17000;
        daftarMakanan[13].jenis = "Mie";
        daftarMakanan[13].restoran = "Mie Gacoan";
        daftarMakanan[14].nama = "Mie Badai Level 3";
        daftarMakanan[14].harga = 18000;
        daftarMakanan[14].jenis = "Mie";
        daftarMakanan[14].restoran = "Mie Pedas Badai";
        daftarMakanan[15].nama = "Mie Goreng Pedas";
        daftarMakanan[15].harga = 16000;
        daftarMakanan[15].jenis = "Mie";
        daftarMakanan[15].restoran = "Mie Pedas Badai";
        daftarMakanan[16].nama = "Bebek Goreng Original";
        daftarMakanan[16].harga = 30000;
        daftarMakanan[16].jenis = "Bebek";
        daftarMakanan[16].restoran = "Bebek Goreng Haji Slamet";
        daftarMakanan[17].nama = "Bebek Bakar";
        daftarMakanan[17].harga = 32000;
        daftarMakanan[17].jenis = "Bebek";
        daftarMakanan[17].restoran = "Bebek Goreng Haji Slamet";
    }

    void cariMakananByJenis() {
        string jenisTarget;
        cout << "\n=== Pencarian Makanan Berdasarkan Jenis (Linear Search) ===\n";
        cout << "Jenis makanan tersedia: Ayam, Martabak, Bakso, Mie, Bebek\n";
        cout << "Masukkan jenis makanan: ";
        cin >> jenisTarget;

        DataMakanan hasil[18];
        int jumlahHasil = 0;

        for (int i = 0; i < jumlahMakanan; i++) {
            if (daftarMakanan[i].jenis == jenisTarget) {
                hasil[jumlahHasil] = daftarMakanan[i];
                jumlahHasil++;
            }
        }

        if (jumlahHasil > 0) {
            cout << "\n=== Makanan Jenis " << jenisTarget << " ===\n";
            for (int i = 0; i < jumlahHasil; i++) {
                cout << i + 1 << ". " << hasil[i].nama
                     << " - Rp " << hasil[i].harga
                     << " (" << hasil[i].restoran << ")" << endl;
            }
        } else {
            cout << "Tidak ada makanan dengan jenis " << jenisTarget << ".\n";
        }
    }
};

class Toko {
private:
    Menutoko menu;
    RiwayatPesanan riwayat;

    struct OrderData {
        string nama;
        int harga;
        string restoran;
    };

    static const int MAX_UNDO = 5;
    string undoStack[MAX_UNDO];
    int topUndo;
    int countUndo;

    static const int MAX_CANCEL_HISTORY = 100;
    OrderData cancelHistory[MAX_CANCEL_HISTORY];
    int cancelCount;

    int lastSyncedPesanan;

public:
    Toko() {
        topUndo = -1;
        countUndo = 0;
        cancelCount = 0;
        lastSyncedPesanan = 0;
    }

    void shortingHarga() {
        if (menu.jumlahpesanan == 0) {
            cout << "Belum ada pesanan untuk disorting.\n";
            return;
        }

        int urutan;
        cout << "\n=== Sorting Harga Menu ===\n";
        cout << "1. Harga Terendah ke Tertinggi\n";
        cout << "2. Harga Tertinggi ke Terendah\n";
        cout << "Pilih urutan (1/2): ";
        cin >> urutan;

        for (int i = 0; i < menu.jumlahpesanan - 1; i++) {
            for (int j = 0; j < menu.jumlahpesanan - i - 1; j++) {
                if ((urutan == 1 && menu.harga[j] > menu.harga[j + 1]) ||
                    (urutan == 2 && menu.harga[j] < menu.harga[j + 1])) {
                    int tempHarga = menu.harga[j];
                    menu.harga[j] = menu.harga[j + 1];
                    menu.harga[j + 1] = tempHarga;

                    string tempPesanan = menu.pesanan[j];
                    menu.pesanan[j] = menu.pesanan[j + 1];
                    menu.pesanan[j + 1] = tempPesanan;
                }
            }
        }

        cout << "\n=== Menu Setelah Disorting ===\n";
        for (int i = 0; i < menu.jumlahpesanan; i++) {
            cout << i + 1 << ". " << menu.pesanan[i] << " - Rp " << menu.harga[i] << endl;
        }
    }

    void kembaliKeMenu() {
        cout << "\nTekan Enter untuk kembali ke menu utama...";
        cin.ignore();
        cin.get();
        pilihsearchingdantoko();
    }

    void tampilkanRingkasanPesanan() {
        cout << "\nDaftar Pesanan:\n";
        for (int i = 0; i < menu.jumlahpesanan; i++) {
            cout << i + 1 << ". " << menu.pesanan[i] << " - Rp " << menu.harga[i] << endl;
        }
        int total = 0;
        for (int i = 0; i < menu.jumlahpesanan; i++) {
            total += menu.harga[i];
        }
        cout << "Total: Rp " << total << endl;
    }

    void pilihsearchingdantoko() {
        int pilihan;

        system("cls");
        cout << "=== Menu Searching ===\n";
        cout << "1. Cari Berdasarkan Jenis Makanan\n";
        cout << "2. Pilih Berdasarkan Toko\n";
        cout << "3. Cari Berdasarkan Rating (Binary Search)\n";
        cout << "4. Cari Berdasarkan Harga (Linear Search)\n";
        cout << "5. Cari Berdasarkan Jenis (Linear Search)\n";
        cout << "Masukan pilihan (1-5): ";
        cin >> pilihan;
        while (pilihan < 1 || pilihan > 5) {
            cout << "Masukan pilihan (1-5): ";
            cin >> pilihan;
        }

        if (pilihan == 1) {
            cout << endl;
            searchingmakanan();
        } else if (pilihan == 2) {
            cout << endl;
            menampilkanmenu();
        } else if (pilihan == 3) {
            PesananRating ratingSearch;
            ratingSearch.cariRestoranByRating();
        } else if (pilihan == 4) {
            PesananHarga hargaSearch;
            hargaSearch.cariMakananByHarga();
        } else if (pilihan == 5) {
            PesananJenis jenisSearch;
            jenisSearch.cariMakananByJenis();
        } else {
            cout << "Pilihan anda tidak ada!!" << endl;
        }
    }

    void searchingmakanan() {
        cout << "\n=== Cari Berdasarkan Jenis Makanan ===\n";
        cout << "1. Tampilkan Semua Makanan (Urut berdasarkan harga)\n";
        cout << "2. Cari Berdasarkan Jenis (Urut berdasarkan harga)\n";
        cout << "3. Ayam\n";
        cout << "4. Martabak\n";
        cout << "5. Bakso\n";
        cout << "6. Mie\n";
        cout << "7. Bebek\n";
        cout << "8. Pecel\n";
        cout << "Pilih menu: ";
        cin >> menu.pilihsearching;
        cout << endl;

        if (menu.pilihsearching == 1) {
            FoodLinkedList foodList;
            foodList.tambahMakanan("Ayam Geprek", 18000, "Ayam", "Ayam Geprek Bangjo");
            foodList.tambahMakanan("Ayam Geprek Keju", 22000, "Ayam", "Ayam Geprek Bangjo");
            foodList.tambahMakanan("Ayam Geprek Sambel Korek", 19000, "Ayam", "Ayam Geprek Sambal Korek");
            foodList.tambahMakanan("Ayam Geprek Original", 17000, "Ayam", "Ayam Geprek Sambal Korek");
            foodList.tambahMakanan("Martabak Manis", 25000, "Martabak", "Martabak Legend");
            foodList.tambahMakanan("Martabak Telur", 30000, "Martabak", "Martabak Legend");
            foodList.tambahMakanan("Martabak Cokelat Keju", 26000, "Martabak", "Martabak Bangka 77");
            foodList.tambahMakanan("Martabak Telur Spesial", 32000, "Martabak", "Martabak Bangka 77");
            foodList.tambahMakanan("Bakso Urat", 25000, "Bakso", "Bakso Pak Kumis");
            foodList.tambahMakanan("Mie Ayam", 20000, "Bakso", "Bakso Pak Kumis");
            foodList.tambahMakanan("Bakso Beranak", 28000, "Bakso", "Bakso Beranak Jaya");
            foodList.tambahMakanan("Bakso Mercon", 25000, "Bakso", "Bakso Beranak Jaya");
            foodList.tambahMakanan("Mie Hompimpa", 17000, "Mie", "Mie Gacoan");
            foodList.tambahMakanan("Mie Suit", 17000, "Mie", "Mie Gacoan");
            foodList.tambahMakanan("Mie Badai Level 3", 18000, "Mie", "Mie Pedas Badai");
            foodList.tambahMakanan("Mie Goreng Pedas", 16000, "Mie", "Mie Pedas Badai");
            foodList.tambahMakanan("Bebek Goreng Original", 30000, "Bebek", "Bebek Goreng Haji Slamet");
            foodList.tambahMakanan("Bebek Bakar", 32000, "Bebek", "Bebek Goreng Haji Slamet");

            foodList.tampilkanSemuaMakanan();
            cout << "\nTekan Enter untuk kembali ke menu searching...";
            cin.ignore();
            cin.get();
            pilihsearchingdantoko();
            return;
        }

        if (menu.pilihsearching == 2) {
            FoodLinkedList foodList;
            foodList.tambahMakanan("Ayam Geprek", 18000, "Ayam", "Ayam Geprek Bangjo");
            foodList.tambahMakanan("Ayam Geprek Keju", 22000, "Ayam", "Ayam Geprek Bangjo");
            foodList.tambahMakanan("Ayam Geprek Sambel Korek", 19000, "Ayam", "Ayam Geprek Sambal Korek");
            foodList.tambahMakanan("Ayam Geprek Original", 17000, "Ayam", "Ayam Geprek Sambal Korek");
            foodList.tambahMakanan("Martabak Manis", 25000, "Martabak", "Martabak Legend");
            foodList.tambahMakanan("Martabak Telur", 30000, "Martabak", "Martabak Legend");
            foodList.tambahMakanan("Martabak Cokelat Keju", 26000, "Martabak", "Martabak Bangka 77");
            foodList.tambahMakanan("Martabak Telur Spesial", 32000, "Martabak", "Martabak Bangka 77");
            foodList.tambahMakanan("Bakso Urat", 25000, "Bakso", "Bakso Pak Kumis");
            foodList.tambahMakanan("Mie Ayam", 20000, "Bakso", "Bakso Pak Kumis");
            foodList.tambahMakanan("Bakso Beranak", 28000, "Bakso", "Bakso Beranak Jaya");
            foodList.tambahMakanan("Bakso Mercon", 25000, "Bakso", "Bakso Beranak Jaya");
            foodList.tambahMakanan("Mie Hompimpa", 17000, "Mie", "Mie Gacoan");
            foodList.tambahMakanan("Mie Suit", 17000, "Mie", "Mie Gacoan");
            foodList.tambahMakanan("Mie Badai Level 3", 18000, "Mie", "Mie Pedas Badai");
            foodList.tambahMakanan("Mie Goreng Pedas", 16000, "Mie", "Mie Pedas Badai");
            foodList.tambahMakanan("Bebek Goreng Original", 30000, "Bebek", "Bebek Goreng Haji Slamet");
            foodList.tambahMakanan("Bebek Bakar", 32000, "Bebek", "Bebek Goreng Haji Slamet");

            string jenisTarget;
            cout << "\nJenis makanan tersedia: Ayam, Martabak, Bakso, Mie, Bebek\n";
            cout << "Masukkan jenis makanan: ";
            cin >> jenisTarget;

            foodList.tampilkanBerdasarkanJenis(jenisTarget);
            cout << "\nTekan Enter untuk kembali ke menu searching...";
            cin.ignore();
            cin.get();
            pilihsearchingdantoko();
            return;
        }

        if (menu.pilihsearching == 3) {
            cout << "Toko dengan menu Ayam:\n";
            cout << "1. Ayam Geprek Bangjo\n";
            cout << "2. ayam Gebrek Sambal Korek\n";
            cout << "Pilih menu: ";
            cin >> menu.pilihmenu;

            switch (menu.pilihmenu) {
                case 1: {
                    cout << "Anda memilih Ayam Geprek Bangjo\n";
                    ifstream file(MENU_DIR "ayamgeprekbangjo.txt");
                    string baris;

                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;

                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Ayam Geprek";
                                menu.harga[menu.jumlahpesanan] = 18000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Ayam Geprek Keju";
                                menu.harga[menu.jumlahpesanan] = 22000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Teh";
                                menu.harga[menu.jumlahpesanan] = 5000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Es Jeruk";
                                menu.harga[menu.jumlahpesanan] = 7000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }

                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;
                        pushCircular(menu.pesanan[menu.jumlahpesanan - 1]);

                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;

                    } while (menu.lagi == 'y' || menu.lagi == 'Y');

                    break;
                }

                case 2: {
                    cout << "Anda memilih Ayam Geprek Sambel Korek\n";
                    ifstream file2(MENU_DIR "ayamgepreksambelkorek.txt");
                    string baris2;

                    if (!file2.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file2, baris2)) {
                            cout << baris2 << endl;
                        }
                        file2.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;

                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Ayam Geprek Sambel Korek";
                                menu.harga[menu.jumlahpesanan] = 19000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Ayam Geprek Original";
                                menu.harga[menu.jumlahpesanan] = 17000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Teh Manis";
                                menu.harga[menu.jumlahpesanan] = 5000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Air Mineral";
                                menu.harga[menu.jumlahpesanan] = 4000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }

                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;
                        pushCircular(menu.pesanan[menu.jumlahpesanan - 1]);

                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;

                    } while (menu.lagi == 'y' || menu.lagi == 'Y');

                    break;
                }

                default:
                    cout << "Pilihan tidak ada pada daftar menu.\n";
                    break;
            }

            return;
        }

        if (menu.pilihsearching == 2) {
            cout << "Toko dengan menu Martabak:\n";
            cout << "1. Martabak Legend\n";
            cout << "2. Martabak Bangka 77\n";
            cout << "Pilih menu: ";
            cin >> menu.pilihmenu;

            switch (menu.pilihmenu) {
                case 1: {
                    cout << "Anda memilih Martabak Legend\n";
                    ifstream file(MENU_DIR "martabaklegend.txt");
                    string baris;
                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;
                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Martabak Manis";
                                menu.harga[menu.jumlahpesanan] = 25000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Martabak Telur";
                                menu.harga[menu.jumlahpesanan] = 30000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Teh Botol";
                                menu.harga[menu.jumlahpesanan] = 6000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Es Jeruk";
                                menu.harga[menu.jumlahpesanan] = 8000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;
                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;
                    } while (menu.lagi == 'y' || menu.lagi == 'Y');
                    break;
                }

                case 2: {
                    cout << "Anda memilih Martabak Bangka 77\n";
                    ifstream file2(MENU_DIR "martabakbangka77.txt");
                    string baris;
                    if (!file2.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file2, baris)) {
                            cout << baris << endl;
                        }
                        file2.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;
                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Martabak Cokelat Keju";
                                menu.harga[menu.jumlahpesanan] = 26000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Martabak Telur Spesial";
                                menu.harga[menu.jumlahpesanan] = 32000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Teh Tarik";
                                menu.harga[menu.jumlahpesanan] = 7000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Susu Jahe Panas";
                                menu.harga[menu.jumlahpesanan] = 8000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;
                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;
                    } while (menu.lagi == 'y' || menu.lagi == 'Y');
                    break;
                }

                default:
                    cout << "Pilihan tidak ada pada daftar menu.\n";
                    break;
            }
            return;
        }

        if (menu.pilihsearching == 3) {
            cout << "Toko dengan menu Bakso:\n";
            cout << "1. Bakso Pak Kumis\n";
            cout << "2. Bakso Beranak Jaya\n";
            cout << "Pilih menu: ";
            cin >> menu.pilihmenu;

            switch (menu.pilihmenu) {
                case 1: {
                    cout << "Anda memilih Bakso Pak Kumis\n";
                    ifstream file(MENU_DIR "baksopakkumis.txt");
                    string baris;
                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;
                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Bakso Urat";
                                menu.harga[menu.jumlahpesanan] = 25000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Mie Ayam";
                                menu.harga[menu.jumlahpesanan] = 20000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Cendol";
                                menu.harga[menu.jumlahpesanan] = 12000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Wedang Jahe";
                                menu.harga[menu.jumlahpesanan] = 8000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;
                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;
                    } while (menu.lagi == 'y' || menu.lagi == 'Y');
                    break;
                }

                case 2: {
                    cout << "Anda memilih Bakso Beranak Jaya\n";
                    ifstream file(MENU_DIR "baksoberanakjaya.txt");
                    string baris;
                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;
                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Bakso Beranak";
                                menu.harga[menu.jumlahpesanan] = 28000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Bakso Mercon";
                                menu.harga[menu.jumlahpesanan] = 25000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Jeruk";
                                menu.harga[menu.jumlahpesanan] = 6000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Es Cincau";
                                menu.harga[menu.jumlahpesanan] = 7000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;
                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;
                    } while (menu.lagi == 'y' || menu.lagi == 'Y');
                    break;
                }

                default:
                    cout << "Pilihan tidak ada pada daftar menu.\n";
                    break;
            }
            return;
        }

        if (menu.pilihsearching == 4) {
            cout << "Toko dengan menu Mie:\n";
            cout << "1. Mie Gacoan\n";
            cout << "2. Mie Pedas Badai\n";
            cout << "Pilih menu: ";
            cin >> menu.pilihmenu;

            switch (menu.pilihmenu) {
                case 1: {
                    cout << "Anda memilih Mie Gacoan\n";
                    ifstream file(MENU_DIR "miegacoan.txt");
                    string baris;
                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;
                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Mie Hompimpa";
                                menu.harga[menu.jumlahpesanan] = 17000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Mie Suit";
                                menu.harga[menu.jumlahpesanan] = 17000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Genderuwo";
                                menu.harga[menu.jumlahpesanan] = 10000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Es Tuyul";
                                menu.harga[menu.jumlahpesanan] = 8000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;
                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;
                    } while (menu.lagi == 'y' || menu.lagi == 'Y');
                    break;
                }

                case 2: {
                    cout << "Anda memilih Mie Pedas Badai\n";
                    ifstream file(MENU_DIR "miepedasbadai.txt");
                    string baris;
                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;
                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Mie Badai Level 3";
                                menu.harga[menu.jumlahpesanan] = 18000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Mie Goreng Pedas";
                                menu.harga[menu.jumlahpesanan] = 16000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Susu Lava";
                                menu.harga[menu.jumlahpesanan] = 9000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Air Mineral";
                                menu.harga[menu.jumlahpesanan] = 4000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;
                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;
                    } while (menu.lagi == 'y' || menu.lagi == 'Y');
                    break;
                }

                default:
                    cout << "Pilihan tidak ada pada daftar menu.\n";
                    break;
            }
            return;
        }

        if (menu.pilihsearching == 5) {
            cout << "Toko dengan menu Bebek:\n";
            cout << "1. Bebek Goreng Haji Slamet\n";
            cout << "2. Bebek Madura Sambal Hitam\n";
            cout << "Pilih menu: ";
            cin >> menu.pilihmenu;

            switch (menu.pilihmenu) {
                case 1: {
                    cout << "Anda memilih Bebek Goreng Haji Slamet\n";
                    ifstream file(MENU_DIR "bebekgorenghaji.txt");
                    string baris;

                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;

                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Bebek Goreng Original";
                                menu.harga[menu.jumlahpesanan] = 30000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Bebek Bakar";
                                menu.harga[menu.jumlahpesanan] = 32000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Teh Manis";
                                menu.harga[menu.jumlahpesanan] = 5000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Es Kelapa";
                                menu.harga[menu.jumlahpesanan] = 10000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }

                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;

                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;

                    } while (menu.lagi == 'y' || menu.lagi == 'Y');

                    break;
                }

                case 2: {
                    cout << "Anda memilih Bebek Madura Sambal Hitam\n";
                    ifstream file(MENU_DIR "bebekmadura.txt");
                    string baris;
                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;

                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Bebek Sambal Hitam";
                                menu.harga[menu.jumlahpesanan] = 31000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Bebek Kremes";
                                menu.harga[menu.jumlahpesanan] = 32000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Kelapa Muda";
                                menu.harga[menu.jumlahpesanan] = 10000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Air Putih";
                                menu.harga[menu.jumlahpesanan] = 3000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;

                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;
                    } while (menu.lagi == 'y' || menu.lagi == 'Y');
                    break;
                }

                default:
                    cout << "Pilihan tidak ada pada daftar menu.\n";
                    break;
            }
            return;
        }

        if (menu.pilihsearching == 6) {
            cout << "Toko dengan menu Pecel:\n";
            cout << "1. Pecel Mbok Darmi\n";
            cout << "2. Pecel Lele Malam 88\n";
            cout << "Pilih menu: ";
            cin >> menu.pilihmenu;

            switch (menu.pilihmenu) {
                case 1: {
                    cout << "Anda memilih Pecel Mbok Darmi\n";
                    ifstream file(MENU_DIR "pecelmbokdarmi.txt");
                    string baris;

                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;

                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Pecel Lele";
                                menu.harga[menu.jumlahpesanan] = 17000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Pecel Ayam";
                                menu.harga[menu.jumlahpesanan] = 18000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Campur";
                                menu.harga[menu.jumlahpesanan] = 12000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Es Dawet";
                                menu.harga[menu.jumlahpesanan] = 8000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;

                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;

                    } while (menu.lagi == 'y' || menu.lagi == 'Y');

                    break;
                }

                case 2: {
                    cout << "Anda memilih Pecel Lele Malam 88\n";
                    ifstream file(MENU_DIR "pecellelemalam88.txt");
                    string baris;
                    if (!file.is_open()) {
                        cerr << "File tidak ditemukan!" << endl;
                    } else {
                        while (getline(file, baris)) {
                            cout << baris << endl;
                        }
                        file.close();
                    }

                    do {
                        cout << "Pilih menu: ";
                        cin >> menu.isimenu;
                        switch (menu.isimenu) {
                            case 1:
                                menu.pesanan[menu.jumlahpesanan] = "Pecel Lele Jumbo";
                                menu.harga[menu.jumlahpesanan] = 19000;
                                break;
                            case 2:
                                menu.pesanan[menu.jumlahpesanan] = "Tahu Tempe Pecel";
                                menu.harga[menu.jumlahpesanan] = 15000;
                                break;
                            case 3:
                                menu.pesanan[menu.jumlahpesanan] = "Es Campur Segar";
                                menu.harga[menu.jumlahpesanan] = 12000;
                                break;
                            case 4:
                                menu.pesanan[menu.jumlahpesanan] = "Teh Hangat";
                                menu.harga[menu.jumlahpesanan] = 4000;
                                break;
                            default:
                                cout << "Pilihan tidak ada pada daftar menu.\n";
                                continue;
                        }
                        cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                        menu.jumlahpesanan++;

                        cout << "Ingin menambah menu lagi? (y/n): ";
                        cin >> menu.lagi;
                    } while (menu.lagi == 'y' || menu.lagi == 'Y');
                    break;
                }

                default:
                    cout << "Pilihan tidak ada pada daftar menu.\n";
                    break;
            }
            return;
        }
    }

    void pilihantoko() {
        int pilihan;

        do {
            cout << "=== Pilih Toko ===\n";
            cout << "1. Bakso Pak Kumis\n";
            cout << "2. Warung Padang\n";
            cout << "3. Sushime\n";
            cout << "4. Cafe Paris\n";
            cout << "5. Warung Sunda\n";
            cout << "6. Ayam Geprek bangjo\n";
            cout << "7. Martabak Legend\n";
            cout << "8. Nasi Goreng Maju Mundur\n";
            cout << "9. Bebek Goreng Haji\n";
            cout << "10. Mie Gacoan\n";
            cout << "11. Pecel Mbok Darmi\n";
            cout << "12. Steak House Premiun\n";
            cout << "Masukan pilihan toko (1-12): ";
            cin >> pilihan;
        } while (pilihan < 1 || pilihan > 12);

        if (pilihan == 1) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Bakso Pak Kumis\n";
            ifstream file(MENU_DIR "baksopakkumis.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            } else {
                while (getline(file, baris)) {
                    cout << baris << endl;
                }
                file.close();
            }

            do {
                cout << "\nPilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Bakso Urat";
                        menu.harga[menu.jumlahpesanan] = 25000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Mie Ayam";
                        menu.harga[menu.jumlahpesanan] = 20000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Es Cendol";
                        menu.harga[menu.jumlahpesanan] = 5000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Tahu Tempe";
                        menu.harga[menu.jumlahpesanan] = 8000;
                        break;
                    default:
                        cout << "Menu tidak tersedia.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 2) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Warung Padang\n";
            ifstream file(MENU_DIR "warungpadang.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            } else {
                while (getline(file, baris)) {
                    cout << baris << endl;
                }
                file.close();
            }

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Rendang";
                        menu.harga[menu.jumlahpesanan] = 35000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Sate Padang";
                        menu.harga[menu.jumlahpesanan] = 30000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Es Teh Tarek";
                        menu.harga[menu.jumlahpesanan] = 10000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Jus Alpukat";
                        menu.harga[menu.jumlahpesanan] = 15000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 3) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Sushime\n";
            ifstream file(MENU_DIR "sushiexpress.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Sushi Roll";
                        menu.harga[menu.jumlahpesanan] = 45000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Ramen";
                        menu.harga[menu.jumlahpesanan] = 40000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Matcha Latte";
                        menu.harga[menu.jumlahpesanan] = 20000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Sakura Tea";
                        menu.harga[menu.jumlahpesanan] = 10000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        continue;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 4) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Cafe Paris\n";
            ifstream file(MENU_DIR "cafeparis.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Croissant";
                        menu.harga[menu.jumlahpesanan] = 35000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Quiche Lorraine";
                        menu.harga[menu.jumlahpesanan] = 50000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Espresso";
                        menu.harga[menu.jumlahpesanan] = 25000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Cafe Latte";
                        menu.harga[menu.jumlahpesanan] = 30000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 5) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Warung Sunda\n";
            ifstream file(MENU_DIR "warungsunda.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Nasi Timbel";
                        menu.harga[menu.jumlahpesanan] = 30000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Karedok";
                        menu.harga[menu.jumlahpesanan] = 20000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Es Cincau";
                        menu.harga[menu.jumlahpesanan] = 10000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Bajigur";
                        menu.harga[menu.jumlahpesanan] = 12000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 6) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Ayam Geprek Bangjo\n";
            ifstream file(MENU_DIR "ayamgeprekbangjo.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Ayam Geprek";
                        menu.harga[menu.jumlahpesanan] = 18000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Ayam Geprek Keju";
                        menu.harga[menu.jumlahpesanan] = 22000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Es Teh";
                        menu.harga[menu.jumlahpesanan] = 5000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Es Jeruk";
                        menu.harga[menu.jumlahpesanan] = 7000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 7) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Martabak Legend\n";
            ifstream file(MENU_DIR "martabaklegend.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Martabak Manis";
                        menu.harga[menu.jumlahpesanan] = 25000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Martabak Telur";
                        menu.harga[menu.jumlahpesanan] = 30000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Teh Botol";
                        menu.harga[menu.jumlahpesanan] = 6000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Es Jeruk";
                        menu.harga[menu.jumlahpesanan] = 8000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        continue;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 8) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Nasi Goreng Maju Mundur\n";
            ifstream file(MENU_DIR "nasigorengmajumundur.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Nasi Goreng Spesial";
                        menu.harga[menu.jumlahpesanan] = 25000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Nasi Goreng Pete";
                        menu.harga[menu.jumlahpesanan] = 22000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Kopi Hitam";
                        menu.harga[menu.jumlahpesanan] = 7000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Teh Tarik";
                        menu.harga[menu.jumlahpesanan] = 10000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 9) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Bebek Goreng Haji\n";
            ifstream file(MENU_DIR "bebekgorenghaji.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Bebek Goreng Original";
                        menu.harga[menu.jumlahpesanan] = 30000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Bebek Bakar";
                        menu.harga[menu.jumlahpesanan] = 32000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Es Teh Manis";
                        menu.harga[menu.jumlahpesanan] = 5000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Es Kelapa";
                        menu.harga[menu.jumlahpesanan] = 10000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 10) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Mie Gacoan\n";
            ifstream file(MENU_DIR "miegacoan.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Mie Hompimpa";
                        menu.harga[menu.jumlahpesanan] = 17000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Mie Suit";
                        menu.harga[menu.jumlahpesanan] = 17000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Es Genderuwo";
                        menu.harga[menu.jumlahpesanan] = 10000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Es Tuyul";
                        menu.harga[menu.jumlahpesanan] = 8000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 11) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Pecel Mbok Darmi\n";
            ifstream file(MENU_DIR "pecelmbokdarmi.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Pecel Lele";
                        menu.harga[menu.jumlahpesanan] = 17000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Pecel Ayam";
                        menu.harga[menu.jumlahpesanan] = 18000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Es Campur";
                        menu.harga[menu.jumlahpesanan] = 12000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Es Dawet";
                        menu.harga[menu.jumlahpesanan] = 8000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        } else if (pilihan == 12) {
            system("timeout /t 2");
            system("cls");
            cout << "Anda memilih Steak House Premium\n";
            ifstream file(MENU_DIR "steakhousepremium.txt");
            string baris;

            if (!file.is_open()) {
                cerr << "File tidak ditemukan!" << endl;
            }
            while (getline(file, baris)) {
                cout << baris << endl;
            }
            file.close();

            do {
                cout << "Pilih menu: ";
                cin >> menu.isimenu;

                switch (menu.isimenu) {
                    case 1:
                        menu.pesanan[menu.jumlahpesanan] = "Beef Steak";
                        menu.harga[menu.jumlahpesanan] = 55000;
                        break;
                    case 2:
                        menu.pesanan[menu.jumlahpesanan] = "Chicken Steak";
                        menu.harga[menu.jumlahpesanan] = 45000;
                        break;
                    case 3:
                        menu.pesanan[menu.jumlahpesanan] = "Red Wine Mocktail";
                        menu.harga[menu.jumlahpesanan] = 25000;
                        break;
                    case 4:
                        menu.pesanan[menu.jumlahpesanan] = "Lemon Tea";
                        menu.harga[menu.jumlahpesanan] = 12000;
                        break;
                    default:
                        cout << "Pilihan tidak ada pada daftar menu.\n";
                        break;
                }

                cout << menu.pesanan[menu.jumlahpesanan] << " ditambahkan ke pesanan.\n";
                menu.jumlahpesanan++;

                cout << "Ingin menambah menu lagi? (y/n): ";
                cin >> menu.lagi;

            } while (menu.lagi == 'y' || menu.lagi == 'Y');
        }
    }

    void menampilkanmenu() {
        pilihantoko();
        syncNewOrders();

        int total = 0;
        cout << "\n=== Pesanan Anda ===\n";
        for (int i = 0; i < menu.jumlahpesanan; i++) {
            cout << i + 1 << ". " << menu.pesanan[i] << " - Rp " << menu.harga[i] << endl;
            total = total + menu.harga[i];
        }
        cout << "Total harga: Rp " << total << endl;

        char undoChoice;
        cout << "\nIngin membatalkan pesanan terakhir? (y/n): ";
        cin >> undoChoice;
        if (undoChoice == 'y' || undoChoice == 'Y') {
            if (undoLastOrder()) {
                cout << "\n=== Pesanan Setelah Pembatalan ===\n";
                int total2 = 0;
                for (int i = 0; i < menu.jumlahpesanan; ++i) {
                    cout << i + 1 << ". " << menu.pesanan[i] << " - Rp " << menu.harga[i] << endl;
                    total2 += menu.harga[i];
                }
                cout << "Total harga: Rp " << total2 << endl;
            }
        }
    }

    void syncNewOrders() {
        for (int i = lastSyncedPesanan; i < menu.jumlahpesanan; ++i) {
            pushCircular(menu.pesanan[i]);
        }
        lastSyncedPesanan = menu.jumlahpesanan;
    }

    bool isEmpty() { return countUndo == 0; }

    void pushCircular(const string& item) {
        topUndo = (topUndo + 1) % MAX_UNDO;
        undoStack[topUndo] = item;
        if (countUndo < MAX_UNDO) countUndo++;
    }

    string popCircular() {
        if (isEmpty()) return "";
        string item = undoStack[topUndo];
        if (topUndo == 0) topUndo = MAX_UNDO - 1;
        else topUndo = topUndo - 1;
        countUndo--;
        if (countUndo == 0) topUndo = -1;
        return item;
    }

    void displayCircular() {
        cout << "\n=== Isi Circular Stack (Undo - nama pesanan) ===\n";
        if (isEmpty()) {
            cout << "(Kosong)\n";
            return;
        }
        int idx = topUndo;
        for (int i = 0; i < countUndo; ++i) {
            cout << i + 1 << ". " << undoStack[idx] << "\n";
            if (idx == 0) idx = MAX_UNDO - 1;
            else idx = idx - 1;
        }
    }

    void displayCancelHistory() {
        cout << "\n=== Riwayat Pembatalan ===\n";
        if (cancelCount == 0) {
            cout << "(Belum ada pembatalan)\n";
            return;
        }
        for (int i = 0; i < cancelCount; ++i) {
            cout << i + 1 << ". " << cancelHistory[i].nama << " - Rp " << cancelHistory[i].harga << "\n";
        }
    }

    bool undoLastOrder() {
        string poppedName = popCircular();
        if (poppedName == "") {
            cout << "Tidak ada pesanan untuk dibatalkan.\n";
            return false;
        }

        if (menu.jumlahpesanan <= 0) {
            cout << "Tidak ada pesanan aktif untuk dibatalkan.\n";
            return false;
        }

        int idx = menu.jumlahpesanan - 1;
        string lastName = menu.pesanan[idx];
        int lastPrice = menu.harga[idx];

        menu.jumlahpesanan--;
        menu.pesanan[menu.jumlahpesanan].clear();
        menu.harga[menu.jumlahpesanan] = 0;

        if (cancelCount < MAX_CANCEL_HISTORY) {
            OrderData od;
            od.nama = lastName;
            od.harga = lastPrice;
            od.restoran = "";
            cancelHistory[cancelCount++] = od;
        }

        lastSyncedPesanan = menu.jumlahpesanan;
        cout << "Pesanan dibatalkan: " << lastName << " - Rp " << lastPrice << endl;
        return true;
    }

    void commitOrdersToHistory() {
        for (int i = 0; i < menu.jumlahpesanan; ++i) {
            riwayat.tambahRiwayat(menu.pesanan[i], menu.harga[i], "", "tanggal");
        }
        for (int i = 0; i < menu.jumlahpesanan; ++i) {
            menu.pesanan[i].clear();
            menu.harga[i] = 0;
        }
        menu.jumlahpesanan = 0;
        topUndo = -1;
        countUndo = 0;
        lastSyncedPesanan = 0;
        cout << "Pesanan dipindahkan ke riwayat.\n";
    }

    int gettotalharga() {
        int total = 0;
        for (int i = 0; i < menu.jumlahpesanan; i++) {
            total += menu.harga[i];
        }
        return total;
    }

    void menuLayananMakanan() {
        int pilihan;
        do {
            cout << "\n=== LAYANAN MAKANAN ===\n";
            cout << "1. Buat Pesanan\n";
            cout << "2. Menu Searching\n";
            cout << "3. Batalkan Pesanan Terakhir (Undo - Circular Stack)\n";
            cout << "4. Lihat Riwayat Pembatalan\n";
            cout << "5. Kembali\n";
            cout << "Pilih: ";
            cin >> pilihan;
            cin.ignore();

            switch (pilihan) {
                case 1:
                    pilihsearchingdantoko();
                    syncNewOrders();
                    menampilkanmenu();
                    break;
                case 2:
                    pilihsearchingdantoko();
                    syncNewOrders();
                    break;
                case 3:
                    undoLastOrder();
                    break;
                case 4:
                    displayCancelHistory();
                    break;
                case 5:
                    cout << "Kembali ke menu utama...\n";
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
            }
        } while (pilihan != 5);
    }
};

#endif
