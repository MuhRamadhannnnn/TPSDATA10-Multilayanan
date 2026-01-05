# GOFOOD+ (Multi Layanan) — Final TP Struktur Data

Aplikasi CLI C++ bertema “super-app” sederhana yang berisi beberapa layanan:
- Login/registrasi + profil (berbasis data KTP)
- Layanan makanan (toko + searching/sorting + undo/cancel history)
- Layanan berpergian & pengiriman (ojek, antrian, GoSend, transportasi publik)
- Marketplace (BST produk + linked list brand)
- Shopping (keranjang + riwayat) + optimasi data struk dengan Huffman Coding

## Build & Run (Windows / MinGW)
Di folder project:

```bash
g++ -std=c++11 -O2 main.cpp -o gofoodplus.exe
./gofoodplus.exe
```

Catatan:
- Program membaca file menu/tarif dari folder `menu_toko/` dan `ojek_toko/`.
- Riwayat disimpan ke: `login_history.txt`, `shopping_history.txt`, dll.

## Struktur Data yang Digunakan
- **Array**: keranjang shopping, stack alamat, circular queue.
- **Stack (array)**: `StackAlamatPengiriman`.
- **Queue (circular array)**: `CircularQueue`, `CartQueue`.
- **Linked List**:
  - Single linked list: `OrderList` (pesanan)
  - Circular linked list: `RiwayatPesanan` (riwayat)
  - Linked list di node brand: `BrandNode`
- **BST**: katalog produk marketplace (`ProductNode`).
- **Huffman Coding**: optimasi/kompresi struk shopping.

## Entry Point
- `main.cpp`: fungsi `main()` menjalankan login lalu menampilkan menu utama.

## Daftar Method/Fungsi yang Tersedia
Bagian ini merangkum method/fungsi yang *tersedia di kode* per modul.

### Modul KTP — `ktp.h`
- `void tampilkanKTP(const KTP& ktp)`
- `void inputKTP(KTP& ktp)`

### Login & User Data — `data.h`
**Class `DataManager`**
- `bool simpanUser(const AkunUser& user)`
- `bool cariUser(const string& username, AkunUser& user)`
- `bool validasiLogin(const string& username, const string& password)`
- `bool cekUsernameAda(const string& username)`
- `bool registrasiUser(const string& username, const string& password, const KTP& ktp)`
- `bool getDataKTP(const string& username, KTP& ktp)`
- `bool simpanLogLogin(const string& username)`
- `bool simpanKTPToFile(const string& username)`

**Class `MenuLogin`**
- `bool registrasi()`
- `bool login()`
- `bool tampilkanMenu()`
- `void logout()`
- `bool cekLogin()`
- `string getUsername()`
- `void tampilkanProfil()`

### Pesanan & Riwayat (Linked List) — `linkedlist.h`
**Class `OrderList`**
- `void tambahPesanan(string nama, int harga, string restoran, int qty = 1)`
- `bool kosong() const`
- `void tampilkanPesanan()`
- `int hitungTotalHarga()`
- `bool hapusPesananTerakhir()`
- `void hapusSemua()`
- `bool undoLastOrder()`
- `void tampilkanRiwayatPembatalan() const`
- `void pindahkanKeRiwayat(RiwayatPesanan& riwayat, const string& tanggal)`

**Class `RiwayatPesanan`**
- `void tambahRiwayat(string nama, int harga, string restoran, string tanggal)`
- `void tampilkanRiwayat()`
- `void hapusRiwayatLama(int batas)`

**Class `FoodLinkedList`**
- `void tambahMakanan(string nama, int harga, string jenis, string restoran)`
- `void tampilkanSemuaMakanan()`
- `void tampilkanBerdasarkanJenis(string jenis)`

### Profil Tambahan (Double Circular Linked List) — `profile.h`
- `Profil* addEnd(Profil* last, string nama, string no_hp, string alamat, string email)`
- `void deleteNode(Profil** last, string nama)`
- `void updateNode(Profil* last, string nama)`
- `void display(Profil* last)`

### Stack — `stack.h`
**Class `StackAlamatPengiriman`**
- `bool isFull()`
- `bool isEmpty()`
- `void push(string alamat)`
- `string pop()`
- `void tampilkan()`

### Queue — `queue.h`
**Class `CircularQueue`**
- `bool isFull()`
- `bool isEmpty()`
- `int getSize()`
- `void enqueue(string nama, int harga, string restoran, string tanggal)`
- `QueueItem dequeue()`
- `QueueItem peek()`
- `void display()`
- `void clear()`

### Pembayaran — `payment.h`
**Class `Alamat`**
- `void inputalamat()`
- `int gettotalongkir()`
- `string getalamat()`

**Class `pembayaran`**
- `bool prosesPembayaranStatus(int totalBelanja, int ongkir)`
- `void prosesPembayaran(int totalBelanja, int ongkir)`
- `template<typename TokoType> void strukPembayaran(int totalBelanja, int ongkir, TokoType& toko)`

### Layanan Makanan (Toko) — `toko_tp7.h`
**Class `PesananRating`**
- `void cariRestoranByRating()`

**Class `PesananHarga`**
- `void cariMakananByHarga()`

**Class `PesananJenis`**
- `void cariMakananByJenis()`

**Class `Toko`**
- `void shortingHarga()`
- `void kembaliKeMenu()`
- `void tampilkanRingkasanPesanan()`
- `void pilihsearchingdantoko()`
- `void searchingmakanan()`
- `void pilihantoko()`
- `void menampilkanmenu()`
- `void syncNewOrders()`
- `void displayCircular()`
- `void displayCancelHistory()`
- `bool undoLastOrder()`
- `void commitOrdersToHistory()`
- `int gettotalharga()`
- `void menuLayananMakanan()`

### Transportasi & Pengiriman — `transport.h`
**Class `pilihBdP`**
- `void loadDataOjek(OjekDestinasi dest[], int& count, const string& kategori)`
- `void menuOjekOnline()`
- `void menuPesanMobil()`
- `void menuGoSend()`
- `void tambahPengiriman()`
- `void tampilkanPengiriman()`
- `void menuTransportasiPublik()`
- `void menuCarBox()`
- `void mulai()`

### Marketplace — `marketplace.h`
- `void addBrand(ProductNode* product, string brand, int price)`
- `ProductNode* insertProduct(ProductNode* root, string name)`
- `ProductNode* findProduct(ProductNode* root, string name)`
- `void displayProducts(ProductNode* root)`
- `void displayBrands(ProductNode* product)`
- `ProductNode* initMarketplace()`
- `void layananMarketplace()`

### Shopping + Huffman — `shopping.h` (namespace `shopping`)
**Huffman Coding**
- `NodeHuffman* buildHuffmanTree(const std::string& teks)`
- `void generateKodeHuffman(NodeHuffman* root, std::string prefix, std::string codes[256])`
- `std::string encodeHuffmanBits(const std::string& teks, const std::string codes[256])`
- `std::string decodeHuffmanBits(const std::string& bits, NodeHuffman* root)`
- `void optimasiDataBelanja_Huffman()` (demo ukuran + encode/decode)

**Keranjang (Queue)**
- `CartQueue::enqueue(int prodIdx, int qty)`
- `CartQueue::display(ShopProduct products[], int prodCount)`
- `CartQueue::makeReceipt(ShopProduct products[])`
- `CartQueue::computeTotal(ShopProduct products[])`

**Flow Shopping**
- `void initShopProducts(ShopProduct products[], int &prodCount)`
- `void tampilkanProdukShopping(ShopProduct products[], int prodCount)`
- `void tambahProdukManualDanMasukKeranjang(CartQueue &cart, ShopProduct products[], int &prodCount)`
- `void tambahProdukKeKeranjang(CartQueue &cart, ShopProduct products[], int prodCount)`
- `void checkoutBelanja(CartQueue &cart, ShopProduct products[], int prodCount, pembayaran &pay)`
- `void tampilkanRiwayatBelanja()`
- `void layananShopping()`

### Fungsi Utility — `main.cpp`
- `void clearScreen()`
- `void pauseScreen()`
- `void menuProfil(Profil*& last)`
- `void menuLayananMakanan()`
- `int main()`

## Catatan
- `foodservice.h` juga berisi versi util searching/filter menu makanan berbasis `OrderList`, tetapi alur utama program memanggil layanan makanan dari `toko_tp7.h`.
