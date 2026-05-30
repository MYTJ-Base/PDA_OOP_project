# Personal Digital Assistant (PDA)

## Project Description
The Personal Digital Assistant (PDA) is a console-based application designed to help users efficiently manage their daily productivity. It provides a centralized system for organizing three core types of information: tasks that need to be completed, reminders for important upcoming events, and personal notes for capturing thoughts. By utilizing object-oriented principles, the application ensures that all items are stored securely and can be retrieved, searched, or modified through a simple, menu-driven interface.

## Features
- **Task Management**: Create, list, and delete tasks. Mark tasks as complete to track your progress.
- **Reminder System**: Set reminders for future events. The system can check due dates and notify you of what is important today.
- **Note Taking**: Capture and store personal notes quickly.
- **Global Search**: Find any item (task, reminder, or note) by searching for keywords in titles or content.
- **Persistent Storage**: All your data is automatically saved to text files and reloaded the next time you start the application.
- **Unique Identification**: Every item is assigned a unique ID for precise management and deletion.

## Folder Structure
```text
PDA_OOP_project /
├── src/
│   ├── Task.h / Task.cpp
│   ├── Reminder.h / Reminder.cpp
│   ├── Note.h / Note.cpp
│   ├── PDA.h / PDA.cpp
│   ├── PDAItems.h / PDAItems.cpp
│   └── main.cpp
│
├── data/
│   ├── tasks.txt
│   ├── reminders.txt
│   └── notes.txt
│
├── docs/
│   ├── README.md
│   ├── UML_diagram.png
│   └── flowchart_schedule.png
│
├── sample_data/
│   ├── sample_tasks.txt
│   ├── sample_note.txt
│   └── sample_reminders.txt
│
└── Makefile
```

## How to Compile
To build the application, open your terminal in the project root directory and type:
```bash
make
```
This will compile the source code and create an executable file named `pda`.

## How to Run
After successful compilation, start the program by typing:
```bash
./pda
```

## How to Test with Sample Data
To test the application with pre-filled sample data, copy the files from the `sample_data/` folder into the `data/` folder:
```bash
cp sample_data/* data/
```
Then, rename the copied files to match the expected names (e.g., rename `sample_tasks.txt` to `tasks.txt`).

## Group Members and Contributions
- **Member 1 (Lead Developer)**: Designed the core `PDA` manager class and implemented the file persistence system (loading/saving data).
- **Member 2 (Logic Specialist)**: Developed the inheritance hierarchy (`PDAItem` base class and `Task`, `Reminder`, `Note` derived classes).
- **Member 3 (UI/UX Designer)**: Created the menu-driven interface in `main.cpp` and handled user input validation.
- **Member 4 (Tester/QA)**: Prepared the sample data files and performed final testing to ensure all features work as expected.
- **Member 5 (Documentation)**: Created the UML diagrams, flowcharts, and the project README.

## Platform Differences
- **Linux/macOS**: Use the instructions above. The `make` command and `./pda` execution are native to these systems.
- **Windows**: 
    - If using **WSL** or **MinGW**, you can use the `make` command as described.
    - If using **Visual Studio**, you may need to create a new project and add the `.h` and `.cpp` files manually.
    - Ensure that the file paths in the code (e.g., `data/tasks.txt`) use the correct slashes for your environment if you encounter file loading errors.
