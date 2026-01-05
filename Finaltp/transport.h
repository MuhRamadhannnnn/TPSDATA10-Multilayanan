#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <string>
#include <fstream>
#include "queue.h"
#include "stack.h"
#include "linkedlist.h"
#include "payment.h"

using namespace std;

// Struct untuk pengiriman barang
struct PengirimanBarang {
    string namaBarang;
    string alamatPengirim;
    string alamatPenerima;
    int berat; // dalam kg
    int biaya;
    PengirimanBarang* next;
};

// Class untuk layanan Berpergian dan Pengiriman
class pilihBdP {
private:
    PengirimanBarang* headPengiriman;
    StackAlamatPengiriman stackAlamat;
    CircularQueue antrianMobil;
    CircularQueue antrianTransportasi;

    int hitungTotalBiayaPengiriman() {
        int total = 0;
        PengirimanBarang* temp = headPengiriman;
        while (temp != NULL) {
            total += temp->biaya;
            temp = temp->next;
        }
        return total;
    }

    void hapusSemuaPengiriman() {
        PengirimanBarang* temp = headPengiriman;
        while (temp != NULL) {
            PengirimanBarang* next = temp->next;
            delete temp;
            temp = next;
        }
        headPengiriman = NULL;
    }

    void checkoutDanBayarPengiriman() {
        if (headPengiriman == NULL) {
            cout << "\nBelum ada pengiriman untuk dibayar.\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "      CHECKOUT GOSEND (PENGIRIMAN)\n";
        cout << "========================================\n";
        tampilkanPengiriman();
        int total = hitungTotalBiayaPengiriman();
        cout << "\n----------------------------------------\n";
        cout << "Total biaya pengiriman: Rp " << total << endl;
        cout << "========================================\n";

        static pembayaran pay;
        bool berhasil = pay.prosesPembayaranStatus(total, 0);
        if (!berhasil) {
            cout << "\nTransaksi dibatalkan. Data pengiriman tidak berubah.\n";
            return;
        }

        cout << "\n✓ Transaksi berhasil! Pengiriman diproses.\n";
        hapusSemuaPengiriman();
    }
    
public:
    pilihBdP() {
        headPengiriman = NULL;
    }
    
    // Struct untuk tujuan ojek
    struct OjekDestinasi {
        string tujuan;
        int jarak;
        int harga;
    };
    

    
    // Fungsi load data ojek dari file
    void loadDataOjek(OjekDestinasi dest[], int& count, const string& kategori) {
        count = 0;
        string filename = "ojek_toko/" + kategori + ".txt";
        ifstream file(filename.c_str());
        
        if (!file.is_open()) {
            cout << "File tidak ditemukan!\n";
            return;
        }
        
        string line;
        getline(file, line); // Skip header
        
        while (getline(file, line) && count < 20) {
            if (line.empty() || line[0] == '=') continue;
            
            // Parse: "1. Tujuan - 10 km - Rp 50000"
            int pos = line.find(". ");
            if (pos == string::npos) continue;
            
            line = line.substr(pos + 2); // Skip "1. "
            
            // Cari dash pertama
            int dash1 = line.find(" - ");
            if (dash1 == string::npos) continue;
            
            dest[count].tujuan = line.substr(0, dash1);
            
            // Cari jarak
            int pos2 = dash1 + 3;
            int dash2 = line.find(" km", pos2);
            if (dash2 == string::npos) continue;
            
            string jarak_str = line.substr(pos2, dash2 - pos2);
            dest[count].jarak = atoi(jarak_str.c_str());
            
            // Cari harga
            int pos3 = line.find("Rp ", dash2);
            if (pos3 == string::npos) continue;
            
            string harga_str = line.substr(pos3 + 3);
            dest[count].harga = atoi(harga_str.c_str());
            
            count++;
        }
        file.close();
    }
    
    // Menu Ojek Online dengan data dari file
    void menuOjekOnline() {
        cout << "\n=== OJEK ONLINE ===\n";
        cout << "1. GoRide Motor\n";
        cout << "2. GoRide Car\n";
        cout << "Pilih jenis kendaraan: ";
        int pilihKendaraan;
        cin >> pilihKendaraan;
        
        if (pilihKendaraan != 1 && pilihKendaraan != 2) {
            cout << "Pilihan tidak valid!\n";
            return;
        }
        
        cout << "\n=== PILIH KATEGORI TUJUAN ===\n";
        cout << "1. Pusat Kota\n";
        cout << "2. Bandara\n";
        cout << "3. Stasiun\n";
        cout << "4. Rumah Sakit\n";
        cout << "5. Universitas\n";
        cout << "6. Wisata\n";
        cout << "7. Kantor\n";
        cout << "8. Sekolah\n";
        cout << "9. Pertokoan\n";
        cout << "10. Hiburan\n";
        cout << "11. Hotel\n";
        cout << "12. Pasar\n";
        cout << "13. Industri\n";
        cout << "14. SPBU\n";
        cout << "15. Bioskop\n";
        cout << "16. Taman\n";
        cout << "17. Restoran\n";
        cout << "18. Olahraga\n";
        cout << "Pilih kategori (1-18): ";
        
        int pilihKat;
        cin >> pilihKat;
        
        string kategori;
        switch(pilihKat) {
            case 1: kategori = "pusat_kota"; break;
            case 2: kategori = "bandara"; break;
            case 3: kategori = "stasiun"; break;
            case 4: kategori = "rumah_sakit"; break;
            case 5: kategori = "universitas"; break;
            case 6: kategori = "wisata"; break;
            case 7: kategori = "kantor"; break;
            case 8: kategori = "sekolah"; break;
            case 9: kategori = "pertokoan"; break;
            case 10: kategori = "hiburan"; break;
            case 11: kategori = "hotel"; break;
            case 12: kategori = "pasar"; break;
            case 13: kategori = "industri"; break;
            case 14: kategori = "spbu"; break;
            case 15: kategori = "bioskop"; break;
            case 16: kategori = "taman"; break;
            case 17: kategori = "restoran"; break;
            case 18: kategori = "olahraga"; break;
            default:
                cout << "Kategori tidak valid!\n";
                return;
        }
        
        OjekDestinasi destinasi[20];
        int count = 0;
        loadDataOjek(destinasi, count, kategori);
        
        if (count == 0) {
            cout << "Tidak ada data destinasi!\n";
            return;
        }
        
        cout << "\n=== PILIH DESTINASI ===\n";
        for (int i = 0; i < count; i++) {
            cout << (i+1) << ". " << destinasi[i].tujuan << " - " << destinasi[i].jarak << " km - Rp " << destinasi[i].harga << endl;
        }
        cout << "Pilih destinasi (1-" << count << "): ";
        
        int pilihDest;
        cin >> pilihDest;
        
        if (pilihDest < 1 || pilihDest > count) {
            cout << "Pilihan tidak valid!\n";
            return;
        }
        
        pilihDest--; // Convert to 0-indexed
        
        int biaya = destinasi[pilihDest].harga;
        string jenisKendaraan = (pilihKendaraan == 1) ? "Motor" : "Mobil";
        
        cout << "\n--- Detail Pesanan ---\n";
        cout << "Jenis: " << jenisKendaraan << endl;
        cout << "Tujuan: " << destinasi[pilihDest].tujuan << endl;
        cout << "Jarak: " << destinasi[pilihDest].jarak << " km\n";
        cout << "Biaya: Rp " << biaya << endl;
        cout << "\nPesanan berhasil! Driver sedang menuju lokasi Anda.\n";
    }
    


    void menuPesanMobil() {
        cout << "\n=== PESAN MOBIL ===\n";
        cout << "1. Tambah Pesanan ke Antrian\n";
        cout << "2. Proses Pesanan\n";
        cout << "3. Lihat Antrian\n";
        cout << "Pilih menu: ";
        int pilih;
        cin >> pilih;
        
        if (pilih == 1) {
            string nama, tujuan;
            int harga;
            cout << "Nama pemesan: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Tujuan: ";
            getline(cin, tujuan);
            cout << "Estimasi biaya: Rp ";
            cin >> harga;
            
            antrianMobil.enqueue(nama, harga, tujuan, "Pending");
            cout << "Pesanan ditambahkan ke antrian!\n";
            
        } else if (pilih == 2) {
            QueueItem item = antrianMobil.dequeue();
            if (!item.nama_makanan.empty()) {
                cout << "Pesanan diproses: " << item.nama_makanan << " ke " << item.restoran << "\n";
            }
        } else if (pilih == 3) {
            antrianMobil.display();
        }
    }
    
    // Menu GoSend (Pengiriman Barang)
    void menuGoSend() {
        int pilih;
        do {
            cout << "\n=== GOSEND - PENGIRIMAN BARANG ===\n";
            cout << "1. Tambah Pengiriman\n";
            cout << "2. Tampilkan Semua Pengiriman\n";
            cout << "3. Riwayat Alamat Pengiriman\n";
            cout << "4. Checkout & Bayar\n";
            cout << "0. Kembali\n";
            cout << "Pilih: ";
            cin >> pilih;
            
            if (pilih == 1) {
                tambahPengiriman();
            } else if (pilih == 2) {
                tampilkanPengiriman();
            } else if (pilih == 3) {
                stackAlamat.tampilkan();
            } else if (pilih == 4) {
                checkoutDanBayarPengiriman();
            }
        } while (pilih != 0);
    }
    
    // Tambah pengiriman barang
    void tambahPengiriman() {
        PengirimanBarang* newNode = new PengirimanBarang();
        
        cout << "\n--- Tambah Pengiriman Baru ---\n";
        cout << "Nama barang: ";
        cin.ignore();
        getline(cin, newNode->namaBarang);
        cout << "Alamat pengirim: ";
        getline(cin, newNode->alamatPengirim);
        cout << "Alamat penerima: ";
        getline(cin, newNode->alamatPenerima);
        cout << "Berat barang (kg): ";
        cin >> newNode->berat;
        
        // Hitung biaya berdasarkan berat
        newNode->biaya = newNode->berat * 5000; // Rp 5000/kg
        newNode->next = NULL;
        
        // Tambahkan ke linked list
        if (headPengiriman == NULL) {
            headPengiriman = newNode;
        } else {
            PengirimanBarang* temp = headPengiriman;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        
        // Tambah alamat ke stack
        stackAlamat.push(newNode->alamatPenerima);
        
        cout << "\nPengiriman berhasil ditambahkan!\n";
        cout << "Biaya: Rp " << newNode->biaya << endl;
    }
    
    // Tampilkan semua pengiriman
    void tampilkanPengiriman() {
        if (headPengiriman == NULL) {
            cout << "\nBelum ada pengiriman.\n";
            return;
        }
        
        PengirimanBarang* temp = headPengiriman;
        int no = 1;
        cout << "\n=== Daftar Pengiriman ===\n";
        while (temp != NULL) {
            cout << "\nPengiriman ke-" << no++ << endl;
            cout << "Barang: " << temp->namaBarang << endl;
            cout << "Dari: " << temp->alamatPengirim << endl;
            cout << "Ke: " << temp->alamatPenerima << endl;
            cout << "Berat: " << temp->berat << " kg\n";
            cout << "Biaya: Rp " << temp->biaya << endl;
            temp = temp->next;
        }
    }
    
    // Menu Transportasi Publik
    void menuTransportasiPublik() {
        cout << "\n=== TRANSPORTASI PUBLIK ===\n";
        cout << "1. Bus Kota - Rp 5.000\n";
        cout << "2. Kereta - Rp 10.000\n";
        cout << "3. Angkot - Rp 3.000\n";
        cout << "Pilih transportasi: ";
        int pilih;
        cin >> pilih;
        
        string jenis[] = {"", "Bus Kota", "Kereta", "Angkot"};
        int harga[] = {0, 5000, 10000, 3000};
        
        if (pilih >= 1 && pilih <= 3) {
            cout << "\n--- Tiket " << jenis[pilih] << " ---\n";
            cout << "Harga: Rp " << harga[pilih] << endl;
            cout << "Tiket berhasil dipesan!\n";
            
            antrianTransportasi.enqueue("Penumpang", harga[pilih], jenis[pilih], "Aktif");
        }
    }
    
    // Menu CarBox
    void menuCarBox() {
        cout << "\n=== CARBOX ===\n";
        cout << "1. Sewa Mobil (Per Jam)\n";
        cout << "2. Pengiriman Barang Besar\n";
        cout << "Pilih layanan: ";
        int pilih;
        cin >> pilih;
        
        if (pilih == 1) {
            int jam;
            cout << "Berapa jam sewa: ";
            cin >> jam;
            int biaya = jam * 50000; // Rp 50.000/jam
            cout << "\nBiaya sewa " << jam << " jam: Rp " << biaya << endl;
            cout << "Mobil akan tiba dalam 10 menit.\n";
        } else if (pilih == 2) {
            string barang;
            int berat;
            cout << "Nama barang: ";
            cin.ignore();
            getline(cin, barang);
            cout << "Berat (kg): ";
            cin >> berat;
            int biaya = berat * 8000; // Rp 8.000/kg untuk barang besar
            cout << "\nBiaya pengiriman: Rp " << biaya << endl;
            cout << "Barang akan dijemput segera.\n";
        }
    }
    
    // Menu utama
    void mulai() {
        int pilih;
        do {
            cout << "\n========================================\n";
            cout << "   LAYANAN BERPERGIAN & PENGIRIMAN\n";
            cout << "========================================\n";
            cout << "1. Ojek Online\n";
            cout << "2. Pesan Mobil (Antrian)\n";
            cout << "3. Pengiriman Barang (GoSend)\n";
            cout << "4. Transportasi Publik\n";
            cout << "5. CarBox (Sewa & Pengiriman Besar)\n";
            cout << "0. Kembali\n";
            cout << "========================================\n";
            cout << "Pilih layanan: ";
            cin >> pilih;
            
            switch(pilih) {
                case 1:
                    menuOjekOnline();
                    break;
                case 2:
                    menuPesanMobil();
                    break;
                case 3:
                    menuGoSend();
                    break;
                case 4:
                    menuTransportasiPublik();
                    break;
                case 5:
                    menuCarBox();
                    break;
                case 0:
                    cout << "Kembali ke menu utama.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
            }
        } while (pilih != 0);
    }
};

#endif
