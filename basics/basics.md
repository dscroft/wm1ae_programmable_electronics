<!--
module_id: isr
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Interrupt Service Routines
comment:  This module introduces the the concepts of interrupt service routines, and how to implement them in Arduino.
long_description: This module introduces the the concepts of interrupt service routines in Arduino, and how to implement them.
estimated_time_in_minutes: 20


@learning_objectives  
- Understand the concept of interrupt service routines and their importance in embedded systems.
- Learn how to implement basic interrupt service routines in Arduino.
- Gain hands-on experience with using interrupts in Arduino projects.

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

import: https://raw.githubusercontent.com/liaTemplates/AVR8js/main/README.md

import: ../assets/macros.md
-->

# Introduction

Arduino is an open-source electronics platform that allows for easy prototyping and development of embedded systems. It provides a simple programming environment and a wide range of libraries and tools that make it accessible to beginners and professionals alike.

There are a range of different Arduino boards available, each with its own set of features, capabilities and form factors. 
The Arduino ecosystem has also been expanded to a wide range of alternative boards from other manufacturers.
Some of which are simply clones of official Arduino boards, whilst others are commercially available microcontrollers specifically designed for real world products and now repurposed.

Some popular Arduino boards include the Arduino Uno, Arduino Mega, and Arduino Nano.


## Arduino IDE

Although the Arduino organisation does provide an official IDE (Integrated Development Environment) for programming Arduino boards.
This module will be operating on the assumption that you are using a more general purpose system, specifically Visual Studio Codio.
VSCode can be used to write and upload code to Arduino boards using the PlatformIO extension.

We will be assuming VSCode and PlatformIO for the following reasons:

- The Arduino IDE is quite basic and lacks many features that are commonly found in more advanced IDEs, such as code completion, programming agent support and unit testing support.
- The Arduino IDE is not well suited for larger projects, as it does not provide good support for organizing code into multiple files and libraries.
- The Arduino IDE is not well suited for collaborative development, as it does not provide good support for version control systems such as Git.






### Non-blocking code

Simple microcontrollers such as the AVR microcontrollers used in Arduino have a single CPU core, and so can only execute one instruction at a time. 
This is the case for most single-core systems, however more capable processors such as those used in general purpose computers can run operating systems that allow for multitasking, which gives the illusion of multiple instructions being executed at the same time.

- In reality, the operating system is rapidly switching between different tasks.

For a microcontroller without an operating system, this means that if the main loop is executing a long-running task, it will not be able to respond to events such as button presses or sensor readings until it has finished. This can lead to unresponsive behaviour in the system.

- Or inputs may be missed entirely if they occur while other activities are being performed.

### a

This is a simple example of blocking code, where the main loop is executing a long-running task (toggling an LED on and off every 3 seconds) and is unable to respond to button presses until it has finished.

- The red LED will toggle on and off every 3 seconds.
- The green LED will illuminate when the button is pressed.

**Run the simulation and try holding down the green button.**

- How long does it take for the green LED to respond to the button press?

<div id="blocking-demo">
  <wokwi-led color="red" pin="13" label="13"></wokwi-led>
  <wokwi-led color="green" pin="12" label="12"></wokwi-led>
  <wokwi-pushbutton color="green" pin="2" label="2"></wokwi-pushbutton>
  <span id="simulation-time"></span>
</div>

```cpp Simple blocking code example
const uint8_t redPin = 13;
const uint8_t greenPin = 12;
const uint8_t buttonPin = 2;

void setup() 
{
  Serial.begin(115200);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() 
{
  // turn the red LED on and off every second
  digitalWrite(redPin, HIGH);
  delay(3000);
  digitalWrite(redPin, LOW); 
  delay(3000);

  // check if the button is pressed and turn the green LED on if it is
  digitalWrite(greenPin, digitalRead(buttonPin));
}
```
@AVR8js.sketch(blocking-demo)



### Non blocking

An alternative to code we just saw is to write our code to be non-blocking. 
I.e. that the execution of one part of the code does not block the execution of other parts of the code.

- Non-blocking code is often more complex to write and understand but it allows for more responsive behaviour in the system.


<div id="nonblocking-demo">
  <wokwi-led color="red" pin="13" label="13"></wokwi-led>
  <wokwi-led color="green" pin="12" label="12"></wokwi-led>
  <wokwi-pushbutton color="green" pin="2" label="2"></wokwi-pushbutton>
  <span id="simulation-time"></span>
</div>

```cpp Simple non-blocking code example
const uint8_t redPin = 13;
const uint8_t greenPin = 12;
const uint8_t buttonPin = 2;

void setup() 
{
  Serial.begin(115200);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() 
{
  static unsigned long redToggleTime = 0;
  static const unsigned long redToggleInterval = 3000;

  const unsigned long currentTime = millis();

  if(redToggleTime <= currentTime)
  {
    // toggle the red LED
    digitalWrite(redPin, !digitalRead(redPin));

    // schedule the next toggle time
    redToggleTime += redToggleInterval;
  }

  // check if the button is pressed and turn the green LED on if it is
  digitalWrite(greenPin, digitalRead(buttonPin));
}
```
@AVR8js.sketch(nonblocking-demo)


Code explanation
===========

This code uses a technique called time-based scheduling to toggle the red LED on and off every 3 seconds without blocking the execution of the main loop.

- The `redToggleTime` variable keeps track of the next time the red LED should be toggled.
  - Notice that this variable is `static`, because we want it to retain its value across multiple iterations of the loop.
- The `redToggleInterval` variable defines the interval at which the red LED should be toggled (3 seconds in this case).
  - This value never changes, so it is defined as a `static const`.
- The `currentTime` variable is simply a meaningful name for the value returned by `millis()`.
  - I.e. the number of milliseconds that have elapsed since the program started. 
  - This value never changes within a single iteration of the loop, so it is defined as `const`.

Every action in the main loop is non-blocking, i.e. it can be executed quickly.

- So the loop will be running many times per second.
- Each time through, it checks:
  - Is time to toggle the red LED?
  - Is the button pressed?
- If either of those conditions are true, it quickly performs the necessary action and then continues on to the next iteration of the loop.








### Demo

Here we have a simple demo of an ISR being used to toggle an LED on and off in response to a button press.

- Note that the main loop function has no interaction with the button or the LED.
  - Everything is handled by the ISR regardless of what the main loop is doing.

-----------------------

<div id="analog-demo" style="position: relative; height: 340px;">
  <wokwi-arduino-uno style="position: absolute; top: 130px; left: 0px; transform: rotate(0deg);"></wokwi-arduino-uno>

  <wokwi-analog-joystick vert="A0" style="position: absolute; top: 0px; left: 300px;"></wokwi-analog-joystick>

  <wokwi-potentiometer pin="14" style="position: absolute; top: 0px; left: 300px;"></wokwi-potentiometer>
</div>

```cpp Simple ISR example
const uint8_t numPins = 6;
const uint8_t pins[] = {14, A1, A2, A3, A4, A5};


void setup() 
{
  Serial.begin(115200);

 // pinMode( 14, INPUT );
}

void loop() 
{
  
    Serial.print( digitalRead(14), DEC );
  
  Serial.println();
  delay(3000);
}
```
@AVR8js.sketch(analog-demo)


