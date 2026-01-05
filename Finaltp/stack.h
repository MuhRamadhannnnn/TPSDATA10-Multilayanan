#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
using namespace std;

// Stack untuk riwayat alamat pengiriman
#define MAKS_STACK_ALAMAT 10

class StackAlamatPengiriman {
private:
    string data[MAKS_STACK_ALAMAT];
    int top;
    
public:
    StackAlamatPengiriman() { 
        top = -1; 
    }

    bool isFull() { 
        return top == MAKS_STACK_ALAMAT - 1; 
    }
    
    bool isEmpty() { 
        return top == -1; 
    }

    void push(string alamat) {
        if (isFull()) {
            cout << "Stack alamat pengiriman penuh!\n";
            return;
        }
        data[++top] = alamat;
    }

    string pop() {
        if (isEmpty()) {
            cout << "Stack alamat pengiriman kosong!\n";
            return "";
        }
        string temp = data[top--];
        cout << "Alamat dihapus dari riwayat: " << temp << endl;
        return temp;
    }

    void tampilkan() {
        cout << "\nRiwayat Alamat Pengiriman (Stack):\n";
        if (isEmpty()) {
            cout << "(Kosong)\n";
            return;
        }
        for (int i = top; i >= 0; i--) {
            cout << i + 1 << ". " << data[i] << endl;
        }
    }
};

#endif
