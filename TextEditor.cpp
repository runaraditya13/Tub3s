#include "TextEditor.h"
#include <iostream>
#include <fstream>
#include <filesystem> // Untuk manipulasi file system

using namespace std;
using namespace fs = std::filesystem;

// Definisi variabel global
Node* head = nullptr;
Node* tail = nullptr;
int lineCount = 0;
Action undoActions[100];
Action redoActions[100];
int undoTop = -1;
int redoTop = -1;

// Menambahkan baris teks ke dalam list
void addLine(const string& text) {
    Node* newNode = new Node(text);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    undoActions[++undoTop] = {"ADD", text};
    redoTop = -1; // Reset redo stack
    lineCount++;

}

// Menghapus baris tertentu berdasarkan nomor baris
void deleteLine(int lineNumber) {
    if (lineNumber <= 0 || lineNumber > lineCount) {
        cout << "Invalid line number!" << endl;
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    for (int i = 1; i < lineNumber; ++i) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    undoActions[++undoTop] = {"DELETE", temp->text};
    redoTop = -1; // Reset redo stack
    delete temp;
    lineCount--;
}

// Menampilkan teks dalam list
void displayText() {
    Node* temp = head;
    int lineNum = 1;
    while (temp != nullptr) {
        cout << lineNum++ << ": " << temp->text << endl;
        temp = temp->next;
    }
}

// Menyimpan teks ke file
void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        file << temp->text << endl;
        temp = temp->next;
    }

    file.close();
    cout << "Text saved to " << filename << endl;
}

// Memuat teks dari file
void loadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Hapus semua data di linked list yang ada
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    lineCount = 0;

    // Baca file baris demi baris dan tambahkan ke linked list
    string line;
    while (getline(file, line)) {
        addLine(line);
    }

    file.close();
    cout << "File loaded successfully from " << filename << endl;
}

// Membatalkan perubahan terakhir
void undo() {
    if (undoTop == -1) {
        cout << "Nothing to undo!" << endl;
        return;
    }

    Action lastAction = undoActions[undoTop--];
    redoActions[++redoTop] = lastAction;

    if (lastAction.type == "ADD") {
        deleteLine(lineCount);
    } else if (lastAction.type == "DELETE") {
        addLine(lastAction.text);
    }
}

// Mengulangi perubahan terakhir yang di-undo
void redo() {
    if (redoTop == -1) {
        cout << "Nothing to redo!" << endl;
        return;
    }

    Action lastRedo = redoActions[redoTop--];
    if (lastRedo.type == "ADD") {
        addLine(lastRedo.text);
    } else if (lastRedo.type == "DELETE") {
        deleteLine(lineCount);
    }
}

// Fungsi untuk menghapus file
void deleteFile(const string& filename) {
    if (fs::exists(filename)) {
        if (fs::remove(filename)) {
            cout << "File '" << filename << "' berhasil dihapus." << endl;
        } else {
            cout << "Gagal menghapus file '" << filename << "'." << endl;
        }
    } else {
        cout << "File '" << filename << "' tidak ditemukan." << endl;
    }
}

// Fungsi untuk melihat daftar file di direktori saat ini
void viewFiles() {
    cout << "Daftar file di direktori saat ini:" << endl;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file()) {
            cout << "- " << entry.path().filename().string() << endl;
        }
    }
}
