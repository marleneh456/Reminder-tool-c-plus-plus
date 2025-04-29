#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_REMINDERS = 100; // Maximum reminders stored

struct Reminder {
    string date;
    string message;
};

// Show menu options
void showMenu() {
    cout << "\nSimple Calendar/Reminder Tool" << endl;
    cout << "1. Add Reminder" << endl;
    cout << "2. View Reminders" << endl;
    cout << "3. Delete Reminder" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
}

// Load reminders from reminders.txt
int loadReminders(Reminder reminders[], int maxReminders) {
    ifstream fin("reminders.txt");
    int count = 0;
    string line;
    while (count < maxReminders && getline(fin, reminders[count].date)) {
        // Skip empty lines (blank lines between reminders)
        if (reminders[count].date.empty()) continue;
        if (!getline(fin, reminders[count].message)) break;
        // Skip the blank line after each reminder
        getline(fin, line);
        count++;
    }
    fin.close();
    return count;
}

// Save all reminders to reminders.txt (overwrite file)
void saveReminders(Reminder reminders[], int numReminders) {
    ofstream fout("reminders.txt");
    for (int i = 0; i < numReminders; ++i) {
        fout << reminders[i].date << endl;
        fout << reminders[i].message << endl;
        fout << endl; // Add a blank line between reminders
    }
    fout.close();
}

// Function to delete a reminder
void deleteReminder(Reminder reminders[], int& numReminders) {
    if (numReminders == 0) {
        cout << "No reminders to delete." << endl;
        return;
    }
    // Show all reminders first
    cout << "\nYour Reminders:" << endl;
    for (int i = 0; i < numReminders; ++i) {
        cout << i + 1 << ". " << reminders[i].date << " - " << reminders[i].message << endl;
    }
    cout << "Enter the number of the reminder you want to delete (or 0 to cancel): ";
    int delIndex;
    cin >> delIndex;
    cin.ignore(); // Clear newline

    if (delIndex == 0) {
        cout << "Delete cancelled." << endl;
        return;
    }
    if (delIndex < 1 || delIndex > numReminders) {
        cout << "Invalid number. No reminder deleted." << endl;
        return;
    }

    // Confirm before deleting
    cout << "Are you sure you want to delete reminder #" << delIndex << "? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(); // Clear newline

    if (confirm == 'y' || confirm == 'Y') {
        // Move all reminders after the deleted one forward
        for (int i = delIndex - 1; i < numReminders - 1; ++i) {
            reminders[i] = reminders[i + 1];
        }
        numReminders--;
        saveReminders(reminders, numReminders); // Save updated list
        cout << "Reminder deleted!" << endl;
    } else {
        cout << "Delete cancelled." << endl;
    }
}

int main() {
    Reminder reminders[MAX_REMINDERS];
    int numReminders = loadReminders(reminders, MAX_REMINDERS);

    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(); // Clear newline

        if (choice == 1) {
            // Add a reminder
            if (numReminders >= MAX_REMINDERS) {
                cout << "Sorry, reminder list is full!" << endl;
                continue;
            }
            cout << "Enter date (MM/DD/YYYY): ";
            getline(cin, reminders[numReminders].date);
            cout << "Enter reminder message: ";
            getline(cin, reminders[numReminders].message);
            numReminders++;
            saveReminders(reminders, numReminders); // Save after every add
            cout << "Reminder added and saved to reminders.txt!" << endl;

        } else if (choice == 2) {
            // View reminders
            cout << "\nYour Reminders:" << endl;
            if (numReminders == 0) {
                cout << "No reminders found." << endl;
            } else {
                for (int i = 0; i < numReminders; ++i) {
                    cout << i + 1 << ". " << reminders[i].date << " - " << reminders[i].message << endl;
                }
            }

        } else if (choice == 3) {
            // Delete reminder
            deleteReminder(reminders, numReminders);

        } else if (choice == 4) {
            cout << "Goodbye!" << endl;
            break;

        } else {
            cout << "Invalid option. Try again." << endl;
        }
    }
    return 0;
}
