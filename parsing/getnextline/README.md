# 🎉 Get_Next_Line

💥 **Get Next Line**: No more guessing what's read – this function handles it all like a champ! 🚀

---

## 📖 Overview

**Get Next Line** is a custom implementation of a function that reads a single line from a file descriptor, including support for files, standard input, and even bonuses like handling multiple file descriptors simultaneously. This project is part of the 1337/42 School curriculum, aiming to enhance your understanding of file I/O and dynamic memory management in C.

---

## 🚀 Features

- **Efficient Reading**: Reads one line at a time from a file or input stream.
- **Dynamic Buffering**: Handles any file size with a dynamically allocated buffer.
- **Multiple File Descriptors**: Bonus support for reading from multiple files simultaneously.
- **Norminette Compatible**: Adheres to the strict coding standards of 1337/42 School.

---

## 🛠️ Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Kharbachzoubair/Get_Next_Line.git
   cd Get_Next_Line
   gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
   ./gnl <file>

---

## 📚 Usage

1. Include the header file in your program:
   ```bash
   #include "get_next_line.h"
2. Call the get_next_line function in a loop to read lines from a file descriptor:
   ```bash
   int fd = open("file.txt", O_RDONLY);
   char *line;
    
   while ((line = get_next_line(fd)) != NULL)
   {
     printf("%s", line);
     free(line);
   }
   close(fd);
3. For bonus functionality, use the get_next_line_bonus files to handle multiple file descriptors.

---

## 🏆 Bonus Features
- Support for Multiple FDs: Read from several files simultaneously without mixing up lines.
- Error Handling: Gracefully manages errors and ensures no memory leaks.

---

## 📂 Files and Structure
- Source Files:
    - get_next_line.c: Core function logic.
    - get_next_line_utils.c: Utility functions for dynamic memory handling.
    - main.c: Example usage for testing.
- Bonus Files:
    - get_next_line_bonus.c and get_next_line_bonus.h: Extended support for multiple file descriptors.
    - Header File: get_next_line.h includes all prototypes and macros.

---

## 🙋‍♂️ Author

- **Kharbach Zoubair**
- [GitHub: Kharbachzoubair](https://github.com/Kharbachzoubair)







