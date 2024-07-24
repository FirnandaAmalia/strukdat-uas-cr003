#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

struct Book { 
    int id;
    string title;
    string author;
    double price;
    int borrowStock; // Stok untuk dipinjam
    int buyStock;    // Stok untuk dibeli
};

vector<Book> library;
int currentId = 1;

void createBook() { //Fungsi CRUD
    Book newBook;
    newBook.id = currentId++;
    cout << "Masukkan judul buku: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Masukkan penulis buku: ";
    getline(cin, newBook.author);
    cout << "Masukkan harga buku: ";
    cin >> newBook.price;
    newBook.borrowStock = 2; // Default stok untuk dipinjam
    newBook.buyStock = 5;    // Default stok untuk dibeli
    library.push_back(newBook);
    cout << "Buku berhasil ditambahkan!\n";
}

void readBooks() {
    cout << "Menampilkan semua buku:\n";
    for (const auto &book : library) {
        cout << "ID: " << book.id 
             << ", Judul: " << book.title 
             << ", Penulis: " << book.author 
             << ", Harga: " << book.price 
             << ", Stok untuk dipinjam: " << book.borrowStock 
             << ", Stok untuk dibeli: " << book.buyStock << endl;
    }
}

void updateBook() {
    int id;
    cout << "Masukkan ID buku yang ingin diupdate: ";
    cin >> id;
    for (auto &book : library) {
        if (book.id == id) {
            cout << "Masukkan judul baru: ";
            cin.ignore();
            getline(cin, book.title);
            cout << "Masukkan penulis baru: ";
            getline(cin, book.author);
            cout << "Masukkan harga baru: ";
            cin >> book.price;
            cout << "Masukkan stok baru untuk dipinjam: ";
            cin >> book.borrowStock;
            cout << "Masukkan stok baru untuk dibeli: ";
            cin >> book.buyStock;
            cout << "Buku berhasil diupdate!\n";
            return;
        }
    }
    cout << "Buku dengan ID tersebut tidak ditemukan.\n";
}

void deleteBook() {
    int id;
    cout << "Masukkan ID buku yang ingin dihapus: ";
    cin >> id;
    for (auto it = library.begin(); it != library.end(); ++it) {
        if (it->id == id) {
            library.erase(it);
            cout << "Buku berhasil dihapus!\n";
            return;
        }
    }
    cout << "Buku dengan ID tersebut tidak ditemukan.\n";
}

void borrowBook() {
    int id;
    cout << "Masukkan ID buku yang ingin dipinjam: ";
    cin >> id;
    for (auto &book : library) {
        if (book.id == id) {
            if (book.borrowStock > 0) {
                book.borrowStock--;
                cout << "Buku berhasil dipinjam!\n";
                return;
            } else {
                cout << "Buku sedang dipinjam. Tunggu info pengembalian buku dari yang lain.\n";
                return;
            }
        }
    }
    cout << "Buku dengan ID tersebut tidak ditemukan.\n";
}

void buyBook() {
    int id, quantity;
    double money;
    cout << "Masukkan ID buku yang ingin dibeli: ";
    cin >> id;
    for (auto &book : library) {
        if (book.id == id) {
            if (book.buyStock == 0) {
                cout << "Stok buku kosong untuk dibeli.\n";
                return;
            }
            cout << "Harga buku \"" << book.title << "\" adalah " << book.price << ".\n";
            cout << "Masukkan jumlah buku yang ingin dibeli: ";
            cin >> quantity;
            if (quantity > book.buyStock) {
                cout << "Stok buku tidak cukup. Stok tersedia: " << book.buyStock << ".\n";
                return;
            }
            double totalPrice = book.price * quantity;
            cout << "Total harga untuk " << quantity << " buku adalah " << totalPrice << ".\n";
            cout << "Masukkan jumlah uang: ";
            cin >> money;
            if (money >= totalPrice) {
                double change = money - totalPrice;
                cout << "Anda telah membeli " << quantity << " buku dengan judul \"" << book.title << "\" seharga " << totalPrice << ".\n";
                if (change > 0) {
                    cout << "Uang kembalian Anda: " << change << ".\n";
                }
                book.buyStock -= quantity;
                return;
            } else {
                cout << "Uang Anda tidak cukup untuk membeli buku ini.\n";
                return;
            }
        }
    }
    cout << "Buku dengan ID tersebut tidak ditemukan.\n";
}

void adminMenu() {
    int choice;
    do {
        cout << "\nMenu Admin:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Lihat Buku\n";
        cout << "3. Update Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Logout\n";
        cout << "Pilihan: ";
        cin >> choice;
        switch (choice) {
            case 1: createBook(); break;
            case 2: readBooks(); break;
            case 3: updateBook(); break;
            case 4: deleteBook(); break;
            case 5: cout << "Logout berhasil.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 5);
}

void userMenu(const string& studentName) {
    int choice;
    do {
        cout << "\nMenu User (" << studentName << "):\n";
        cout << "1. Lihat Buku\n";
        cout << "2. Pinjam Buku\n";
        cout << "3. Beli Buku\n";
        cout << "4. Logout\n";
        cout << "Pilihan: ";
        cin >> choice;
        switch (choice) {
            case 1: readBooks(); break;
            case 2: borrowBook(); break;
            case 3: buyBook(); break;
            case 4: cout << "Logout berhasil.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 4);
}

void loadingAnimation() { 
    cout << "Loading";
    for (int i = 0; i < 3; ++i) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
    }
    cout << endl;
}

void welcomeAnimation() {
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    string welcomeMessage = "Selamat Datang di Perpustakaan Firnanda Amalia!";
    for (char c : welcomeMessage) {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout << "\n-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    cout << endl;
}

void login() {
    string role;
    cout << "Masukkan aktor (admin/user): ";
    cin >> role;
    loadingAnimation();
    if (role == "admin") {
        adminMenu();
    } else if (role == "user") {
        string studentName;
        cout << "Masukkan nama mahasiswa: ";
        cin.ignore();
        getline(cin, studentName);
        userMenu(studentName);
    } else {
        cout << "aktor tidak valid.\n";
    }
}

int main() {
    welcomeAnimation();
    int choice;
    do {
        cout << "\nSistem Informasi Perpustakaan\n";
        cout << "----------------------------\n";
        cout << "1. Login\n";
        cout << "2. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;
        switch (choice) {
            case 1: login(); break;
            case 2: cout << "Keluar dari sistem.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 2);
    return 0;
}

