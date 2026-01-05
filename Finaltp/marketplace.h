#ifndef MARKETPLACE_H
#define MARKETPLACE_H

#include <iostream>
#include <string>

#include "payment.h"
using namespace std;

// Node untuk brand (linked list)
struct BrandNode {
    string brand;
    int price;
    BrandNode* next;
    
    BrandNode(string b, int p) : brand(b), price(p), next(NULL) {}
};

// Node untuk produk (BST)
struct ProductNode {
    string name;
    BrandNode* brands;
    ProductNode* left;
    ProductNode* right;
    
    ProductNode(string n) : name(n), brands(NULL), left(NULL), right(NULL) {}
};

// Fungsi untuk menambah brand ke produk
void addBrand(ProductNode* product, string brand, int price) {
    if (product == NULL) return;
    
    BrandNode* newBrand = new BrandNode(brand, price);
    if (!product->brands) {
        product->brands = newBrand;
    } else {
        BrandNode* temp = product->brands;
        while (temp->next) temp = temp->next;
        temp->next = newBrand;
    }
}

// Fungsi untuk insert produk ke BST
ProductNode* insertProduct(ProductNode* root, string name) {
    if (!root) return new ProductNode(name);
    
    if (name < root->name)
        root->left = insertProduct(root->left, name);
    else if (name > root->name)
        root->right = insertProduct(root->right, name);
        
    return root;
}

// Fungsi untuk mencari produk di BST
ProductNode* findProduct(ProductNode* root, string name) {
    if (!root) return NULL;
    if (root->name == name) return root;
    
    if (name < root->name)
        return findProduct(root->left, name);
    else
        return findProduct(root->right, name);
}

// Fungsi untuk menampilkan semua produk (in-order traversal)
void displayProducts(ProductNode* root) {
    if (!root) return;
    
    displayProducts(root->left);
    
    cout << "\n" << root->name << ":\n";
    BrandNode* temp = root->brands;
    int no = 1;
    while (temp) {
        cout << "  " << no++ << ". " << temp->brand << " - Rp " << temp->price << endl;
        temp = temp->next;
    }
    
    displayProducts(root->right);
}

// Fungsi untuk menampilkan brand suatu produk
void displayBrands(ProductNode* product) {
    if (!product || !product->brands) {
        cout << "Tidak ada brand tersedia.\n";
        return;
    }
    
    BrandNode* temp = product->brands;
    int idx = 1;
    while (temp) {
        cout << idx << ". " << temp->brand << " (Rp " << temp->price << ")" << endl;
        temp = temp->next;
        idx++;
    }
}

// Fungsi untuk inisialisasi produk marketplace
ProductNode* initMarketplace() {
    ProductNode* root = NULL;
    
    // Insert produk ke BST
    root = insertProduct(root, "Beras");
    root = insertProduct(root, "Gula");
    root = insertProduct(root, "Minyak Goreng");
    root = insertProduct(root, "Telur");
    root = insertProduct(root, "Sayur");
    root = insertProduct(root, "Daging");
    root = insertProduct(root, "Susu");
    root = insertProduct(root, "Garam");
    root = insertProduct(root, "Mie Instan");
    
    // Tambah brand untuk setiap produk
    addBrand(findProduct(root, "Beras"), "Ramos", 12000);
    addBrand(findProduct(root, "Beras"), "Setra", 15000);
    addBrand(findProduct(root, "Beras"), "Pandan Wangi", 17000);
    
    addBrand(findProduct(root, "Gula"), "Gulaku", 14000);
    addBrand(findProduct(root, "Gula"), "Rose Brand", 13500);
    addBrand(findProduct(root, "Gula"), "Tebu Asli", 13000);
    
    addBrand(findProduct(root, "Minyak Goreng"), "Bimoli", 20000);
    addBrand(findProduct(root, "Minyak Goreng"), "Tropical", 18500);
    addBrand(findProduct(root, "Minyak Goreng"), "Fortune", 19000);
    
    addBrand(findProduct(root, "Telur"), "Ayam Negeri", 25000);
    addBrand(findProduct(root, "Telur"), "Ayam Kampung", 35000);
    
    addBrand(findProduct(root, "Sayur"), "Bayam", 5000);
    addBrand(findProduct(root, "Sayur"), "Kangkung", 4000);
    addBrand(findProduct(root, "Sayur"), "Wortel", 6000);
    
    addBrand(findProduct(root, "Daging"), "Sapi Lokal", 90000);
    addBrand(findProduct(root, "Daging"), "Ayam Potong", 35000);
    
    addBrand(findProduct(root, "Susu"), "Indomilk", 12000);
    addBrand(findProduct(root, "Susu"), "Ultra", 11000);
    addBrand(findProduct(root, "Susu"), "Greenfields", 15000);
    
    addBrand(findProduct(root, "Garam"), "Refina", 4000);
    addBrand(findProduct(root, "Garam"), "Cap Kapal", 3500);
    
    addBrand(findProduct(root, "Mie Instan"), "Indomie", 3500);
    addBrand(findProduct(root, "Mie Instan"), "Supermi", 3000);
    addBrand(findProduct(root, "Mie Instan"), "Mie Sedaap", 3200);
    
    return root;
}

// Fungsi untuk layanan marketplace
void layananMarketplace() {
    static ProductNode* root = NULL;
    if (!root) root = initMarketplace();

    static pembayaran pay;
    int menuMarketplace;
    
    // Struct untuk keranjang
    struct CartItem {
        string product;
        string brand;
        int price;
        int qty;
    };
    CartItem cart[20];
    int cartCount = 0;
    
    do {
        cout << "\n========================================\n";
        cout << "        LAYANAN MARKETPLACE\n";
        cout << "========================================\n";
        cout << "1. Tampilkan Seluruh Produk dan Merk\n";
        cout << "2. Cari Produk dan Merk\n";
        cout << "3. Pesan Produk\n";
        cout << "4. Tambah Produk & Merk (Input)\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "========================================\n";
        cout << "Pilih menu: ";
        cin >> menuMarketplace;
        cin.ignore();
        
        if (menuMarketplace == 1) {
            cout << "\n=== DAFTAR PRODUK DAN MERK ===\n";
            displayProducts(root);
            
        } else if (menuMarketplace == 2) {
            string cariProduk;
            cout << "\nMasukkan nama produk yang dicari: ";
            getline(cin, cariProduk);
            
            ProductNode* prod = findProduct(root, cariProduk);
            if (!prod) {
                cout << "Produk tidak ditemukan!\n";
            } else {
                cout << "\nMerk untuk " << cariProduk << ":\n";
                displayBrands(prod);
            }
            
        } else if (menuMarketplace == 3) {
            // Sub-menu pemesanan produk
            int menuPesan;
            bool pesananSelesai = false, pesananBatal = false;
            
            do {
                cout << "\n--- Menu Pemesanan Produk ---\n";
                cout << "1. Cari & Pesan Produk\n";
                cout << "2. Input Pesanan Manual\n";
                cout << "3. Lihat Keranjang\n";
                cout << "4. Checkout & Bayar\n";
                cout << "5. Batalkan Pesanan\n";
                cout << "0. Kembali\n";
                cout << "Pilih menu: ";
                cin >> menuPesan;
                cin.ignore();
                
                if (menuPesan == 1) {
                    string cariProduk;
                    cout << "\nMasukkan nama produk yang ingin dibeli: ";
                    getline(cin, cariProduk);
                    
                    ProductNode* prod = findProduct(root, cariProduk);
                    if (!prod) {
                        cout << "Produk tidak ditemukan!\n";
                        continue;
                    }
                    
                    cout << "\nPilih merk:\n";
                    displayBrands(prod);
                    
                    int pilihMerk, qty;
                    cout << "\nNomor merk: ";
                    cin >> pilihMerk;
                    cout << "Jumlah yang ingin dibeli: ";
                    cin >> qty;
                    cin.ignore();
                    
                    // Cari brand yang dipilih
                    BrandNode* temp = prod->brands;
                    int idx = 1;
                    while (temp && idx < pilihMerk) {
                        temp = temp->next;
                        idx++;
                    }
                    
                    if (!temp) {
                        cout << "Merk tidak ditemukan!\n";
                        continue;
                    }
                    
                    if (cartCount >= 20) {
                        cout << "\nKeranjang penuh!" << endl;
                        continue;
                    }

                    // Tambah ke keranjang
                    cart[cartCount].product = prod->name;
                    cart[cartCount].brand = temp->brand;
                    cart[cartCount].price = temp->price;
                    cart[cartCount].qty = qty;
                    cartCount++;
                    
                    cout << "\n✓ Ditambahkan ke keranjang: " << prod->name 
                         << " - " << temp->brand << " x" << qty << "\n";
                    
                } else if (menuPesan == 2) {
                    if (cartCount >= 20) {
                        cout << "\nKeranjang penuh!" << endl;
                        continue;
                    }

                    string product, brand;
                    int price, qty;
                    cout << "\nMasukkan nama produk: ";
                    getline(cin, product);
                    cout << "Masukkan nama merk: ";
                    getline(cin, brand);
                    cout << "Masukkan harga satuan: Rp ";
                    cin >> price;
                    cout << "Masukkan jumlah (qty): ";
                    cin >> qty;
                    cin.ignore();

                    if (product.empty() || brand.empty() || price <= 0 || qty <= 0) {
                        cout << "Input tidak valid!" << endl;
                        continue;
                    }

                    cart[cartCount].product = product;
                    cart[cartCount].brand = brand;
                    cart[cartCount].price = price;
                    cart[cartCount].qty = qty;
                    cartCount++;

                    cout << "\n✓ Ditambahkan ke keranjang: " << product
                         << " - " << brand << " x" << qty << "\n";

                } else if (menuPesan == 3) {
                    // Lihat keranjang
                    if (cartCount == 0) {
                        cout << "\nKeranjang kosong!\n";
                    } else {
                        cout << "\n=== KERANJANG BELANJA ===\n";
                        int total = 0;
                        for (int i = 0; i < cartCount; i++) {
                            int subtotal = cart[i].price * cart[i].qty;
                            cout << i+1 << ". " << cart[i].product << " - " 
                                 << cart[i].brand << " x" << cart[i].qty 
                                 << " = Rp " << subtotal << endl;
                            total += subtotal;
                        }
                        cout << "-------------------------\n";
                        cout << "Total: Rp " << total << endl;
                    }
                    
                } else if (menuPesan == 4) {
                    // Checkout & Bayar
                    if (cartCount == 0) {
                        cout << "\nKeranjang kosong!\n";
                        continue;
                    }
                    
                    int total = 0;
                    cout << "\n========================================\n";
                    cout << "            CHECKOUT\n";
                    cout << "========================================\n";
                    for (int i = 0; i < cartCount; i++) {
                        int subtotal = cart[i].price * cart[i].qty;
                        cout << cart[i].product << " - " << cart[i].brand 
                             << " x" << cart[i].qty << " = Rp " << subtotal << endl;
                        total += subtotal;
                    }
                    cout << "========================================\n";
                    cout << "Total belanja: Rp " << total << endl;
                    cout << "========================================\n";

                    Alamat alamat;
                    alamat.inputalamat();
                    int ongkir = alamat.gettotalongkir();

                    bool berhasil = pay.prosesPembayaranStatus(total, ongkir);
                    if (!berhasil) {
                        cout << "\nTransaksi dibatalkan. Keranjang tidak berubah.\n";
                        continue;
                    }

                    cout << "\n✓ Transaksi berhasil! Barang akan segera diantar.\n";
                    
                    // Reset keranjang
                    cartCount = 0;
                    pesananSelesai = true;
                    
                } else if (menuPesan == 5) {
                    cartCount = 0;
                    pesananBatal = true;
                    cout << "\n✓ Pesanan dibatalkan.\n";
                }
                
            } while (menuPesan != 0 && !pesananSelesai && !pesananBatal);
            
            if (pesananSelesai) {
                cout << "\nPesanan selesai diantar!\n";
            }

        } else if (menuMarketplace == 4) {
            string namaProduk, namaMerk;
            int harga;

            cout << "\n=== INPUT PRODUK & MERK BARU ===\n";
            cout << "Nama produk: ";
            getline(cin, namaProduk);
            cout << "Nama merk: ";
            getline(cin, namaMerk);
            cout << "Harga: Rp ";
            cin >> harga;
            cin.ignore();

            if (namaProduk.empty() || namaMerk.empty() || harga <= 0) {
                cout << "Input tidak valid!\n";
                continue;
            }

            ProductNode* prod = findProduct(root, namaProduk);
            if (!prod) {
                root = insertProduct(root, namaProduk);
                prod = findProduct(root, namaProduk);
            }

            addBrand(prod, namaMerk, harga);
            cout << "\n✓ Produk/merk berhasil ditambahkan.\n";
        }
        
    } while (menuMarketplace != 0);
}

#endif
