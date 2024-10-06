# Ft_printf

## Overview
The `Ft_printf` project at 42 involves creating a C library that replicates the behavior of the standard `printf` function, along with other useful functions for formatting outputs. This project helps deepen your understanding of formatted output in C, memory management, and the intricacies of handling variable arguments.

## Project Objectives
- Understand the mechanics of formatted output functions.
- Learn to implement common C formatting functions without relying on external libraries.
- Gain experience in managing memory dynamically for buffers and formatted strings.
- Create a reusable library that will assist in future projects requiring formatted output.

## Project Requirements
- **Language**: C
- **Compilation Flags**: `-Wall -Wextra -Werror`
- **Output**: A static library `libprintf.a`
- **Makefile**: Required with rules `all`, `clean`, `fclean`, `re`, and `bonus`.

## Learning Goals
- Understand how standard formatted functions like `printf` are implemented.
- Develop better memory management skills, preventing memory leaks and handling dynamic allocation correctly.
- Apply advanced function handling (variable arguments, function pointers).
- Improve your use of Makefiles and shell commands.

## Instructions

### Part 1: Recreating Formatted Output Functions
You will implement the following functions to mimic the behavior of the standard `printf` function:

- Character output: `putchar_fd`
- String output: `putstr_fd`, `putendl_fd`, `putnbr_fd`
- Formatting: `format_string`, `format_char`, `format_number`, `format_pointer`

### Part 2: Additional Utility Functions

- Buffer management: `write_in_buf`, `stdout_buf`
- String manipulation for formatting: `put_str_in_buf`, `put_char_in_buf`
- Precision and width handling: `set_space`, `set_zeros`, `set_spaces_num`

### Bonus Part: Additional Formatting Features

- Support for hexadecimal and octal formats: `itoa_base_buf`, `render_num`
- Support for flags and width/precision specifiers
- Linked list functions for managing formatted output options

## Evaluation Criteria
- All mandatory functions must compile and behave as expected.
- Memory management will be strictly evaluated, especially with dynamic allocation (use of `malloc`).
- Bonus functions will only be evaluated if the mandatory part is perfect.
