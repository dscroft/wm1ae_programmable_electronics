<!--
module_id: cpp_foundations
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: C++ Containers
comment:  This module introduces C-style arrays, `std::array`, range-based iteration, and standard and embedded-friendly container options.
long_description: This module introduces the fundamentals of C++ programming, including variables, data types, and control structures.
estimated_time_in_minutes: 20


@learning_objectives  
- Explain how C-style arrays and `std::array` store and access elements by index.
- Iterate through arrays and containers using range-based `for` loops.
- Choose `std::set`, `std::queue`, `std::deque`, and `std::map` for common data needs.
- Compare STL and ETL container trade-offs for embedded systems.

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

# Containers

@overview

Programs often need to work with collections of values, such as a set of
sensor readings or a queue of tasks. A **container** is a type that stores a
collection and provides operations for accessing and managing its elements.
Containers let us work with the collection through those operations instead of
writing its storage structure ourselves.

The C++ Standard Library (often called the STL in this material) provides
container abstractions such as `std::array`, `std::set`, and `std::map`. Each
offers operations suited to a different way of organising data. This
abstraction makes common data structures easier to use, but does not make them
interchangeable: their capacity, ordering, memory use, and available
operations still matter.


## C-style arrays

Before we get to the STL containers we need to discuss C-style arrays.
These are still supported in C++ and still common, especially in embedded development.

A C-style array is a built-in collection that stores a fixed number of values
of the same type. Its number of elements is fixed when declared, and indexing
starts at zero:

An **index** is the position used to select an element; the **value** is the
data stored at that position. For `readings`, index `0` selects the first
value, `12`, while index `2` selects the third value, `11`. The index is not
the value itself.



```cpp
int readings[5] = {12, 14, 11, 18, 15};

for( int index=0; index<5; ++index ) 
{
  std::cout << "Index: " << index << ", value: " << readings[index] << std::endl;
}
```
@addcppmain()

```ascii
               Value is 12    Value is 18
                    |              |
                  +-V--+----+----+-V--+----+
int readings[5] = | 12 | 14 | 11 | 18 | 15 |
                  +-^--+----+----+----+--^-+
                    |                    |
               Index is 0           Index is 4

```

<div class="warning">
@boxheader(Warning)
Only use indexes from `0` to one less than the array's length. 
Accessing an index outside that range causes undefined behaviour and this will be explored in more detail in the memory materials.

C-style arrays do not provide a convenient record of their length.
For simple static arrays you can calculate it using the overall size of the array divided by the size of each element in the array.
I.e. `sizeof(readings) / sizeof(int)`.

[preview-lia](../memory/memory.md)
</div>


<div class="pass-task">
@boxheader(Question)

**What does `readings[2]` refer to?**

[[ ]] The second element, `14`.
[[X]] The third element, `11`.
[[ ]] The element after the end of the array.
***
Array indexes start at zero, so index `2` refers to the third element.
***
</div>


<div class="pass-task">
@boxheader(Try it)

Change the readings in the example, then change the loop to print their total
instead of printing each reading.

<script input="submit" default="Answer">
`LIASCRIPT:
```cpp
int readings[5] = {12, 14, 11, 18, 15};
int total = 0;

for( int index=0; index<5; ++index ) 
{
  total += readings[index];
}
std::cout << "Total: " << total << std::endl;
```
`
</script>
</div>


## `std::array`

In C++, `std::array` is a standard-library container for a fixed number of
elements. It keeps the size as part of its type and provides useful container
operations, including `.size()`. 

```cpp
#include <array> // std::array needs to be included, C-style arrays do not
#include <iostream>

int main()
{
  std::array<int, 5> readings{12, 14, 11, 18, 15};

  for( std::size_t index=0; index<readings.size(); ++index ) 
  {
    std::cout << "Index: " << index << ", value: " << readings[index] << std::endl;
  }

  return 0;
}
```
@LIA.cpp()

The size `5` is part of the type `std::array<int, 5>`, so it cannot change
during the array's lifetime. Unlike a C-style array, a `std::array` can be
copied or assigned as a whole and can be used with standard-library algorithms.
Indexing with `[]` still requires a valid index.

You may have noticed that we are using std::size_t as our variable type for `index` in our `for` loop.
This is because this is the variable type that is returned by `.size()`. 
Most of the time, we can just use `int` instead, but `std::size_t` is an alias an unsigned integer variable.
The exactly nature changes depending on the platform, i.e. 32 or 64 bits depending on platform. 
This helps us avoid issues if we have very, very large arrays.


<div class="good-task">
@boxheader(Question)

**Which statement about `std::array` is correct?**

[[ ]] It grows automatically whenever a new element is added.
[[X]] Its size is fixed, and `.size()` reports the number of elements.
[[ ]] It can only store values of different types.
***
`std::array` has a fixed size, known at compile time. Use `std::vector` when
you need a dynamically sized sequence.
***
</div>


## Range-based `for` loops

C++11 introduced range-based `for` loops to visit each element in an array or
container without writing an index. This works naturally with `std::array`.

```cpp
#include <array>
#include <iostream>

int main()
{
  const std::array<int, 5> readings{12, 14, 11, 18, 15};

  for( const int& reading : readings )
  {
    std::cout << reading << std::endl;
  }

  return 0;
}
```
@LIA.cpp()

Use `const int&` when you only need to read each element; it avoids copying the element and prevents accidental changes. 
Use `int&` when you want to modify elements. 
Use `int` when you deliberately want a separate copy. 
A range-based loop is convenient when you do not need an element's index; use an indexed loop when you need positions or want to process only part of a
container.

Range-based loops also work with C-style arrays, `std::vector`, and most other
standard containers.

<div class="learn-more">
@boxheader(Learn more)

This `&` syntax is to make our variables 'references', rather than traditional variables.

We will cover references during the memory materials later in the module.

[preview-lia](../memory/memory.md)
</div>

<div class="good-task">
@boxheader(In the browser)

Change the example code so that the loop doubles each value and then prints the updated values.

- Make sure that the values stored in the array are being doubled.

<script input="submit" default="Hint">
"LIASCRIPT: Remember the meaning of `const`"
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">
```cpp
for( int& reading : readings )
{
  reading *= 2;
  std::cout << reading << std::endl;
}
```
</div>
</div>


## Other standard containers

The standard library provides different containers for different ways of
organising data. Choose a container based on how values are stored and how the
program needs to access them.

| Container | What it is useful for |
|---|---|
| `std::set<T>` | Unique values kept in sorted order |
| `std::vector<T>` | Like a `std::array` but can be resized |
| `std::queue<T>` | First-in, first-out processing |
| `std::deque<T>` | A sequence that can be efficiently extended or shortened at either end |
| `std::map<K, V>` | Values looked up by unique keys, kept in key order |

<div class="learn-more">
@boxheader(Learn more)

It is completely unfeasible for us to cover all of the available STL containers in the time available.
To learn about the complete set of containers and the full capabilities of each, read the [documentation](https://cppreference.com/cpp/container).
</div>


### `std::vector`

A `std::vector` stores a sequence of values whose size can change. Unlike
`std::array`, it can grow when new elements are added, while still providing
indexed access.

```cpp
#include <iostream>
#include <vector>

int main()
{
  std::vector<double> readings{12.2, 14.4, 11.1};
  readings.emplace_back(18.8);

  for( double reading : readings ) 
  {
    std::cout << reading << ' ';
  }
  std::cout << std::endl;

  return 0;
}
```
@LIA.cpp()

This prints `12 14 11 18`: `.emplace_back()` adds the new value at the end of the vector.

<div class="pass-task">
@boxheader(In the browser)

Add another reading to the vector. 
Confirm that it is printed at the end.
</div>



### `std::set`

A `std::set` stores unique values in sorted order. 
Inserting a value that is already present does not create a duplicate.

```cpp
#include <iostream>
#include <set>

int main()
{
  std::set<int> sensor_ids{4, 2, 4, 1};
  sensor_ids.insert(3);

  for( int id : sensor_ids ) 
  {
    std::cout << id << ' ';
  }
  std::cout << std::endl;;

  return 0;
}
```

This prints `1 2 3 4`: the set sorts the values and stores `4` only once.

<div class="pass-task">
@boxheader(In the browser)

Add another ID that is already in the set. 
Confirm that it is still printed only once.
</div>


### `std::queue`

A `std::queue` processes values in first-in, first-out (FIFO) order: the first
value added is the first one removed. It is a container adaptor, providing
queue operations such as `push`, `front`, and `pop` rather than direct access to
every element.

```cpp
#include <iostream>
#include <queue>

int main()
{
  std::queue<int> jobs;
  jobs.push(10);
  jobs.push(20);
  jobs.push(30);

  while( !jobs.empty() ) 
  {
    std::cout << jobs.front() << std::endl;
    jobs.pop();
  }

  return 0;
}
```

`pop()` removes the front value but does not return it, so read it with
`front()` first. A queue is useful when work should be handled in arrival
order.

<div class="important">
@boxheader(Important)

Unlike `std::array` and `std::vector`, `std::queue` does not provide indexed
access or iterators. You can access the first and last elements using `front()`
and `back()`, but cannot get to the elements in between.
</div>

<div class="good-task">
@boxheader(Question)

Which value is printed first by the example?
[[X]] `10`
[[ ]] `20`
[[ ]] `30`
[[ ]] The queue prints the newest value first.
***
A queue is FIFO: the first value pushed is the first value at the front.
***
</div>


### `std::deque`

A `std::deque` (double-ended queue) is a sequence that supports adding and
removing values at both its front and its back. It also supports indexed
access. Unlike a fixed-size C-style array or `std::array`, a standard
`std::deque` can grow dynamically.

```cpp
#include <deque>
#include <iostream>

int main()
{
  std::deque<int> recent{12, 13, 14};
  recent.pop_front();
  recent.push_back(15);

  for( int value : recent ) 
  {
    std::cout << value << ' ';
  }
  std::cout << std::endl;

  return 0;
}
```

The example removes the oldest value and adds a new one at the back, leaving
`13 14 15`.

<div class="pass-task">
@boxheader(In the browser)

Change the example to add a value at the front instead. 
Predict the output before running it.
</div>


### `std::map`

A `std::map` stores key-value pairs. 
Each key is unique, and the map keeps its elements sorted by key. 
Use a map when a value needs to be found using an associated key, such as a sensor ID and its name.

```cpp
#include <iostream>
#include <map>
#include <string>

int main()
{
  std::map<int, std::string> sensorNames
  {
    {2, "temperature"},
    {1, "light"}
  };

  /* using auto here because it's easier than writing
     std::pair<int, std::string> for the type */
  for( auto entry : sensorNames ) 
  {
    std::cout << entry.first << ": " << entry.second << std::endl;
  }

  /* or we could use structured binding to get named variables
       rather than .first and .second */
  for( auto [key, value] : sensor_names ) 
  {
    std::cout << key << ": " << value << std::endl;
  }

  return 0;
}
```

In each entry, `.first` is the key and `.second` is its associated value. This
example prints the entry with key `1` before the entry with key `2`.

<div class="pass-task">
@boxheader(In the browser)

Add a third sensor ID and name. 
What order are the entries printed in if you insert the new ID between the existing two?
</div>


## Choosing a container

<div class="good-task">
@boxheader(Question)

**Which container best fits the requirement to keep one copy of each unique ID
and visit IDs in sorted order?**

[[ ]] `std::queue`
[[X]] `std::set`
[[ ]] `std::map`
[[ ]] `std::array`
***
`std::set` stores unique values in sorted order.
***
</div>

<div class="good-task">
@boxheader(Question)

**Which container is designed to process tasks in the same order they arrive?**

[[X]] `std::queue`
[[ ]] `std::deque`
[[ ]] `std::set`
[[ ]] `std::array`
***
`std::queue` processes the oldest item first.
***
</div>

<div class="good-task">
@boxheader(Question)

**Which container is best for associating each student number with a name?**

[[ ]] `std::set`
[[ ]] `std::queue`
[[X]] `std::map`
[[ ]] `std::array`
***
`std::map` stores values under unique keys, making it suitable for key-value
lookups.
***
</div>

<div class="adv-task">
@boxheader(Question)

Without running this code, work out the final contents of every container:

```cpp
std::set<int> ids{4, 2, 4};
std::deque<int> readings{10, 20, 30};
std::queue<int> pending;
std::map<int, int> totals{{2, 1}, {1, 3}};

pending.push(readings.front());
readings.pop_front();
readings.push_back(static_cast<int>(ids.size()));
pending.push(readings.front());
totals[2] += pending.front();
pending.pop();
totals[3] = readings.back();
```

Give the values in `ids` and `readings` in iteration order, the values that
would be removed from `pending` in order, and all key-value pairs in `totals`
in key order. Explain why the number of IDs differs from the number initially
listed, and what happens when `totals[3]` is evaluated.

<script input="submit" default="Hint">
"LIASCRIPT: Trace each statement in order. A set keeps unique sorted values, a deque supports changes at both ends, and a queue removes values from the front."
</script>

<script input="submit" default="Answer">
`LIASCRIPT: 
- \`ids\` contains \`2, 4\` because the repeated \`4\` is stored once. 
- \`readings\` contains \`20, 30, 2\`. 
- \`pending\` contains \`20\`, so that is the only value removed from it. 
- \`totals\` contains \`1: 3, 2: 11, 3: 2\` in key order. 
- \`ids.size()\` is 2, so 2 is appended to \`readings\`. 
- \`totals[2]\` adds the queue's front value, 10, to the existing value 1. 
- \`totals[3]\` creates a new key-value entry because key 3 was not already present, and assigns it the last reading, 2.`
</script>
</div>


## Tasks

<div class="good-task">
@boxheader(On your machine)

Write a program that asks the user to input non-negative integers.

- Read in values until the user enters a negative.
- Then print out all values in reverse order.

<script input="submit" default="Hint">
"LIASCRIPT: Think carefully about the requirements of the task, what would be the best container to use?"
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
#include <deque>
#include <iostream>

int main()
{
  std::deque<int> values;
  int input {0};
  
  std::cout << "Enter non-negative integers (negative to stop):" << std::endl;
  while( std::cin >> input && input >= 0 )
  {
    values.push_back(input);
  }
  
  std::cout << "Values in reverse order:" << std::endl;
  while( !values.empty() )
  {
    std::cout << values.back() << std::endl;
    values.pop_back();
  }
  
  return 0;
}
```
@LIA.cpp()
</div>
</div>


# STL vs ETL

All the containers that we have shown you so far have been part of the C++ Standard Template Library (STL).
Functionality that is part of the STL can generally be identified as having `std::` before it, i.e. `std::cout`.

The standard library provides ready-made container types, such as `std::array`,
`std::vector`, and `std::map`, so programs do not need to implement common storage structures themselves. 
The C++ standard specifies their interfaces and behaviour, which helps the same container code work across conforming implementations. 
It also specifies computational complexity guarantees for many operations.

An important reason for using STL containers is that they handle the memory management requirements.
Memory management in C/C++ is a particularly problematic area of the languages and so off-loading those aspects to 
established and well tested code is generally a smart move.

-------------------------------

However, the use of STL containers in embedded development is problematic.
Firstly, the way that STL containers manage memory is not designed for a highly resource constrained embedded environment.
You simply cannot use STL containers on AVR Arduino boards for example as there is not enough flash memory.
Even on Renesas MCUs, whilst STL containers *can* be used, they often rely on dynamic allocation and consume scarce RAM, so their use should be considered carefully.

This brings us to the [*Embedded* Template Library (ETL)](https://www.etlcpp.com/docs/).
The ETL reimplements and imitates many aspects of the STL and keep the same benefits, but does so in a manner that is a better fit for the specific constraints of MCU platforms.

For example, `etl::vector` is functionally almost exactly the same as `stl::vector`, except that it requires you specify a maximum size when declaring.
This means that an `etl::vector` cannot grow excessively large on the very limited memory of an MCU.

## PlatformIO

Adding the ETL to your PlatformIO projects is trivial. 
All that is required is to add the following to your `platformio.io` file.

```txt
[env]
lib_deps =
    git+https://github.com/ETLCPP/etl-arduino.git
```

<div class="learn-more">
@boxheader(Learn more)

PlatformIO project configuration and libraries will be covered in greater depth in the Build Processes materials.

We are adding directly from the git repository as the version in the PlatformIO library registry appears to have issues.

[preview-lia](../build/build.md)
</div>


## Example

Converting code from STL containers to ETL equivalents is generally straightforward.
This is one of the benefits of the STL, there is a standardised interface and set of functionality for their containers.

The ETL may has some differences, but the high degree of similarity makes it simple to adapt code between general purpose programs and MCUs.

<section class="flex-container">
<div class="flex-child">
STL vector
==========

```cpp
#include <Arduino.h>
#include <vector>

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  // declare the store
  static std::vector<unsigned long> timestamps;

  // check if full
  if( sequence.size() < 20 )
    sequence.emplace_back( millis() );

  // print contents
  for( unsigned long i : sequence )
  {
    Serial.print( i );
    Serial.print( " " );
  }
  Serial.println();

  delay(500);
}
```
</div>
<div class="flex-child">
ETL vector
==========

```cpp
#include <Arduino.h>
#include <etl/vector>

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  /* declare the store,
    make it static so the contents persist between loops */
  static etl::vector<unsigned long, 20> timestamps;

  // check if not full
  if( !sequence.full() )
    sequence.emplace_back( millis() );

  // print contents
  for( unsigned long i : sequence )
  {
    Serial.print( i );
    Serial.print( " " );
  }
  Serial.println();

  delay(500);
}
```
</div>
</section>

<div class="good-task">
@boxheader(Question?)

**What are the differences in the code?**

<script input="submit" default="Answers">
`LIASCRIPT: 

- \`#include<etl/vector>\` instead of the STL \`vector\`.
- Change declaration from \`std::vector\` to \`etl::vector\`.
- \`etl::vector\` requires an element type *and* a maximum capacity (20).
- \`std::vector\` does not have a maximum size so cannot be \`.full()\`.
  - Checks for current \`.size() < 20\` instead.

Besides that the functionality is identical, which is the point.
`
</script>
</div>

## Tasks

<div class="pass-task">
@boxheader(On the hardware)

Setup a PlatformIO project environment with the ETL library.
Build, upload and monitor the ETL example above and confirm that it is running correctly.
</div>


<div class="good-task">
@boxheader(On the hardware)

Modify the ETL example code so that the program stores and prints the most recent 20 recorded timestamps. 
Not the first 20 timestamps as it does currently. You will want to look at the [documentation](https://www.etlcpp.com/docs/containers/) for alternative containers.

<script input="submit" default="Hint">
"Queues, specifically double ended queues (dequeues)"
</script>

<script input="submit" default="Hint">
"LIASCRIPT: Use an `etl::dequeue` instead of an `etl::vector`"
</script>

<script input="submit" default="Hint">
"LIASCRIPT: Read the [documentation](https://www.etlcpp.com/docs/containers/queues--stacks/deque/). Try emplacing to the back and popping from the front."
</script>

<script id="button" input="submit" default="Answer">
document.getElementById("answer").style.display = "block";
"Answer"
</script>

<div id="answer" style="display: none">

```cpp
#include <Arduino.h>
#include <etl/deque.h>

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  // declaring dequeue instead of vector
  static etl::deque<unsigned long, 20> timestamps;
  
  // if full, remove first item
  if( timestamps.full() )
    timestamps.pop_front();

  // thanks to pop, there will be space
  timestamps.emplace_back( millis() );

  /* this is why we use deque instead of queue,
      so we can iterate over it */
  for( unsigned long i : timestamps )
  {
    Serial.print( i );
    Serial.print( " " );
  }
  Serial.println();

  delay(500);
}
```
</div>
</div>

# Recap 

@recap
