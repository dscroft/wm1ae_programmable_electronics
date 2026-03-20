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


# Memory

Memory management is a critical aspect of C/C++ programming, especially in embedded systems where resources are limited. In this section, we will explore the basics of memory management in C/C++, including dynamic memory allocation, pointers, and best practices for avoiding memory leaks and other common pitfalls.

The dependency on the programmer to manually manage dynamic memory can lead to issues such as memory leaks, dangling pointers, and buffer overflows if not handled carefully. 
The difficulty of and regular failure of programmers to correctly manage memory is the primary reason that migration away from C and C++ to memory safe languages such as Rust is seen as important for safety critical applications and software development in general.

Given the issues associated with dynamic memory management we cannot ignore the subject.
In general software development dynamic memory is an invaluable tool that allows for flexible and efficient use of memory, enabling developers to create complex data structures and manage resources effectively.
However for safety critical applications, coding standards such as MISRA C and MISRA C++ prohibit dynamically allocated memory due to the risks associated with it.

So, we will be covering the subject, you need to understand and use it correctly; but also we want you to avoid using it where possible.


## C/C++ manual memory management

C and C++ provide manual memory management through the use of pointers and dynamic memory allocation functions. 

In C, you can use `malloc()`, `calloc()`, `realloc()`, and `free()` to manage memory. 
In C++, you can use the `new` and `delete` operators for dynamic memory allocation.


As we are working with Arduino, we will focus on using the C++ memory management commands.
But if you see `malloc()`. `free()` etc, they are still valid and work as expected.


## Embedded systems and memory constraints

In embedded systems, memory is often limited, and efficient memory management is crucial. 
When working with Arduino, it's important to be mindful of the available memory and to use it wisely.

