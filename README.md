# CLI-notes
Simple CLI note-taking application capable of creating, editing and displaying notes. Each note has a timestamp of when it was made. Notes are also encrypted so the text file cannot be read without the program (anyone can read your notes if they have the program, though).

## Building
This project only depends on C++17 and can be built using CMake:
```bash
cmake -B build
cmake --build build
```
The executable will be located in `build/notes`. Or build using your favorite compiler:
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o notes
```

## Usage
Simply run the executable after building and you'll be presented by a REPL interface. Type `help` for a list of all commands. The program will create a `note.txt` file in the same directory in which it is ran that will contain all of the encrypted notes.

## Credits
This project was made by Daniel Vishnevsky and is licensed under MIT License. It was made in August of 2025 and published on October 2026 as an effort to make all of my projects open-source.
