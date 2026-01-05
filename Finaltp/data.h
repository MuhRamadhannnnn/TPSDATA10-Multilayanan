#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <string>
#include "ktp.h"

using namespace std;

// Struktur untuk akun user
struct AkunUser {
    string username;
    string password;
    KTP dataKTP;
    bool isRegistered;
    
    AkunUser() {
        username = "";
        password = "";
        isRegistered = false;
    }
};

// Class untuk mengelola data login dan registrasi
class DataManager {
private:
    string filename;
    
    // Fungsi untuk encode string sederhana (XOR encryption)
    string encodePassword(const string& pass) {
        string encoded = pass;
        char key = 'K'; // key untuk XOR
        for (size_t i = 0; i < encoded.length(); i++) {
            encoded[i] = encoded[i] ^ key;
        }
        return encoded;
    }
    
public:
    DataManager() {
        filename = "users_data.txt";
    }
    
    // Simpan data user ke file
    bool simpanUser(const AkunUser& user) {
        ofstream file(filename.c_str(), ios::app);
        if (!file.is_open()) {
            cout << "Gagal membuka file untuk menyimpan data!\n";
            return false;
        }
        
        // Encode password sebelum disimpan
        string encodedPass = encodePassword(user.password);
        
        // Format: username|password|nik|nama|...
        file << user.username << "|" 
             << encodedPass << "|"
             << user.dataKTP.nik << "|"
             << user.dataKTP.nama << "|"
             << user.dataKTP.tempatLahir << "|"
             << user.dataKTP.tanggalLahir << "|"
             << user.dataKTP.jenisKelamin << "|"
             << user.dataKTP.alamat << "|"
             << user.dataKTP.rt << "|"
             << user.dataKTP.rw << "|"
             << user.dataKTP.kelurahan << "|"
             << user.dataKTP.kecamatan << "|"
             << user.dataKTP.kabupaten << "|"
             << user.dataKTP.provinsi << "|"
             << user.dataKTP.agama << "|"
             << user.dataKTP.statusPerkawinan << "|"
             << user.dataKTP.pekerjaan << "|"
             << user.dataKTP.kewarganegaraan << endl;
        
        file.close();
        return true;
    }
    
    // Cari user berdasarkan username
    bool cariUser(const string& username, AkunUser& user) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            // Parse data dari file
            size_t pos = 0;
            string token;
            int field = 0;
            string tempUsername = "";
            string tempPassword = "";
            KTP tempKTP;
            
            while ((pos = line.find('|')) != string::npos) {
                token = line.substr(0, pos);
                
                switch(field) {
                    case 0: tempUsername = token; break;
                    case 1: tempPassword = token; break;
                    case 2: tempKTP.nik = token; break;
                    case 3: tempKTP.nama = token; break;
                    case 4: tempKTP.tempatLahir = token; break;
                    case 5: tempKTP.tanggalLahir = token; break;
                    case 6: tempKTP.jenisKelamin = token; break;
                    case 7: tempKTP.alamat = token; break;
                    case 8: tempKTP.rt = token; break;
                    case 9: tempKTP.rw = token; break;
                    case 10: tempKTP.kelurahan = token; break;
                    case 11: tempKTP.kecamatan = token; break;
                    case 12: tempKTP.kabupaten = token; break;
                    case 13: tempKTP.provinsi = token; break;
                    case 14: tempKTP.agama = token; break;
                    case 15: tempKTP.statusPerkawinan = token; break;
                    case 16: tempKTP.pekerjaan = token; break;
                }
                
                line.erase(0, pos + 1);
                field++;
            }
            // Field terakhir (kewarganegaraan)
            tempKTP.kewarganegaraan = line;
            
            // Jika username cocok
            if (tempUsername == username) {
                user.username = tempUsername;
                user.password = tempPassword; // password masih terenkripsi
                user.dataKTP = tempKTP;
                user.isRegistered = true;
                file.close();
                return true;
            }
        }
        
        file.close();
        return false;
    }
    
    // Validasi login
    bool validasiLogin(const string& username, const string& password) {
        AkunUser user;
        if (!cariUser(username, user)) {
            return false;
        }
        
        // Decode password dari file dan bandingkan
        string decodedPass = encodePassword(user.password); // XOR bersifat reversible
        return (decodedPass == password);
    }
    
    // Cek apakah username sudah ada
    bool cekUsernameAda(const string& username) {
        AkunUser user;
        return cariUser(username, user);
    }
    
    // Registrasi user baru
    bool registrasiUser(const string& username, const string& password, const KTP& ktp) {
        if (cekUsernameAda(username)) {
            cout << "Username sudah terdaftar!\n";
            return false;
        }
        
        AkunUser newUser;
        newUser.username = username;
        newUser.password = password;
        newUser.dataKTP = ktp;
        newUser.isRegistered = true;
        
        return simpanUser(newUser);
    }
    
    // Ambil data KTP user yang login
    bool getDataKTP(const string& username, KTP& ktp) {
        AkunUser user;
        if (cariUser(username, user)) {
            ktp = user.dataKTP;
            return true;
        }
        return false;
    }
    
    // Simpan log aktivitas login ke file
    bool simpanLogLogin(const string& username) {
        ofstream file("login_history.txt", ios::app);
        if (!file.is_open()) {
            return false;
        }

        // Tanpa timestamp (dibatasi hanya header iostream/fstream/string)
        file << "Login: " << username << endl;
        file.close();
        return true;
    }
    
    // Simpan data KTP ke file terpisah (backup)
    bool simpanKTPToFile(const string& username) {
        AkunUser user;
        if (!cariUser(username, user)) {
            return false;
        }
        
        string ktpFilename = "ktp_" + username + ".txt";
        ofstream file(ktpFilename.c_str());
        if (!file.is_open()) {
            return false;
        }
        
        file << "========== DATA KTP ==========\n";
        file << "Username         : " << username << endl;
        file << "NIK              : " << user.dataKTP.nik << endl;
        file << "Nama             : " << user.dataKTP.nama << endl;
        file << "Tempat Lahir     : " << user.dataKTP.tempatLahir << endl;
        file << "Tanggal Lahir    : " << user.dataKTP.tanggalLahir << endl;
        file << "Jenis Kelamin    : " << user.dataKTP.jenisKelamin << endl;
        file << "Alamat           : " << user.dataKTP.alamat << endl;
        file << "RT/RW            : " << user.dataKTP.rt << "/" << user.dataKTP.rw << endl;
        file << "Kelurahan        : " << user.dataKTP.kelurahan << endl;
        file << "Kecamatan        : " << user.dataKTP.kecamatan << endl;
        file << "Kabupaten/Kota   : " << user.dataKTP.kabupaten << endl;
        file << "Provinsi         : " << user.dataKTP.provinsi << endl;
        file << "Agama            : " << user.dataKTP.agama << endl;
        file << "Status Perkawinan: " << user.dataKTP.statusPerkawinan << endl;
        file << "Pekerjaan        : " << user.dataKTP.pekerjaan << endl;
        file << "Kewarganegaraan  : " << user.dataKTP.kewarganegaraan << endl;
        file << "==============================\n";
        
        file.close();
        return true;
    }
};

// Class untuk mengelola menu login
class MenuLogin {
private:
    DataManager dataManager;
    string currentUsername;
    bool isLoggedIn;
    
public:
    MenuLogin() {
        currentUsername = "";
        isLoggedIn = false;
    }
    
    // Proses registrasi
    bool registrasi() {
        cout << "\n========== FORM REGISTRASI ==========\n";
        
        string username, password, konfirmasiPassword;
        
        cout << "Masukkan Username: ";
        cin >> username;
        
        // Cek apakah username sudah ada
        if (dataManager.cekUsernameAda(username)) {
            cout << "Username sudah terdaftar! Silakan gunakan username lain.\n";
            return false;
        }
        
        cout << "Masukkan Password: ";
        cin >> password;
        
        cout << "Konfirmasi Password: ";
        cin >> konfirmasiPassword;
        
        if (password != konfirmasiPassword) {
            cout << "Password tidak cocok! Registrasi gagal.\n";
            return false;
        }
        
        // Input data KTP
        KTP ktp;
        inputKTP(ktp);
        
        // Simpan ke file
        if (dataManager.registrasiUser(username, password, ktp)) {
            cout << "\n=== REGISTRASI BERHASIL! ===\n";
            cout << "Silakan login dengan username dan password Anda.\n";
            return true;
        } else {
            cout << "Registrasi gagal! Silakan coba lagi.\n";
            return false;
        }
    }
    
    // Proses login
    bool login() {
        cout << "\n========== FORM LOGIN ==========\n";
        
        string username, password;
        
        cout << "Username: ";
        cin >> username;
        
        cout << "Password: ";
        cin >> password;
        
        if (dataManager.validasiLogin(username, password)) {
            cout << "\n=== LOGIN BERHASIL! ===\n";
            cout << "Selamat datang, " << username << "!\n";
            currentUsername = username;
            isLoggedIn = true;
            
            // Simpan log login ke file
            dataManager.simpanLogLogin(username);
            
            // Simpan data KTP ke file terpisah
            dataManager.simpanKTPToFile(username);
            
            return true;
        } else {
            cout << "\n=== LOGIN GAGAL! ===\n";
            cout << "Username atau password salah!\n";
            return false;
        }
    }
    
    // Menu utama login/register
    bool tampilkanMenu() {
        int pilihan;
        bool success = false;
        
        do {
            cout << "\n==================================\n";
            cout << "   SELAMAT DATANG DI GOFOOD+      \n";
            cout << "==================================\n";
            cout << "1. Login\n";
            cout << "2. Registrasi\n";
            cout << "3. Keluar\n";
            cout << "==================================\n";
            cout << "Pilih menu (1-3): ";
            cin >> pilihan;
            
            switch(pilihan) {
                case 1:
                    success = login();
                    if (success) return true;
                    break;
                case 2:
                    registrasi();
                    break;
                case 3:
                    cout << "Terima kasih!\n";
                    return false;
                default:
                    cout << "Pilihan tidak valid!\n";
            }
        } while (pilihan != 3 && !success);
        
        return success;
    }
    
    // Logout
    void logout() {
        currentUsername = "";
        isLoggedIn = false;
        cout << "Anda telah logout.\n";
    }
    
    // Cek status login
    bool cekLogin() {
        return isLoggedIn;
    }
    
    // Dapatkan username yang sedang login
    string getUsername() {
        return currentUsername;
    }
    
    // Tampilkan profil user yang login
    void tampilkanProfil() {
        if (!isLoggedIn) {
            cout << "Anda belum login!\n";
            return;
        }
        
        KTP ktp;
        if (dataManager.getDataKTP(currentUsername, ktp)) {
            cout << "\n========== PROFIL ANDA ==========\n";
            cout << "Username: " << currentUsername << endl;
            tampilkanKTP(ktp);
        } else {
            cout << "Gagal mengambil data profil!\n";
        }
    }
};

#endif
