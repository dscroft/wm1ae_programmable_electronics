<!--
module_id: isr
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Interrupt Service Routines
comment:  This module introduces the the concepts of interrupt service routines, and how to implement them in Arduino.
long_description: This module introduces the the concepts of interrupt service routines in Arduino, and how to implement them.
estimated_time_in_minutes: 20


@learning_objectives  
- Understand the concept of interrupt service routines and their importance in embedded systems.
- Learn how to implement basic interrupt service routines in Arduino.
- Gain hands-on experience with using interrupts in Arduino projects.

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

import: https://raw.githubusercontent.com/LiaScript/CodeRunner/master/README.md
import: ../assets/macros.md
-->


# Variables

In standard C there are four main variable types.

- `int` - A signed integer, typically 16 or 32 bits in size depending on the platform.
- `float` - A single-precision floating-point number, typically 32 bits in size.
- `double` - A double-precision floating-point number, typically 64 bits in size.
- `char` - A single character, typically 8 bits in size.

A number of other variable types are also available, such as `long`, `short`, `unsigned int`, etc., which provide different ranges and sizes for integers. Additionally, C supports arrays, pointers, and structures for more complex data management.

- `long` - A signed integer that is typically 32 or 64 bits in size, depending on the platform.
- `short` - A signed integer that is typically 16 bits in size.
- `unsigned int` - An unsigned integer that is typically 16 or 32 bits in size, depending on the platform.

In particular for embedded programming, the precise size of variables is important, and so fixed-width integer types such as `uint8_t`, `int16_t`, etc. are often used to ensure consistent behavior across different platforms.

Notice that there is no built-in string type in C. 
Instead, strings are typically represented as arrays of characters, terminated by a null character (`'\0'`).

For example, to declare a string in C, you might use:

```c
char myString[] = "Hello, World!";
```

In C++, or more precisely in the C++ standard library, there is a `std::string` type that provides a more convenient and powerful way to work with strings. 
In embedded programming, especially on resource-constrained devices, it is common to use C-style strings (character arrays) for efficiency reasons, but the Arduino environment does provide a `String` class that offers many of the conveniences of `std::string` while being optimized for embedded use.

<div class = "important">
<b style="color: rgb(var(--color-highlight));">Important note</b><br>

You can see how, although C and C++ are closely related languages, and even within C++ the specific environment you are developing for, can have a significant impact on the features and functionality available to you.

</div>


## Variable ranges and sizes

The size and range of variables in C/C++ can vary depending on the platform and compiler being used.
Importantly however, C and C++ use fixed sizes for their basic data types, such as `int`.
This means that these variables have hard limits on the range of values they can represent, and if you exceed these limits, you will encounter overflow or underflow issues.

### Overflow and underflow

When a variable exceeds its maximum value, it wraps around to the minimum value (overflow) and when it goes below its minimum value, it wraps around to the maximum value (underflow).

```cpp signed.cpp
#include <iostream>
#include <limits>

int main()
{
    int myInt = std::numeric_limits<int>::max();

    std::cout << "myInt: " << myInt << std::endl;

    myInt = myInt + 1; // This will cause overflow

    std::cout << "myInt after overflow: " << myInt << std::endl;

    return 0;
}
```
@LIA.eval(`["signed.cpp"]`, `g++ --std=c++17 signed.cpp`, `./a.out`)
@headlesscode("signed.cpp")



```cpp unsigned.cpp
#include <iostream>
#include <limits>

int main() 
{
    unsigned int myUInt = std::numeric_limits<unsigned int>::min();

    std::cout << "myUInt: " << myUInt << std::endl;

    myUInt = myUInt - 1; // This will cause underflow

    std::cout << "myUInt after underflow: " << myUInt << std::endl;

    return 0;
}
```
@LIA.eval(`["unsigned.cpp"]`, `g++ --std=c++17 unsigned.cpp`, `./a.out`)
@headlesscode("unsigned.cpp")


<div class="important">
<b style="color: rgb(var(--color-highlight));">Important note</b><br>

This overflow and underflow behaviour is extremely common and a large quantity of code has been written that relies on this behaviour.
However, there is nothing in the C or C++ standards that requires this behaviour, and so it is technically possible for a platform to implement a different behaviour for overflow and underflow, such as saturating at the maximum or minimum value instead of wrapping around.

Simply because this behaviour is common and works on most compilers and platforms does not mean that it is guaranteed to work on all compilers and platforms, and so it is important to be aware of this when writing code that may be compiled for different targets.
</div>


### `sizeof`

If you are unsure about the size of a variable type on your platform, you can use the `sizeof` operator to determine the size in bytes.

```cpp sizeof.cpp
#include <cstdint>
#include <iostream>

int main() 
{
    std::cout << "Size of int:     " << sizeof(int)     << " bytes" << std::endl;
    std::cout << "Size of float:   " << sizeof(float)   << " bytes" << std::endl;
    std::cout << "Size of bool:    " << sizeof(bool)    << " bytes" << std::endl;
    std::cout << "Size of char:    " << sizeof(char)    << " bytes" << std::endl;
    std::cout << "Size of int16_t: " << sizeof(int16_t) << " bytes" << std::endl;

    return 0;
}
```
@LIA.eval(`["sizeof.cpp"]`, `g++ --std=c++17 sizeof.cpp`, `./a.out`)
@headlesscode("sizeof.cpp")

Note that C/C++ variables will have a size in whole bytes, and so the size of a variable will always be a multiple of 8 bits.
These applies even for variables that could be represented with fewer bits, such as a `bool` which only needs 1 bit to represent its two possible values, but will typically be stored in a full byte (8 bits).


# Iteration

## `for` loops

Traditional C/C++ `for` loops have the syntax:

```cpp
for (initialization; condition; update) 
{
    // loop body
}
```

This allows you to specify an initialization step, a condition for continuing the loop, and an increment step that is executed after each iteration of the loop body.

```cpp loop.cpp
#include <chrono>
#include <iostream>
#include <thread> // for sleep function

int main()
{
    for (int i = 0; i < 5; i++) 
    {
        std::cout << "Iteration: " << i << std::endl;

        // Sleep for 1 second to slow down the output
        std::this_thread::sleep_for(std::chrono::seconds(1));  
    }

    return 0;
}
```
@LIA.eval(`["loop.cpp"]`, `g++ --std=c++17 loop.cpp`, `./a.out`)
@headlesscode("loop.cpp")



### Range-based `for` loops

Modern C++ (c++11 and later) provides range-based `for` loops, which offer a cleaner and more intuitive way to iterate over collections. A range-based `for` loop has the syntax:

```cpp
for (type variable : collection) 
{
    // loop body
}
```

This automatically iterates through each element in the collection without needing manual index management. For example:

```cpp range_for.h
int numbers[] = {1, 2, 3, 4, 5};
for (int num : numbers) {
    std::cout << num << std::endl;
}
```
```cpp range_for.cpp
#include <iostream>

int main() 
{
    #include "range_for.h"

    return 0;
}
```
@LIA.eval(`["range_for.h","range_for.cpp"]`, `g++ --std=c++17 range_for.cpp`, `./a.out`)
@headlesscode("range_for.h")
@hidecode("range_for.cpp")

Range-based `for` loops work with arrays, vectors, and other container types, making code more readable and less error-prone than traditional index-based loops.



# C-style strings

Normally I would strongly advise against using C-style strings in C++ code unless there were specific and measurable performance requirements.
In general, the `std::string` class provided by the C++ standard library is much safer and easier to use than C-style strings, as it manages memory automatically and provides a wide range of useful member functions for string manipulation.

However, in embedded programming, especially on resource-constrained devices, it is common to use C-style strings (character arrays) for efficiency reasons, as they can be more memory-efficient.

C-style strings are represented as arrays of characters, terminated by a null character (`'\0'`).

- The null character is ASCII character with the value of 0.
- For reference, the ASCII value of 'A' is 65, and the ASCII value of 'a' is 97.

This means that in order to store a 5 letter word, you need to allocate an array of 6 characters to accommodate the null terminator.

```cpp c_string.cpp
#include <iostream>
#include <cstring> // for strlen function

int main() 
{
    char myString[] = "Hello";  // null terminator is automatically added

    std::cout << "myString: " << myString << std::endl;
    std::cout << "Length: " << strlen(myString) << std::endl; // Use strlen to get the length of the string
    std::cout << "Byte size: " << sizeof(myString) << " bytes" << std::endl; // Use sizeof to get the size of the array in bytes
    
    return 0;
}
```
@LIA.eval(`["c_string.cpp"]`, `g++ --std=c++17 c_string.cpp`, `./a.out`)
@headlesscode("c_string.cpp")