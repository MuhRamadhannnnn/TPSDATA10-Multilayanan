#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
using namespace std;

// Class untuk alamat dan ongkir
class Alamat {
private:
    string alamat;
    int jarak;
    int ongkir;
    int totalongkir;
    
public:
    Alamat() {
        alamat = "";
        jarak = 0;
        ongkir = 0;
        totalongkir = 0;
    }
    
    void inputalamat() {
        cout << "\n=== INPUT ALAMAT PENGIRIMAN ===\n";
        cout << "Masukkan alamat lengkap: ";
        cin.ignore();
        getline(cin, alamat);
        cout << "Masukkan jarak (km): ";
        cin >> jarak;
        
        // Hitung ongkir: Rp 2000/km
        ongkir = jarak * 2000;
        totalongkir = ongkir;
        
        cout << "\nAlamat: " << alamat << endl;
        cout << "Jarak: " << jarak << " km\n";
        cout << "Ongkir: Rp " << ongkir << endl;
    }
    
    int gettotalongkir() {
        return totalongkir;
    }
    
    string getalamat() {
        return alamat;
    }
};

// Class untuk pembayaran
class pembayaran {
private:
    int saldoDompet;
    int limitKartu;
    
public:
    pembayaran() {
        saldoDompet = 200000;  // Saldo awal Rp 200.000
        limitKartu = 1000000;  // Limit kartu Rp 1.000.000
    }

    bool prosesPembayaranStatus(int totalBelanja, int ongkir) {
        int totalPembayaran = totalBelanja + ongkir;
        
        cout << "\n========================================\n";
        cout << "         PROSES PEMBAYARAN\n";
        cout << "========================================\n";
        cout << "Total Belanja : Rp " << totalBelanja << endl;
        cout << "Ongkos Kirim  : Rp " << ongkir << endl;
        cout << "----------------------------------------\n";
        cout << "TOTAL BAYAR   : Rp " << totalPembayaran << endl;
        cout << "========================================\n\n";
        
        cout << "Pilih Metode Pembayaran:\n";
        cout << "1. Dompet Digital (Saldo: Rp " << saldoDompet << ")\n";
        cout << "2. Kartu Kredit/Debit (Limit: Rp " << limitKartu << ")\n";
        cout << "3. Cash/Tunai\n";
        cout << "Pilih (1-3): ";
        
        int metode;
        cin >> metode;
        
        bool berhasil = false;
        
        switch(metode) {
            case 1:
                if (saldoDompet >= totalPembayaran) {
                    saldoDompet -= totalPembayaran;
                    cout << "\n✓ Pembayaran berhasil via Dompet Digital!\n";
                    cout << "Sisa saldo: Rp " << saldoDompet << endl;
                    berhasil = true;
                } else {
                    cout << "\n✗ Saldo tidak mencukupi!\n";
                    cout << "Silakan pilih metode pembayaran lain.\n";
                }
                break;
                
            case 2:
                if (limitKartu >= totalPembayaran) {
                    cout << "\n✓ Pembayaran berhasil via Kartu Kredit/Debit!\n";
                    cout << "Terima kasih telah berbelanja.\n";
                    berhasil = true;
                } else {
                    cout << "\n✗ Limit kartu tidak mencukupi!\n";
                }
                break;
                
            case 3:
                cout << "\nMasukkan jumlah uang: Rp ";
                int uang;
                cin >> uang;
                if (uang >= totalPembayaran) {
                    int kembalian = uang - totalPembayaran;
                    cout << "\n✓ Pembayaran berhasil!\n";
                    cout << "Kembalian: Rp " << kembalian << endl;
                    berhasil = true;
                } else {
                    cout << "\n✗ Uang tidak mencukupi!\n";
                }
                break;
                
            default:
                cout << "\n✗ Metode pembayaran tidak valid!\n";
        }
        
        if (!berhasil) {
            cout << "\nPembayaran dibatalkan.\n";
        }

        return berhasil;
    }

    void prosesPembayaran(int totalBelanja, int ongkir) {
        (void)prosesPembayaranStatus(totalBelanja, ongkir);
    }
    
    // Fungsi untuk cetak struk (akan dipanggil dari Toko)
    template<typename TokoType>
    void strukPembayaran(int totalBelanja, int ongkir, TokoType& toko) {
        int totalPembayaran = totalBelanja + ongkir;
        
        cout << "\n========================================\n";
        cout << "              STRUK PEMBAYARAN\n";
        cout << "========================================\n";
        cout << "Tanggal: " << __DATE__ << " " << __TIME__ << endl;
        cout << "========================================\n\n";
        
        cout << "DETAIL PESANAN:\n";
        cout << "----------------------------------------\n";
        // Akan menampilkan pesanan dari toko
        
        cout << "\n----------------------------------------\n";
        cout << "Subtotal      : Rp " << totalBelanja << endl;
        cout << "Ongkos Kirim  : Rp " << ongkir << endl;
        cout << "========================================\n";
        cout << "TOTAL         : Rp " << totalPembayaran << endl;
        cout << "========================================\n";
        cout << "\nTerima kasih telah berbelanja!\n";
        cout << "Pesanan Anda akan segera dikirim.\n";
        cout << "========================================\n";
    }
};

#endif
