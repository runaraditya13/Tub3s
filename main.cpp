#include "TextEditor.h"
#include <iostream>

using namespace std;

int main() {
    int choice;
    string input;

    do {
        cout << "\n=== Text Editor ===" << endl;
        cout << "1. Add Line" << endl;
        cout << "2. Delete Line" << endl;
        cout << "3. Display Text" << endl;
        cout << "4. Save to File" << endl;
        cout << "5. Load from File" << endl;
        cout << "6. Undo" << endl;
        cout << "7. Redo" << endl;
        cout << "8. View Files in Directory" << endl;
        cout << "9. Delete File" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter text: ";
            getline(cin, input);
            addLine(input);
            break;
        case 2:
            cout << "Enter line number to delete: ";
            int line;
            cin >> line;
            deleteLine(line);
            break;
        case 3:
            displayText();
            break;
        case 4:
            cout << "Enter filename to save: ";
            cin >> input;
            saveToFile(input);
            break;
        case 5:
            cout << "Enter filename to load: ";
            cin >> input;
            loadFromFile(input);
            break;
        case 6:
            undo();
            break;
        case 7:
            redo();
            break;
        case 8:
            viewFiles();
            break;
        case 9:
            cout << "Enter filename to delete: ";
            cin >> input;
            deleteFile(input);
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
