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


# Blocks

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


# Conditionals

Programs rarely run the same instructions in the same order for every input.
Conditionals select which statements to execute, and loops repeat statements
until a task is complete. Together, these constructs let a program respond to
its inputs and process collections of data.

Conditionals run a block only when a condition is satisfied. 
In C++, use `if` and `else` for branching, the conditional operator for a simple value choice, and `switch` when selecting among several integral or enumeration values.

C++ has a built-in `bool` type with the values `true` and `false`. 
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
@addcppmain()


## Comparison operators

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
`if( count = 3 )` assigns `3` to `count`, and the resulting non-zero value makes
the condition true. Write `if( count == 3 )` to compare. Compilers can warn
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

## Logical Expressions

| Expression | Meaning |
|:----------:|---------|
| `a || b` | `true` when at least one operand is true |
| `a && b` | `true` when both operands are true |
| `!a` | The logical inverse of `a` |

Logical operators combine boolean conditions. 
For example:

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
Brackets `()` are used to control evaluation order, as with mathematical notation.
Otherwise they are evaluated in `!`, `&&`, `||` order from left to right.

### Range checks

Relational comparisons do not chain as they do in mathematical notation.
`minimum < value < maximum` first evaluates `minimum < value` to a boolean,
then compares that true/false against `maximum`. To test a range, combine the two
comparisons with `&&`:

```cpp In range example
const int value {-9};
const bool inRange = 0 < value < 10;

std::cout << std::boolalpha;
std::cout << "inRange: " << inRange << std::endl;
```
@addcppmain()

<div class="pass-task">
@boxheader(In the browser)

Run the code above, notice that `inRange` is true despite the fact that -9 is *not* between 0 and 10.

Fix the comparison that `inRange` has the correct value.

<script input="submit" default="Answer">
"LIASCRIPT: `const bool inRange = 0 < value && value < 10;`"
</script>
</div>


### Short circuiting

Logical `&&` and `||` use short-circuit evaluation.
What that means is that C++ skips the right operand when the left operand already determines the overall result. 

This is useful for safeguard checks:

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
if( word.size() > 2 && is_banned(word) ) 
{
    std::cout << "Bad word!" << std::endl;
}
```

Here, `is_banned` is only called when the word is long enough to need checking.
Keep the checks in an order that preserves the intended logic; in particular,
put any guard before an expression that depends on it.


# `if` and `else`

Use `if` to run code when a condition is true. 
An optional `else` handles the other case, and `else if` tests additional conditions in order. 
Only the first matching block of an `if`/`else if` chain runs:

```cpp
if( condition ) 
{
  // Runs when condition is true.
} 
else 
{
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

