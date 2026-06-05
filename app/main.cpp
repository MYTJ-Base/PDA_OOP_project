#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "PDA.h"
#include "Task.h"
#include "Reminder.h"
#include "Note.h"

using namespace std;

enum AppMode { NORMAL, TEST };

// ─── Helper: safely read an integer ─────────────────────────────────────────
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. Please enter a number." << endl;
    }
}

// ─── Helper: safely read a string (including spaces) ───────────────────────
string readString(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

/**
 * @brief Helper to handle ID input with a "list" option.
 * @param pda The PDA object.
 * @param type The item type.
 * @return The ID selected, or -1 if user cancels.
 */
int promptForId(const PDA& pda, const string& type, const string& action) {
    if (!pda.hasItems(type)) {
        cout << "  No " << type << "s available to " << action << "." << endl;
        return -1;
    }

    while (true) {
        cout << endl;
        cout << "  Enter " << type << " ID to " << action << " (or type '0' to list all " << type << "s, '-1' to cancel): ";
        int input;
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter a number." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (input == -1) return -1;
        if (input == 0) {
            pda.listItems(type);
            continue;
        }
        return input;
    }
}

// ─── Opening banner ──────────────────────────────────────────────────────────
void showBanner(AppMode mode) {
    cout << endl;
    cout << "  ==========================================" << endl;
    cout << "         PERSONAL DIGITAL ASSISTANT         " << endl;
    cout << "  ==========================================" << endl;
    cout << "   Current Mode: " << (mode == NORMAL ? "[NORMAL]" : "[TEST - ISOLATED]") << endl;
    cout << "  ==========================================" << endl;
}

// ─── Main menu ───────────────────────────────────────────────────────────────
void showMenu() {
    cout << endl;
    cout << "  1. Tasks" << endl;
    cout << "  2. Reminders" << endl;
    cout << "  3. Notes" << endl;
    cout << "  4. Show Due Reminders" << endl;
    cout << "  5. Search All Items" << endl;
    cout << "  6. Switch Mode (Normal/Test)" << endl;
    cout << "  7. Save & Exit" << endl;
    cout << endl;
}

// ─── Task sub-menu ───────────────────────────────────────────────────────────
void showTaskMenu(PDA& pda) {
    int choice;
    do {
        cout << endl;
        cout << "  ---- TASKS ----" << endl;
        cout << "    1. Add Task" << endl;
        cout << "    2. List Tasks" << endl;
        cout << "    3. Mark Task Complete" << endl;
        cout << "    4. Delete Task" << endl;
        cout << "    5. Back to Main Menu" << endl;
        cout << endl;

        choice = readInt("  Choose an option: ");

        switch (choice) {
            case 1: {
                string title = readString("  Enter title: ");
                string dueDate = readString("  Enter due date (YYYY-MM-DD): ");
                string priority = readString("  Enter priority (High/Medium/Low): ");
                pda.addItem(new Task(pda.generateId(), title, dueDate, priority));
                cout << "  Task added!" << endl;
                break;
            }
            case 2:
                pda.listItems("task");
                break;
            case 3: {
                int id = promptForId(pda, "task", "mark complete");
                if (id != -1) pda.markTaskComplete(id);
                break;
            }
            case 4: {
                int id = promptForId(pda, "task", "delete");
                if (id != -1) pda.removeItem(id);
                break;
            }
            case 5: break;
            default: cout << "  Invalid option." << endl;
        }
    } while (choice != 5);
}

// ─── Reminder sub-menu ───────────────────────────────────────────────────────
void showReminderMenu(PDA& pda) {
    int choice;
    do {
        cout << endl;
        cout << "  ---- REMINDERS ----" << endl;
        cout << "    1. Add Reminder" << endl;
        cout << "    2. List Reminders" << endl;
        cout << "    3. Delete Reminder" << endl;
        cout << "    4. Back to Main Menu" << endl;
        cout << endl;

        choice = readInt("  Choose an option: ");

        switch (choice) {
            case 1: {
                string title = readString("  Enter title: ");
                string dateTime = readString("  Enter date/time (YYYY-MM-DD HH:MM): ");
                string message = readString("  Enter message: ");
                bool alarm = (readString("  Enable alarm? (y/n): ") == "y");
                pda.addItem(new Reminder(pda.generateId(), title, dateTime, message, alarm));
                cout << "  Reminder added!" << endl;
                break;
            }
            case 2:
                pda.listItems("reminder");
                break;
            case 3: {
                int id = promptForId(pda, "reminder", "delete");
                if (id != -1) pda.removeItem(id);
                break;
            }
            case 4: break;
            default: cout << "  Invalid option." << endl;
        }
    } while (choice != 4);
}

// ─── Note sub-menu ───────────────────────────────────────────────────────────
void showNoteMenu(PDA& pda) {
    int choice;
    do {
        cout << endl;
        cout << "  ---- NOTES ----" << endl;
        cout << "    1. Add Note" << endl;
        cout << "    2. List Notes" << endl;
        cout << "    3. Delete Note" << endl;
        cout << "    4. Back to Main Menu" << endl;
        cout << endl;

        choice = readInt("  Choose an option: ");

        switch (choice) {
            case 1: {
                string title = readString("  Enter title: ");
                string content = readString("  Enter content: ");
                string date = readString("  Enter date (YYYY-MM-DD): ");
                pda.addItem(new Note(pda.generateId(), title, content, date));
                cout << "  Note added!" << endl;
                break;
            }
            case 2:
                pda.listItems("note");
                break;
            case 3: {
                int id = promptForId(pda, "note", "delete");
                if (id != -1) pda.removeItem(id);
                break;
            }
            case 4: break;
            default: cout << "  Invalid option." << endl;
        }
    } while (choice != 4);
}

int main() {
    PDA pda;
    AppMode currentMode = NORMAL;
    
    // Initial load
    pda.loadAll();

    int choice;
    do {
        showBanner(currentMode);
        showMenu();
        choice = readInt("  Choose an option (1-7): ");

        switch (choice) {
            case 1: showTaskMenu(pda); break;
            case 2: showReminderMenu(pda); break;
            case 3: showNoteMenu(pda); break;
            case 4: pda.showDueReminders(); break;
            case 5: pda.search(readString("  Enter search keyword: ")); break;
            case 6: {
                cout << "  Saving current data before switching..." << endl;
                pda.saveAll();
                pda.clearItems();
                
                if (currentMode == NORMAL) {
                    currentMode = TEST;
                    pda.setStoragePaths("data/test_tasks.txt", "data/test_reminders.txt", "data/test_notes.txt");
                    cout << "  Switched to TEST mode. Using isolated test files." << endl;
                } else {
                    currentMode = NORMAL;
                    pda.setStoragePaths("data/tasks.txt", "data/reminders.txt", "data/notes.txt");
                    cout << "  Switched to NORMAL mode. Using production files." << endl;
                }
                pda.loadAll();
                break;
            }
            case 7:
                cout << "  Saving data and exiting..." << endl;
                pda.saveAll();
                break;
            default:
                cout << "  Invalid option." << endl;
        }
    } while (choice != 7);

    return 0;
}
