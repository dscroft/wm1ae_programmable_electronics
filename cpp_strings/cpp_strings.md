<!--
module_id: cpp_strings
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.1.0

language: en
narrator: UK English Female

mode: Textbook

title: C++ Strings
comment:  This module introduces string representations: C-style strings, ASCII encoding, std::string, Arduino String, and etl::string, comparing their trade-offs for different contexts.
long_description: This module explores how strings are represented and manipulated in C++, from low-level C-style character arrays to high-level string classes. Covers ASCII encoding, memory management, and practical choices for different environments (desktop, embedded, Arduino).
estimated_time_in_minutes: 40


@learning_objectives  
- Understand how C-style strings are represented as null-terminated character arrays.
- Learn ASCII character encoding and how characters map to numeric values.
- Use C-style strings with functions like strlen() and string manipulation.
- Understand std::string and its advantages over C-style strings.
- Convert between std::string and C-style strings using .c_str().
- Compare std::string, Arduino String, and etl::string for different use cases.
- Choose the appropriate string type for your problem context.

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

@overview

Text and character data are fundamental to many programs. 
Embedded applications are generally less reliant on them, but even then data logging and error messages will be dependent on your ability to output text.

C++ provides several ways to represent and work with strings, each with different trade-offs in terms of safety, convenience, and resource usage. Understanding these options helps you choose the right tool for your specific problem.


# ASCII and Character Encoding

Before discussing strings, we need to understand how characters are stored. 
Computers store characters as numeric values, which value corresponds to which character depends on the specific encoding that you are using and there are a great many options.

We are going to assume that you are using **ASCII (American Standard Code for Information Exchange)** encoding because it is the standard encoding for most programming environments, it works well for English and it provides for easy migration onto Unicode if we need that in the future. 

Normal letters are in the 65-122 range.
Numbers in the 48-57 range.
With punctuation scattered in the available gaps.

What you might also notice are these control characters in the 0-31 range.
Most of these will not be relevant for us when writing text to be printed (although 9 and 10 definitely will being Tab and Newline respectively).
The rest are terminal control characters—commands that tell a terminal device (printer, screen, etc.) how to format output. 

![ASCII table](https://thumb.wikimedia.org/wikipedia/commons/thumb/1/1b/ASCII-Table-wide.svg/960px-ASCII-Table-wide.svg.png "ASCII-Table.svg: ZZT32 derivative work: YUFENG HUANG, Public domain, via Wikimedia Commons")

<div class="history">
@boxheader(History)

The reason for the apparently odd placement of upper and lower case characters ensures that each letter is exactly 32 (`0b100000`) away from it's alternative version. 
Which means that you can change between upper and lower case by just toggling bit 5. 

This is the sort of incredibly obsessive optimizations that gets programmers excited.
</div>

-------------------------------------

```cpp ASCII example
char letter = 'A';
char digit = '7';
int value = 97;

std::cout << "Letter A as number: " << static_cast<int>(letter) << std::endl;
std::cout << "Character 7 as number: " << static_cast<int>(digit) << std::endl;
std::cout << "Number 97 as character: " << static_cast<char>(value) << std::endl;

```
@addcppmain()

The key insight you need to get here is that characters are just numbers, but the character '7' is not the same as the *value* 7.
The character '7' has a value of 55, the value 7 is the non-printing (invisible) character [BELL].


# Type of strings

Due to it's long life and desire to maintain backwards compatibility and the number of different platforms with different capabilities that it can be used to program.
C++ has accumulated a range of different string types.

The best choice for any given situation will depend on multiple factors.
Embedded programming has traditionally used C-style strings, because they were normally the only option.
For general C++ programming you are advised against C-style strings and to use `std::string`.
For our Renesas based Arduino boards the situation is less clear but we have various options.


## C-Style Strings

C-style strings are arrays of characters terminated by a **[NULL] character** (value 0). 
The null terminator marks the end of the string, allowing functions to know when to stop reading.
The [NULL] character can be writing in C/C++ as the number `0` or the character `'\0'`.
It is not the same as the character (i.e. letter ) `'0'`.


```cpp Null char demo
char greeting[] = "Hello";  // null terminator automatically added
    
std::cout << "String: " << greeting << std::endl;
std::cout << "Length: " << strlen(greeting) << std::endl;
std::cout << "Array size: " << sizeof(greeting) << " bytes" << std::endl;
```
@addcppmain1(cstring)

<div class="important">
@boxheader(Important)

In C/C++ a 5-letter word needs *6* characters to be stored in the array. 5 visible letters + 1 null terminator.

If you don't have the null terminator at the end then many C/C++ functions won't stop at the end of the 5 letters, they will keep going.

This can, and does, cause something called buffer overflow, a distressingly common security vulnerability that attackers exploit to crash programs or inject malicious code.
</div>

<div class="pass-task">
@boxheader(Question)

**What is the size of this C-style string array? Select all that apply**

```cpp
char message[] = "Hi";
```
[[ ]] 1 byte
[[ ]] 1 character
[[ ]] 2 bytes
[[X]] 2 characters
[[X]] 3 bytes
[[ ]] 3 characters
***
"Hi" contains 2 characters. The null terminator `'\0'` requires 1 more byte, for a total of 3 bytes.
***
</div>

-----------------------------

If we are declaring a C-style string with a value, then the array will be created with the appropriate size for that value.
If you are declaring a C-style string to be filled later, for example if we are going to be storing user input, then we need to provide a size for the array.

```cpp
// Declaring with initialization (size inferred)
char greeting[] = "Hello";  // Size is 6 (5 letters + null terminator)
    
// Declaring with fixed size (to be filled later)
char buffer[50];  // Can hold up to 49 characters + null terminator
std::cin.getline(buffer, 50);  // Read up to 49 characters safely
    
std::cout << "Greeting length: " << strlen(greeting) << std::endl;
std::cout << "You entered: " << buffer << std::endl;
```
@addcppmain1(cstring)

We cannot change the size of our array after we have declared to allow for more characters.
This means that we need to declare our array to be big enough to store the longest string we might encounter.
If we declare an array of 1000 characters in case, but then only use 5, we are wasting significant memory that we may not have spare on an embedded device.

<div class="learn-more">
@boxheader(Learn more)

Ok we *can* resize the array but not until we have done the memory materials and even then there are problems.

[preview-lia](../memory/memory.md)
</div>


## `std::string`

`std::string` is part of the C++ Standard Library and provides a modern, safe way to work with strings. 
It manages memory automatically and offers convenient operations.
This means that you can keep adding characters to it and it will grow to accommodate them.

Whilst C-style strings are just C-style arrays of `char` variables, `std::string` is effectively a `std::vector` of `char` variables. Or close enough to be a useful analogy.

```cpp std::string example
std::string greeting = "Hello";
    
std::cout << "String: " << greeting << std::endl;
std::cout << "Length: " << greeting.length() << std::endl;
    
// Easy concatenation
greeting += ", World!";
std::cout << "After concatenation: " << greeting << std::endl;
    
// Easy substring
std::string sub = greeting.substr(0, 5);
std::cout << "Substring: " << sub << std::endl;
```
@addcppmain(string)

### Converting std::string to C-Style String

Often you need to pass a `std::string` to a function that expects a C-style string. Use the `.c_str()` method:

```cpp
std::string text = "Hello, C!";

// Now you can use it with C functions
std::cout << "Using strlen: " << strlen( text.c_str() ) << std::endl;
std::cout << "Using C printf: ";
printf( "%s\n", text.c_str() );  // printf expects C-style string
```
@addcppmain2(string,cstring)


## Arduino `String`

The Arduino environment provides a `String` class (note the capital S) that offers many conveniences of `std::string` while being optimized for embedded systems with limited RAM.

```cpp Arduino String example
#include <Arduino.h>

void setup()
{
  Serial.begin( 9600 );

  // Arduino example (would run on Arduino board)
  String greeting = "Hello, Arduino!";
  greeting += " How are you?";

  Serial.println(greeting);
  Serial.println(greeting.length());

  // Substring
  String sub = greeting.substring(0, 5);
  Serial.println(sub);  // Prints "Hello"
}

void loop() {}
```
@AVR8js.sketch(simple-demo)


## `etl::string`

For embedded systems needing safety and efficiency without the full Standard Library, [`etl::string`](https://www.etlcpp.com/docs/strings/#string) (Embedded Template Library) is a good choice. 
It provides a fixed-size, stack-allocated string with no dynamic memory.
For real time systems, `etl::string` offers the safety and convenience of `std::string`, with the deterministic behaviour of C-strings.

```cpp
#include "etl/string.h"

// Fixed size of 20 characters maximum
etl::string<20> greeting = "Hello";
greeting += ", ETL!";
```

<div class="learn-more">
@boxheader(Learn more)

Deterministic behaviour is highly desirable in safety critical and real time applications.
Although `std::string` has the benefits of being able to change size to accommodate longer text, the way this is achieved means that code using `std::string` can take unpredictable amounts of time to run depending on whether or not a string had to resize.

Predictability and consistence is *much* more important than speed in these safety and real time systems.
</div>


## Choosing a String Type

The best string type for your specific use case will depend on multiple factors. 
You will also be constrained by your platform. You could not, for example, use `std::string` on an AVR Arduino.

| Feature | C-Style | `std::string` | Arduino `String` | `etl::string` |
|:---|:---|:---|:---|:---|
| **Memory Overhead** | ✅ Minimal | Moderate | Moderate | ✅ Minimal |
| **Resizeable** | ❌ No[^1] | ✅ Automatic | ✅ Automatic | ✅ No |
| **Buffer Overflow Risk** | ❌ High | ✅ Safe | ✅ Safe | ✅ Safe |
| **Built-in Operations** | ❌ None[^2] | ✅ Rich API (concat, substr, find, replace) | ✅ Similar to std::string | ✅ Similar to std::string |
| **Max Size Tracking** | ❌ Manual | ✅ Automatic | ✅ Automatic | ✅ Automatic |
| **Standard Library** | ✅ Available | ✅ C++ Standard | ❌ Arduino-only | ❌ External library |
| **Real-Time Safe** | ✅ Deterministic | ❌ Unpredictable allocation | ❌ Unpredictable allocation | ✅ Deterministic |
| **Embedded Systems** | ✅ Works | ⚠️ Limited | ✅ Designed for it | ✅ Designed for it |
| **Performance** | ✅ Fastest | ⚠️ Depends | Moderate | ✅ Very fast |

[^1] Not until we cover memory.
[^2] But there are standard [C-string handling functions](https://en.cppreference.com/cpp/header/cstring).


<div style="display: none">
# String Processing Patterns

@sectiontoc(1)

## Finding a character

```cpp
#include <iostream>
#include <string>

int main() {
    std::string text = "Hello, World!";
    
    // Find first occurrence
    size_t pos = text.find(',');
    if (pos != std::string::npos) {
        std::cout << "Comma found at position " << pos << std::endl;
    } else {
        std::cout << "Comma not found\n";
    }
    
    return 0;
}
```
@addcppmain()

# Tasks

## Replacing text

```cpp
#include <iostream>
#include <string>

int main() {
    std::string text = "I like cats";
    
    // Replace first occurrence
    size_t pos = text.find("cats");
    if (pos != std::string::npos) {
        text.replace(pos, 4, "dogs");  // Replace 4 chars starting at pos with "dogs"
    }
    
    std::cout << text << std::endl;  // "I like dogs"
    
    return 0;
}
```
@addcppmain()

</div>

# Questions

<div class="good-task">
@boxheader(Question)

**What does this code print?**

```cpp
std::string text = "ABC";
std::cout << text.length() << std::endl;
std::cout << strlen(text.c_str()) << std::endl;
```

[[ ]] 3 and 4
[[X]] 3 and 3
[[ ]] 4 and 4
***
`.length()` returns the string length (3), and `strlen(text.c_str())` also returns 3. The null terminator is NOT counted in either case.
***
</div>

<div class="good-task">
@boxheader(Question)

**Which string type would be best for a real-time flight control system?**

[( )] `std::string`
[( )] Arduino `String`
[(X)] `etl::string`
[(X)] C-style strings
***
Real-time systems need **deterministic timing**. 
Dynamic memory allocation (`std::string` and `Arduino String`) can cause unpredictable delays when the heap runs out of contiguous space. 
`etl::string` or C-style strings allocates on the stack at compile time, ensuring consistent timing[^1].

----------------------
[^1] Yes C-style strings can be dynamically allocated on the heap but we haven't covered that yet and regardless, it would be under your explicit control. 
***
</div>

# Tasks

<div class="good-task">
@boxheader(On your machine)

Write a program that:

1. Reads a word from the user into a `std::string`
2. Prints the length
3. Reverses the string

<script input="submit" default="Hint">
"LIASCRIPT: Read the [documentation](https://en.cppreference.com/cpp/algorithm), in particular the features available in the `algorithm` library. Or manually reverse it with a loop."
</script>

<script input="submit" default="Hint">
"LIASCRIPT: The `reverse()` function maybe? Read the [documentation](https://en.cppreference.com/cpp/algorithm/reverse)."
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
#include <algorithm>
#include <iostream>
#include <string>

int main()
{
  std::cout << "Enter something: ";

  std::string input;
  std::cin >> input;

  // reverse using the algorithms library
  std::reverse( input.begin(), input.end() );
  std::cout << input << std::endl;

  /* reverse using a for loop
    step through the first half of the string and
    swap each element with its counterpart */
  for( int i=0; i<input.length()/2; ++i )
  {
    std::swap( input[i], input[input.length()-i-1] );
  }

  // this has been reversed twice now so it's back to the original version
  std::cout << input << std::endl;

  return 0;
}
```
</div>
</div>


# Recap

@recap
