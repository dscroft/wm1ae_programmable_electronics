<!--
module_id: control_flow
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Control Flow - Conditionals 
comment:  This module covers conditional statements (if/else, switch)
long_description: This module explores how to control the execution flow of C/C++ programs using conditional statements. These constructs allow programs to make decisions and repeat actions, which are fundamental to any useful program.
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

```cpp Integer as boolean example
for( int i=-5; i<=5; ++i )
{
  std::cout << i << " is " << 

  // i is an int but will be converted to a boolean
  if( i )
  {
    std::cout << "True" << std::endl;
  }
  else
  {
    std::cout << "False" << std::endl;
  }
}
```
@addcppmain()

<div class="learn-more">
@boxheader(Learn more)

There are multiple occasional when programming when you will need to convert from one variable type to another.
C++ sometimes converts a value from one type to another automatically as seen here with booleans and conditionals.

But we can also make a conversion explicit by **casting** a variable. 
Conversions can lose information; for example, converting a floating-point value to an integer discards its fractional part.

Older C++ code often uses a C-style cast, written as `(type)value`:

```cpp
double measurement = 4.8;
int cStyleResult = (int)measurement;
int cppStyleResult = static_cast<int>(measurement);
```

Both casts convert `4.8` to `4`, truncating the fractional part rather than rounding. 
C-style casts are still supported, but in C++ we prefer `static_cast<type>(value)`.
It is preferred because it provides additional compiler checks to the casting.
</div>


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
Without parentheses, these operators bind in the order `!`, then `&&`, then
`||`. This is precedence, not a promise that every operand will be evaluated.

<div class="warning">
@boxheader(Warning)

Do not confuse logical `&&`, `||`, and `!` with bitwise `&`, `|`, and `~`.
Logical operators work with conditions and can short-circuit; bitwise
operators work on the individual bits of integer values and always evaluate
their operands. Use the operator that matches your intention.

</div>

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



## Short circuiting

Logical `&&` and `||` use short-circuit evaluation.
What that means is that C++ evaluates the left operand first and skips the
right operand when the left operand already determines the overall result.


```cpp
#include <iostream>
#include <string>

bool check( std::string s )
{
    std::cout << "Checking " << s << std::endl;
    return false;
}

int main()
{
  bool andResult = check("left of and") && check("right of and");
  
  bool orResult = check("left of or") || check("right of or");

  return 0;
}
```
@LIA.cpp()

<div class="good-task">
@boxheader(Question)

**What happens if you change the return value of the `check()` function of `true`?**

[[ ]] Both expressions call both checks, so all four messages print.
[[X]] Both `&&` checks run, but `||` skips its right check.
[[ ]] The `&&` skips its right check and `||` runs both checks.
***
If `check()` always returns `true`. 
Then once the left hand side of the `&&` has returned `true`, the overall result depends on whether the right hand side is going to be `true` or `false`.
So we evaluate the right hand side to find out the answer.

With the `||`, once the left hand side has returned `true`, the overall result is going to be `true` no matter what happens on the right hand side. 
Since the right hand result is irrelevant, we don't bother evaluating it.
***
</div>


------------------------------

Short circuiting is extremely useful if you have checks that should only be run if other criteria are met, such as with array access.

```cpp
if( wifi.connected() && website.up() )
{
  download();
}
```


Short-circuiting can also avoid unnecessary work when a later check is expensive. 
Put a quick check first and it can help avoid more computationally expensive checks before they run.
Here, `is_banned` is only called when the word is long enough to need checking.

```cpp
if( word.length() > 2 && is_banned(word) ) 
{
  std::cout << "Bad word!" << std::endl;
}
```


## Chained `if` statements

Separate `if` statements each test their own condition. 
More than one condition can be true, so more than one block can run. 

```cpp Separate if example
const int temperature = 32;

if( temperature > 30 ) 
{
  std::cout << "Fan on high" << std::endl;
}

if( temperature > 25 ) 
{
  std::cout << "Fan on low" << std::endl;
}
```
@addcppmain()

With a temperature of `32`, both messages are printed. 

-----------------------------

If we only want multiple conditions but only want 1 block to run, then we need to chain our if statements.
This is an expansion on the the `if-else` statements we have already seen.

```cpp Chained if example
const int temperature = 32;

if( temperature > 30 )
{
  std::cout << "Fan on high" << std::endl;
}
else if( temperature > 25 ) 
{
  std::cout << "Fan on low" << std::endl;
}
```
@addcppmain()

Use `else if` when the cases are alternatives and only one action should be selected.
Use separate `if` statements when the actions are independent and should run regardless of the other blocks.


## Nested `if` statements

An `if` statement can be placed inside another `if` statement. 
The inner condition is checked only when execution enters the outer block. 
Nesting is useful when one decision depends on another:

```cpp Nested if example
const bool power_on = true;
const bool door_closed = true;

if( power_on ) 
{
  if( door_closed ) 
  {
    std::cout << "Motor can start" << std::endl;
  } 
  else 
  {
    std::cout << "Close the door first" << std::endl;
  }
} 
else 
{
  std::cout << "Turn on the power first" << std::endl;
}
```
@addcppmain()


Here, the door condition matters only when the power is on. Braces make it
clear which `else` belongs to which `if`. Avoid deep nesting where possible;
guard clauses or combining conditions can sometimes make the logic easier to
follow.

### The dangling `else`

When braces are omitted from nested `if` statements, an `else` belongs to the
nearest preceding `if` that does not already have an `else`. 
Indentation does not change this rule as, unlike other languages, indentation in C++ is purely aesthetic, it has no impact on the code.

```cpp
bool powerOn = true;
bool doorClosed = false;

if( powerOn )
  if( doorClosed )
    std::cout << "Motor can start" << std::endl;
  else
    std::cout << "Close the door first" << std::endl;
```
@addcppmain()

The `else` belongs to `if( doorClosed )`, not to `if( powerOn )`. 
This is sometimes called the **dangling `else`** problem. 
Use braces when nesting conditions so the intended pairing is explicit:

Omitting braces is valid for a single controlled statement, but braces are
usually clearer when an `if` is nested or may be extended later.

<div class="good-task">
@boxheader(In the browser)

Add braces to the example code so that the `else` block belongs to the `powerOn` check.

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
document.activeElement.style.display = "none";
</script>

<div id="answer" style="display: none">
```cpp
if( powerOn ) 
{
  if( doorClosed ) 
  {
    std::cout << "Motor can start" << std::endl;
  }
} 
else 
{
  std::cout << "Turn on the power first" << std::endl;
}
```
</div>
</div>



# `switch` statements

The use of chained and nested if statements allows you to handle multiple conditions but if you have a large number of possible outcomes the syntax can become unwieldly.

```cpp Unwieldly example
const int httpStatusCode = 404;

if( httpStatusCode == 200 )
{
  std::cout << "OK" << std::endl;
}
else if (httpStatusCode == 301)
{
  std::cout << "Moved Permanently" << std::endl;
}
else if (httpStatusCode == 400)
{
  std::cout << "Bad Request" << std::endl;
}
else if (httpStatusCode == 403)
{
  std::cout << "Forbidden" << std::endl;
}
else if (httpStatusCode == 404)
{
    std::cout << "Not Found" << std::endl;
}
else if (httpStatusCode == 500)
{
    std::cout << "Internal Server Error" << std::endl;
}
else
{
    std::cout << "Unknown Status" << std::endl;
}
```
@addcppmain()

As you can see in the example we have to compare `statusCode` for each block,
It would be easy to make a mistake and, for example, put `=` instead of `==` on one line.
Because every conditional is separate, we would only detect the issue when that specific value was checked.

-----------------------------------------

`switch` statements are an alternative option that can reduce code repetition.

Each `case` label needs to be a compile-time constant. 
In a traditional `switch`, execution continues into the next case unless it is stopped with `break` or `return`.

```cpp switch example
const int httpStatusCode = 404;

switch( httpStatusCode )
{
  case 200:
    std::cout << "OK" << std::endl;
    break;

  case 301:
    std::cout << "Moved Permanently" << std::endl;
    break;

  case 400:
    std::cout << "Bad Request" << std::endl;

  case 403:
    std::cout << "Forbidden" << std::endl;
    break;

  case 404:
    std::cout << "Not Found" << std::endl;
    break;

  case 500:
    std::cout << "Internal Server Error" << std::endl;
    break;

  default:
    std::cout << "Unknown Status" << std::endl;
    break;
}
```
@addcppmain()

<div class="good-task">
@boxheader(Question)

If you change `httpStatusCode` to `400`, what is printed and why?

[( )] Only `Bad Request`, because each `case` ends automatically.
[(X)] `Bad Request` followed by `Forbidden`, because there is no `break`.
[( )] `Unknown Status`, because `400` is not a recognized case.
***
There is no `break` after `case 400`, so execution continues into `case 403`.
It stops at the `break` after `Forbidden`.
Continuing from one case into the following one is called "fallthrough".
***
</div>

<div class="warning">
@boxheader(Warning)

Accidentally falling through from one case into the next one is a common bug.

But fallthrough is also a very useful ability when intended. 
Mark deliberate fall-through with the `[[fallthrough]];` attribute.

```cpp
const int value = 1;

switch( value )
{
  case 1: [[fallthrough]];
    std::cout << "Case 1 and I want to also run case 2" << std::endl;

  case 2:
    std::cout << "Case 2" << std::endl;
    break;

  default:
    std::cout << "Default" << std::endl;
    break;
}
```
@addcppmain()
</div>


# Recap

@recap
