
# get_next_line

## Overview

**get_next_line** is a project from the 42 Network curriculum designed to implement a function that reads one line at a time from a file descriptor (fd). This function handles edge cases and adheres to specific requirements, ensuring it works seamlessly for both files and standard input.

---

## Function Prototype

```c
char *get_next_line(int fd);
```

---

## Project Structure

| File                  | Description                              |
|-----------------------|------------------------------------------|
| `get_next_line.c`     | Contains the main `get_next_line` logic. |
| `get_next_line_utils.c` | Contains helper functions for `get_next_line`. |
| `get_next_line.h`     | Header file with function prototypes and macros. |

### For Bonus Part:

| File                          | Description                                      |
|-------------------------------|--------------------------------------------------|
| `get_next_line_bonus.c`       | Handles multiple file descriptors (fd).          |
| `get_next_line_utils_bonus.c` | Helper functions for the bonus implementation.   |
| `get_next_line_bonus.h`       | Header file for the bonus implementation.        |

---

## Features

1. **Line Reading:**
   - Reads a single line from a given file descriptor.
   - The line includes the newline (`\n`) character, if present.
   - Returns `NULL` if the end of the file is reached or an error occurs.

2. **Dynamic Buffer Size:**
   - The buffer size is defined during compilation using the `BUFFER_SIZE` macro.
   - Supports varying buffer sizes to optimize performance.

3. **Static Variable:**
   - Efficiently manages leftover data between function calls.

4. **File Descriptor Management (Bonus):**
   - Can handle multiple file descriptors simultaneously without losing context.

---

## Usage

### Compilation

Compile the mandatory files:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

For the bonus part:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

### Function Behavior

- Call `get_next_line(fd)` repeatedly to read one line at a time from the file descriptor.
- The function continues until the end of the file is reached or an error occurs.

### Example Usage
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Bonus Implementation

### Requirements:
- Manage multiple file descriptors independently.
- Use a single static variable.

### Example Bonus Usage:
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line1, *line2;

    if (fd1 < 0 || fd2 < 0)
        return (1);

    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);

    printf("File 1: %s", line1);
    printf("File 2: %s", line2);

    free(line1);
    free(line2);
    close(fd1);
    close(fd2);
    return (0);
}
```
