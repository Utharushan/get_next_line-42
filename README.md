# get_next_line

This project focuses on creating a function, `get_next_line()`, that reads one line at a time from a file descriptor. It is an essential exercise to practice **memory management**, **file handling**, and **working with buffers** in C programming.

## Objective

The goal of this project is to implement the `get_next_line()` function, which should read the next line from a file (or standard input) on each call, without reading the entire file into memory. The function should return the line as a string and handle multiple calls to process a large file efficiently.

## Functionality

The `get_next_line()` function reads input line by line and handles the following cases:

- **Line ending**: A line is considered as text ending with a newline character (`\n`), or the end of the file (EOF).
- **Buffer management**: The function should dynamically manage memory to read and store the current line.
- **Multiple calls**: The function should allow multiple calls to read different lines from the file or input stream.
- **End of file**: When the end of the file is reached, `get_next_line()` should return `NULL`.

### Prototype:
```c
char *get_next_line(int fd);
```

## Static Variables

In this project, **static variables** are essential to maintain state information across multiple calls to `get_next_line()`. Static variables persist their values between function calls but are not visible outside the function, making them ideal for this kind of use.

### Why Static Variables?
- **Buffer Management**: A static variable can store the buffer used to accumulate data between calls, ensuring that the function continues where it left off each time it's called.
- **File Descriptor Tracking**: Static variables can also track the state of each file descriptor (`fd`), enabling the function to handle multiple file reads efficiently across different invocations.
- **Efficiency**: Static variables minimize memory allocation and re-initialization on each call, making the function more efficient for large files or continuous reading operations.
