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
import: https://raw.githubusercontent.com/liaTemplates/AVR8js/main/README.md
import: https://raw.githubusercontent.com/dscroft/mermaid_template/refs/heads/master/README.md
import: ../assets/macros.md
-->

# Functions and Procedures

@overview

# Basics

A **function** is a reusable block of code that performs a specific task. Functions allow you to:

- Break large programs into manageable pieces
- Reuse code without repeating it
- Test code in isolation
- Improve readability

## Function Declaration

A **function declaration** (also called a prototype) tells the compiler about a function before you use it.

It consists of the function's name, return type and any parameters. 
It does not include the block for the code to run when the function is called.

```c
return_type function_name( parameter_type param1, parameter_type param2 );
```

Example:

```c
int add( int a, int b );  // Function declaration (prototype)
```

## Function Definition

A **function definition** provides the actual implementation, i.e. the block of code that should be run when this function is called.


```c
return_type function_name( parameter_type param1, parameter_type param2 ) 
{
  // Function body
  return return_value;
}
```

Example:

```c
int add( int a, int b ) 
{
  int sum = a + b;
  return sum;
}
```

<div class="pass-task">
@boxheader(Question)

**Which of the following is a valid function declaration?**

[( )] `int add(int a, int b) { return a + b; }`
[(X)] `int add(int a, int b);`
[( )] `int add;`
***
A function declaration (prototype) must include return type, name, and parameters, but NOT the implementation body. The implementation comes in the function definition.
`int add;` is just a variable, not a function.
***
</div>

<div class="pass-task">
@boxheader(Question)

Complete this function declaration for a function that takes an integer and returns a double.

*This is a fill-in-the-blanks question.*

<div style="font-family: LiaSourceCodePro">
[[ double ]] convertToDouble( [[ int ]] input );
***
```cpp
double convertToDouble( int input );
```
***
</div>
</div>

<div class="good-task">
@boxheader(Question)

**What is the key difference between a function declaration and a function definition?**

[[ ]] A declaration includes the curly braces with the code body
[[X]] A declaration is a prototype without the body; a definition includes the body with the implementation
[[ ]] A declaration is used in C, while a definition is used in C++
[[ ]] There is no difference; the terms are interchangeable
***
A function declaration (prototype) tells the compiler the function's name, parameters, and return type, but does NOT include the implementation block. A function definition includes the full implementation block (the code inside the curly braces). You need the declaration before using the function and the definition to implement it.
***
</div>

## Complete Example

<section class="flex-container">
<div class="flex-child">

```cpp
#include <iostream>

// Function declaration (prototype)
int add(int a, int b);

// Main function
int main() 
{
  int result = add(5, 3);
  std::cout << "5 + 3 = " << result << std::endl;

  return 0;
}

// Function definition
int add( int a, int b ) 
{
    return a + b;
}
```
@LIA.cpp()
</div>
<div class="flex-child">

```cpp
#include <iostream>

// Function declaration and definition
int add( int a, int b ) 
{
    return a + b;
}

// Main function
int main() 
{
  int result = add(5, 3);
  std::cout << "5 + 3 = " << result << std::endl;

  return 0;
}
```
@LIA.cpp()
</div>
</section>

<div class="good-task">
@boxheader(Question)

**Looking at the left example above, which part is the function definition?**

[[ ]] `int add(int a, int b);` on line 4
[[X]] The `int add( int a, int b ) { return a + b; }` block from lines 16-19
[[ ]] The entire file is the definition
***
A function definition includes the function signature AND the implementation block (the curly braces with the code inside). The declaration on line 4 is only a prototype. The actual definition with the body comes later.
***
</div>

### Code management and structure

It is common in larger C/C++ projects to organise your code over multiple files as a single massive file containing everything becomes unmanageable.
In these scenarios the function declarations are typically placed in .h or .hpp (header) files inside an include/ folder.
Whilst the function declarations are placed in .c or .cpp (source) files in a src/ folder.
Other structures can and do exist, but for a simple project this would be standard.
This will become increasingly relevant when we cover the unit testing and version control materials.

It is sometimes possible to just put the combined function declaration/definition in a header file but this has negative consequences on larger projects.
For a small simple project you would be fine.

<section class="flex-container">
<div class="flex-child">
**Arduino project example**

```mermaid @mermaid
treeView-beta
project/                ## Your project directory
├── include/
│   └── myfunctions.h   ## Function declarations
├── src/
|   ├── main.cpp
│   └── myfunctions.cpp ## Function definitions
└── platformio.ini      ## Project configuration file
```
</div>
<div class="flex-child">
**General project example**

```mermaid @mermaid
treeView-beta
project/                ## Your project directory
├── include/
│   └── myfunctions.h   ## Function declarations
├── src/
|   ├── main.cpp
│   └── myfunctions.cpp ## Function definitions
└── CMakeLists.txt      ## Build configuration file
```
</div>
</section>

```cpp myfunctions.h
int add( int a, int b );
```
```cpp myfunctions.cpp
#include "myfunctions.h"

int add( int a, int b )
{
  return a + b;
}
```
```cpp main.cpp
#include <iostream>

#include "myfunctions.h"

int main()
{
  std::cout << add( 42, 67 ) << std::endl;

  return 0;
}
```
@LIA.eval(`["myfunctions.h", "myfunctions.cpp", "main.cpp"]`, `g++ myfunctions.cpp main.cpp`, `./a.out`)


# Function Parameters

@sectiontoc(1)


## Pass by Value

By default, function arguments are **passed by value**. This means the function receives a **copy** of the value:

```cpp
void increment( int x ) 
{
  x++;  // This increments the copy, not the original
}

int main() 
{
  int num = 5;
  increment(num);
  std::cout << "num = " << num << std::endl; // Still 5, not 6!
  return 0;
}
```
@LIA.cpp()

<div class="good-task">
@boxheader(Question)

**Without running it, what does this code print?**

```cpp
void modify( int x ) { x = 100; }
int main() 
{
  int value = 5;
  modify(value);
  std::cout << value << std::endl;
  return 0;
}
```

[(X)] 5
[( )] 100
***
Pass by value creates a copy of the parameter. Changes inside the function don't affect the original variable.
***
</div>


### Pass by Reference

To modify a variable in a function, pass a **reference** to it instead.
This passes the memory address of the original variable as opposed to the value in that memory.
Meaning that changes made affect the original variable.

```c
#include <iostream>

void increment( int &x ) 
{
  x++;  // this is a reference fo it modifies the original
}

int main() 
{
  int num = 5;
  increment(num);  // Pass address of num
  std::cout << "num = " << num << std::endl;  // Now 6!
  return 0;
}
```

<div class="learn-more">
@boxheader(Learn more)

We'll learn more about reference (and pointers) in the memory materials in a later module. 
For now, understand that declaring a variable type as `type & ` makes it a reference to the original variable and not a copy it.

[preview-lia](../memory/memory.md)
</div>

<div class="good-task">
@boxheader(Question)

**Without running it, what does this code print?**

```cpp
void modify( int& x ) { x = 100; }
int main() 
{
  int value = 5;
  modify(value);
  std::cout << value << std::endl;
  return 0;
}
```

[( )] 5
[(X)] 100
***
Pass by reference modifies the original variable. The & creates an alias to the original.
***
</div>

<div class="good-task">
@boxheader(On your machine)

Write a function called `swap` that takes two integer references and swaps their values. 
Test it with two variables.

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
void swap( int &a, int &b )
{
  const int temp = a;
  a = b;
  b = a;
}

// although if you want to get fancy, wait until we cover templates
template<typename T>
void swap( T &a, T &b )
{
    const T temp = a;
    a = b;
    b = a;
}
```
</div>
</div>


## Default Parameters

C++ allows default values for parameters.
This means that you can write functions that take a large number of parameters but callers don't need to provide them all, they can use sensible defaults for the ones they omit. 

```cpp
#include <iostream>
#include <string>

//                                         delay_ms defaults to 1000
void delay_message( const std::string msg, int delay_ms=1000 ) 
{  
    std::cout << "Print with delay of " << delay_ms << std::endl; 
}

int main()
{
  // Can call with or without the parameter
  delay_message("Hello");           // Uses default 1000ms
  delay_message("Urgent!", 100);    // Uses 100ms

  return 0;
}
```
@LIA.cpp()

<div class="warning">
@boxheader(Warning)

C does **not** support default parameters.
</div>

---------------------------------------

Unfortunately in C++ you cannot skip default parameters[^1]. 
If you have multiple parameters with default values and want to provide a value for the last one, you must also provide values for all the parameters before it. 
This is a limitation of positional arguments.

```cpp
void configure( int speed=100, int delay=50, int retries=3 );

// Valid calls
configure();                    // All defaults
configure(200);                 // speed=200, delay and retries use defaults
configure(200, 100);            // speed=200, delay=100, retries uses default
configure(200, 100, 5);         // All specified

// INVALID - cannot do this:
// configure(200, , 5);         // Error: cannot skip delay parameter
// configure(, 100, 5);         // Error: cannot skip speed parameter
```

<div class="good-task">
@boxheader(Question)

**This code has an error. What is it?**

```cpp
int calculate(int a, int b = 10, int c) { return a + b + c; }
```

<script input="submit" default="Answer">
"LIASCRIPT: Default parameters must come after non-default parameters. Parameter `c` cannot come after `b` with a default."
</script>
</div>

[^1] Ask again for C++20 onwards. 


# Return Values

Functions return a value using the `return` statement:

A function can have **multiple return statements**. 
The function exits immediately when any `return` statement is executed, and no code after that return is executed.

```cpp
int get_maximum( int a, int b ) 
{
  if (a > b) 
  {
    return a;
  } 
  else 
  {
   return b;
  }

  std::cout << "Never going to run!" << std::endl;
}
```

## `void` Functions

Functions with return type `void` do **not** return a value.

```c
void print_separator() 
{
  std:cout << "====================" << std::endl;
  // No return statement needed, but 'return;' is allowed
}
```

## Multiple Values

Sometimes a function needs to return multiple values. 
C++ provides several ways to do this:

1. **Using `std::tuple`** (C++11 and later) - type-safe and elegant
2. **Using output parameters** (pass by reference).
3. **Using a struct** - when return values are related
4. **Using a class** - for more complex scenarios

<div class="learn-more">
@boxheader(Learn more)

Classes are a fairly major topic that you have yet to cover.
But structs are much simpler and well worth you investigating if you have the time.
Read the [documentation](https://en.cppreference.com/c/language/struct_initialization).
</div>


### Returning Tuples 

A `std::tuple` allows a function to return multiple values of different types in a single return statement.
A `std::tuple` is a container that can store multiple different types of variables in specific positions.

```cpp
#include <iostream>
#include <tuple>

// Function returns three values: success (bool), name (string), age (int)
std::tuple<bool, std::string, int> parse_person_data( const std::string data ) 
{
  // Simple parsing (in real code, use proper parsing)
  if( data.empty() ) 
  {
    // can create a tuple using the std::make_tuple function
    return std::make_tuple( false, "", 0 );  // Parse failed
  }
    
  // can create a tuple using brace initialisation
  return { true, "Alice", 30 };  // Parse succeeded
}

int main() 
{
  // return a tuple
  std::tuple<bool, std::string, int> result = parse_person_data("some data");

  /* or for simpler code use auto keyword, the variable is still a tuple,
    but the compiler automatically figures out the variable type based on the 
    function's declared return type */
  auto resultAuto = parse_person_data("some data");

  // Access by index
  bool success = std::get<0>(result);
  std::string name = std::get<1>(result);
  int age = std::get<2>(resultAuto);
    
  std::cout << "Success: " << success << ", Name: " << name << ", Age: " << age << std::endl;
    
  return 0;
}
```
@LIA.cpp()

<div class="important">
@boxheader(Important)

Returning tuples is only for C++11 onwards.
</div>

<div class="warning">
@boxheader(Warning)

The `auto` keyword is great but use it with caution. 
For function return values you are generally safe, but it does obscure variable types when reading the code.
</div>

<div class="good-task">
@boxheader(Question)

**What is the type of `result` in this code?**

*This is a fill-in-the-blanks question.*

<div style="font-family: LiaSourceCodePro">
std::tuple< [[ int ]], [[ double ]] > result;
***
```cpp
`std::tuple<int, double>`
```
***
</div>
</div>


### Structured Binding

**Structured binding** provides a cleaner, more readable way to unpack multiple return values than extracting from tuples by index.
It automatically extracts tuple elements into separate variables.

```cpp
#include <iostream>
#include <tuple>

// Same function as before
std::tuple<bool, std::string, int> parse_person_data( const std::string data ) 
{
  if( data.empty() ) return { false, "", 0 };
  return { true, "Alice", 30 };
}

int main() 
{
  // Structured binding - much cleaner!
  auto [success, name, age] = parse_person_data("some data");
    
  std::cout << "Success: " << success << ", Name: " << name << ", Age: " << age << std::endl;
    
  // Can use auto for automatic type deduction
  auto [ok, person, years] = parse_person_data("another data");
    
  return 0;
}
```
@LIA.cpp()

**Benefits of structured binding:**

- More readable and concise than `std::get<N>()`.
- Automatically deduces types.
- Variables are named meaningfully.
- Reduces verbosity compared to traditional tuple unpacking.

<div class="important">
@boxheader(Important)

Returning tuples is only for C++17 onwards.
</div>

<div class="adv-task">
@boxheader(On your machine)

Rewrite this code using structured bindings.

```cpp
auto result = std::make_tuple(25, 5.9);
int error = std::get<0>(result);
double value = std::get<1>(result);
```

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
auto [error, value] = std::make_tuple(25, 5.9);
```
</div>
</div>


## Return-Early Pattern (Guard Clauses)

A common best practice is to use **return-early** (also called guard clauses) at the beginning of a function to validate parameters and exit quickly if conditions aren't met. 
This reduces nesting and makes the code more readable.

```cpp
#include <iostream>
#include <string>

// Return early pattern: validate inputs at the top
bool is_valid_email( const std::string email ) 
{
  // Guard clauses: check invalid conditions first and return early
    
  if( email.empty() ) 
  {
    std::cerr << "Error: Email cannot be empty" << std::endl;
    return false;
  }
    
  if( email.length() < 5 ) 
  {
    std::cerr << "Error: Email too short" << std::endl;
    return false;
  }
    
  if( email.find('@') == std::string::npos ) 
  {
    std::cerr << "Error: Email must contain @" << std::endl;
    return false;
  }
    
  if( email.find('.') == std::string::npos ) 
  {
    std::cerr << "Error: Email must contain ." << std::endl;
    return false;
  }
    
  // If we reach here, all checks passed
  return true;
}

int main() 
{
  std::cout << "user@example.com: " << is_valid_email("user@example.com") << std::endl;
  std::cout << "invalid: " << is_valid_email("invalid") << std::endl;
  std::cout << "@example.com: " << is_valid_email("@example.com") << std::endl;
    
  return 0;
}
```
@LIA.cpp()

**Advantages of return-early:**

- Reduces deeply nested if-else blocks.
- Makes error handling explicit and obvious.
- Improves readability by validating preconditions first.
- Easier to debug and maintain.

---------------------------------

In comparision, the nested if version of this code is almost unreadable.

```cpp
// Nested if statements version (harder to read)
bool is_valid_email( const std::string email ) 
{
  if( !email.empty() ) 
  {
    if( email.length() >= 5 ) 
    {
      if( email.find('@') != std::string::npos ) 
      {
        if( email.find('.') != std::string::npos ) 
        {
          // All checks passed - deeply nested!
          return true;
        } 
        else 
        {
          std::cerr << "Error: Email must contain ." << std::endl;
        }
      } 
      else 
      {
        std::cerr << "Error: Email must contain @" << std::endl;
      }
    } 
    else 
    {
      std::cerr << "Error: Email too short" << std::endl;
    }
  } 
  else 
  {
    std::cerr << "Error: Email cannot be empty" << std::endl;
  }
    
  return false;
}
```

<div class="adv-task">
@boxheader(On your machine)

Refactor this function using the return-early pattern.

```cpp
int processValue( int value ) 
{
  if( value >= 0 ) 
  {
    // lots of processing code
    return result;
  }
  else 
  {
    return -1;  // Error code
  }
}
```

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
int processValue( int value ) 
{
  if( value < 0 ) return -1 // Error code

  // lots of processing code
  return result;
}
```
</div>
</div>

<div class="adv-task">
@boxheader(Question)

**What is the main benefit of the return-early pattern?**

[(X)] It reduces nesting and improves readability by handling error cases first.
[( )] It makes functions run faster.
[( )] It reduces memory usage.
***
The return-early pattern improves code clarity by putting boundary conditions and error handling at the top, leaving the main logic unindented and easier to follow.
***
</div>


# Scope and Lifetime

Variables declared in a function have **scope** (the block where they can be accessed) and **lifetime** (how long they exist). 
When you leave a block (function), anything declared within that block goes out of scope and ceases to exist.


## Local Variables

Local variables are declared **inside** a function block. 
They are only available within that function's block and only exist during that function's execution.

```cpp
#include <iostream>

int function() 
{
  int localVar = 5;                     // Created here, in function block
  std::cout << localVar << std::endl;  // 5 - still in scope
  return localVar;
}  // End of function block - localVar goes out of scope and is destroyed

int main()
{
  function();
  std::cout << localVar << std::endl;  // ERROR! localVar is out of scope - doesn't exist

  return 0;
}
```
@LIA.cpp()

<div class="pass-task">
@boxheader(In the browser)

Run the example code and see the issue.
</div>


## Global Variables

Global variables are declared **outside** all function blocks and exist for the entire program's lifetime. 
They can be accessed from any function block.

```c
#include <iostream>

int globalVar = 10;  // Global - exists for entire program

void function1() 
{
  std:;cout << globalVar << std::endl;  // Can access - in scope everywhere
  globalVar++;
}

void function2() 
{
  std::cout << globalVar << std::endl;  // Sees the modified value from function1()
}

int main()
{
  function1();
  function2();
  return 0;
}
```
@LIA.cpp()

<div class="important">
@boxheader(Important)

Minimize global variables! 

They make code harder to understand and test because any function block can modify them. 
Pass variables as parameters instead to make dependencies explicit.

Large numbers of global variables is often a sign of poor code quality, although there are some specific specialized exceptions where it cannot be avoided.
None of those exceptions apply to *anything* that you are going to be doing on this module, year, or (probably) the entire course!
</div>

<div class="learn-more">
@boxheader(Learn more)

There are various other scopes that variables can exist within but they are not required for this module.

For example the following would declare a variable at file scope (also called internal linkage).
I.e. it is 'global' for any code in the same file, but not accessible by code outside that file.

```cpp
namespace
{
  int fileVar = 99;
}
```
</div>

<div class="pass-task">
@boxheader(Question)

**What variables are in scope at each point? (marked with comments)**

```cpp
int global = 10;

void example() 
{
  int a = 1;
  // Point A: Which variables are in scope?
  
  if( true ) 
  {
    int b = 2;
    // Point B: Which variables are in scope?
  }
  
  // Point C: Which variables are in scope?
}
```

<section class="flex-container">
<div class="flex-child">
*Point A*

[[X]] `global`
[[X]] `a`
[[ ]] `b`
</div>
<div class="flex-child">
*Point B*

[[X]] `global`
[[X]] `a`
[[X]] `b`
</div>
<div class="flex-child">
*Point C*

[[X]] `global`
[[X]] `a`
[[ ]] `b`
</div>
</section>
</div>


## Static Variables

Because local variables are created fresh each time a function runs, they do not persist their values from one call to the next.
Historically, global variables were used to store information that needs to persist across function calls.
However, following best practices to minimize global variables, **use static local variables instead** when you need data to persist between calls to a specific function.

Static variables retain their value between function calls. 
They are initialized once and persist for the program's lifetime.

```cpp
#include <iostream>

void counter() 
{
  static int count = 0;  // Initialized only once, retains value between calls
  count++;
  std::cout << "Called " << count << " times" << std::endl;
}

int main() 
{
  counter();  // Called 1 times
  counter();  // Called 2 times
  counter();  // Called 3 times
  return 0;
}
```

<div class="good-task">
@boxheader(On your machine)

Write a solution that keeps track of the number of times two different functions are called.

- Solve it using global variables.

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp Global solution
#include <iostream>

unsigned int counter = 0;

unsigned int function1()
{
  return ++counter; // both functions increment the same counter.
}

unsigned int function2()
{
  /* using pre-increment as opposed to counter++
    because this increases the count and *then*
    returns the updated value */
  return ++counter; 
}

int main()
{
  std::cout << function1() << std::endl;
  std::cout << function1() << std::endl;
  std::cout << function2() << std::endl;
  std::cout << function2() << std::endl;

  return 0;
}
```
@LIA.cpp()
</div>
</div>

<div class="adv-task">
@boxheader(On your machine)

Solve it again *without* using global variables.

<script id="button" input="submit" default="Answer">
document.getElementById("answer2").style.display = "block";
"Answer"
</script>

<div id="answer2" style="display: none">

```cpp Static solution
#include <iostream>

/* static variable belongs to the counter function
   this helps to ensure that the variable can *only*
   be incremented */
unsigned int _inc_counter()
{
  static unsigned int counter = 0;
  return ++counter;
}

unsigned int function1()
{
  return _inc_counter();
}

unsigned int function2()
{
  return _inc_counter();
}

int main()
{
  std::cout << function1() << std::endl;
  std::cout << function1() << std::endl;
  std::cout << function2() << std::endl;
  std::cout << function2() << std::endl;

  return 0;
}
```
@LIA.cpp()
</div>
</div>


# Recursion

**Recursion** is a specific design pattern in which a function calls itself. 
Some problems are **naturally recursive** because they have a structure where the solution to a large problem can be built from solutions to smaller versions of the same problem.

Recursion is ideal for problems with **self-similar structure**:

- **Factorial** (`n! = n × (n-1)!`): Each factorial depends on a smaller factorial
- **Tree traversal**: Processing a tree node involves processing its subtrees
- **Directory searching**: Searching for files in a folder involves searching in subfolders
- **Parsing**: Parsing nested structures (JSON, XML) naturally maps to recursive parsing
- **Divide-and-conquer algorithms**: Binary search, quicksort, mergesort


Every recursive function needs:

1. **Base case**: Condition that stops recursion.
2. **Recursive case**: Call to itself with different arguments.

```cpp Recursive factorial example
int factorial( int n ) 
{
  std::cout << "Called factorial(" << n << ")" << std::endl;

  if( n <= 1 ) 
  {
    return 1;  // Base case
  } 
  else 
  {
    return n * factorial(n - 1);  // Recursive case
  }
}

int main()
{
  // factorial(5) = 5 * factorial(4) = 5 * 4 * 3 * 2 * 1 = 120
  factorial(5);
  return 0;
}
```
@LIA.cpp()


## Recursion Depth

Every function call uses stack space (memory).
If a function calls another function then both functions exist on the stack using the space needed for both.
If a recursive function, as you go deeper and deeper into the recursion, more and more functions are on the stack needing more and more memory.

Too many calls will use up all the memory and cause a **stack overflow**:

```cpp Infinite example
void infinite_recursion() 
{
  infinite_recursion();  // WRONG! Never reaches base case - stack overflow!
}
```

<div class="warning">
@boxheader(Warning)

Embedded systems often have very limited stack space, therefore recursion is generally a poor choice on MCUs.
Use loops instead if at all possible.

Multiple safe coding standards explicitly ban recursion because of this.
Rule 1 of the [JPL Power of 10](https://en.wikipedia.org/wiki/The_Power_of_10:_Rules_for_Developing_Safety-Critical_Code) for example.

Our factorial example from before can be re-written as an iterative (solved using loops) problem, even if recursion might have been a more natural fit.

```cpp Iterative factorial example
int factorial( int n ) 
{
  if( n <= 1 ) return 1;  // Base case
    
  int result = 1;
    
  // Loop from 2 to n, multiplying each value
  for( int i=2; i<=n; ++i ) 
  {
    result *= i;
  }
    
  return result;
}
```
</div>

<div class="good-task">
@boxheader(On your machine)

Write a recursive function `fibonacci(int n)` that returns the n<sup>th</sup> Fibonacci number. 

- Test with n=5 (should return 5).

<script id="button" input="submit" default="Answer">
document.getElementById("answer2").style.display = "block";
"Answer"
</script>

<div id="answer2" style="display: none">

```cpp Fibonacci solution
#include <iostream>

/**
 * @brief Calculate the nth Fibonacci number recursively.
 *
 * @param n The position in the Fibonacci sequence (0-indexed).
 * @return The nth Fibonacci number.
 *
 * @note For n=5, returns 5 (0,1,1,2,3,5,...)
 */
int fibonacci(int n)
{
  if( n <= 1 )
  {
    return n;
  }
  
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
  std::cout << fibonacci(5) << std::endl;
  return 0;
}
```
@LIA.cpp()
</div>
</div>

<div class="good-task">
@boxheader(Question)

**Identify a problem that is inherently recursive**

*Choose all that apply.*

[[X]] Searching a directory tree.
[[ ]] Printing numbers from 1 to 100.
[[X]] Traversing a file system.
[[X]] Parsing nested structures.
[[ ]] Summing an array of integers.
***
Recursive problems have self-similar subproblems. 
Directory searching, file systems, and nested data structures (JSON, XML etc) are naturally recursive. 
Simple counting and summing are better solved iteratively.
***
</div>



# Good Design

Well-designed functions are the foundation of maintainable code. 
When functions are clear, focused, and follow established principles, your code becomes easier to understand, test, debug, and modify. 
This section covers key principles for designing functions that will serve you well throughout your programming career.

<blockquote style="border-left: 4px solid; padding-left: 15px; margin: 20px 0; font-style: italic;">
  <p>"Always code as if the guy who ends up maintaining your code will be a violent psychopath who knows where you live."</p>
  <p style="text-align: right; margin-top: 10px; font-weight: bold; color: #333;">— Martin Golding</p>
</blockquote>


## 1. Single Responsibility

Each function should do one thing well:

<section class="flex-container">
<div class="flex-child">

**Good**
```cpp
int calculate_sum( int a, int b ) 
{
  return a + b;
}
```

- Clear, single purpose.
</div>
<div class="flex-child">

**Poor**
```cpp
int add_and_print( int a, int b ) 
{
  int sum = a + b;
  std::cout << "Sum: " << sum << std::endl;
  return sum;
}
```

- Mixes calculation and I/O.
</div>
</section>


## 2. Meaningful Names

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

## 3. Keep Functions Small

Functions should be small enough to understand at a glance (typically less than 20-30 lines):

```cpp
// If a function gets too large, split it:
void process_data( data_t &data ) 
{
  validate_data(data);
  transform_data(data);
  save_data(data);
}
```

<div class="learn-more">
@boxheader(Learn more)

Refering again to code quality and safety critical code. 
Rule 4 of the [JPL Power of 10](https:R//en.wikipedia.org/wiki/The_Power_of_10:_Rules_for_Developing_Safety-Critical_Code) for example.

If you are concerned about the complexity of your function then metrics such as [McCabe's cyclomatic complexity](https://en.wikipedia.org/wiki/Cyclomatic_complexity) can help. 
These kind of checks can be run against your code base automatically, but in the meantime there are [websites](https://calculateyogi.com/technology/cyclomatic-complexity-calculator) that can assist you in checking a single function.
</div>



## 4. Minimize Side Effects

Functions should avoid unexpected behavior (side effects):

<section class="flex-container">
<div class="flex-child">
**Bad**

```cpp
int multiply( int a, int b ) 
{
  global_operations_count++;  // Side effect!
  return a * b;
}
```

- Has side effect (modifies global).
</div>
<div class="flex-child">
**Good**

```cpp
int multiply( int a, int b ) 
{
  return a * b;
}
```

- Good: Self-contained, no surprises
</div>
</section>

## 5. Document Expectations

```c
// Find the index of the first occurrence of value in array
// Returns -1 if not found
int find_index( std::vector<int> data, int size, int value ) 
{
  for( int i = 0; i < size; i++ ) 
  {
    if( data[i] == value ) 
    {
      return i;
    }
  }
  
  return -1;
}
```

### Doxygen

<div class="learn-more">
@boxheader(Learn more)

If you want to get extra fancy you can look into documentation generation systems such as [Doxygen](https://www.doxygen.nl/).

Doxygen is a widely-used documentation generator tool. 
It automates the generation of documentation from source code comments, parsing suitably formatted comments to produce output in formats like HTML.

```cpp Doxygen Example
/**
 * @brief Find the index of the first occurrence of a value in a vector.
 * 
 * @param data The vector to search through.
 * @param size The number of elements to search (useful for partial searches).
 * @param value The value to find.
 * 
 * @return The index of the first occurrence of value in the vector.
 * @return -1 if the value is not found.
 * 
 * @note This function performs a linear search with O(n) time complexity.
 * 
 * @example
 * @code
 * std::vector<int> numbers = {10, 20, 30, 40};
 * int index = find_index(numbers, 4, 30);  // Returns 2
 * int not_found = find_index(numbers, 4, 99);  // Returns -1
 * @endcode
 */
int find_index(std::vector<int> data, int size, int value) 
{
  for(int i = 0; i < size; i++) 
  {
    if(data[i] == value) 
    {
      return i;
    }
  }
  
  return -1;
}
```
</div>

<div class="adv-task">
@boxheader(On your machine)

Write the Doxygen style comment for this function.

```cpp
double celsius_to_fahrenheit( double celsius ) 
{
  return (celsius * 9.0 / 5.0) + 32.0;
}
```

<script input="submit" default="Hint">
"LIASCRIPT: Remember your `@brief`, `@param`, `@return` tags."
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
/**
 * @brief Convert temperature from Celsius to Fahrenheit.
 *
 * Uses the standard formula: F = (C × 9/5) + 32
 *
 * @param celsius The temperature in degrees Celsius.
 * @return The equivalent temperature in degrees Fahrenheit.
 *
 * @example
 * @code
 * double freezing = celsius_to_fahrenheit(0.0);    // Returns 32.0
 * double boiling = celsius_to_fahrenheit(100.0);   // Returns 212.0
 * @endcode
 *
 * @note The input can be any double value, including negative numbers.
 */
```
</div>
</div>


## Example: Arduino Function Structure

So lets see how everything that has been discussed so far comes together for an Arduino program.
There are still improvements that could be made, e.g. separating functions into separate files, but code like that below would be considered good quality for this module.

<div id="function-example">
  <wokwi-pushbutton pin="2"></wokwi-pushbutton>
  <wokwi-led color="green" pin="13"></wokwi-led>
</div>

```cpp Arduino example
// Global variables
constexpr int BUTTON_PIN = 2;
constexpr int LED_PIN = 13;
unsigned long lastPress = 0;

// Function declarations (prototypes)
void setup();
void loop();
void handle_button_press();
void toggle_led();
void debounce_delay();

// Implementation

/**
 * @brief Initialize hardware pins for button input and LED output.
 *
 * Configures BUTTON_PIN as an input pin and LED_PIN as an output pin.
 * This function should be called once during program startup.
 */
void setup() 
{
  pinMode( BUTTON_PIN, INPUT );
  pinMode( LED_PIN, OUTPUT );
}

/**
 * @brief Main program loop that continuously checks for button presses.
 *
 * Reads the button state and triggers the debounce routine if a HIGH signal
 * is detected. After debouncing, calls the button press handler if the signal
 * is still HIGH.
 */
void loop() 
{
  if( digitalRead(BUTTON_PIN) == HIGH ) 
  {
    debounce_delay();
    if( digitalRead(BUTTON_PIN) == HIGH ) 
    {
      handle_button_press();
    }
  }
}

/**
 * @brief Handle button press events with debounce protection.
 *
 * Checks if enough time has elapsed since the last press (200ms debounce window).
 * If valid, toggles the LED and updates the last press timestamp.
 *
 * @note This function prevents false multiple presses from electrical noise.
 */
void handle_button_press() 
{
  unsigned long now = millis();
  if( now - lastPress > 200 ) 
  { 
    // Debounce 200ms
    toggle_led();
    lastPress = now;
  }
}

/**
 * @brief Toggle the LED state between ON and OFF.
 *
 * Maintains a static boolean state variable and inverts it each time
 * this function is called. The new state is written to the LED_PIN.
 */
void toggle_led() 
{
  static boolean state = false;
  state = !state;
  digitalWrite(LED_PIN, state);
}

/**
 * @brief Add a hardware debounce delay.
 *
 * Pauses execution for 20 milliseconds to allow electrical noise to settle
 * before reading the button state again.
 */
void debounce_delay() 
{
  delay(20);
}
```
@AVR8js.sketch(function-example)


# Recap

@recap

------------------------------------

- **Functions** break code into reusable, testable pieces
- **Parameters** pass information to functions
- **Return values** pass information back from functions
- **Scope** determines where variables can be accessed
- **Recursion** allows functions to call themselves (but watch stack usage!)
- **Write small, focused functions** with clear names
- **Minimize side effects** and global variables
