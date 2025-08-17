#include <iostream>
#include <fstream>
#include <string>
#include <direct.h> // for _mkdir()
#include <cstdlib>  // for getenv()

using namespace std;

const int MAX_REMINDERS = 100;

struct Reminder {
    string date;
    string message;
};

string getReminderFilePath() {
    // Build folder path in OneDrive Documents
    string folder = string(getenv("USERPROFILE")) + "\\OneDrive\\Documents\\ReminderDocuments";
    _mkdir(folder.c_str()); // create folder if it doesn't exist
    return folder + "\\reminders.txt";
}

void showMenu() {
    cout << "\nSimple Calendar/Reminder Tool" << endl;
    cout << "1. Add Reminder" << endl;
    cout << "2. View Reminders" << endl;
    cout << "3. Delete Reminder" << endl;
    cout << "4. Save Reminders" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

int loadReminders(Reminder reminders[], int maxReminders) {
    string path = getReminderFilePath();
    ifstream fin(path);
    int count = 0;
    string line;
    while (count < maxReminders && getline(fin, reminders[count].date)) {
        if (reminders[count].date.empty()) continue;
        if (!getline(fin, reminders[count].message)) break;
        getline(fin, line); // skip blank line
        count++;
    }
    fin.close();
    return count;
}

void saveReminders(Reminder reminders[], int numReminders) {
    string path = getReminderFilePath();
    ofstream fout(path);
    for (int i = 0; i < numReminders; ++i) {
        fout << reminders[i].date << endl;
        fout << reminders[i].message << endl;
        fout << endl;
    }
    fout.close();
    cout << "Reminders saved to " << path << endl;
}

void deleteReminder(Reminder reminders[], int& numReminders) {
    if (numReminders == 0) {
        cout << "No reminders to delete." << endl;
        return;
    }
    cout << "\nYour Reminders:" << endl;
    for (int i = 0; i < numReminders; ++i)
        cout << i + 1 << ". " << reminders[i].date << " - " << reminders[i].message << endl;

    cout << "Enter the number of the reminder to delete (0 to cancel): ";
    int delIndex;
    cin >> delIndex;
    cin.ignore();

    if (delIndex == 0) {
        cout << "Delete cancelled." << endl;
        return;
    }
    if (delIndex < 1 || delIndex > numReminders) {
        cout << "Invalid number. No reminder deleted." << endl;
        return;
    }

    cout << "Are you sure you want to delete reminder #" << delIndex << "? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = delIndex - 1; i < numReminders - 1; ++i)
            reminders[i] = reminders[i + 1];
        numReminders--;
        saveReminders(reminders, numReminders);
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
        cin.ignore();

        if (choice == 1) {
            if (numReminders >= MAX_REMINDERS) {
                cout << "Reminder list is full!" << endl;
                continue;
            }
            cout << "Enter date (MM/DD/YYYY): ";
            getline(cin, reminders[numReminders].date);
            cout << "Enter reminder message: ";
            getline(cin, reminders[numReminders].message);
            numReminders++;
            saveReminders(reminders, numReminders);
            cout << "Reminder added and saved!" << endl;

        } else if (choice == 2) {
            cout << "\nYour Reminders:" << endl;
            if (numReminders == 0)
                cout << "No reminders found." << endl;
            else
                for (int i = 0; i < numReminders; ++i)
                    cout << i + 1 << ". " << reminders[i].date << " - " << reminders[i].message << endl;

        } else if (choice == 3) {
            deleteReminder(reminders, numReminders);

        } else if (choice == 4) {
            saveReminders(reminders, numReminders);

        } else if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;

        } else {
            cout << "Invalid option. Try again." << endl;
        }
    }
    return 0;
}
