#ifndef TEXTEDITOR_H_INCLUDED
#define TEXTEDITOR_H_INCLUDED

#include <string>

using namespace std;

// Struktur Node untuk Single Linked List
struct Node {
    string text;
    Node* next;

    Node(const string& text) : text(text), next(nullptr) {}
};

// Struktur untuk menyimpan aksi (Undo/Redo)
struct Action {
    string type; // "ADD" atau "DELETE"
    string text; // Teks yang terlibat dalam aksi
};

// Deklarasi variabel global
extern Node* head;
extern Node* tail;
extern int lineCount;

// Variabel global untuk undo/redo
extern Action undoActions[100];
extern Action redoActions[100];
extern int undoTop;
extern int redoTop;

// Deklarasi fungsi global
void addLine(const string& text);
void deleteLine(int lineNumber);
void displayText();
void saveToFile(const string& filename);
void loadFromFile(const string& filename);
void undo();
void redo();
void deleteFile(const string& filename); // Menghapus file
void viewFiles();                       // Melihat daftar file di direktori

#endif // TEXTEDITOR_H_INCLUDED
