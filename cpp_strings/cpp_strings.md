<!--
module_id: cpp_foundations
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: C++ Foundations
comment:  This module introduces the fundamentals of C++ programming, including variables, data types, and control structures.
long_description: This module introduces the fundamentals of C++ programming, including variables, data types, and control structures.
estimated_time_in_minutes: 20


@learning_objectives  
- Understand the concept of C++ variables and data types.
- Learn how to implement basic C++ programming constructs in Arduino.
- Gain hands-on experience with using C++ features in Arduino projects.

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

import: https://raw.githubusercontent.com/dscroft/mermaid_template/refs/heads/master/README.md
import: https://raw.githubusercontent.com/dscroft/CodeRunner/master/README.md
import: https://raw.githubusercontent.com/liaTemplates/AVR8js/main/README.md
import: ../assets/macros.md
-->


# Strings

Instead, strings are typically represented as arrays of characters, terminated by a null character (`'\0'`).

For example, to declare a string in C, you might use:

```c
char myString[] = "Hello, World!";
```

In C++, or more precisely in the C++ standard library, there is a `std::string` type that provides a more convenient and powerful way to work with strings. 
In embedded programming, especially on resource-constrained devices, it is common to use C-style strings (character arrays) for efficiency reasons, but the Arduino environment does provide a `String` class that offers many of the conveniences of `std::string` while being optimized for embedded use.



## C-style strings

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