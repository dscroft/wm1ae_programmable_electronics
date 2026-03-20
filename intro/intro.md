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
This module will be operating on the assumption that you are using a more general purpose system, specifically Visual Studio Code.
VSCode can be used to write and upload code to Arduino boards using the PlatformIO extension.

We will be assuming VSCode and PlatformIO for the following reasons:

- The Arduino IDE is quite basic and lacks many features that are commonly found in more advanced IDEs, such as code completion, programming agent support and unit testing support.
- The Arduino IDE is not well suited for larger projects, as it does not provide good support for organizing code into multiple files and libraries.
- The Arduino IDE is not well suited for collaborative development, as it does not provide good support for version control systems such as Git.



