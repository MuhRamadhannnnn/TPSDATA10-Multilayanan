#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>
#include <string>
using namespace std;

// Node untuk double link list Profil
struct Profil {
    string nama;
    string no_hp;
    string alamat;
    string email;
    Profil* next;
    Profil* prev;
};

// Fungsi untuk menambah profil di akhir list
Profil* addEnd(Profil* last, string nama, string no_hp, string alamat, string email) {
    if (last == NULL) {
        Profil* newNode = new Profil();
        newNode->nama = nama;
        newNode->no_hp = no_hp;
        newNode->alamat = alamat;
        newNode->email = email;
        newNode->next = newNode->prev = newNode;
        return newNode;
    }
    
    Profil* newNode = new Profil();
    newNode->nama = nama;
    newNode->no_hp = no_hp;
    newNode->alamat = alamat;
    newNode->email = email;
    
    Profil* first = last->next;
    newNode->prev = last;
    last->next = newNode;
    newNode->next = first;
    first->prev = newNode;
    
    return newNode;
}

// Fungsi untuk menghapus profil berdasarkan nama
void deleteNode(Profil** last, string nama) {
    if (*last == NULL) {
        cout << "List kosong.\n";
        return;
    }
    
    Profil* current = (*last)->next;
    Profil* first = current;
    bool found = false;
    
    do {
        if (current->nama == nama) {
            found = true;
            if (current->next == current) {
                delete current;
                *last = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == *last) {
                    *last = current->prev;
                }
                delete current;
            }
            cout << "Data berhasil dihapus.\n";
            break;
        }
        current = current->next;
    } while (current != first);
    
    if (!found) {
        cout << "Data tidak ditemukan.\n";
    }
}

// Fungsi untuk update profil berdasarkan nama
void updateNode(Profil* last, string nama) {
    if (last == NULL) {
        cout << "List kosong.\n";
        return;
    }
    
    Profil* current = last->next;
    bool found = false;
    do {
        if (current->nama == nama) {
            found = true;
            cout << "Masukkan No HP baru  : ";
            getline(cin, current->no_hp);
            cout << "Masukkan Alamat baru : ";
            getline(cin, current->alamat);
            cout << "Masukkan Email baru  : ";
            getline(cin, current->email);
            cout << "Data berhasil diupdate.\n";
            break;
        }
        current = current->next;
    } while (current != last->next);
    
    if (!found) {
        cout << "Data tidak ditemukan.\n";
    }
}

// Fungsi untuk menampilkan semua profil
void display(Profil* last) {
    if (last == NULL) {
        cout << "List kosong.\n";
        return;
    }
    
    Profil* current = last->next;
    int no = 1;
    cout << "\n=== DATA PROFIL ===\n";
    do {
        cout << "\nData ke-" << no++ << endl;
        cout << "Nama   : " << current->nama << endl;
        cout << "No HP  : " << current->no_hp << endl;
        cout << "Alamat : " << current->alamat << endl;
        cout << "Email  : " << current->email << endl;
        current = current->next;
    } while (current != last->next);
}

#endif
