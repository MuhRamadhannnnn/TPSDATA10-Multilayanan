#include <iostream>
#include <string>
#include <fstream>

// Include semua header files
#include "ktp.h"
#include "data.h"
#include "linkedlist.h"
#include "profile.h"
#include "toko_tp7.h"
#include "transport.h"
#include "payment.h"
#include "marketplace.h"
#include "shopping.h"

using namespace std;

// Fungsi untuk clear screen (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk pause/tunggu user
void pauseScreen() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

// Menu Profil
void menuProfil(Profil*& last) {
    int pilihanProfil;
    string nama, no_hp, alamatProfil, email;
    
    do {
        clearScreen();
        cout << "\n=== MENU DATA PROFIL ===\n";
        cout << "1. Tambah Data\n";
        cout << "2. Hapus Data\n";
        cout << "3. Update Data\n";
        cout << "4. Tampilkan Data\n";
        cout << "5. Kembali Ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilihanProfil;
        
        switch (pilihanProfil) {
            case 1:
                cout << "Masukkan Nama   : ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan No HP  : ";
                getline(cin, no_hp);
                cout << "Masukkan Alamat : ";
                getline(cin, alamatProfil);
                cout << "Masukkan Email  : ";
                getline(cin, email);
                last = addEnd(last, nama, no_hp, alamatProfil, email);
                cout << "Data berhasil ditambahkan!\n";
                pauseScreen();
                break;
                
            case 2:
                cout << "Masukkan Nama yang akan dihapus: ";
                cin.ignore();
                getline(cin, nama);
                deleteNode(&last, nama);
                pauseScreen();
                break;
                
            case 3:
                cout << "Masukkan Nama yang akan diupdate: ";
                cin.ignore();
                getline(cin, nama);
                updateNode(last, nama);
                pauseScreen();
                break;
                
            case 4:
                display(last);
                pauseScreen();
                break;
                
            case 5:
                cout << "Kembali ke menu utama.\n";
                break;
                
            default:
                cout << "Pilihan tidak valid.\n";
                pauseScreen();
        }
    } while (pilihanProfil != 5);
}

// Menu Layanan Makanan
void menuLayananMakanan() {
    static Toko toko;
    toko.menuLayananMakanan();
}

// Main function
int main() {
    MenuLogin loginSystem;
    Profil* profilList = NULL;
    
    // Proses login terlebih dahulu
    clearScreen();
    if (!loginSystem.tampilkanMenu()) {
        cout << "Program selesai.\n";
        return 0;
    }
    
    clearScreen();
    cout << "\n=== LOGIN BERHASIL ===\n";
    cout << "Selamat datang, " << loginSystem.getUsername() << "!\n";
    pauseScreen();
    
    // Menu utama setelah login
    int pilihan;
    bool exitProgram = false;
    
    while (!exitProgram) {
        clearScreen();
        cout << "\n========================================\n";
        cout << "   SELAMAT DATANG DI GOFOOD+ (MULTI LAYANAN)\n";
        cout << "========================================\n";
        cout << "User: " << loginSystem.getUsername() << "\n";
        cout << "========================================\n";
        cout << "Layanan yang tersedia:\n";
        cout << "1. Layanan Makanan\n";
        cout << "2. Layanan Berpergian dan Pengiriman\n";
        cout << "3. Layanan Marketplace\n";
        cout << "4. Layanan Shopping\n";
        cout << "5. Profil Saya (dari KTP)\n";
        cout << "6. Profil Tambahan\n";
        cout << "7. Logout\n";
        cout << "========================================\n";
        cout << "Pilih layanan (1-7): ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                menuLayananMakanan();
                break;
                
            case 2: {
                pilihBdP transport;
                transport.mulai();
                break;
            }
                
            case 3:
                layananMarketplace();
                break;

            case 4:
                shopping::layananShopping();
                break;

            case 5:
                clearScreen();
                loginSystem.tampilkanProfil();
                pauseScreen();
                break;

            case 6:
                menuProfil(profilList);
                break;

            case 7:
                loginSystem.logout();
                cout << "Anda telah logout. Terima kasih!\n";
                exitProgram = true;
                break;
                
            default:
                cout << "Pilihan tidak valid!\n";
                pauseScreen();
        }
    }
    
    cout << "\n========================================\n";
    cout << "  TERIMA KASIH TELAH MENGGUNAKAN GOFOOD+\n";
    cout << "========================================\n";
    
    return 0;
}
