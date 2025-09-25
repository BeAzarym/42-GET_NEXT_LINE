# GET_NEXT_LINE - File Reading Line by Line

A 42 Common Core project that implements a function to read files line by line using static variables and buffer management.

## Overview

The Get Next Line project implements a function that reads a file descriptor line by line, returning one line at a time on each function call. This project teaches crucial concepts in memory management, static variables, file I/O operations, and buffer handling in C programming.

The main challenge is to efficiently manage memory allocation and handle different buffer sizes while maintaining state between function calls using static variables. The implementation supports multiple file descriptors simultaneously in the bonus version.

## Quick Start

### Installation
```bash
git clone https://github.com/BeAzarym/42-GET_NEXT_LINE.git
cd get_next_line
```

### Compilation
```bash
# Basic version
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# Bonus version (multiple file descriptors)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c

# With test main
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

### Basic Usage
```c
#include "get_next_line.h"

int main()
{
    int fd;
    char *line;
    
    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## Function Prototype
```c
char *get_next_line(int fd);
```

### Parameters
| Parameter | Description | Type |
|-----------|-------------|------|
| `fd` | File descriptor to read from | `int` |

### Return Value
- **Success**: Returns the line read including the `\n` character (except for EOF without `\n`)
- **EOF/End**: Returns `NULL` when end of file is reached
- **Error**: Returns `NULL` on error (invalid fd, read error, memory allocation failure)

## Buffer Size Configuration

The `BUFFER_SIZE` is defined at compilation time and determines how many bytes are read at once:

```bash
# Small buffer (good for testing)
gcc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c

# Medium buffer (default in header)
gcc -D BUFFER_SIZE=500 get_next_line.c get_next_line_utils.c

# Large buffer (more efficient for big files)
gcc -D BUFFER_SIZE=4096 get_next_line.c get_next_line_utils.c
```

### Buffer Size Validation
- **Range**: 1 to 99,999 bytes
- **Default**: 500 bytes if not specified or out of range
- **Automatic Reset**: Invalid values are automatically reset to 500

## Testing

### Basic Tests
```bash
# Test with different buffer sizes
gcc -D BUFFER_SIZE=1 -o gnl_test1 get_next_line.c get_next_line_utils.c main.c
gcc -D BUFFER_SIZE=42 -o gnl_test42 get_next_line.c get_next_line_utils.c main.c
gcc -D BUFFER_SIZE=9999 -o gnl_large get_next_line.c get_next_line_utils.c main.c

# Run tests
./gnl_test1
./gnl_test42
./gnl_large
```

### Edge Case Tests
```bash
# Test with empty file
touch empty.txt
./gnl_test

# Test with file without newline at end
echo -n "No newline" > no_nl.txt
./gnl_test

# Test with only newlines
printf "\n\n\n\n" > only_nl.txt
./gnl_test

# Test with very long lines
python3 -c "print('x' * 10000)" > long_line.txt
./gnl_test
```

### Bonus Tests (Multiple File Descriptors)
```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);
int fd3 = open("file3.txt", O_RDONLY);

// Alternating reads from different files
char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);
char *line3 = get_next_line(fd3);
// Continue alternating...
```

## Project Structure

```
get_next_line/
├── get_next_line.c              # Main function implementation
├── get_next_line.h              # Header file with prototypes and definitions
├── get_next_line_utils.c        # Utility functions (strjoin, strdup, etc.)
├── get_next_line_bonus.c        # Bonus: Multiple file descriptors support
├── get_next_line_bonus.h        # Bonus header file
├── get_next_line_utils_bonus.c  # Bonus utility functions
├── main.c                       # Test file
├── test.txt                     # Sample test file
└── README.md                    # Project documentation
```

## Technical Implementation

### Core Components

#### 1. Static Buffer Management
```c
static char buffer[BUFFER_SIZE + 1];
```
- Maintains state between function calls
- Stores remaining characters after line extraction
- Automatically initialized to zero

#### 2. Dynamic Line Construction
- Lines are built dynamically using string joining
- Memory is allocated as needed for each line
- Handles lines longer than buffer size

#### 3. Newline Detection
```c
static int check_endline(char *str);
```
- Scans buffer for newline characters
- Returns position of `\n` or end of buffer
- Handles both `\n` and end-of-string scenarios

### Key Functions

#### Main Function
- **`get_next_line(int fd)`**: Main function that returns next line

#### Utility Functions
- **`ft_strjoin(char *s1, char *s2, int *check_newline)`**: Joins two strings
- **`ft_strdup(char *str, int *check_newline)`**: Duplicates string up to newline
- **`ft_strlcpy(char *dst, char *src, size_t dstsize)`**: Safe string copying
- **`ft_bzero(void *s, size_t n)`**: Zero-fills memory

### Algorithm Overview

1. **Check Parameters**: Validate file descriptor and buffer size
2. **Process Buffer**: Extract any remaining data from static buffer
3. **Read Loop**: Read from file until newline found or EOF
4. **Line Construction**: Build complete line using string operations
5. **Buffer Management**: Store remaining characters for next call
6. **Memory Cleanup**: Free temporary allocations, return final line

## Memory Management

### Allocation Strategy
- Each returned line is dynamically allocated
- **Caller responsibility**: Must `free()` returned lines
- Internal buffers are managed automatically
- No memory leaks in normal operation

### Error Handling
```c
// Always check return values
char *line = get_next_line(fd);
if (line == NULL) {
    // Either EOF or error occurred
    // Check if fd is still valid to distinguish
}

// Don't forget to free
free(line);
```

## Bonus Features

### Multiple File Descriptors
The bonus version supports reading from multiple file descriptors simultaneously:

```c
// Each fd maintains its own static buffer
char *line1 = get_next_line(fd1);  // First line of file1
char *line2 = get_next_line(fd2);  // First line of file2
char *line3 = get_next_line(fd1);  // Second line of file1
```

### Implementation Differences
- Uses array of static buffers indexed by file descriptor
- Supports up to `FOPEN_MAX` simultaneous file descriptors
- Same interface as mandatory version

## Performance Considerations

### Buffer Size Impact
- **Small buffers (1-10)**: More system calls, good for testing edge cases
- **Medium buffers (100-1000)**: Balanced performance for most use cases
- **Large buffers (4096+)**: Fewer system calls, more memory usage

### Optimization Tips
- Choose buffer size based on typical line length
- Larger buffers reduce system calls but use more memory
- Consider file size and available memory

## Common Edge Cases

### File Scenarios
- Empty files
- Files ending without newline
- Files with only newlines
- Very long lines (> BUFFER_SIZE)
- Binary files with null bytes

### System Scenarios
- Invalid file descriptors
- Read permission denied
- Files on slow/network filesystems
- Memory allocation failures

### Error Conditions
- `fd < 0` or `fd >= FOPEN_MAX`
- `BUFFER_SIZE <= 0`
- Read errors (`read()` returns -1)
- Memory allocation failures
