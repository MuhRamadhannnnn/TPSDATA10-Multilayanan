#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "payment.h"

namespace shopping {

// =============================
// Huffman Coding (untuk optimasi struk belanja)
// Implementasi diambil dari `progrestp7.cpp` dan dipaketkan agar bisa dipakai dari proyek ini.

struct NodeHuffman {
    char data;
    int frekuensi;
    NodeHuffman* left;
    NodeHuffman* right;
    NodeHuffman(char c, int f) : data(c), frekuensi(f), left(NULL), right(NULL) {}
};

struct PQNode {
    NodeHuffman* tree;
    PQNode* next;
    PQNode(NodeHuffman* t) : tree(t), next(NULL) {}
};

inline void pushPQ(PQNode*& head, NodeHuffman* tree) {
    PQNode* node = new PQNode(tree);
    if (!head || tree->frekuensi < head->tree->frekuensi) {
        node->next = head;
        head = node;
        return;
    }
    PQNode* cur = head;
    while (cur->next && cur->next->tree->frekuensi <= tree->frekuensi) {
        cur = cur->next;
    }
    node->next = cur->next;
    cur->next = node;
}

inline NodeHuffman* popPQ(PQNode*& head) {
    if (!head) return NULL;
    PQNode* tmp = head;
    head = head->next;
    NodeHuffman* res = tmp->tree;
    delete tmp;
    return res;
}

inline void freeHuffmanTree(NodeHuffman* root) {
    if (!root) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

inline NodeHuffman* buildHuffmanTree(const std::string& teks) {
    if (teks.empty()) return NULL;

    int freq[256];
    for (int i = 0; i < 256; i++) freq[i] = 0;
    for (size_t i = 0; i < teks.size(); i++) {
        unsigned char uc = (unsigned char)teks[i];
        freq[uc]++;
    }

    PQNode* pq = NULL;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            NodeHuffman* node = new NodeHuffman((char)i, freq[i]);
            pushPQ(pq, node);
        }
    }

    if (!pq) return NULL;

    while (pq && pq->next) {
        NodeHuffman* a = popPQ(pq);
        NodeHuffman* b = popPQ(pq);
        NodeHuffman* parent = new NodeHuffman('\0', a->frekuensi + b->frekuensi);
        parent->left = a;
        parent->right = b;
        pushPQ(pq, parent);
    }

    NodeHuffman* root = popPQ(pq);
    return root;
}

inline void generateKodeHuffman(NodeHuffman* root, std::string prefix, std::string codes[256]) {
    if (!root) return;
    if (!root->left && !root->right) {
        if (prefix.empty()) prefix = "0";
        unsigned char uc = (unsigned char)root->data;
        codes[uc] = prefix;
        return;
    }
    generateKodeHuffman(root->left, prefix + "0", codes);
    generateKodeHuffman(root->right, prefix + "1", codes);
}

inline void tampilkanKodeHuffman(const std::string codes[256]) {
    std::cout << "\n=== Kode Huffman (karakter : kode) ===\n";
    for (int i = 0; i < 256; i++) {
        if (!codes[i].empty()) {
            char c = (char)i;
            std::cout << "'";
            if (c == ' ') std::cout << "[spasi]";
            else if (c == '\n') std::cout << "[newline]";
            else if (c == '\t') std::cout << "[tab]";
            else std::cout << c;
            std::cout << "' : " << codes[i] << "\n";
        }
    }
}

inline std::string encodeHuffmanBits(const std::string& teks, const std::string codes[256]) {
    std::string bits;
    // Perkiraan kapasitas agar tidak terlalu sering realloc
    bits.reserve(teks.size() * 2);
    for (size_t i = 0; i < teks.size(); i++) {
        unsigned char uc = (unsigned char)teks[i];
        bits += codes[uc];
    }
    return bits;
}

inline std::string decodeHuffmanBits(const std::string& bits, NodeHuffman* root) {
    if (!root) return "";

    // Kasus khusus: hanya 1 karakter unik
    if (!root->left && !root->right) {
        std::string out;
        out.assign(bits.size(), root->data);
        return out;
    }

    std::string out;
    NodeHuffman* cur = root;
    for (size_t i = 0; i < bits.size(); i++) {
        char b = bits[i];
        if (b == '0') cur = cur->left;
        else if (b == '1') cur = cur->right;
        else continue;

        if (!cur) {
            // Bitstream tidak valid; reset supaya tidak crash
            cur = root;
            continue;
        }

        if (!cur->left && !cur->right) {
            out.push_back(cur->data);
            cur = root;
        }
    }
    return out;
}

// =============================
// Layanan Shopping

inline std::string intToStrSimple(int val) {
    if (val == 0) return std::string("0");
    bool neg = val < 0;
    unsigned int v = neg ? (unsigned int)(-val) : (unsigned int)val;
    std::string r = "";
    while (v > 0) { r = char('0' + (v % 10)) + r; v /= 10; }
    if (neg) r = "-" + r;
    return r;
}

struct ShopProduct {
    std::string nama;
    int harga;
};

struct ShoppingCartItem {
    int productIndex;
    int qty;
};

class CartQueue {
private:
    ShoppingCartItem items[100];
    int head, tail, count;
public:
    CartQueue() { head = 0; tail = -1; count = 0; }
    bool isEmpty() { return count == 0; }
    bool isFull() { return count == 100; }
    int size() { return count; }

    void enqueue(int prodIdx, int qty) {
        if (isFull()) { std::cout << "Keranjang penuh!" << std::endl; return; }
        tail = (tail + 1) % 100;
        items[tail].productIndex = prodIdx;
        items[tail].qty = qty;
        count++;
    }

    void clear() { head = 0; tail = -1; count = 0; }

    void display(ShopProduct products[], int prodCount) {
        (void)prodCount;
        if (isEmpty()) { std::cout << "Keranjang kosong!" << std::endl; return; }
        std::cout << "\n=== Keranjang Belanja ===\n";
        int idx = head; int no = 1;
        for (int i = 0; i < count; i++) {
            ShoppingCartItem &it = items[idx];
            std::cout << no++ << ". " << products[it.productIndex].nama << " x" << it.qty
                      << " - Rp " << products[it.productIndex].harga * it.qty << "\n";
            idx = (idx + 1) % 100;
        }
    }

    std::string makeReceipt(ShopProduct products[]) {
        if (isEmpty()) return "";
        std::string s = "--- STRUK BELANJA ---\n";
        int idx = head;
        int total = 0;
        for (int i = 0; i < count; i++) {
            ShoppingCartItem &it = items[idx];
            int linePrice = products[it.productIndex].harga * it.qty;
            s += products[it.productIndex].nama + " x" + intToStrSimple(it.qty) + " = Rp " + intToStrSimple(linePrice) + "\n";
            total += linePrice;
            idx = (idx + 1) % 100;
        }
        s += std::string("Total = Rp ") + intToStrSimple(total) + "\n";
        return s;
    }

    int computeTotal(ShopProduct products[]) {
        if (isEmpty()) return 0;
        int idx = head;
        int total = 0;
        for (int i = 0; i < count; i++) {
            ShoppingCartItem &it = items[idx];
            total += products[it.productIndex].harga * it.qty;
            idx = (idx + 1) % 100;
        }
        return total;
    }
};

inline void initShopProducts(ShopProduct products[], int &prodCount) {
    prodCount = 6;
    products[0].nama = "Kaos Polos"; products[0].harga = 75000;
    products[1].nama = "Celana Jeans"; products[1].harga = 120000;
    products[2].nama = "Sepatu Olahraga"; products[2].harga = 250000;
    products[3].nama = "Tas Ransel"; products[3].harga = 150000;
    products[4].nama = "Topi"; products[4].harga = 45000;
    products[5].nama = "Jaket"; products[5].harga = 200000;
}

inline void tampilkanProdukShopping(ShopProduct products[], int prodCount) {
    std::cout << "\n=== Daftar Produk Shopping ===\n";
    for (int i = 0; i < prodCount; i++) {
        std::cout << i + 1 << ". " << products[i].nama << " - Rp " << products[i].harga << "\n";
    }
}

inline void tambahProdukManualDanMasukKeranjang(CartQueue &cart, ShopProduct products[], int &prodCount) {
    if (prodCount >= 20) {
        std::cout << "Daftar produk penuh!" << std::endl;
        return;
    }

    std::string nama;
    int harga;
    int qty;

    std::cout << "Masukkan nama produk: ";
    std::cin.ignore();
    std::getline(std::cin, nama);
    std::cout << "Masukkan harga: Rp ";
    std::cin >> harga;
    std::cout << "Masukkan jumlah: ";
    std::cin >> qty;

    if (nama.empty() || harga <= 0 || qty <= 0) {
        std::cout << "Input tidak valid." << std::endl;
        return;
    }

    int newIndex = prodCount;
    products[newIndex].nama = nama;
    products[newIndex].harga = harga;
    prodCount++;

    cart.enqueue(newIndex, qty);
    std::cout << "Produk ditambahkan ke keranjang." << std::endl;
}

inline void tambahProdukKeKeranjang(CartQueue &cart, ShopProduct products[], int prodCount) {
    (void)products;
    int idx, qty;
    std::cout << "Masukkan nomor produk yang ingin ditambah: ";
    std::cin >> idx;
    if (idx < 1 || idx > prodCount) { std::cout << "Produk tidak valid." << std::endl; return; }
    std::cout << "Masukkan jumlah: ";
    std::cin >> qty;
    if (qty <= 0) { std::cout << "Jumlah tidak valid." << std::endl; return; }
    cart.enqueue(idx - 1, qty);
    std::cout << "Produk ditambahkan ke keranjang." << std::endl;
}

// Riwayat belanja (persist selama program berjalan)
// Catatan: C++11 tidak mendukung inline variables, jadi pakai static internal linkage.
static std::string riwayatBelanja[200];
static int riwayatCount = 0;

inline void checkoutBelanja(CartQueue &cart, ShopProduct products[], int prodCount, pembayaran &pay) {
    (void)prodCount;
    if (cart.isEmpty()) { std::cout << "Keranjang kosong. Tidak ada yang di-checkout." << std::endl; return; }

    int subtotal = cart.computeTotal(products);
    std::cout << "\nSubtotal: Rp " << subtotal << std::endl;

    Alamat alamat;
    alamat.inputalamat();
    int ongkir = alamat.gettotalongkir();

    bool berhasil = pay.prosesPembayaranStatus(subtotal, ongkir);
    if (!berhasil) return;

    std::string receipt = cart.makeReceipt(products);
    receipt += std::string("Ongkir = Rp ") + intToStrSimple(ongkir) + "\n";
    receipt += std::string("Grand Total = Rp ") + intToStrSimple(subtotal + ongkir) + "\n";

    if (riwayatCount < 200) riwayatBelanja[riwayatCount++] = receipt;

    std::ofstream ofs("shopping_history.txt", std::ios::app);
    if (ofs.is_open()) {
        ofs << receipt << "\n";
        ofs.close();
    }

    std::cout << "Checkout berhasil. Struk:\n" << receipt;
    cart.clear();
}

inline void tampilkanRiwayatBelanja() {
    if (riwayatCount == 0) { std::cout << "Belum ada riwayat belanja." << std::endl; return; }
    std::cout << "\n=== Riwayat Transaksi Belanja ===\n";
    for (int i = 0; i < riwayatCount; i++) {
        std::cout << "Transaksi " << i + 1 << ":\n" << riwayatBelanja[i] << "\n";
    }
}

inline void optimasiDataBelanja_Huffman() {
    if (riwayatCount == 0) { std::cout << "Belum ada riwayat belanja untuk dioptimasi." << std::endl; return; }

    std::string teks = riwayatBelanja[riwayatCount - 1];
    std::cout << "\n-- Optimasi Data Belanja (Huffman) untuk transaksi terakhir --\n";
    std::cout << "Struk asli:\n" << teks << "\n";

    NodeHuffman* root = buildHuffmanTree(teks);
    if (!root) { std::cout << "Gagal membuat Huffman Tree." << std::endl; return; }

    std::string codes[256];
    for (int i = 0; i < 256; i++) codes[i] = "";
    generateKodeHuffman(root, "", codes);

    int asliBits = (int)teks.size() * 8;
    int compressedBits = 0;
    for (size_t i = 0; i < teks.size(); i++) {
        unsigned char uc = (unsigned char)teks[i];
        compressedBits += (int)codes[uc].size();
    }

    tampilkanKodeHuffman(codes);
    std::cout << "\nUkuran asli (perkiraan) : " << asliBits << " bit" << std::endl;
    std::cout << "Ukuran terkompresi      : " << compressedBits << " bit" << std::endl;
    if (asliBits > 0) {
        double ratio = (double)compressedBits / (double)asliBits * 100.0;
        std::cout << "Rasio kompresi          : " << ratio << "%" << std::endl;
    }

    // Demo encode -> decode agar terlihat metodenya benar-benar bekerja
    std::string encodedBits = encodeHuffmanBits(teks, codes);
    std::string decodedText = decodeHuffmanBits(encodedBits, root);

    std::cout << "\n-- Demo Encoding/Decoding Huffman --\n";
    std::cout << "Panjang bit hasil encode : " << encodedBits.size() << " bit" << std::endl;
    std::cout << "Decode sesuai teks asli  : " << (decodedText == teks ? "YA" : "TIDAK") << std::endl;
    if (encodedBits.size() > 0) {
        size_t preview = encodedBits.size() < 200 ? encodedBits.size() : 200;
        std::cout << "Contoh bit (awal)        : " << encodedBits.substr(0, preview);
        if (preview < encodedBits.size()) std::cout << "...";
        std::cout << std::endl;
    }

    freeHuffmanTree(root);
}

inline void layananShopping() {
    ShopProduct products[20];
    int prodCount = 0;
    initShopProducts(products, prodCount);

    CartQueue cart;
    static pembayaran pay;
    int pilihan = -1;

    while (pilihan != 0) {
        std::cout << "\n=== Layanan Shopping ===\n";
        std::cout << "1) Lihat Daftar Produk\n";
        std::cout << "2) Tambah Produk ke Keranjang\n";
        std::cout << "3) Lihat Keranjang Belanja\n";
        std::cout << "4) Checkout Belanja\n";
        std::cout << "5) Riwayat Transaksi Belanja\n";
        std::cout << "6) Optimasi Data Belanja (Huffman Coding)\n";
        std::cout << "0) Kembali\n";
        std::cout << "Pilih: ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanProdukShopping(products, prodCount);
                break;
            case 2:
                std::cout << "\n1) Pilih dari daftar\n";
                std::cout << "2) Input produk manual\n";
                std::cout << "Pilih: ";
                {
                    int sub = 0;
                    std::cin >> sub;
                    if (sub == 1) {
                        tampilkanProdukShopping(products, prodCount);
                        tambahProdukKeKeranjang(cart, products, prodCount);
                    } else if (sub == 2) {
                        tambahProdukManualDanMasukKeranjang(cart, products, prodCount);
                    } else {
                        std::cout << "Pilihan tidak valid." << std::endl;
                    }
                }
                break;
            case 3:
                cart.display(products, prodCount);
                break;
            case 4:
                checkoutBelanja(cart, products, prodCount, pay);
                break;
            case 5:
                tampilkanRiwayatBelanja();
                break;
            case 6:
                optimasiDataBelanja_Huffman();
                break;
            case 0:
                std::cout << "Kembali ke menu utama." << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid." << std::endl;
        }
    }
}

} // namespace shopping
