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

### Range-based `for` loops

C++11 introduced range-based `for` loops to iterate directly over arrays and containers without maintaining an index. 
Until we cover containers
For read-only access, bind
each element through `const auto&`:

```cpp
for (const auto& element : collection) {
    // Use element.
}
```

For example, this prints each value in an array:

```cpp range_for.h
const std::array<int, 5> numbers{1, 2, 3, 4, 5};
for (const auto& number : numbers) {
    std::cout << number << '\n';
}
```
```cpp range_for.cpp
#include <array>
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

Range-based loops also work with `std::vector` and most other standard
containers. Use `auto&` when you need to modify elements, or `auto` when a
separate copy is intended. Prefer this form when the index is not needed; use
an indexed loop when you need positions or want to process only part of a
collection.
