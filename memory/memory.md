<!--
module_id: memory
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Memory Management
comment:  This module introduces the concepts of memory management in C/C++, and how to implement them in Arduino.
long_description: This module introduces the concepts of memory management in C/C++, and how to implement them in Arduino.
estimated_time_in_minutes: 60


@learning_objectives  
- Understand the concept of memory management and its importance in embedded systems.
- Learn how to implement basic memory management techniques in Arduino.
- Gain hands-on experience with using memory management in Arduino projects.

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

A quick description of the computer memory. By memory we mean RAM, not disk space (i.e. hard drives). When programs are run they are loaded into memory, as programs run they use memory to store variables etc.


Memory consists of blocks. Each block of memory is the same size and has an address. 
This memory address describes each block's position in memory and acts as a unique index for each block. 
We can visualise memory as two columns, one column of addresses and one column of the values that are stored in each of those addresses.
Or like an excel spreadsheet, each cell has a unique id and can fit some information.

The number of bits used for an address limits how many distinct memory locations can be addressed. 
The actual amount of *usable* memory may be lower, depending on the hardware and how the address space is used but the reason that 
<script input="number" value="32" min="8" max="128" step="1" output="I">@input</script>
bit operating systems generally max out at 
<script>
const bytes = 2 ** @input(`I`);
const units = ["B", "KiB", "MiB", "GiB", "TiB"];
const scale = Math.min(
  Math.floor(Math.log(bytes) / Math.log(1024)),
  units.length - 1
);
(bytes / 1024 ** scale).toFixed(0) + " " + units[scale];
</script>
of RAM is because they can't address more than 
<script>let b = 2 ** @input(`I`); b + " bytes"</script>.

```ascii Simplified memory layout (addresses are illustrative)
Address       Memory block
+------------+  +----------+
| 0x0000     |->| 00000000 |
+------------+  +----------+
| 0x0001     |->| 00000000 |
+------------+  +----------+
| 0x1002     |->| 00000000 |

           *etc*

| 0xFFFFFFFD |->| 00000000 |
+------------+  +----------+
| 0xFFFFFFFE |->| 00000000 |
+------------+  +----------+
| 0xFFFFFFFF |->| 00000000 |
+------------+  +----------+
```


## Variables

Variables are pieces of information stored in a computer's memory. A variables name is really just a label for a specific chunk of memory. We don't usually care exactly where in memory a variable is, just that we we can use it.

When we create a variable your program picks an unused memory location, with enough space to store the variable. Different types of variables have different sizes and sizes differ depending on OS, compiler, 32 or 64 bit etc. Your program allocates the required memory and the name of our variable just acts as an alias for that memory location.

When our code is finished with a variable then the portion of memory that it was occupying is made available for the next set of variables.

```cpp
char myVariable = 'Q';
bool myBool = false;
char anotherVariable = '@';
```

```ascii Simplified memory layout (addresses are illustrative)
Address       Memory block
+----------+  +----------------------+
| 0x1000   |->| myVariable: 'Q'      |
+----------+  +----------------------+
| 0x1001   |->| myBool: false        |
+----------+  +----------------------+
| 0x1002   |->| anotherVariable: '@' |
+----------+  +----------------------+
```


## Arrays
How does this apply to arrays? From a programming standpoint arrays are groups of variables where each element in the array has a unique index. From a memory standpoint arrays are groups of variables where each element in the array has a unique address.

When an array is created the memory required is allocated as a single contiguous block. The size of the array in memory is simply the size of an individual element multiplied by the number of elements.

```cpp
std::array<char,6> myArray { "Hello" };
```

```ascii Simplified memory layout (addresses are illustrative)
Address       Memory block
+----------+  +------------------+------------------+
| 0x1000   |->| myArray[0]: 'H'  |                  |
+----------+  +------------------+                  |
| 0x1001   |->| myArray[1]: 'e'  |                  |
+----------+  +------------------+                  |
| 0x1002   |->| myArray[2]: 'l'  |                  |
+----------+  +------------------+ myArray: “Hello” |
| 0x1003   |->| myArray[3]: 'l'  |                  |
+----------+  +------------------+                  |
| 0x1004   |->| myArray[4]: 'o'  |                  |
+----------+  +------------------+                  |
| 0x1005   |->| myArray[5]: '\0' |                  |
+----------+  +------------------+------------------+
```

<div class="important">
@boxheader(The NULL character)

The `'\0'` character is the NULL character. 
Characters like `'A'` have an ASCII integer value of 65, the NULL has a value of 0.
It's not a visible character when printed but all C and C++ strings have this present to indicate that you have reached the end of a string.

If string is missing the NULL character, there is a very good chance that we you attempt to print the contents of additional and unintended chunks of memory. This can be a security issue.
</div>

### Missing features

The classis C-style array is missing a number of features that we might expect.

Size
====

Firstly, no length.
Unlike `std::array` with it's `.size()` method. C-style arrays do not have a direct way to get their size. Instead you have to get the size in bytes of the entire array and then divide that by the size of each element.

For a dynamically allocated C-style array, the array itself does not store its element count, so you need to keep track of the size when you allocate it. 

```cpp
float myArray[10];
std::cout << sizeof(myArray) / sizeof(float) << std::endl;
```
@addcppmain()

---------------------------

Bounds checking
===============

C-style arrays do not check whether an index is within the array's bounds. For an
array with 3 elements, valid indices are `0`, `1`, and `2`; accessing index `3`
or a negative index is out of bounds.

```cpp
int values[3] {10, 20, 30};
// Valid: values[0], values[1], and values[2]

// Invalid: values[3] but C/C++ doesn't stop or warn us.
std::cout << values[3] << std::endl;
```
@addcppmain()

An out-of-bounds access has undefined behavior in C++. It might appear to work,
produce an unexpected value, or crash, and the compiler is not required to
detect it. Check the index yourself before accessing the array, or use `std::array`.

`std::array` *still* won't check bounds if you use `[]` but it also provides a `.at()` method which does check.

```cpp
std::array<int,3> values { 10, 20, 30 };

// Invalid: values[3] but C/C++ doesn't stop or warn us.
std::cout << values[3] << std::endl;

// Invalid: values[3], C/C++ does stop us
std::cout << values.at(3) << std::endl;
```
@addcppmain1(`array`)


## Multibyte variables

Some variable types need more than one byte of memory. 
An `int`, for example, is commonly 4 bytes.

```cpp
int myNumber = 42;
sizeof(myNumber); // commonly 4
```

The bytes that make up a multibyte variable occupy consecutive memory locations. For example, on a system with 8-bit bytes and a 4-byte `int`, the value `42` is represented as `0x0000002A`. On a little-endian system, its bytes are stored in this order:

```ascii Simplified memory layout (addresses and int size are illustrative)
Address       Memory block
+----------+  +----------------+--------------+
| 0x1000   |->| myNumber: 0x2A |              |
+----------+  +----------------+              |
| 0x1001   |->| myNumber: 0x00 |              |
+----------+  +----------------+ myNumber: 42 |
| 0x1002   |->| myNumber: 0x00 |              |
+----------+  +----------------+              |
| 0x1003   |->| myNumber: 0x00 |              |
+----------+  +----------------+--------------+
```

The order in which bytes are stored is called endianness. A big-endian system stores the most significant byte first, so the byte order in this example would be reversed. The size of an `int` and the byte order are not the same on every system, so avoid assuming either in portable code.


## Pointers

Pointers are special kind of variable that stores the memory location of another variables. Every variable type has an associated pointer type. Pointers are declared in the same manner as normal variables but with a `*` after the type name.

<table>
  <tr>
    <td>Typename $\rightarrow$</td>
    <td><code>int * intPointer</code></td>
    <td>$\leftarrow$ Variable name</td>
  </tr>
  <tr>
    <td/>
    <td><code>int intVariable;</code></td>
    <td/>  
  </tr>
  <tr>
    <td/>
    <td><code>char * charPointer;</code></td>
    <td/>  
  </tr>
  <tr>
    <td/>
    <td><code>char charVariable;</code></td>
    <td/>  
  </tr>  
</table>


## Referencing

Of course if we want to store a memory address in a pointer then we are going to need to find out what the memory addresses of our variables are. 
This is called referencing, we take our variable and find the location in memory that it is referring to. 
Once we have the location we can store that address in a pointer.

We get the memory address of a variable using the `&` operator. Just put it before the variable name that you want the address of. When a pointer has a memory address of another variable it is said to be 'pointing' at that variable. You will need to make sure that you are using the correct types of pointers when referencing. For example, don't try and use a `char *` to store the memory address of an int, it won't work. You need to use a `int *` instead.

In the example below the pointer `char *myPointer` is pointing at `char myVariable`.

```
char myVariable = 'Q';
char *myPointer = &myVariable;
```

![](.guides/img/dd.png)

<h2 style="color:green">lab_pointers</h2>

1. Complete lab\_pointers.cpp.
    - Each of the test functions expects a pointer to a different type of variable, pass each function a pointer to the correct type.

1. Run the code.
    - How much space do the different types need?
    - How much space do the different pointers need?

{Check It!|assessment}(fill-in-the-blanks-2304593987)

{Check It!|assessment}(test-237146650)

|||
</div>


# Pointers

## Dereferencing

The opposite of referencing is dereferencing. One a pointer is pointing at a variable we can use the pointer to look at that variable indirectly.

In the example below, the pointer `myPointer` holds the address of the variable `myVarible`. The variable `myOther` has the same value as the variable `myVariable` which it got by dereferencing the pointer `myPointer`.

```
char myVariable = 'Q';
char *myPointer = &myVariable;
char myOther = *myPointer;
```

![](.guides/img/dd.png)

We can also set the value of a variable via a pointer.

```
char myVariable;
char *myPointer = &myVariable;
*myPointer = 'Q';
```

![](.guides/img/ee.png)


## Nulls

Pointers do not have to point anywhere, those that don't are called null pointers. Care needs to be taken with null pointers since any attempt to dereference them will cause your program to crash. 

Null pointers are similar to a Python `None`.

Pointers can be set to null in two ways using the old method:
```
int *myPointer = NULL;
```

Or using the new and preferred C++11 onwards method:
```
int *myPointer = nullptr;
```

Since we're only going to be using C++14 in this module you should never be using the old method. It is only mentioned here so that you can recognise it in the future.

<div class="learn-more">
@boxheader(Why?)

`nullptr` has a dedicated pointer type, so the compiler can tell the difference betwee a null pointer from the integer `0`. 

- The classic `NULL`, is a macro that may be defined as `0`, which can cause confusing bugs in C++. 
- Using `nullptr` in modern C++ code is clearer and you get better error messages.
</div>


# References

So far, we've seen how pointers can be used to access memory locations indirectly. Pointers are powerful, but they can also be a source of bugs. C++ provides references as a more restricted alternative.

A reference is an alias for an existing object. Declare one by placing `&` after the type, rather than using `*` as you do for a pointer.

The main differences are:
1. A reference must be bound to an object when it is created; it cannot be null.
2. A reference cannot be rebound to refer to a different object.
3. Accessing a reference accesses the object it refers to directly, so no explicit dereferencing is needed.

------------------------------------------

Declaring a reference without binding it to an object is a compile-time error. 
References do not support pointer arithmetic, and are often a good choice when an object must be accessed indirectly but should not be replaced with another object. 
However, a reference can still dangle if the object it refers to no longer exists, so references are not automatically safe in every situation.

```cpp
int myVariable = 42;
		
int &refA = myVariable;
int &refB = refA; 
		
int &refC; // will not work, HAS to have a value	
```
@addcppmain()


# Dynamic memory

One place where it is definitely not possible to use references instead of pointers is when dynamically allocating memory.
Dynamic memory is memory that you manually specify when to allocate and deallocate.

The use of dynamic memory in embedded systems is especially tricky, especially if we are working with safety critical systems.
Various code standards ban or limit the use of dynamic memory allocation. 
For example the NASA/JPL [standard](https://yurichev.com/mirrors/C/JPL_Coding_Standard_C.pdf) explicitly bans it after initialisation.


## Allocation

How do we request additional memory? We use the `new` command to request it. 

<div class="important">
@boxheader(Legacy)

When doing this with arrays in C++ we have unfortunately got to use the old C-style arrays. 
We can't use a C++ `std::array` and get differently sized arrays dynamically.

If writing real code we would use a `std::vector` instead but we can't do that here then you wouldn't learn about pointers.
</div>

`new` will return a memory address to the newly allocated memory so you need to use a pointer to store it. `new` can be used to dynamically allocate variable or arrays of any type.

```cpp
int *myVariable = new int;
char *myArray = new char[10];
```

Of course the real advantage for dynamically declared arrays is that you don't need to know the size of the array at compile time.

```cpp
int size;
cout << "How big an array do you want?" << endl;
cin >> size;
		
int staticArray[size];              // won't work
int *dynamicArray = new int[size];  // will work
	
// do stuff	
	
delete [] dynamicArray;				// deallocate memory
```

## Deallocation

As we saw in the previous section, if we have dynamically allocated some memory we have to manually deallocate that same memory once we're finished with it. 
You **MUST** remember to deallocate (free up) the memory. Failure to do so causes memory leaks. 
When you have a leak, memory gradually gets `lost' until the program ends.

Deallocating memory is done using the `delete` command. 
`delete` is used to deallocate individual variables and `delete []` is used to deallocate arrays.

```cpp
int *myVariable = new int;
int *myArray = new int[1000];
		
// do stuff		
		
delete myVariable;
delete [] myArray;
```

## Leaks

If we dynamically allocate some memory during our program but then forget to deallocate it, we have a memory leak. The memory we allocated hangs around even though nothing is using it (or even knows it exists).

In order to assist us in detecting preventing memory leaks there are a wide range of tools available (e.g. valgrind and gdb). As most of these are platform or `IDE` specific we will not bee discussing them directly, however you may want to investigate what options are available on/in your platform/IDE of choice.
 
We are going to use Valgrind. It's a pretty fully featured detector and mastering it is well outside the scope of this module but it can be used at a basic level easily enought.
<div class="good">

<h2 style="color:darkorange">Dynamic memory</h2>

1. Compile the lab\_dynamic code.
2. Run the code.
    - Does the program produce any errors?
	
3. Compile the lab\_dynamic code again, but THIS time check for memory leaks.
    - You will want to add extra debugging information to your code using the `-g` option.
    `g++ --std=c++14 -g lab_dynamic.cpp -o bin/lab_dynamic`
		- If you are using CMake then you can compile in debug mode using the command below and then calling your normal compile command.
		`cmake . -DCMAKE_BUILD_TYPE=Debug`
    
4. Run your code using a memory leak checker. 
    - The default Linux checker is Valgrind.
    `valgrind --leak-check=yes bin/lab_dynamic`

    - What's wrong?

5. Fix lab\_dynamic.			

{Check It!|assessment}(test-2096279435)


```cpp
int i=42;
int *j = new int;
```
```cpp -main.cpp
#include <iostream>
#include "leaker.h"
int main() { 
    #include "visible.h"
    return 0;
}
```
@LIA.eval(`["visible.h", "main.cpp", ["leaker.h", "assets/leaker.h"], ["leaker.c", "assets/leaker.c"]]`, `g++ --std=c++17 -g main.cpp leaker.c`, `./a.out`)
@hidecode("main.cpp")

<div class="good-task">
@boxheader(In the browser)

Fix the code above for that we are no longer leaking memory.

<script input="submit" default="Answer">
"LIASCRIPT: You need to add a `delete j;` line at the end."
</script>

</div>

	
## adaptive

<div class="good=task">
@boxheader(Wherever)

Write a program that:

- Asks the user for a size, read in that many numbers and then print those numbers in reverse order on a single line.
  - If you are working on the Arduino hardware you will need to use `Serial`.
- E.g. if you enter 1, 2 and 3 the output would be "3 2 1" or similar.

**What is the maximum number of values that your solution is capable of handling?**

**What are the pros and cons of your solution?**
</div>


## Smart pointers

As of C++11 there is a new features for C++, smart pointers. 
Smart pointers are a wrapper around the traditional pointers that we've already discussed.

We've talked previously about the issues that can occur if allocated memory is not deallocated. 
When using traditional pointers it is absolutely vital that any memory which is allocated by your code is also deallocated. Smart pointers handle this automatically.

### Shared pointers

There are several different types of smart pointer but the ones that we are going to discuss right now are shared pointers and unique pointers. Shared pointers work in the same way as normal pointers but with one addition, they have an internal counter which is used to keep track of the number of shared pointers pointing at that memory location.

This means that when a piece of allocated memory is no longer being pointed at by any pointer, it is automatically deleted.

When using a shared pointer the memory allocation syntax changes slightly, there are a couple of different ways to allocate memory to a shared pointer but the recommended method is to use `std::make_shared<>()`.

Once a shared pointer has been defined it can be used in the same way as a traditional pointer. See the examples below for a comparision.

Dumb pointers
=============
```cpp
#include <iostream>

int main()
{
  int *pointer = new int(42);  
  std::cout << *pointer << std::endl;

  *pointer = 123;               
  std::cout << *pointer << std::endl;

  delete pointer;
  return 0;
}
```
@LIA.cpp()

Shared pointers
==============

```cpp
#include <iostream>
#include <memory>

int main()
{
  std::shared_ptr<int> pointer = std::make_shared<int>(42);
  std::cout << *pointer << std::endl;

  *pointer = 123;
  std::cout << *pointer << std::endl;

  // delete happens automatically
  return 0;
}
```
@LIA.cpp()


### Unique pointers

Unique pointers work in much the same way as shared pointers with one extra restriction, only one pointer can be pointing at each chunk of memory.

```
// Old style pointers          New style smart pointers
                               #include <memory>
#include <iostream>            #include <iostream>
using namespace std;           using namespace std;

int main()                     int main()
{                              {

  int *pointer = new int(42);    unique_ptr<int> pointer = std::make_unique<int>(42);
  int *arrayPtr = new int[10];   unique_ptr<int[]> arrayPtr = std::make_unique<int[]>(10);

  cout << *pointer << endl;      cout << *pointer << endl;

  *pointer = 123;                 *pointer = 123;

  cout << *pointer << endl;      cout << *pointer << endl;

  delete pointer;                // delete happens automatically
  delete [] arrayPtr;            // delete happens automatically

  return 0;                      return 0;
}                              }

```

Going forwards C++ will be making more and more use of smart pointers. However, for the moment traditional pointers are a major part of the language and are likely to remain so for the foreseeable future so we have to teach you the old way as well.

It is also good to understand memory allocation and deallocation even when it is being handled for you. When writing your own code it may be helpful to use smart pointers, when dealing with older C++ code or working with 3rd party libraries you may have to work with traditional pointers.

<h2 style="color:darkorange">smart_pointers</h2>

1. Convert your lab\_adaptive code to use smart\_pointers instead of traditional pointers.
    - Save your new code as lab_smart.cpp.
    - Consider which type of smart pointer is best used in this case.
    
1. Test your program for memory leaks.

{Check It!|assessment}(test-167468937)


<h2 style="color:red">Advanced</h2>

1. Convert your lab\_adaptive code to use vectors instead of arrays.
    - Save your new code as lab_vector.cpp.
    
1. Test your program for memory leaks.


{Check It!|assessment}(test-360924754)











