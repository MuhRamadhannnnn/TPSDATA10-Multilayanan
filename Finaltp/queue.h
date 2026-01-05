#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

#define MAX_QUEUE_SIZE 100

struct QueueItem {
    string nama_makanan;
    int harga;
    string restoran;
    string tanggal;
};

class CircularQueue {
private:
    QueueItem items[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int count;
    
public:
    CircularQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }
    
    bool isFull() {
        return count == MAX_QUEUE_SIZE;
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    int getSize() {
        return count;
    }
    
    void enqueue(string nama, int harga, string restoran, string tanggal) {
        if (isFull()) {
            cout << "Queue penuh! Tidak dapat menambah elemen baru.\n";
            return;
        }
        
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        items[rear].nama_makanan = nama;
        items[rear].harga = harga;
        items[rear].restoran = restoran;
        items[rear].tanggal = tanggal;
        count++;
    }
    
    QueueItem dequeue() {
        QueueItem temp;
        if (isEmpty()) {
            cout << "Queue kosong! Tidak ada elemen untuk dihapus.\n";
            temp.nama_makanan = "";
            temp.harga = 0;
            temp.restoran = "";
            temp.tanggal = "";
            return temp;
        }
        
        temp = items[front];
        front = (front + 1) % MAX_QUEUE_SIZE;
        count--;
        return temp;
    }
    
    QueueItem peek() {
        QueueItem temp;
        if (isEmpty()) {
            cout << "Queue kosong!\n";
            temp.nama_makanan = "";
            temp.harga = 0;
            temp.restoran = "";
            temp.tanggal = "";
            return temp;
        }
        return items[front];
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Queue kosong.\n";
            return;
        }
        
        cout << "\n=== Isi Circular Queue ===\n";
        cout << "Total elemen: " << count << "\n";
        cout << "Kapasitas: " << MAX_QUEUE_SIZE << "\n\n";
        
        int index = front;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << items[index].nama_makanan 
                 << " - Rp " << items[index].harga 
                 << " (" << items[index].restoran << ")"
                 << " - " << items[index].tanggal << endl;
            index = (index + 1) % MAX_QUEUE_SIZE;
        }
        cout << endl;
    }
    
    void clear() {
        front = 0;
        rear = -1;
        count = 0;
        cout << "Queue telah dikosongkan.\n";
    }
};

#endif
