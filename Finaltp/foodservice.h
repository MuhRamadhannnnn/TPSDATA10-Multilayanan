#ifndef FOODSERVICE_H
#define FOODSERVICE_H

#include <iostream>
#include <string>
#include <fstream>
#include "linkedlist.h"
#include "payment.h"
using namespace std;

// Struct untuk data restoran berdasarkan rating
struct Restoran {
    string nama;
    float rating;
    string jenismakanan;
};

// Struct untuk data makanan berdasarkan harga dan jenis
struct DataMakanan {
    string nama;
    int harga;
    string jenis;
    string restoran;
};

inline int isiMenuMakananMinuman(DataMakanan menu[], int maxMenu) {
    int n = 0;
    auto add = [&](const string& nama, int harga, const string& jenis, const string& restoran) {
        if (n >= maxMenu) return;
        menu[n].nama = nama;
        menu[n].harga = harga;
        menu[n].jenis = jenis;
        menu[n].restoran = restoran;
        n++;
    };

    // Makanan
    add("Ayam Geprek", 18000, "Ayam", "Ayam Geprek Bangjo");
    add("Ayam Geprek Keju", 22000, "Ayam", "Ayam Geprek Bangjo");
    add("Ayam Geprek Sambal Korek", 20000, "Ayam", "Ayam Geprek Sambal Korek");
    add("Bakso Urat", 25000, "Bakso", "Bakso Pak Kumis");
    add("Bakso Beranak", 28000, "Bakso", "Bakso Beranak Jaya");
    add("Mie Hompimpa", 17000, "Mie", "Mie Gacoan");
    add("Mie Pedas", 19000, "Mie", "Mie Pedas Badai");
    add("Martabak Manis", 25000, "Martabak", "Martabak Legend");
    add("Martabak Telur", 27000, "Martabak", "Martabak Bangka 77");
    add("Bebek Goreng Original", 30000, "Bebek", "Bebek Goreng Haji Slamet");
    add("Bebek Sambal Hitam", 32000, "Bebek", "Bebek Madura Sambal Hitam");

    // Minuman
    add("Es Teh", 5000, "Minuman", "Ayam Geprek Bangjo");
    add("Es Jeruk", 7000, "Minuman", "Martabak Legend");
    add("Kopi", 10000, "Minuman", "Mie Gacoan");
    add("Air Mineral", 4000, "Minuman", "Bakso Pak Kumis");

    return n;
}

inline void tampilkanMenuMakananMinuman(const DataMakanan menu[], int jumlahMenu) {
    if (jumlahMenu <= 0) {
        cout << "Tidak ada menu tersedia.\n";
        return;
    }

    cout << "\n=== DAFTAR MENU (MAKANAN & MINUMAN) ===\n";
    for (int i = 0; i < jumlahMenu; i++) {
        cout << i + 1 << ". " << menu[i].nama
             << " - Rp " << menu[i].harga
             << " (" << menu[i].restoran << ")"
             << " [" << menu[i].jenis << "]\n";
    }
}

inline void pesanDariDaftarMenu(OrderList& orderList, const DataMakanan menu[], int jumlahMenu) {
    tampilkanMenuMakananMinuman(menu, jumlahMenu);
    if (jumlahMenu <= 0) return;

    int nomor;
    cout << "\nPilih nomor menu untuk dipesan (0 batal): ";
    cin >> nomor;
    if (nomor <= 0 || nomor > jumlahMenu) return;

    int qty;
    cout << "Masukkan jumlah (qty): ";
    cin >> qty;

    const DataMakanan& item = menu[nomor - 1];
    orderList.tambahPesanan(item.nama, item.harga, item.restoran, qty);
    cout << "\n✓ Ditambahkan ke pesanan: " << item.nama << " x" << (qty < 1 ? 1 : qty) << "\n";
}

inline int filterMenuByHarga(const DataMakanan menu[], int jumlahMenu, int hargaMin, int hargaMax, DataMakanan out[], int outMax) {
    int n = 0;
    for (int i = 0; i < jumlahMenu && n < outMax; i++) {
        if (menu[i].harga >= hargaMin && menu[i].harga <= hargaMax) {
            out[n++] = menu[i];
        }
    }
    return n;
}

inline int filterMenuByRestoran(const DataMakanan menu[], int jumlahMenu, const string& restoranTarget, DataMakanan out[], int outMax) {
    int n = 0;
    for (int i = 0; i < jumlahMenu && n < outMax; i++) {
        if (menu[i].restoran == restoranTarget) {
            out[n++] = menu[i];
        }
    }
    return n;
}

inline int filterMenuByJenis(const DataMakanan menu[], int jumlahMenu, const string& jenisTarget, DataMakanan out[], int outMax) {
    int n = 0;
    for (int i = 0; i < jumlahMenu && n < outMax; i++) {
        if (menu[i].jenis == jenisTarget) {
            out[n++] = menu[i];
        }
    }
    return n;
}

inline bool restoranMasuk(const string& resto, const Restoran daftar[], int startIndex, int jumlahRestoran) {
    if (startIndex < 0) return false;
    for (int i = startIndex; i < jumlahRestoran; i++) {
        if (daftar[i].nama == resto) return true;
    }
    return false;
}

inline int filterMenuByRating(const DataMakanan menu[], int jumlahMenu, float ratingMin, DataMakanan out[], int outMax) {
    Restoran daftarRestoran[10];
    int jumlahRestoran = 10;

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

    // Sort asc by rating (bubble)
    for (int i = 0; i < jumlahRestoran - 1; i++) {
        for (int j = 0; j < jumlahRestoran - i - 1; j++) {
            if (daftarRestoran[j].rating > daftarRestoran[j + 1].rating) {
                Restoran temp = daftarRestoran[j];
                daftarRestoran[j] = daftarRestoran[j + 1];
                daftarRestoran[j + 1] = temp;
            }
        }
    }

    // Binary search first >= ratingMin
    int left = 0, right = jumlahRestoran - 1;
    int startIndex = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (daftarRestoran[mid].rating >= ratingMin) {
            startIndex = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (startIndex == -1) return 0;

    int n = 0;
    for (int i = 0; i < jumlahMenu && n < outMax; i++) {
        if (restoranMasuk(menu[i].restoran, daftarRestoran, startIndex, jumlahRestoran)) {
            out[n++] = menu[i];
        }
    }
    return n;
}

inline void tampilkanHasilDanPesan(OrderList& orderList, const DataMakanan hasil[], int jumlahHasil) {
    if (jumlahHasil <= 0) {
        cout << "Tidak ada menu yang cocok.\n";
        return;
    }

    cout << "\n=== HASIL PENCARIAN ===\n";
    for (int i = 0; i < jumlahHasil; i++) {
        cout << i + 1 << ". " << hasil[i].nama
             << " - Rp " << hasil[i].harga
             << " (" << hasil[i].restoran << ")"
             << " [" << hasil[i].jenis << "]\n";
    }

    int nomor;
    cout << "\nPilih nomor untuk dipesan (0 kembali): ";
    cin >> nomor;
    if (nomor <= 0 || nomor > jumlahHasil) return;

    int qty;
    cout << "Masukkan jumlah (qty): ";
    cin >> qty;

    const DataMakanan& item = hasil[nomor - 1];
    orderList.tambahPesanan(item.nama, item.harga, item.restoran, qty);
    cout << "\n✓ Ditambahkan ke pesanan: " << item.nama << " x" << (qty < 1 ? 1 : qty) << "\n";
}

// Class untuk pencarian berdasarkan rating menggunakan binary search
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

// Class untuk pencarian berdasarkan harga menggunakan linear search
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
        
        // ... Tambahkan data makanan lainnya sesuai kebutuhan
        daftarMakanan[2].nama = "Martabak Manis";
        daftarMakanan[2].harga = 25000;
        daftarMakanan[2].jenis = "Martabak";
        daftarMakanan[2].restoran = "Martabak Legend";
        
        daftarMakanan[3].nama = "Bakso Urat";
        daftarMakanan[3].harga = 25000;
        daftarMakanan[3].jenis = "Bakso";
        daftarMakanan[3].restoran = "Bakso Pak Kumis";
        
        daftarMakanan[4].nama = "Mie Hompimpa";
        daftarMakanan[4].harga = 17000;
        daftarMakanan[4].jenis = "Mie";
        daftarMakanan[4].restoran = "Mie Gacoan";
        
        daftarMakanan[5].nama = "Bebek Goreng Original";
        daftarMakanan[5].harga = 30000;
        daftarMakanan[5].jenis = "Bebek";
        daftarMakanan[5].restoran = "Bebek Goreng Haji Slamet";
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

// Class untuk pencarian berdasarkan jenis makanan
class PesananJenis {
private:
    DataMakanan daftarMakanan[18];
    int jumlahMakanan;
    
public:
    PesananJenis() {
        jumlahMakanan = 6;
        
        daftarMakanan[0].nama = "Ayam Geprek";
        daftarMakanan[0].harga = 18000;
        daftarMakanan[0].jenis = "Ayam";
        daftarMakanan[0].restoran = "Ayam Geprek Bangjo";
        
        daftarMakanan[1].nama = "Martabak Manis";
        daftarMakanan[1].harga = 25000;
        daftarMakanan[1].jenis = "Martabak";
        daftarMakanan[1].restoran = "Martabak Legend";
        
        daftarMakanan[2].nama = "Bakso Urat";
        daftarMakanan[2].harga = 25000;
        daftarMakanan[2].jenis = "Bakso";
        daftarMakanan[2].restoran = "Bakso Pak Kumis";
        
        daftarMakanan[3].nama = "Mie Hompimpa";
        daftarMakanan[3].harga = 17000;
        daftarMakanan[3].jenis = "Mie";
        daftarMakanan[3].restoran = "Mie Gacoan";
        
        daftarMakanan[4].nama = "Bebek Goreng Original";
        daftarMakanan[4].harga = 30000;
        daftarMakanan[4].jenis = "Bebek";
        daftarMakanan[4].restoran = "Bebek Goreng Haji Slamet";
        
        daftarMakanan[5].nama = "Ayam Geprek Keju";
        daftarMakanan[5].harga = 22000;
        daftarMakanan[5].jenis = "Ayam";
        daftarMakanan[5].restoran = "Ayam Geprek Bangjo";
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

// Fungsi untuk menampilkan menu layanan food + bisa pesan + bisa checkout
void menuSearchingMakanan(OrderList& orderList, RiwayatPesanan& riwayat, pembayaran& pay) {
    int pilihan;
    DataMakanan menu[30];
    int jumlahMenu = isiMenuMakananMinuman(menu, 30);
    
    do {
        cout << "\n=== Menu Searching Makanan ===\n";
        cout << "1. Cari Berdasarkan Jenis Makanan\n";
        cout << "2. Pilih Berdasarkan Toko\n";
        cout << "3. Cari Berdasarkan Rating (Binary Search)\n";
        cout << "4. Cari Berdasarkan Harga (Linear Search)\n";
        cout << "5. Cari Berdasarkan Jenis (Linear Search)\n";
        cout << "0. Kembali\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: {
                string jenisTarget;
                cout << "\n=== Pencarian Makanan Berdasarkan Jenis ===\n";
                cout << "Contoh jenis: Ayam, Martabak, Bakso, Mie, Bebek, Minuman\n";
                cout << "Masukkan jenis: ";
                cin >> jenisTarget;

                DataMakanan hasil[30];
                int jumlahHasil = filterMenuByJenis(menu, jumlahMenu, jenisTarget, hasil, 30);
                tampilkanHasilDanPesan(orderList, hasil, jumlahHasil);
                break;
            }
            case 2: {
                string restoranTarget;
                cout << "\n=== Pilih Berdasarkan Toko ===\n";
                cout << "Masukkan nama toko/restoran: ";
                cin.ignore();
                getline(cin, restoranTarget);

                DataMakanan hasil[30];
                int jumlahHasil = filterMenuByRestoran(menu, jumlahMenu, restoranTarget, hasil, 30);
                tampilkanHasilDanPesan(orderList, hasil, jumlahHasil);
                break;
            }
            case 3: {
                float targetRating;
                cout << "\n=== Pencarian Berdasarkan Rating ===\n";
                cout << "Masukkan rating minimum (1.0 - 5.0): ";
                cin >> targetRating;

                DataMakanan hasil[30];
                int jumlahHasil = filterMenuByRating(menu, jumlahMenu, targetRating, hasil, 30);
                tampilkanHasilDanPesan(orderList, hasil, jumlahHasil);
                break;
            }
            case 4: {
                int hargaMin, hargaMax;
                cout << "\n=== Pencarian Berdasarkan Harga ===\n";
                cout << "Masukkan harga minimum: Rp ";
                cin >> hargaMin;
                cout << "Masukkan harga maksimum: Rp ";
                cin >> hargaMax;

                DataMakanan hasil[30];
                int jumlahHasil = filterMenuByHarga(menu, jumlahMenu, hargaMin, hargaMax, hasil, 30);
                tampilkanHasilDanPesan(orderList, hasil, jumlahHasil);
                break;
            }
            case 5: {
                string jenisTarget;
                cout << "\n=== Pencarian Berdasarkan Jenis ===\n";
                cout << "Masukkan jenis: ";
                cin >> jenisTarget;

                DataMakanan hasil[30];
                int jumlahHasil = filterMenuByJenis(menu, jumlahMenu, jenisTarget, hasil, 30);
                tampilkanHasilDanPesan(orderList, hasil, jumlahHasil);
                break;
            }
            case 0:
                cout << "Kembali ke menu utama.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);
}

#endif
