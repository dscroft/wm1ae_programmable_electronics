<!--
module_id: cpp_iteration
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: C++ Iteration
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

## Loops

Loops repeat a block of statements while a condition is true or while there are
items left to process. They avoid duplicated code and make the stopping rule
explicit. Choose a loop form that makes its condition and progress easy to see.


### `while` loops

A `while` loop checks its condition before each iteration. If the condition is
false at the start, the body runs zero times. Make sure each iteration can
eventually make the condition false; otherwise the loop is infinite.

```cpp
int power{1};
while (power < 100) {
    std::cout << power << '\n';
    power *= 2;
}
```

The body runs for `power` values 1, 2, 4, 8, 16, 32, and 64. At the end of
each iteration, execution returns to the condition check. The condition is not
rechecked in the middle of the body.

`break` exits the nearest enclosing loop immediately. `continue` skips the
remaining statements in the current iteration and proceeds to the next
condition check. Use these only when they make the loop's intent clearer.

```cpp
int value{1};
while (value <= 10) {
    if (value == 5) {
        ++value;
        continue;
    }
    if (value == 8) {
        break;
    }
    std::cout << value << '\n';
    ++value;
}
```

A `while` loop is useful when the number of repetitions is not known in
advance, such as processing input until a stop condition is reached. Braces
should be used even for a one-statement body so the loop remains easy to extend.


### `for` loops

A counting `for` loop keeps its setup, continuation condition, and per-iteration
update together:

```cpp
for (initialization; condition; update) 
{
  // loop body
}
```

Initialization runs once, before the first condition check. It commonly
declares and initializes the loop variable.

Before each iteration, C++ evaluates the condition. If it is true, the body
runs; otherwise, execution continues after the loop.

After each iteration, the update expression runs. If a `continue` statement
is used, C++ still performs this update before the next condition check.

```cpp
#include <array>
#include <cstddef>

std::array<int, 12> values{};
for (std::size_t index = 0; index < values.size(); ++index) {
    values[index] = 5 * static_cast<int>(index) + 3;
}
```

The index starts at zero because C++ arrays and standard containers are
zero-indexed. The condition uses `< values.size()` so the last index is
`values.size() - 1`; using `<=` here would access one element past the end.
Counting down is also common:

```cpp
#include <iostream>

for (int count = 5; count > 0; --count) {
    std::cout << count << ' ';
}
```

Use a `for` loop when its setup, test, and update form a clear pattern. Each
clause can be omitted, but `for (;;) { ... }` is an infinite loop unless it
contains an exit such as `break`. Prefer a `while` loop when repetition depends
on a condition rather than a counting pattern. Avoid packing unrelated updates
into a `for` loop's comma-separated clauses; separate code is easier to read.




### `do`-`while` loops

A `do`-`while` loop checks its condition after running the body, so its body
executes at least once. The semicolon after the condition is required:

```cpp
do {
    // Perform an action before deciding whether to repeat.
} while (condition);
```

`break` exits the loop, while `continue` proceeds to the condition check. Use
this form when the body must run before the condition can be tested, such as
when prompting for input at least once. In other cases, a regular `while`
loop may express the intent more directly.






# Recap

@recap