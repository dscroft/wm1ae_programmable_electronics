<!--
module_id: functions
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Functions and Procedures
comment:  This module covers how to write, call, and organize code using functions.
long_description: Functions allow you to break code into reusable, testable pieces. This module covers function declarations, definitions, parameters, return values, function scope, and best practices for writing maintainable code.
estimated_time_in_minutes: 60

@learning_objectives  
- Understand function declaration and definition
- Learn about function parameters and return values
- Understand function scope and variable lifetime
- Learn about recursion
- Understand function pointers
- Write modular, testable code using functions

@end

@style
.flex-container {
    display: flex;
    flex-wrap: wrap; /* Allows the items to wrap as needed */
    align-items: stretch;
    gap: 20px; /* Adds both horizontal and vertical spacing between items */
}

.flex-child { 
    flex: 1;
    margin-right: 20px; /* Adds space between the columns */
}

@media (max-width: 600px) {
    .flex-child {
        flex: 100%; /* Makes the child divs take up the full width on slim devices */
        margin-right: 0; /* Removes the right margin */
    }
}
@end

@version_history 

Previous versions: 

@end

import: https://raw.githubusercontent.com/dscroft/CodeRunner/master/README.md
import: ../assets/macros.md
-->

# Functions and Procedures

A **function** is a reusable block of code that performs a specific task. Functions allow you to:

- Break large programs into manageable pieces
- Reuse code without repeating it
- Test code in isolation
- Improve readability

## Function Basics

### Function Declaration

A **function declaration** (also called a prototype) tells the compiler about a function before you use it:

```c
return_type function_name(parameter_type param1, parameter_type param2);
```

Example:

```c
int add(int a, int b);  // Function declaration (prototype)
```

### Function Definition

A **function definition** provides the actual implementation:

```c
return_type function_name(parameter_type param1, parameter_type param2) {
    // Function body
    return return_value;
}
```

Example:

```c
int add(int a, int b) {
    int sum = a + b;
    return sum;
}
```

### Complete Example

```c
#include <stdio.h>

// Function declaration (prototype)
int add(int a, int b);

// Main function
int main() {
    int result = add(5, 3);
    printf("5 + 3 = %d\n", result);
    return 0;
}

// Function definition
int add(int a, int b) {
    return a + b;
}
```

## Function Parameters

### Pass by Value

By default, function arguments are **passed by value**. This means the function receives a **copy** of the value:

```c
void increment(int x) {
    x++;  // This increments the copy, not the original
}

int main() {
    int num = 5;
    increment(num);
    printf("num = %d\n", num);  // Still 5, not 6!
    return 0;
}
```

### Pass by Reference (Pointers)

To modify a variable in a function, pass a **pointer** to it:

```c
void increment(int *x) {
    (*x)++;  // Dereference pointer to modify original
}

int main() {
    int num = 5;
    increment(&num);  // Pass address of num
    printf("num = %d\n", num);  // Now 6!
    return 0;
}
```

We'll learn more about pointers in a later module. For now, understand that `&variable` gives the address, and `*pointer` accesses the value through the pointer.

### Default Parameters (C++ only)

C++ allows default values for parameters:

```cpp
void delay_message(const char *msg, int delay_ms = 1000) {  // delay_ms defaults to 1000
    // If delay_ms not provided, uses 1000
}

// Can call with or without the parameter
delay_message("Hello");           // Uses default 1000ms
delay_message("Urgent!", 100);    // Uses 100ms
```

C does **not** support default parameters.

### Variable Number of Arguments

Use `...` (ellipsis) for functions with variable arguments:

```c
#include <stdio.h>
#include <stdarg.h>

void print_numbers(int count, ...) {
    va_list args;
    va_start(args, count);  // Start reading variable arguments
    
    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int);  // Get next argument
        printf("%d ", num);
    }
    
    va_end(args);
}

int main() {
    print_numbers(4, 10, 20, 30, 40);
    return 0;
}
```

**Note**: Variable arguments are error-prone because the compiler cannot check types. Use with caution.

## Return Values

Functions return a value using the `return` statement:

```c
int get_maximum(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
```

### void Functions

Functions with return type `void` do **not** return a value:

```c
void print_separator() {
    printf("====================\n");
    // No return statement needed, but 'return;' is allowed
}
```

### Returning Pointers

Functions can return pointers:

```c
int *get_pointer(int x) {
    static int value = 0;
    value = x;
    return &value;  // Returns address of static variable
}
```

**Important**: Never return a pointer to a local variable! Local variables cease to exist when the function returns:

```c
int *bad_function() {
    int x = 5;
    return &x;  // DANGER! x ceases to exist after function returns
}
```

## Function Scope and Lifetime

Variables have **scope** (where they can be accessed) and **lifetime** (how long they exist).

### Local Variables

Local variables are declared **inside** a function and only exist during that function's execution:

```c
int function() {
    int local_var = 5;  // Created here
    printf("%d\n", local_var);  // 5
    return local_var;
}  // local_var is destroyed here

printf("%d\n", local_var);  // ERROR! local_var doesn't exist
```

### Global Variables

Global variables are declared **outside** all functions and exist for the program's lifetime:

```c
int global_var = 10;  // Global - accessible from anywhere

void function1() {
    printf("%d\n", global_var);  // Can access and modify
    global_var++;
}

void function2() {
    printf("%d\n", global_var);  // Sees the modified value
}
```

**Best Practice**: Minimize global variables! They make code harder to understand and test. Pass variables as parameters instead.

### Static Variables

Static variables retain their value between function calls:

```c
void counter() {
    static int count = 0;  // Initialized only once
    count++;
    printf("Called %d times\n", count);
}

int main() {
    counter();  // Called 1 times
    counter();  // Called 2 times
    counter();  // Called 3 times
    return 0;
}
```

### const Parameters

Use `const` to prevent a function from modifying a parameter:

```c
void print_message(const char *msg) {
    printf("%s\n", msg);
    // msg[0] = 'X';  // ERROR! msg is const
}
```

This is a contract with the caller: "I promise not to modify this."

## Recursion

**Recursion** is when a function calls itself. Every recursive function needs:

1. **Base case**: Condition that stops recursion
2. **Recursive case**: Call to itself with different arguments

Example: Factorial

```c
int factorial(int n) {
    if (n <= 1) {
        return 1;  // Base case
    } else {
        return n * factorial(n - 1);  // Recursive case
    }
}

// factorial(5) = 5 * factorial(4) = 5 * 4 * 3 * 2 * 1 = 120
```

### Recursion Depth

Each recursive call uses stack space. Too many calls cause a **stack overflow**:

```c
void infinite_recursion() {
    infinite_recursion();  // WRONG! Never reaches base case - stack overflow!
}
```

**Embedded Systems Note**: Embedded systems often have very limited stack space. Recursion can be dangerous. Use loops instead when possible.

## Function Pointers

A **function pointer** is a pointer that points to a function rather than data:

### Declaring Function Pointers

```c
// Declare a pointer to a function that takes two ints and returns an int
int (*operation)(int, int);
```

### Using Function Pointers

```c
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

int main() {
    int (*operation)(int, int);  // Declare function pointer
    
    operation = add;              // Point to add function
    printf("%d\n", operation(3, 4));  // Calls add: prints 7
    
    operation = multiply;         // Point to multiply function
    printf("%d\n", operation(3, 4));  // Calls multiply: prints 12
    
    return 0;
}
```

### Practical Use: Callbacks

Function pointers are useful for callbacks - passing a function to be called later:

```c
// Takes a function pointer as a parameter
void execute_operation(int a, int b, int (*func)(int, int)) {
    int result = func(a, b);
    printf("Result: %d\n", result);
}

int main() {
    execute_operation(5, 3, add);      // Pass add function
    execute_operation(5, 3, multiply); // Pass multiply function
    return 0;
}
```

**Embedded Systems Example**: Interrupt handlers are often function pointers:

```c
void button_pressed() {
    printf("Button was pressed!\n");
}

int main() {
    void (*interrupt_handler)() = button_pressed;
    // When interrupt occurs, system calls (*interrupt_handler)()
    return 0;
}
```

## Inline Functions (C++ and C99+)

Inline functions are optimized by the compiler to avoid function call overhead:

```cpp
inline int square(int x) {
    return x * x;
}

// Compiler replaces function call with actual code:
int result = square(5);  // Becomes: int result = 5 * 5;
```

**Note**: `inline` is a **hint** to the compiler; the compiler decides whether to inline.

**Embedded Systems**: Use `inline` for small, frequently-called functions to reduce overhead.

## Good Function Design

### 1. Single Responsibility

Each function should do one thing well:

```c
// Good: Clear single purpose
int calculate_sum(int a, int b) {
    return a + b;
}

// Poor: Mixes calculation and I/O
int add_and_print(int a, int b) {
    int sum = a + b;
    printf("Sum: %d\n", sum);
    return sum;
}
```

### 2. Meaningful Names

Function names should describe what they do:

```c
// Good
int get_temperature();
void initialize_sensor();
int is_temperature_safe(int temp);

// Poor
int get_t();
void init();
int check(int x);
```

### 3. Keep Functions Small

Functions should be small enough to understand at a glance (typically less than 20-30 lines):

```c
// If a function gets too large, split it:
void process_data(data_t *data) {
    validate_data(data);
    transform_data(data);
    save_data(data);
}
```

### 4. Minimize Side Effects

Functions should avoid unexpected behavior (side effects):

```c
// Bad: Has side effect (modifies global)
int multiply(int a, int b) {
    global_operations_count++;  // Side effect!
    return a * b;
}

// Good: Self-contained, no surprises
int multiply(int a, int b) {
    return a * b;
}
```

### 5. Document Expectations

```c
// Find the index of the first occurrence of value in array
// Returns -1 if not found
int find_index(int array[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}
```

## Example: Arduino Function Structure

```cpp
// Global variables
const int BUTTON_PIN = 2;
const int LED_PIN = 13;
unsigned long last_press = 0;

// Function declarations (prototypes)
void setup();
void loop();
void handle_button_press();
void toggle_led();
void debounce_delay();

// Implementation
void setup() {
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == HIGH) {
        debounce_delay();
        if (digitalRead(BUTTON_PIN) == HIGH) {
            handle_button_press();
        }
    }
}

void handle_button_press() {
    unsigned long now = millis();
    if (now - last_press > 200) {  // Debounce 200ms
        toggle_led();
        last_press = now;
    }
}

void toggle_led() {
    static boolean state = false;
    state = !state;
    digitalWrite(LED_PIN, state);
}

void debounce_delay() {
    delay(20);
}
```

## Summary

- **Functions** break code into reusable, testable pieces
- **Parameters** pass information to functions
- **Return values** pass information back from functions
- **Scope** determines where variables can be accessed
- **Recursion** allows functions to call themselves (but watch stack usage!)
- **Function pointers** enable callbacks and flexible code
- **Write small, focused functions** with clear names
- **Minimize side effects** and global variables
