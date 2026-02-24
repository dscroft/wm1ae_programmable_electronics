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


# Interrupt Service Routines

An Interrupt Service Routine (ISR) is a special function that is executed in response to an interrupt. 

- An interrupt is a signal that indicates that an event has occurred that requires immediate attention. 
- When an interrupt occurs, the normal flow of program execution is interrupted, and the ISR is executed to handle the event.
  
  - When the ISR routine finishes, execution resumes from the point where it left off.
  - 
ISRs are commonly used in embedded systems to handle events such as:

- Timer interrupts 
- External interrupts from sensors or buttons 
- Communication interrupts from peripherals such as UART or I2C

--------------------------

Example of an ISR affecting the main program flow:

- With an Arduino sketch, we have a `setup()` function that runs once at the beginning, and a `loop()` function that runs repeatedly.
- If we have an ISR that is triggered by an external event, it interupts the existing execution flow to handle the event and then returns to the original flow.

```ascii
       Time  ------------------------------------------>

void setup() █▋ 
              |
              v
void loop()   ▐███████▚███████▚█░░░██████▚█░░░████░░░██
                                | ^        | ^    | ^
                                v |        v |    v |
void ISR()                      ███        ███    ███
```


## Implemention on Arduino

In Arduino, you can define an ISR using the `attachInterrupt()` function.

The `attachInterrupt()` function takes three parameters: the interrupt number, the ISR function, and the mode of the interrupt (e.g., `RISING`, `FALLING`, `CHANGE`).
  
- The interrupt number relates to, but is not the same as the pin number.

  - Only certain pins on an Arduino board can be used for interrupts and which pins various by board.
  - Fortunately Arduino provides a helper function `digitalPinToInterrupt(pin)` to get the correct interrupt number for a given pin, so you can just specify the pin number and let the function handle the conversion to the correct interrupt number.

- The ISR function is simply a regular function that you declare.

  - The only requirement is that it must have a `void` return type and take no parameters.

- The mode of the interrupt specifies when the ISR should be triggered.

  - RISING: Trigger the ISR when the signal goes from LOW to HIGH.
  - FALLING: Trigger the ISR when the signal goes from HIGH to LOW.
  - CHANGE: Trigger the ISR when the signal changes in either direction.
  - The correct mode to use will depend on the specific application and the type of signal you are working with.
  
------

`detachInterrupt()` can be used to disable an interrupt when it is no longer needed.

----------

Full function documentation is available at the links below:

- [attachInterrupt](https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/).
- [digitalPinToInterrupt](https://docs.arduino.cc/language-reference/en/functions/external-interrupts/digitalPinToInterrupt/).
- [detachInterrupt](https://docs.arduino.cc/language-reference/en/functions/external-interrupts/detachInterrupt/).



### Demo

Here we have a simple demo of an ISR being used to toggle an LED on and off in response to a button press.

- Note that the main loop function has no interaction with the button or the LED.
  - Everything is handled by the ISR regardless of what the main loop is doing.

-----------------------

<div id="isr-demo" style="position: relative; height: 340px;">
  <wokwi-arduino-uno style="position: absolute; top: 130px; left: 0px; transform: rotate(0deg);"></wokwi-arduino-uno>

  <svg width="600" height="520" style="position: absolute; top: 0; left: 0;" fill="none" id="wires" stroke-width="3" stroke-linejoin="round">
    <path stroke="orange" d="M145,42L145,60L145,140"></path>
    <path stroke="black" d="M136,42L115,42"></path>
    <path stroke="orange" d="M236,100L236,140"></path>
    <path stroke="black" d="M236,84L236,3L115,3L115,140"></path>
  </svg>

  <wokwi-resistor style="position: absolute; top: 80px; left: 115px; transform: rotate(90deg);" value="220"></wokwi-resistor>
  <wokwi-pushbutton color="green" 
                    pin="2"
                    style="position: absolute; 
                           top: 70px; 
                           left: 170px;"></wokwi-pushbutton>
  <wokwi-led color="green" 
             pin="11" 
             style="position: absolute; 
                    top: 0px; 
                    left: 120px;"></wokwi-led>
</div>

```cpp Simple ISR example
const uint8_t ledPin = 11, buttonPin = 2;

void isr()
{
  digitalWrite(ledPin, !digitalRead(ledPin));
}

void setup() 
{
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin), isr, FALLING);
}

void loop() 
{
  static int count = 0;
  Serial.print("Loop ");
  Serial.println(count++);
  delay(3000);
}
```
@AVR8js.sketch(isr-demo)



## Good `isr()` practices

*Nothing on this page.*

### Should be fast

Because calling an ISR interrupts the normal flow of execution, it is important to keep ISRs as short and fast as possible. 

- This is especially important if you have multiple ISRs that can be triggered by different events, as they can interfere with each other if they take too long to execute.
- A general rule of thumb is that an ISR should take no more than a few microseconds to execute.
  - If you need to perform a longer task in response to an interrupt, it is often better to set a flag in the ISR and then check that flag in the main loop to perform the response.
- The longer the ISR takes to execute, the more it will disrupt the normal flow of the program.

```cpp ISR flag setting example
volatile bool flag = false;

void isr()
{
    flag = true; // Set a flag to indicate that the interrupt has occurred
}

void loop()
{
    if (flag) // Check the flag in the main loop
    {
        flag = false; // Reset the flag
        doTimeConsumingActivity();
    }
}
```

### Have informative name

An ISR does not need to be called `isr()`.

- But it is common practice to name it something that indicates its purpose, such as `buttonPressISR()` or `timerISR()`.



### Self-contained

You should be careful calling additional functions from within an ISR.

- For example, calling `delay()` from within an ISR is not recommended, as it can cause the ISR to take a long time to execute and can lead to unexpected behavior.
- Calling functions such as `millis()` can also be problematic, as they themselves rely on interrupts to function properly.
  
  - `millis()` for example will not update while you are within an ISR.
  


### Use the `volatile` keyword

It is important that we identify any global variables that are manipulated by and ISR with the `volatile` keyword.


The code that we write in C/C++ is not the instructions that are actually performed on the CPU.

- As with all compiled languages, the high-level source code that we write as programmers is transformed into low-level assembly before it can be executed.


Modern compilers are quite intelligent in identifying improvements that can to the series of actions that your code is requesting.

```c High-level C code
int count = 0;
void a() { count += 1; }
void b() { count += 2; }

int status = 5;

void loop()
{
    if( status == 5 )
        a();

    if( status == 5 )
        b();
}
```

```asm Low-level assembly code
loop():
    cmp    DWORD PTR status[rip], 5  ; if status is 5
    add    DWORD PTR count[rip], 3   ; add 3 to count
    ret                              ; return
status:
    .long  5
count:
    .zero  4

; Generated using x86-64 gcc 15.2 with -O3 and slightly adjusted for clarity.
```



If we look specifically at the `loop()` portion of the code we see the following instructions:


- `cmp    DWORD PTR status[rip], 5` This instruction compares the value of `status` with 5.

  - Basically, go get the value of status so that we can see what it is.

- `add    DWORD PTR count[rip], 3` This instruction adds 3 to the value of `count`. 

This is the compiler's optimisation of our code. 

- It has recognised that if status is 5 when it checks for `a()`, it will still be 5 when it checks for `b()`. 
- So there is not, in fact, any point in checking it again.
- If `a()` increases `count` by 1 and `b()` increases it by 2, then we can instead just add 3 to `count`.

  - Replacing two instructions with one is obviously more efficient so an obvious optimisation opportunity for the compiler to take.
  - 


#### Dangerous Assumptions

But, what if the value of `status` did change between the two checks?
Obviously there is no way for that to happen in this code, but if `status` was being manipulated by an ISR, then it could change at any point in the code because ISRs can break into the normal flow of execution at any point.
If that happened, then the compiler's optimisation would be incorrect. 

To prevent this from happening, we can declare `status` as a `volatile` variable. This tells the compiler that the value of `status` can change at any time, and so it should not make any assumptions about its value when optimizing the code.

------------------------------

Declaring `volatile int status = 5;`, the assembly we get from our compiler changes.

```asm
loop():
    mov    eax, DWORD PTR status[rip]  ; Get the value of status
    cmp    eax, 5                      ; Compare it with 5
    jne    .L5                         ; If it is not 5, jump to .L5
    add    DWORD PTR count[rip], 1     ; If here then status is 5, so add 1 as per a()
.L5:
    mov    eax, DWORD PTR status[rip]  ; Get the value of status again
    cmp    eax, 5                      ; Compare it with 5 again
    je     .L7                         ; If it is 5, jump to .L7
    ret                                ; If it is not 5, return
.L7:
    add    DWORD PTR count[rip], 2     ; If here then status is 5, so add 2 as per b()
    ret
status:
    .long  5
count:
    .zero  4   

; Generated using x86-64 gcc 15.2 with -O3 and slightly adjusted for clarity.
```

As we can see, the compiler has now generated code that checks the value of `status` twice, once for each function call.
The use of `volatile` is therefore important if a variable may be manipulated in a non-trivial manner.

Examples of this include:

- Variables that are manipulated by ISRs. 

  - Relevant for embedded systems, but also for any system that uses interrupts, such as operating systems.
  
- Variables that are shared between multiple threads in a multi-threaded program.

  - Not a concern for a simple Arduino board but more capable microcontrollers and general-purpose computers will often support multi-threading.




## demo

<div id="isr-demo" style="position: relative; height: 340px;">
<wokwi-chip-pulse></wokwi-chip-pulse>

  <wokwi-arduino-uno style="position: absolute; top: 130px; left: 0px; transform: rotate(0deg);"></wokwi-arduino-uno>

  <svg width="600" height="520" style="position: absolute; top: 0; left: 0;" fill="none" id="wires" stroke-width="3" stroke-linejoin="round">
    <path stroke="orange" d="M145,42L145,60L145,140"></path>
    <path stroke="black" d="M136,42L115,42"></path>
    <path stroke="orange" d="M236,100L236,140"></path>
    <path stroke="black" d="M236,84L236,3L115,3L115,140"></path>
  </svg>

  <wokwi-resistor style="position: absolute; top: 80px; left: 115px; transform: rotate(90deg);" value="220"></wokwi-resistor>
  <wokwi-pushbutton color="green" 
                    pin="2"
                    style="position: absolute; 
                           top: 70px; 
                           left: 170px;"></wokwi-pushbutton>
  <wokwi-led color="green" 
             pin="11" 
             style="position: absolute; 
                    top: 0px; 
                    left: 120px;"></wokwi-led>
</div>