#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

// Node untuk Single Linked List (Pesanan)
struct OrderNode {
    string nama_makanan;
    int harga;
    int qty;
    string restoran;
    OrderNode* next;
    
    OrderNode(string nama, int hrg, string resto, int quantity = 1) {
        nama_makanan = nama;
        harga = hrg;
        qty = quantity;
        restoran = resto;
        next = NULL;
    }
};

class RiwayatPesanan;

// Single Linked List untuk manajemen pesanan
class OrderList {
private:
    OrderNode* head;
    int total_pesanan;

    // Circular Stack (Undo) - berbasis array (tp7-style)
    static const int MAX_UNDO = 5;
    string undoStack[MAX_UNDO];
    int topUndo;
    int countUndo;

    struct CancelItem {
        string nama;
        int harga;
        string restoran;
    };
    static const int MAX_CANCEL_HISTORY = 100;
    CancelItem cancelHistory[MAX_CANCEL_HISTORY];
    int cancelCount;

    bool undoIsEmpty() const { return countUndo == 0; }

    void pushCircular(const string& item) {
        topUndo = (topUndo + 1) % MAX_UNDO;
        undoStack[topUndo] = item;
        if (countUndo < MAX_UNDO) countUndo++;
    }

    string popCircular() {
        if (undoIsEmpty()) return "";
        string item = undoStack[topUndo];
        if (topUndo == 0) topUndo = MAX_UNDO - 1; else topUndo = topUndo - 1;
        countUndo--;
        if (countUndo == 0) topUndo = -1;
        return item;
    }

public:
    OrderList() {
        head = NULL;
        total_pesanan = 0;
        topUndo = -1;
        countUndo = 0;
        cancelCount = 0;
    }

    void tambahPesanan(string nama, int harga, string restoran, int qty = 1) {
        if (qty < 1) qty = 1;
        OrderNode* newNode = new OrderNode(nama, harga, restoran, qty);
        if (!head) {
            head = newNode;
        } else {
            OrderNode* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        total_pesanan++;

        // catat untuk undo (gunakan nama item saja seperti tp7)
        pushCircular(nama);
    }

    bool kosong() const {
        return head == NULL;
    }

    void tampilkanPesanan() {
        OrderNode* temp = head;
        int no = 1;
        cout << "\n=== Daftar Pesanan ===\n";
        while (temp) {
            int subtotal = temp->harga * temp->qty;
            cout << no << ". " << temp->nama_makanan
                 << " x" << temp->qty
                 << " - Rp " << temp->harga
                 << " (" << temp->restoran << ")"
                 << " = Rp " << subtotal << "\n";
            temp = temp->next;
            no++;
        }
        cout << "Total pesanan: " << total_pesanan << endl;
    }

    int hitungTotalHarga() {
        OrderNode* temp = head;
        int total = 0;
        while (temp) {
            total += temp->harga * temp->qty;
            temp = temp->next;
        }
        return total;
    }

    bool hapusPesananTerakhir() {
        if (!head) return false;
        if (!head->next) {
            delete head;
            head = NULL;
            total_pesanan = 0;
            return true;
        }
        OrderNode* cur = head;
        while (cur->next && cur->next->next) cur = cur->next;
        delete cur->next;
        cur->next = NULL;
        total_pesanan--;
        return true;
    }

    void hapusSemua() {
        OrderNode* cur = head;
        while (cur) {
            OrderNode* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = NULL;
        total_pesanan = 0;
    }

    bool undoLastOrder() {
        if (!head || total_pesanan <= 0) {
            cout << "Tidak ada pesanan untuk dibatalkan.\n";
            return false;
        }

        // pop dari circular stack (jika kosong, tetap coba batalkan node terakhir)
        (void)popCircular();

        // hapus node terakhir dan simpan ke riwayat pembatalan
        if (!head->next) {
            if (cancelCount < MAX_CANCEL_HISTORY) {
                cancelHistory[cancelCount].nama = head->nama_makanan;
                cancelHistory[cancelCount].harga = head->harga * head->qty;
                cancelHistory[cancelCount].restoran = head->restoran;
                cancelCount++;
            }
            cout << "Pesanan dibatalkan: " << head->nama_makanan << " - Rp " << (head->harga * head->qty) << endl;
            delete head;
            head = NULL;
            total_pesanan = 0;
            return true;
        }

        OrderNode* prev = head;
        while (prev->next && prev->next->next) prev = prev->next;
        OrderNode* last = prev->next;

        if (cancelCount < MAX_CANCEL_HISTORY) {
            cancelHistory[cancelCount].nama = last->nama_makanan;
            cancelHistory[cancelCount].harga = last->harga * last->qty;
            cancelHistory[cancelCount].restoran = last->restoran;
            cancelCount++;
        }

        cout << "Pesanan dibatalkan: " << last->nama_makanan << " - Rp " << (last->harga * last->qty) << endl;

        delete last;
        prev->next = NULL;
        total_pesanan--;
        return true;
    }

    void tampilkanRiwayatPembatalan() const {
        cout << "\n=== Riwayat Pembatalan ===\n";
        if (cancelCount == 0) {
            cout << "(Belum ada pembatalan)\n";
            return;
        }
        for (int i = 0; i < cancelCount; ++i) {
            cout << i + 1 << ". " << cancelHistory[i].nama << " - Rp " << cancelHistory[i].harga;
            if (!cancelHistory[i].restoran.empty()) cout << " (" << cancelHistory[i].restoran << ")";
            cout << "\n";
        }
    }

    void pindahkanKeRiwayat(RiwayatPesanan& riwayat, const string& tanggal);
};

// Node untuk Circular Linked List (Riwayat)
struct RiwayatNode {
    string nama_makanan;
    int harga;
    string restoran;
    string tanggal;
    RiwayatNode* next;
    
    RiwayatNode(string nama, int hrg, string resto, string tgl) {
        nama_makanan = nama;
        harga = hrg;
        restoran = resto;
        tanggal = tgl;
        next = NULL;
    }
};

// Circular Linked List untuk riwayat pesanan
class RiwayatPesanan {
private:
    RiwayatNode* head;
    int jumlah_riwayat;

public:
    RiwayatPesanan() {
        head = NULL;
        jumlah_riwayat = 0;
    }

    void tambahRiwayat(string nama, int harga, string restoran, string tanggal) {
        RiwayatNode* newNode = new RiwayatNode(nama, harga, restoran, tanggal);
        if (!head) {
            head = newNode;
            head->next = head;
        } else {
            RiwayatNode* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        jumlah_riwayat++;
    }

    void tampilkanRiwayat() {
        if (!head) {
            cout << "Belum ada riwayat pesanan.\n";
            return;
        }

        RiwayatNode* temp = head;
        int no = 1;
        cout << "\n=== Riwayat Pesanan ===\n";
        do {
            cout << no << ". " << temp->nama_makanan 
                 << " - Rp " << temp->harga 
                 << " (" << temp->restoran << ")"
                 << " - " << temp->tanggal << "\n";
            temp = temp->next;
            no++;
        } while (temp != head);
        cout << "Total riwayat: " << jumlah_riwayat << endl;
    }

    void hapusRiwayatLama(int batas) {
        if (!head || jumlah_riwayat <= batas) return;

        while (jumlah_riwayat > batas) {
            if (head->next == head) {
                delete head;
                head = NULL;
            } else {
                RiwayatNode* temp = head;
                while (temp->next != head) {
                    temp = temp->next;
                }
                RiwayatNode* newHead = head->next;
                delete head;
                head = newHead;
                temp->next = head;
            }
            jumlah_riwayat--;
        }
    }
};

inline void OrderList::pindahkanKeRiwayat(RiwayatPesanan& riwayat, const string& tanggal) {
    OrderNode* cur = head;
    while (cur) {
        string nama = cur->nama_makanan;
        if (cur->qty > 1) {
            nama += " x" + to_string(cur->qty);
        }
        riwayat.tambahRiwayat(nama, cur->harga * cur->qty, cur->restoran, tanggal);
        cur = cur->next;
    }
    hapusSemua();
}

// Node untuk linked list makanan
struct FoodNode {
    string nama;
    int harga;
    string jenis;
    string restoran;
    FoodNode* next;

    FoodNode(string n, int h, string j, string r) {
        nama = n;
        harga = h;
        jenis = j;
        restoran = r;
        next = NULL;
    }
};

// Linked List untuk mengurutkan makanan
class FoodLinkedList {
private:
    FoodNode* head;
    int count;

public:
    FoodLinkedList() {
        head = NULL;
        count = 0;
    }

    void tambahMakanan(string nama, int harga, string jenis, string restoran) {
        FoodNode* newNode = new FoodNode(nama, harga, jenis, restoran);
        if (!head || harga < head->harga) {
            newNode->next = head;
            head = newNode;
        } else {
            FoodNode* current = head;
            while (current->next && current->next->harga <= harga) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        count++;
    }

    void tampilkanSemuaMakanan() {
        if (!head) {
            cout << "Tidak ada data makanan.\n";
            return;
        }

        FoodNode* current = head;
        int no = 1;
        cout << "\n=== Daftar Makanan (Diurutkan berdasarkan harga) ===\n";
        while (current) {
            cout << no << ". " << current->nama 
                 << " - Rp " << current->harga 
                 << " (" << current->restoran << ")"
                 << " [" << current->jenis << "]\n";
            current = current->next;
            no++;
        }
    }

    void tampilkanBerdasarkanJenis(string jenis) {
        if (!head) {
            cout << "Tidak ada data makanan.\n";
            return;
        }

        FoodNode* current = head;
        int no = 1;
        bool found = false;
        cout << "\n=== Makanan Jenis " << jenis << " (Diurutkan berdasarkan harga) ===\n";
        while (current) {
            if (current->jenis == jenis) {
                cout << no << ". " << current->nama 
                     << " - Rp " << current->harga 
                     << " (" << current->restoran << ")\n";
                no++;
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            cout << "Tidak ditemukan makanan dengan jenis " << jenis << endl;
        }
    }
};

#endif
