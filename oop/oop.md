<!--
module_id: oop
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Object Oriented Programming
comment:  An introduction to C++ classes and objects, with a focus on encapsulation and abstraction for embedded development.
long_description: This module introduces object-oriented programming in C++ through self-contained embedded-system examples. It covers classes, objects, constructors, instance and static attributes, methods, access control, getters and setters, and destructors. Each example stands alone, so learners do not need to carry code forward from one activity to the next.
estimated_time_in_minutes: 75

@learning_objectives
- Explain the difference between classes, objects, and primitive data types
- Define C++ classes with constructors, attributes, and methods
- Distinguish instance attributes from static attributes
- Use public and private access to encapsulate object data
- Implement accessors, mutators, and destructors
- Apply classes to simple embedded-development examples
- Explain why this module focuses on encapsulation and abstraction rather than inheritance and polymorphism
@end

@style
.flex-container {
    display: flex;
    flex-wrap: wrap;
    align-items: stretch;
    gap: 20px;
}

.flex-child {
    flex: 1;
    margin-right: 20px;
}

@media (max-width: 600px) {
    .flex-child {
        flex: 100%;
        margin-right: 0;
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

# Object Oriented Programming

@overview

## C/C++

This module introduces classes and objects in C++. C does not have classes, although it does have `struct`s. C++ `struct`s can also have methods, but we will use the `class` keyword in these examples.

Defining a **class** means defining a new C++ data type. Types such as `std::string` and `std::vector` are classes. Types such as `int`, `float`, and `bool` are primitive types.

An **object** is a particular value of a type, or an instance of a class. For example, `std::string` is a class and `"Hello"` is an object of that class.

Classes bring data and the methods that work on it together. This approach is called **Object-Oriented Programming (OOP)**.

## Embedded development and the four pillars

OOP is often described using four pillars:

- **Encapsulation**
    - Keeping data and the functions that work on it together, while controlling access to that data.
- **Abstraction**
    - Exposing the essential operations of a component while hiding the details of how they work.
- **Inheritance** 
    - Defining a class in terms of another class, reusing or extending its behaviour.
- **Polymorphism**
    - Using a common interface for different types, so the appropriate behaviour is selected for each type.

![4 pillars of OOP](https://upload.wikimedia.org/wikipedia/commons/3/3e/4pillars.webp "4 pillars of OOP<br>Arabboy Ismoilov, [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0), via [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:4pillars.webp)")

In this module, we focus on encapsulation and abstraction. Embedded devices often have limited memory and processing power, and their timing and behaviour need to be predictable. Inheritance and polymorphism are useful in some systems, but can introduce extra layers of indirection and complexity. They are not needed for the examples here, so we will favour straightforward classes and composition.

The examples below use familiar embedded-system ideas, but each is a complete, independent program. You can compile and explore one without having to carry code forward from an earlier activity.

# Classes, objects, constructors, and instance attributes

A class defines the data and operations that its objects have. 
The following program defines an `LED` class. Each LED stores its own pin number and state, and its constructor sets the pin and initial state when an object is created.

<div id="simple-demo">
  <wokwi-led color="green" pin="13"></wokwi-led>
  <wokwi-led color="red" pin="11"></wokwi-led>
</div>

```cpp
#include <Arduino.h>

class LED 
{
public:
  /* constructor */
  LED(int pin) : _pin(pin)
  {
    pinMode(_pin, OUTPUT);
  }

  void turnOn() 
  {
    digitalWrite(_pin, HIGH);
  }

  void turnOff() 
  {
    digitalWrite(_pin, LOW);
  }

  void printState() const 
  {
    Serial.print("LED on pin ");
    Serial.print(_pin);
    Serial.print(" is ");
    Serial.println(digitalRead(_pin) ? "on" : "off");
  }

private:
  const int _pin;
};

// global variables
LED statusLED(13);
LED warningLED(11);

void setup() 
{
  statusLED.turnOn();
  statusLED.printState();
  warningLED.printState();
}

void loop() {}
```
@AVR8js.sketch(simple-demo)

`LED` is the class; `statusLED` and `warningLED` are objects of that class. 
The constructor is named after the class and runs automatically when an object is created. `pin` is an **instance attribute**: each object has its own values. 
The methods `turnOn`, `turnOff`, and `printState` are operations provided by the class.

The value to the left of the dot (`statusLED` or `warningLED`) is the object the method is called on. 
Values inside the parentheses are the method's parameters. 

The `printState()` method is marked `const` because it although it uses information from the object, it does not change anything.

<div class="pass-task">
@boxheader(In the browser)

Change the initial state or pin number of one LED. Check that it does not change the other object's state.
</div>


## Methods with parameters

An object method can take extra information as a parameter. 
Here we have added a `setState` method to our previous example that accepts a state parameter and sets the LED appropriately.

<div class="learn-more">
@boxheader(Professionalism)

Although we don't have to, we are also going to start putting our class definitions in their own file, rather than with our `main()` function.

Structuring our code like this is good practice will have multiple benefits:

- Code reuse.
- Testing.
- Version control.

Remember that you will have to `#include` your class file from any other file that needs to know about the `LED` class.
</div>

------------------------------------------------

<div id="param-demo">
  <wokwi-led color="green" pin="13"></wokwi-led>
  <wokwi-led color="red" pin="11"></wokwi-led>
</div>

```cpp led.h
#include <Arduino.h>

class LED 
{
public:
  /* constructor */
  LED(int pin) : _pin(pin)
  {
    pinMode(_pin, OUTPUT);
  }

  void turnOn() 
  {
    digitalWrite(_pin, HIGH);
  }

  void turnOff() 
  {
    digitalWrite(_pin, LOW);
  }

  void setState(bool state)
  {
    digitalWrite(_pin, state);
  }

  void printState() const 
  {
    Serial.print("LED on pin ");
    Serial.print(_pin);
    Serial.print(" is ");
    Serial.println(digitalRead(_pin) ? "on" : "off");
  }

private:
  const int _pin;
};
```
```cpp main.cpp
#include "led.h"

// global variables
LED statusLED(13);
LED warningLED(11);

void setup() 
{
    statusLED.setState(HIGH);
    statusLED.printState();
    warningLED.printState();
}

void loop() {}
```
@AVR8js.project(param-demo,led.h,main.cpp)


## Static attributes and methods

An instance attribute belongs to one object. A **static attribute** belongs to the class and is shared by all its objects. A static method is called on the class and can work with static attributes without needing a particular object.

This complete example uses a static counter to record how many sensor objects have been constructed.

```cpp sensor.h
class Sensor 
{
public:
  Sensor() 
  {
    _numberCreated += 1;
  }

  static int getNumberCreated() 
  {
    return _numberCreated;
  }

private:
    static int _numberCreated;
};

// initialise the static variable
int Sensor::numberCreated = 0;
```
```cpp main.cpp
#include <Arduino.h>
#include "sensor.h"

Sensor firstSensor; // declare single instance

// can declare multiple instances
Sensor secondSensor, thirdSensor, forthSensor;

void setup()
{
  Serial.begin(9600);

  const int howMany = Sensor::getNumberCreated();

  Serial.print( "Sensors created: " );
  Serial.println( howMany );
}

void loop() {}
```
@AVR8js.project(static,sensor.h,sketch.ino)

`numberCreated` is shared by the class. Its definition and initial value appear outside the class body; this is the usual pattern for a static data member in C++ versions commonly used for embedded toolchains. The method is called using the class name: `Sensor::getNumberCreated()`.

<div class="good-task">
@boxheader(In the browser)

Object methods have to be called against a specific instance of the class (e.g. `firstSensor`).
Static methods can be called against specific instances or the general class.

Change the code in the example so that `howMany` is initialised by calling `getNumberCreated()` against any specific instance of `Sensor`.

<script input="submit" default="Answer">
"LIASCRIPT:E.g. `const int howMany = thirdSensor.getNumberCreated();`"
</script>
</div>


## Encapsulation and controlled access

Making data `private` prevents code outside the class from changing it directly. 
A public getter can provide read access, and a setter can validate a proposed change before accepting it.

This `DutyCycle` example stores a percentage between 0 and 100. Its setter returns `false` for an invalid value and leaves the stored percentage unchanged.

```cpp duty_cycle.h
class DutyCycle 
{
public:
  DutyCycle() : percentage(0) {}

  int getPercentage() const 
  {
    return percentage;
  }

  bool setPercentage(int newPercentage) 
  {
    if (newPercentage < 0 || newPercentage > 100) 
      return false;

    percentage = newPercentage;
    return true;
  }

private:
  int percentage;
};
```
```cpp -main.cpp
#include <iostream>
#include "duty_cycle.h"

int main() 
{
  DutyCycle motorOutput;

  std::cout << "Enter a duty cycle percentage:";
  
  int value;
  std::cin >> value;

  motorOutput.setPercentage(value);
  
  std::cout << "Duty cycle = "
            << motorOutput.getPercentage() << "%" << std::endl;
}
```
@LIA.eval(`["duty_cycle.h", "main.cpp"]`, `g++ --std=c++17 main.cpp`, `./a.out`)

The `DutyCycle` class hides how the value is stored and ensures that invalid values cannot be assigned through its public interface. The user of the class only needs to know the available operations. This is **encapsulation** and **abstraction** in practice.

<div class="pass-task">
@boxheader(In the browser)

Try running the example and see how the method projects the private variable's value.
</div>

<div class="learn-more">
@boxheader(Security theater)

Making a class attribute private helps prevent accidental access through the class's public interface.
It helps to enforce correct access to resources and data.

However, `private` is a language-level access control, not a cybersecurity boundary. 
It is not intended to, and does not, protect data from code that can inspect or modify the program's memory.
</div>
</div>

<div class="adv-task">
@boxheader(In the browser)

Without making `percentage` public or similar. Try and set its value to something out of bounds.

<script input="submit" default="Hint">
"Try casting the object to a pointer"
</script>

<script input="submit" default="Answer" style="display: block">
`LIASCRIPT: 
\`\`\`cpp
DutyCycle motorOutput;
*reinterpret_cast<int*>(&motorOutput) = 999;
std::cout << motorOutput.getPercentage() << std::endl;
\`\`\`
`
</script>


## Constructors and destructors

A constructor runs when an object is created. A **destructor** runs when an object is destroyed, for example when a local object leaves scope. Destructors are commonly used to release resources an object owns. They should not be used to infer a long-lived object count in systems where object copying or lifetime is more complex.

This small program prints when its `Resource` object is constructed and destroyed. The braces create a scope, so the object's destructor runs before the final message.

Understanding destructors and object scope is vitally important for general C++ development as part of the rule of 3/5/0.
For us doing embedded development if we are declaring an object instance globally or as static variable, it means that we don't need to be concerned for the simple reason that the instance will never go out of scope and so will never call the destructor.

```cpp
#include <iostream>

class Resource {
public:
    Resource() {
        std::cout << "Resource acquired\n";
    }

    ~Resource() {
        std::cout << "Resource released\n";
    }
};

int main() {
    std::cout << "Before scope\n";
    {
        Resource resource;
        std::cout << "Inside scope\n";
    }
    std::cout << "After scope\n";
}
```

In embedded code, a destructor can be useful when an object manages a resource that needs explicit cleanup. Many simple objects do not need one.

# Your turn: battery monitor

Create a new, standalone program containing a `Battery` class. Do not reuse or extend code from another example. Give the class:

- A constructor that takes the battery's capacity and starts it fully charged.
- A private attribute holding the current charge.
- A getter that reports the current charge without changing it.
- A `charge` method that accepts a positive amount only when it will not exceed the capacity. It should return `true` if the operation succeeds and `false` otherwise.
- A `discharge` method that accepts a positive amount only when it will not make the charge negative. It should return `true` if the operation succeeds and `false` otherwise.
- A short `main` function that creates a battery, charges it, discharges it, and prints its charge after each operation.

After the class works, test ordinary operations and boundary cases such as charging a full battery, discharging an empty battery, and passing a zero or negative amount.

## Unit testing

A class is a useful unit to test: create an object, call its public methods, and compare the results with the expected behaviour. 
For the `Battery` class, test that it starts full, can be charged and discharged, and rejects operations that would take its charge outside the range from zero to its capacity.

Keep the class and its tests in separate files. This allows the application and the test program to use the same class without copying its code:

```mermaid @mermaid
treeView-beta
project/                            ## Project directory
├── include/
│   └── Battery.h                   ## Class declaration and implementation
├── test/
│   └── test_battery/
│       └── test_battery.cpp        ## Unit tests for Battery
├── src/
│   └── main.cpp                    ## The application that uses Battery
└── platformio.ini                  ## Project and test configuration
```

The class belongs in `include/Battery.h`. The application's `src/main.cpp` includes that header and uses the class. The test file also includes the same header, but tests the class directly rather than testing the whole application. 

<div class="good-task">
@boxheader(On the hardware)

Make sure that your Battery class has a suitable test suite to validate its functionality.
</div>

<!-- style="display: none" -->
```cpp
#include <Arduino.h>
#include <unity.h>
#include "Battery.h"

void test_battery_starts_at_capacity(void) {
    Battery battery(100);
    TEST_ASSERT_EQUAL_FLOAT(100, battery.getCharge());
}

void test_battery_can_be_discharged_and_charged(void) {
    Battery battery(100);

    TEST_ASSERT_TRUE(battery.discharge(30));
    TEST_ASSERT_EQUAL_FLOAT(70, battery.getCharge());

    TEST_ASSERT_TRUE(battery.charge(20));
    TEST_ASSERT_EQUAL_FLOAT(90, battery.getCharge());
}

void test_battery_rejects_out_of_range_operations(void) {
    Battery battery(100);

    TEST_ASSERT_FALSE(battery.charge(1));
    TEST_ASSERT_FALSE(battery.charge(0));
    TEST_ASSERT_FALSE(battery.charge(-1));
    TEST_ASSERT_EQUAL_FLOAT(100, battery.getCharge());

    TEST_ASSERT_TRUE(battery.discharge(100));
    TEST_ASSERT_FALSE(battery.discharge(1));
    TEST_ASSERT_FALSE(battery.discharge(0));
    TEST_ASSERT_FALSE(battery.discharge(-1));
    TEST_ASSERT_EQUAL_FLOAT(0, battery.getCharge());
}

void setup() {
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_battery_starts_at_capacity);
    RUN_TEST(test_battery_can_be_discharged_and_charged);
    RUN_TEST(test_battery_rejects_out_of_range_operations);
    UNITY_END();
}

void loop() {}
```

# Recap

@recap
