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

# Containers

## C-style arrays

C-style arrays store a fixed number of values of the same type under one name.
They are useful when a program needs to keep and process several related
values, rather than creating a separate variable for each one. The number of
elements is fixed when the array is declared, and indexing starts at zero:

```cpp
#include <iostream>

int main()
{
    int readings[5] = {12, 14, 11, 18, 15};

    for (int index = 0; index < 5; ++index) {
        std::cout << readings[index] << '\n';
    }
}
```

Use an index from `0` to one less than the array length. Accessing an index
outside that range causes undefined behaviour. A C-style array does not provide
a member function such as `.size()`, so the length must be kept track of
separately when it is needed.

<div class="pass-task">
@boxheader(Try it)

Change the readings in the example, then change the loop to print their total
instead of printing each reading.
</div>

<div class="good-task">
@boxheader(Question)

What does `readings[2]` refer to?
[[ ]] The second element, `14`
[[X]] The third element, `11`
[[ ]] The element after the end of the array
***
Array indexes start at zero, so index `2` refers to the third element.
***
</div>

## `std::array`

In C++, `std::array` is a standard-library container for a fixed number of
elements. It keeps the size as part of its type and provides useful container
operations, including `.size()`. Like a C-style array, its elements are stored
with the array object rather than allocated dynamically.

```cpp
#include <array>
#include <cstddef>
#include <iostream>

int main()
{
    std::array<int, 5> readings{12, 14, 11, 18, 15};

    for (std::size_t index = 0; index < readings.size(); ++index) {
        std::cout << readings[index] << '\n';
    }
}
```

The size `5` is part of the type `std::array<int, 5>`, so it cannot change
during the array's lifetime. Unlike a C-style array, a `std::array` can be
copied or assigned as a whole and can be used with standard-library algorithms.
Indexing with `[]` still requires a valid index.

<div class="good-task">
@boxheader(Question)

Which statement about `std::array` is correct?
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
container without writing an index. This works naturally with `std::array`:

```cpp
#include <array>
#include <iostream>

int main()
{
    const std::array<int, 5> readings{12, 14, 11, 18, 15};

    for (const auto& reading : readings) {
        std::cout << reading << '\n';
    }
}
```

Use `const auto&` when you only need to read each element; it avoids copying
the element and prevents accidental changes. Use `auto&` when you want to
modify elements. Use `auto` when you deliberately want a separate copy. A
range-based loop is convenient when you do not need an element's index; use an
indexed loop when you need positions or want to process only part of a
container.

Range-based loops also work with C-style arrays, `std::vector`, and most other
standard containers.

<div class="pass-task">
@boxheader(Try it)

Change the range-based loop so it adds all the readings and prints their sum.
What would you need to change if the program also had to print each reading's
index?
</div>

## Other standard containers

The standard library provides different containers for different ways of
organising data. Choose a container based on how values are stored and how the
program needs to access them.

| Container | What it is useful for |
|---|---|
| `std::set<T>` | Unique values kept in sorted order |
| `std::queue<T>` | First-in, first-out processing |
| `std::deque<T>` | A sequence that can be efficiently extended or shortened at either end |
| `std::map<K, V>` | Values looked up by unique keys, kept in key order |

<div class="learn-more">
@boxheader(Learn more)

It is completely unfeasible for us to cover all of the available STL containers in the time available.
To learn about the complete set read the [documentation](https://cppreference.com/cpp/container).
</div>


### `std::set`

A `std::set` stores unique values in sorted order. Inserting a value that is
already present does not create a duplicate.

```cpp
#include <iostream>
#include <set>

int main()
{
    std::set<int> sensor_ids{4, 2, 4, 1};
    sensor_ids.insert(3);

    for (int id : sensor_ids) {
        std::cout << id << ' ';
    }
    std::cout << '\n';
}
```

This prints `1 2 3 4`: the set sorts the values and stores `4` only once.

<div class="pass-task">
@boxheader(Try it)

Add another ID that is already in the set. Confirm that it is still printed
only once.
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

    while (!jobs.empty()) {
        std::cout << jobs.front() << '\n';
        jobs.pop();
    }
}
```

`pop()` removes the front value but does not return it, so read it with
`front()` first. A queue is useful when work should be handled in arrival
order.

<div class="good-task">
@boxheader(Question)

Which value is printed first by the example?
[[X]] `10`
[[ ]] `20`
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

    for (int value : recent) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}
```

The example removes the oldest value and adds a new one at the back, leaving
`13 14 15`.

<div class="pass-task">
@boxheader(Try it)

Change the example to add a value at the front instead. Predict the output
before running it.
</div>

### `std::map`

A `std::map` stores key-value pairs. Each key is unique, and the map keeps its
elements sorted by key. Use a map when a value needs to be found using an
associated key, such as a sensor ID and its name.

```cpp
#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<int, std::string> sensor_names{
        {2, "temperature"},
        {1, "light"}
    };

    for (const auto& entry : sensor_names) {
        std::cout << entry.first << ": " << entry.second << '\n';
    }
}
```

In each entry, `.first` is the key and `.second` is its associated value. This
example prints the entry with key `1` before the entry with key `2`.

<div class="pass-task">
@boxheader(Try it)

Add a third sensor ID and name. What order are the entries printed in if you
insert the new ID between the existing two?
</div>

### Choose a container

<div class="good-task">
@boxheader(Question)

Which container best fits the requirement to keep one copy of each unique ID
and visit IDs in sorted order?

[[ ]] `std::queue`
[[X]] `std::set`
[[ ]] `std::map`
***
`std::set` stores unique values in sorted order.
***
</div>

<div class="good-task">
@boxheader(Question)

Which container is designed to process tasks in the same order they arrive?

[[X]] `std::queue`
[[ ]] `std::deque`
[[ ]] `std::set`
***
`std::queue` processes the oldest item first.
***
</div>

<div class="good-task">
@boxheader(Question)

Which container is best for associating each student number with a name?

[[ ]] `std::set`
[[ ]] `std::queue`
[[X]] `std::map`
***
`std::map` stores values under unique keys, making it suitable for key-value
lookups.
***
</div>

# STL vs ETL

All the containers that we have shown you so far have been part of the C++ Standard Template Library (STL).
Functionality that is part of the STL can generally be identified as having `std::` before it, i.e. `std::cout`.

The standard library provides ready-made container types, such as `std::array`,
`std::vector`, and `std::map`, so programs do not need to implement common
storage structures themselves. 
The C++ standard specifies their interfaces and
behaviour, which helps the same container code work across conforming
implementations. 
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
  // declare the store
  static etl::vector<unsigned long, 20> timestamps;

  // check if full
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
document.activeElement.style.display = "none";
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
