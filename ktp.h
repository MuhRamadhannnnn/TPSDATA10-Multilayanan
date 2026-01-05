#ifndef KTP_H
#define KTP_H

#include <string>
using namespace std;

// Struktur data untuk KTP
struct KTP {
    string nik;           // NIK (Nomor Induk Kependudukan)
    string nama;          // Nama lengkap
    string tempatLahir;   // Tempat lahir
    string tanggalLahir;  // Format: DD/MM/YYYY
    string jenisKelamin;  // L/P
    string alamat;        // Alamat lengkap
    string rt;            // RT
    string rw;            // RW
    string kelurahan;     // Kelurahan/Desa
    string kecamatan;     // Kecamatan
    string kabupaten;     // Kabupaten/Kota
    string provinsi;      // Provinsi
    string agama;         // Agama
    string statusPerkawinan; // Kawin/Belum Kawin/Cerai
    string pekerjaan;     // Pekerjaan
    string kewarganegaraan; // Kewarganegaraan (WNI/WNA)

    // Constructor
    KTP() {
        nik = "";
        nama = "";
        tempatLahir = "";
        tanggalLahir = "";
        jenisKelamin = "";
        alamat = "";
        rt = "";
        rw = "";
        kelurahan = "";
        kecamatan = "";
        kabupaten = "";
        provinsi = "";
        agama = "";
        statusPerkawinan = "";
        pekerjaan = "";
        kewarganegaraan = "WNI";
    }
};

// Fungsi untuk menampilkan data KTP
void tampilkanKTP(const KTP& ktp) {
    cout << "\n========== DATA KTP ==========\n";
    cout << "NIK              : " << ktp.nik << endl;
    cout << "Nama             : " << ktp.nama << endl;
    cout << "Tempat Lahir     : " << ktp.tempatLahir << endl;
    cout << "Tanggal Lahir    : " << ktp.tanggalLahir << endl;
    cout << "Jenis Kelamin    : " << ktp.jenisKelamin << endl;
    cout << "Alamat           : " << ktp.alamat << endl;
    cout << "RT/RW            : " << ktp.rt << "/" << ktp.rw << endl;
    cout << "Kelurahan        : " << ktp.kelurahan << endl;
    cout << "Kecamatan        : " << ktp.kecamatan << endl;
    cout << "Kabupaten/Kota   : " << ktp.kabupaten << endl;
    cout << "Provinsi         : " << ktp.provinsi << endl;
    cout << "Agama            : " << ktp.agama << endl;
    cout << "Status Perkawinan: " << ktp.statusPerkawinan << endl;
    cout << "Pekerjaan        : " << ktp.pekerjaan << endl;
    cout << "Kewarganegaraan  : " << ktp.kewarganegaraan << endl;
    cout << "==============================\n";
}

// Fungsi untuk input data KTP
void inputKTP(KTP& ktp) {
    cout << "\n=== INPUT DATA KTP ===\n";

    cout << "NIK: ";
    cin >> ktp.nik;
    
    cin.ignore();
    cout << "Nama Lengkap: ";
    getline(cin, ktp.nama);
    cout << "Tempat Lahir: ";
    getline(cin, ktp.tempatLahir);
    cout << "Tanggal Lahir (DD/MM/YYYY): ";
    getline(cin, ktp.tanggalLahir);
    
    do {
        cout << "Jenis Kelamin (L/P): ";
        cin >> ktp.jenisKelamin;
        if (ktp.jenisKelamin != "L" && ktp.jenisKelamin != "P") {
            cout << "Pilihan tidak valid! Masukkan L atau P.\n";
        }
    } while (ktp.jenisKelamin != "L" && ktp.jenisKelamin != "P");
    
    cin.ignore();
    cout << "Alamat: ";
    getline(cin, ktp.alamat);
    cout << "RT: ";
    getline(cin, ktp.rt);
    cout << "RW: ";
    getline(cin, ktp.rw);
    cout << "Kelurahan/Desa: ";
    getline(cin, ktp.kelurahan);
    cout << "Kecamatan: ";
    getline(cin, ktp.kecamatan);
    cout << "Kabupaten/Kota: ";
    getline(cin, ktp.kabupaten);
    cout << "Provinsi: ";
    getline(cin, ktp.provinsi);
    cout << "Agama: ";
    getline(cin, ktp.agama);
    cout << "Status Perkawinan: ";
    getline(cin, ktp.statusPerkawinan);
    cout << "Pekerjaan: ";
    getline(cin, ktp.pekerjaan);
    
    cout << "\nData KTP berhasil diinput!\n";
}

#endif
