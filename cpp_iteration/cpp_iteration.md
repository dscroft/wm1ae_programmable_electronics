<!--
module_id: cpp_iteration
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.1.0

language: en
narrator: UK English Female

mode: Textbook

title: C++ Iteration
comment:  This module explains how C++ `while`, `for`, and `do-while` loops repeat code, including loop control and choosing an appropriate loop.
long_description: This module introduces the fundamentals of C++ iteration and looping structures, demonstrating how to repeat code blocks efficiently and safely. Covers while, for, and do-while loops with practical examples and control flow techniques.
estimated_time_in_minutes: 40


@learning_objectives  
- Explain how `while`, `for`, and `do-while` loops check conditions and repeat code.
- Understand loop flow: initialization, condition checks, body execution, and updates.
- Choose a loop form for counting, condition-driven, or at-least-once repetition.
- Use `break` and `continue` to control loop execution.
- Identify and avoid infinite loops and off-by-one errors.
- Apply loops to solve practical problems like summing values and processing collections.

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

# Loops

Loops repeat a block of statements while a condition is true or while there are
items left to process. They avoid duplicated code and make the stopping rule
explicit. Choose a loop form that makes its condition and progress easy to see.

Three loop forms exist in C++:
- **`while`**: Check the condition before each iteration.
- **`for`**: Combine initialization, condition, and update in one place.
- **`do`-`while`**: Check the condition after the body runs (at least one execution).


## `while` loops

A `while` loop checks its condition before each iteration. 
If the condition is false at the start, the body runs zero times. 
Make sure each iteration can eventually make the condition false; otherwise the loop is infinite.

```cpp
int power{1};

while( power < 100 )
{
    std::cout << power << std::endl;
    power *= 2;
}
```
@addcppmain()

The body runs for `power` values 1, 2, 4, 8, 16, 32, and 64. At the end of
each iteration, execution returns to the condition check. The condition is not
rechecked in the middle of the body.

<div class="pass-task">
@boxheader(In the browser)

Run the example above. How many times does the loop iterate? Try changing `power < 100` to `power < 50` and observe how the number of iterations changes.

</div>


### Loop Control: `break` and `continue`

`break` exits the nearest enclosing loop immediately. 
`continue` skips the remaining statements in the current iteration and proceeds to the next
condition check. 
Use these only when they make the loop's intent clearer.

```cpp
int value{1};

while( value <= 10 ) 
{
  if( value == 5 ) 
  {
    ++value;
    continue;
  }
  
  if( value == 8 ) 
  {
    break;
  }

  std::cout << value << std::endl;
  ++value;
}
```
@addcppmain()

This loop prints 1, 2, 3, 4, 6, 7, then stops. 
When `value` is 5, `continue` skips the `std::cout` and jumps to the next condition check. 
When `value` is 8, `break` exits the loop immediately.


<div class="pass-task">
@boxheader(Question)

What would the output be if the `++value` inside the `if( value == 5 )` block were removed?

[[ ]] 1, 2, 3, 4, 6, 7
[[X]] The loop would run forever (infinite loop)
[[ ]] 1, 2, 3, 4, 7
***
Without incrementing `value` when it equals 5, the value remains 5 forever. 
The condition `value <= 10` will always be true. 
The `continue` statement skips the increment outside the if block, so `value` never changes. 
This demonstrates why each loop iteration must make progress toward the loop's exit condition.
***
</div>

------------------------------------

A `while` loop is useful when the number of repetitions is not known in
advance, such as processing input until a stop condition is reached. Braces
should be used even for a one-statement body so the loop remains easy to extend.

<div class="good-task">
@boxheader(On your machine)

Write a `while` loop that counts how many times the user enters positive values. 
Keep reading integers until the user enters a negative, then print the count.

Use the "C C++ Toolkit" as discussed in the Basics materials to help you set up a new project.

[preview-lia](../basics/basics.md)

<script input="submit" default="Hint">
"LIASCRIPT: Use `std::cin >> value` to read input."
</script>

<script input="submit" default="Hint">
"LIASCRIPT: Read the [documentation](https://en.cppreference.com/cpp/io/cin)."
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
#include <iostream>

int main()
{
  int counter {0};
    
  while( true )
  {
    int value;         // uninitalised 
    std::cin >> value; // but we immediately set a value

    if( value < 0 ) break; // stop the loop *before* the counter
    ++counter;
  }

  std::cout << counter << std::endl;

  return 0;
}
```
@LIA.cpp()
</div>
</div>


## `for` loops

A counting `for` loop keeps its setup, continuation condition, and per-iteration
update together:

```cpp
for (initialization; condition; update) 
{
  // loop body
}
```

Initialization runs once, before the first condition check. 
It commonly declares and initializes the loop variable.

Before each iteration, C++ evaluates the condition. 
If it is true, the contents of the body block runs; otherwise, execution continues after the loop.

After each iteration, the update expression runs. 
If a `continue` statement is used, C++ still performs this update before the next condition check.

```cpp
for( int i=0; i<10; ++i )
{
  std::cout << "i = " << i << std::endl;
}
```
@addcppmain()


### For Loop Variations

The `for` loop is flexible. Each clause can be omitted:

```cpp
int i = 0;
for( ; i < 10; ++i ) 
{
  std::cout << "i = " << i << std::endl;
}
```
@addcppmain()

-----------------------------------

Omitting all three clauses creates an infinite loop:

```cpp
for (;;) 
{
  std::cout << "Infinite loop" << std::endl;
  // Must have a break or return to exit
}
```

However, this is rare and can be confusing. 
Prefer a `while` loop when repetition depends on a condition rather than a counting pattern. 
Avoid packing unrelated updates into a `for` loop's comma-separated clauses; separate code is easier to read.


## `do`-`while` loops

A `do`-`while` is, as the name suggests, closely related to the `while` loop.
However, it checks its condition *after* running the body block, so its body
executes at least once. 
The semicolon after the condition is required:

```cpp
do 
{
  // Perform an action before deciding whether to repeat.
} 
while( condition );
```

-----------------------------

A common use case is validating user input:

```cpp
int value;

do 
{
  std::cout << "Enter a number between 1 and 10: ";
  std::cin >> value;
  if( value < 1 || value > 10 ) 
  {
    std::cout << "Invalid input, try again.\n";
  }
} 
while( value < 1 || value > 10 );

std::cout << "You entered: " << value << '\n';
```
@addcppmain()

Here, the prompt displays at least once, and the loop repeats if the input is invalid.

<div class="important">
@boxheader(Important)

Remember about variable block scope in C/C++.
Variables that are declared inside a block `{}` *only* exist inside that block.
For `do-while` loops this means that you cannot declare a variable inside a block and then use that variable in the condition.
</div>


<div class="pass-task">
@boxheader(On your machine)

Adjust your previous `while` loop code to use `do-while` instead.

<script input="submit" default="Hint">
"LIASCRIPT: Remember what we just said about variable block scope."
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
#include <iostream>

int main()
{
  int counter {-1};    // start at -1 so we increase to 0 on the first loop
  int value;           // uninitalised     

  do
  {
    std::cin >> value; // but we immediately set a value

    ++counter;
  }
  while( value >= 0 ); // can't use variables from inside the block

  std::cout << counter << std::endl;

  return 0;
}
```
@LIA.cpp()
</div>
</div>


## Choosing the Right Loop

<section class="flex-container">
<div class="flex-child">
**Use `while` when:**

- The number of iterations is unknown
- Repetition depends on a runtime condition
- Reading until end-of-file or a sentinel value

```cpp
while( std::cin >> value ) 
{
  // process value
}
```
</div>

<div class="flex-child">
**Use `for` when:**

- Iterating a fixed or known number of times
- Processing collections with an index
- The pattern is: start, test, update

```cpp
for( int i=0; i<100; ++i )
{
  // process i
}
```
</div>

<div class="flex-child">
**Use `do-while` when:**

- The body must execute at least once
- Validating user input or menu choices
- The condition depends on the body's output

```cpp
do 
{
  // get input
} 
while( input_invalid );
```
</div>
</section>

<div class="good-task">
@boxheader(Question)

**Which loop should you choose for printing a message 100 times?**

[( )] while
[(X)] for
[( )] do-while
***
Use a `for` loop when you know exactly how many iterations you need.
***
</div>

<div class="good-task">
@boxheader(Question)

**Which loop should you choose for reading sensor data until a threshold is crossed?**

[(X)] while
[( )] for
[( )] do-while
***
Use a `while` loop when the number of iterations depends on a runtime condition.
***
</div>

<div class="good-task">
@boxheader(Question)

**Which loop should you choose for prompting a user to enter valid input, trying at least once?**

[( )] while
[( )] for
[(X)] do-while
***
Use a `do`-`while` loop when the body must execute at least once before testing the condition.
***
</div>


# Nested Loops

Loops can be nested inside other loops. 
The inner loop completes all its iterations for each iteration of the outer loop:

```cpp
for( int row=1; row<=3; ++row ) 
{
  for( int col=1; col<=3; ++col ) 
  {
    std::cout << "(" << row << "," << col << ") ";
  }
  std::cout << std::endl;
}
```
@addcppmain()

This prints a 3×3 grid of coordinates. The inner loop runs 3 times for each
iteration of the outer loop, for a total of 9 iterations.

```
(1,1) (1,2) (1,3) 
(2,1) (2,2) (2,3) 
(3,1) (3,2) (3,3) 
```

<div class="pass-task">
@boxheader(Task: Nested Loop Pattern)

Write nested loops to print a triangle pattern:
```
*
* *
* * *
* * * *
```

Hint: The outer loop controls the number of rows (1 to 4), and the inner loop controls how many stars appear in each row.

</div>

<div class="learn-more">
@boxheader(Learn more)

Watch out! 

Nesting loops like this can have significant performance consequences.
Our 3x3 grid for example, the inner loop block ran 3 times for each of the outer loops, a total of $3*3=9$.

9 loops is not a worry but what about a 100 to a side grid? That's $100*100=10000$.

Nested loops like this are what's known as 'quadratic complexity' or $O(n^2)$ algorithms. 
$n$ is the size of the input, in this case 3 or 100. 
For $O(n^2)$ code, doubling $n$ quadruples the time it takes to run.

Different problems have [different $O()$ notations](https://en.wikipedia.org/wiki/Time_complexity).

There are many problems in programming that are difficult or effectively impossible to solve because they simply take too long to calculate as $n$ gets larger.
</div>


# Infinite Loops and Guard Conditions

An infinite loop repeats forever because the exit condition never becomes true:

Infinite loops are advised against except in very specific circumstances.

```cpp
int count {0};
while (count < 10) {
    std::cout << count << ' ';
    // Oops! forgot to increment count
}
```

This loop never exits because `count` never changes. Always ensure that:
1. The loop variable is updated each iteration.
2. The update moves toward the exit condition.

<div class="learn-more">
@boxheader(Learn more)

Infinite loops have caused multiple issues. 
One of the more public examples was the Microsoft Zune infinite loop bug as discussed in detail [here](https://web.archive.org/web/20091223083344/http://winjade.net/2009/01/lesson-on-infinite-loops/).

For safety critical code, infinite loops are often explicitly banned, e.g. [Rule 2 of the JPL Power of 10](https://en.wikipedia.org/wiki/The_Power_of_10:_Rules_for_Developing_Safety-Critical_Code).
A loop that tries 10,000 times but *eventually* gives up with an error message is to be preferred over an infinite one.
</div>


# Common Loop Patterns

@sectiontoc(1)


## Summing values

```cpp
int sum {0};

for( int i=1; i<=100; ++i ) 
{
  sum += i;
}

std::cout << "Sum: " << sum << std::endl;
```
@addcppmain()

This computes the sum 1 + 2 + ... + 100 = 5050.


## Counting matches

Not covered containers yet but we will.

[lia-preview](../cpp_containers/cpp_containers.md)

```cpp
std::array<int, 5> values { 3, 7, 2, 7, 9 };
int count{0};

for( int i=0; i<values.size(); ++i ) 
{
  if( values[i] == 7 ) 
  {
    ++count;
  }
}

std::cout << "7 appears " << count << " times" << std::endl;
```
@addcppmain1(array)


## Finding a value

```cpp
#include <array>

std::array<int, 5> values {3, 7, 2, 7, 9};
int target {7};
bool found {false};

for( int v : values ) 
{
  if( v == target ) 
  {
    found = true;
    break;
 }
}

if( found ) 
{
  std::cout << "Target found" << std::endl;
} 
else 
{
  std::cout << "Target not found" << std::endl;
}
```
@addcppmain1(array)

This uses a **range-based for loop** (`for (type var : collection)`), which is cleaner than index-based loops for iterating over all elements.

# Tasks

<div class="pass-task">
@boxheader(On your machine)

Write a program that outputs every even number from 1-100.

<script input="submit" default="Hint">
"LIASCRIPT: Think about the update section of a `for` loop."
</script>

<script input="submit" default="Hint">
"LIASCRIPT: You don't have to increament your loop variables by 1. You can increment by any amount."
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
#include <iostream>

int main()
{
  /* 1 isn't even so start at 2,
     increment by 2 each time */
  for( int i=2; i<=100; i+=2 )
  {
    std::cout << i << std::endl;
  }

  return 0;
}
```
@LIA.cpp()
</div>
</div>


<div class="adv-task">
@boxheader(On your machine)

Write a program that:

1. Asks the user to enter a positive integer `n`
2. Calculates and prints the factorial of `n` (n! = n × (n-1) × (n-2) × ... × 1)
3. For example, 5! = 5 × 4 × 3 × 2 × 1 = 120

<script input="submit" default="Hint">
"LIASCRIPT: Try decrementing from `n` down to 0."
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer2").style.display = "block";
"Answer"
</script>

<div id="answer2" style="display: none">

```cpp
#include <iostream>

int main()
{
  int n {0};
  std::cout << "Enter a positive integer: ";
  std::cin >> n;
  
  int factorial {1};
  for( int i=n; i>0; --i )
  {
    factorial *= i;
  }
  
  std::cout << n << "! = " << factorial << std::endl;

  return 0;
}
```
@LIA.cpp()

</div>
</div>


# Questions

<div class="good-task">
@boxheader(Question)

**Without running it, what does this code print?**

```cpp
for( int i=0; i<5; ++i ) 
{
    if (i == 2) continue;
    std::cout << i << ' ';
}
std::cout << std::endl;
```

[[ ]] 0 1 2 3 4
[[ ]] 0 1 2 2 3 4 5
[[ ]] 0 1 3 4 5
[[X]] 0 1 3 4
***
When `i` equals 2, `continue` skips the `std::cout` and jumps to the next iteration. 
The value 2 is never printed.
***
</div>

<div class="good-task">
@boxheader(Question)

**How many times does this loop iterate?**

```cpp
int count {0};
for( double x=0.0; x<1.0; x+=0.1 ) 
{
  ++count;
}
std::cout << count << std::endl;
```

[[ ]] 9
[[ ]] 10
[[X]] 11
***
Floating-point arithmetic can introduce rounding errors. 
After 10 iterations, `x` might be 0.9999999... or 1.0000001..., causing the loop to terminate unpredictably. 
In this specific example, after 10 iterations the `x` is 0.99999999999999988897769753748434595763683319091796875.
On the 11th iteration `x` is 1.0999999999999998667732370449812151491641998291015625.
For counting loops, prefer integers.

```cpp
#include <iomanip>
#include <iostream>

int main()
{
  int count {0};
  for( double x=0.0; x<1.0; x+=0.1 ) 
  {
    // print *all* the decimal places
    std::cout << std::setprecision(999) << x << std::endl;
  }

  return 0;
}
```
@LIA.cpp()
***
</div>


# Recap

@recap