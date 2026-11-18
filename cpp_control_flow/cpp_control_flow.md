<!--
module_id: control_flow
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Control Flow - Conditionals and Loops
comment:  This module covers conditional statements (if/else, switch) and looping constructs (for, while, do-while).
long_description: This module explores how to control the execution flow of C/C++ programs using conditional statements and loops. These constructs allow programs to make decisions and repeat actions, which are fundamental to any useful program.
estimated_time_in_minutes: 50

@learning_objectives  
- Understand if/else conditional statements
- Learn switch statements for multi-way branching
- Understand for, while, and do-while loops
- Learn loop control (break, continue)
- Understand nested control structures
- Write clear, maintainable control flow code

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


# Program flow

Programs rarely run the same instructions in the same order for every input.
Conditionals select which statements to execute, and loops repeat statements
until a task is complete. Together, these constructs let a program respond to
its inputs and process collections of data.

A block is a group of statements enclosed in braces, `{` and `}`. A block can
contain other blocks, and it does not need a trailing semicolon. An empty block
is valid, though it does no work.

In C/C++ blocks are generally defined as part of an conditional or loop in order to specify which lines of code are part of it. 
But headless blocks are also sometimes useful.
If a conditional or loop only has a single line of code within it, then you braces can be left out. 
But this is not recommended, especially as a beginner, including the braces generally makes your code clearer.

---------------------------------

Variables that are declared inside of a block as only available within that block's scope.
When your program leaves a block, anything declared within it goes out of scope and (simplification) ceases to exist.

```cpp Scope Example
int main()
{                 // start of function block
  int a = 42;

  {               // start of a nested block
    a += 1;       // variables from the outer block are still in scope
    int b = 999;  // b is local to this block
  }               // end of the nested block

  b += 1;         // error: b is not in scope outside the block

  return 0;
}                 // end of function block
```
@LIA.cpp()

<div class="pass-task">
@boxheader(In the browser)

What happens when you try and run the scope example code?
</div>

<div class="learn-more">
@boxheader(Style guidelines)

It does not matter where you place your brace characters in your code.
Some programmers prefer to place the `{` character at the end of the line as it saves page space.
I.e. 

```cpp
int main() {
  return 0;
}
```

Others, prefer the brace characters to line up as it makes it easier to keep track of when you have multiple blocks.
I.e.

```cpp
int main()
{
  return 0;
}
```

As it makes absolutely no difference to the compiled code, this module does not care what you use so long as you use it consistently.
</div>


## Conditionals

Conditionals run a block only when a condition is satisfied. 
In C++, use `if` and `else` for branching, the conditional operator for a simple value choice, and `switch` when selecting among several integral or enumeration values.

C++ has a built-in `bool` type with the values `true` and `false`, (C99 and C23 respectively for C). 
Comparisons produce a `bool`, and `if` only accepts a boolean value. 
If you supply a non-boolean value it will first be converted to a boolean and then evaluated.
With integer variables for example, 0 converts to `false` and all other values convert to `true`.
Other variable types work differently and exactly how every different type converts to a boolean is not going to be covered for now.
If you are unsure how a specific variable type converts, use an explicit comparison instead, for clarity and certainty.

```cpp Integer to boolean example
int counter = 10;

for( int i=-5; i<=5; ++i )
{
  std::cout << i << " is " << std::boolalpha << static_cast<bool>(i) << std::endl;
}
```
```cpp -main.cpp
#include <iostream>
#include <string>
int main() { 
  #include "visible.h"
}
```
@LIA.eval(`["visible.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)
@hidecode("main.cpp")


### Comparison operators

| Expression | Meaning |
|:----------:|---------|
| `a < b` | `true` when `a` is less than `b` |
| `a > b` | `true` when `a` is greater than `b` |
| `a <= b` | `true` when `a` is less than or equal to `b` |
| `a >= b` | `true` when `a` is greater than or equal to `b` |
| `a == b` | `true` when `a` equals `b` |
| `a != b` | `true` when `a` and `b` differ |

Assignment uses one equals sign (`=`); equality comparison uses two (`==`).
Confusing them can silently change a value instead of testing it. For example,
`if (count = 3)` assigns `3` to `count`, and the resulting non-zero value makes
the condition true. Write `if (count == 3)` to compare. Compilers can warn
about suspicious assignments in conditions, so enable warnings and take them
seriously.

<div style="display:none">
Comparisons produce `bool` results in modern C++. Test the condition you mean:
for example, a string search with `std::string::find` should be compared with
`std::string::npos`, not with zero.

```cpp
#include <string>

const std::string message{"sensor ready"};
if (message.find("ready") != std::string::npos) {
    // The substring was found.
}
```
</div>

-----------------------------------

Relational comparisons do not chain as they do in mathematical notation.
`minimum < value < maximum` first evaluates `minimum < value` to a boolean,
then compares that boolean with `maximum`. To test a range, combine the two
comparisons with `&&`:

```cpp In range example
const int value {9};

if( 0 < value && value < 10 ) 
{
  // Runs only when value is strictly between 0 and 10.
  std::cout << "If block" << std::endl;
}
else
{
  std::cout << "Else block" << std::endl;
}
```
```cpp -main.cpp
#include <iostream>
int main() { 
  #include "visible.h"
}
```
@LIA.eval(`["visible.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)
@hidecode("main.cpp")


### Logical Expressions

| Expression | Meaning |
|:----------:|---------|
| `a || b` | `true` when at least one operand is true |
| `a && b` | `true` when both operands are true |
| `!a` | The logical inverse of `a` |


Logical operators combine boolean conditions. For example:

```cpp Combine example
const bool door_closed {true};
const bool power_on {true};
const int temperature {22};
const int limit {25};
const bool ready = (door_closed && power_on) || temperature < limit;

std::cout << std::boolalpha << ready << std::endl;
```
@addcppmain

`ready` is true when both `door_closed` and `power_on` are true, or when the
temperature is below the limit.


#### Short circuiting

Logical `&&` and `||` use short-circuit evaluation: C++ skips the right operand
when the left operand already determines the result. This is useful for safe
guard checks:

```cpp
#include <array>
#include <cstddef>

const std::array<int, 12> values{};
const int i{4};
if (i >= 0 && i < static_cast<int>(values.size()) &&
    values[static_cast<std::size_t>(i)] > 3) {
    // The array access is reached only when i is in range.
}
```

The index checks must come before the access because `&&` evaluates from left
to right. Similarly, in `first_check() || second_check()`, the second function
is not called if the first check is true.

Short-circuiting can also avoid unnecessary work when a later check is
expensive. Put a quick check first when it can rule out the case before the
more costly check:

```cpp
if (word.size() > 2 && is_banned(word)) {
    std::cout << "Bad word!\n";
}
```

Here, `is_banned` is only called when the word is long enough to need checking.
Keep the checks in an order that preserves the intended logic; in particular,
put any guard before an expression that depends on it.


### `if` and `else`

Use `if` to run code when a condition is true. An optional `else` handles the
other case, and `else if` tests additional conditions in order. Only the first
matching branch of an `if`/`else if` chain runs:

```cpp
if (condition) {
    // Runs when condition is true.
} else {
    // Runs otherwise.
}
```

For example, select the greater of two values, using zero when they are equal:

```cpp If-else example
const int a {8};
const int b {5};

if( a > b )
{
  std::cout << "A is greater than b" << std::endl;
} 
else if( b > a ) 
{
  std::cout << "A is less than b" << std::endl;
} 
else 
{
  std::cout << "A and B are the same" << std::endl;
}
```
@addcppmain

An `else if` chain makes the possible outcomes explicit and prevents the
program from checking later conditions once a branch has already matched.
Use it when the cases are alternatives and only one action should be selected.
Use separate `if` statements when multiple conditions may each require an
action, since more than one separate `if` can run.

<div class="pass-task">
@boxheader(In the browser)

Adjust the values of A and B to explore all possible code paths.
</div>


#### The conditional expression

A conditional expression (often called the ternary operator) chooses one of
two values. Its form is `condition ? value_if_true : value_if_false`:

```cpp
const int a{8};
const int b{5};
const int larger = (a > b) ? a : b;
```

Use this operator when both alternatives are short and clear. Prefer a regular
`if`/`else` for multi-step actions, and avoid nesting conditional operators.
The shorter form does not inherently make a program faster.


### `switch` statements

Use `switch` to select a branch based on one integral or enumeration value.
Each `case` label is a compile-time constant. In a traditional `switch`,
execution continues into the next case unless it is stopped with `break`,
`return`, or another control-flow statement. Accidental fall-through is a common
bug; group intentional cases or mark deliberate fall-through with
`[[fallthrough]];`.

```cpp
#include <iostream>

enum class Grade { A, B, C, D, F };

void print_grade(Grade grade)
{
    switch (grade) {
    case Grade::A:
        std::cout << "A\n";
        break;
    case Grade::B:
        std::cout << "B\n";
        break;
    case Grade::C:
        std::cout << "C\n";
        break;
    case Grade::D:
        std::cout << "D\n";
        break;
    case Grade::F:
        std::cout << "F\n";
        break;
    }
}
```

`enum class` keeps enumerator names scoped and avoids implicit conversion to
integers. When handling an enumeration, consider omitting `default` so compiler
warnings can help identify newly added values that need a case. Several labels
can share the same action:

```cpp
switch (command) {
case Command::Start:
case Command::Resume:
    start_system();
    break;
case Command::Stop:
    stop_system();
    break;
}
```

Use `switch` for straightforward integral or enum selection; for other kinds
of matching, an `if` chain or a suitable standard-library facility may be a
better fit.


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
for (initialization; condition; update) {
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




### Range-based `for` loops

C++11 introduced range-based `for` loops to iterate directly over arrays and
standard containers without maintaining an index. For read-only access, bind
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



