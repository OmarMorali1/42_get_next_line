*This project has been created as part of the 42 curriculum by ommorali.*

# Get Next Line (GNL)

## Description

Get Next Line (GNL) is a project at 42 asks students to code a function capable of returning a single line read from a file descriptor.

The primary goal of this project is to master low-level file input/output handling, dynamic memory allocation (malloc and free), static variables, and linked lists in C. The function must handle arbitrary buffer sizes (BUFFER_SIZE) efficiently without leaking memory or mixing up data across multiple file descriptors.

### Algorithm Explanation & Justification

Selected Approach: Linked Lists with Static File Management

To handle reading lines of unknown lengths while preserving data read past a newline character (\n), this implementation uses a Linked List (t_list) combined with a Static File Structure (t_file).

## Instructions

Compilation

The project can be compiled along with your own test files using standard gcc/cc flags. You can define a custom BUFFER_SIZE using the -D compilation flag:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl


### Execution Example

Here is how you can use get_next_line inside a C program:

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}


## Resources & AI Usage

References & Documentation

C Man Pages: man read, man malloc, man free

42 Norm v4 Documentation: Official guidelines for code formatting and structure.

Articles & Tutorials: Various community explanations on handling static variables and file descriptors in C.

### AI Assistance Disclosure

Artificial Intelligence (AI) was utilized during the development of this project under the following specific scopes:Debugging & Edge-Case Analysis, Norminette Structuring.