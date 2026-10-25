<!--
module_id: intro
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Introduction to C/C++ for Embedded Systems
comment:  This module provides an overview of C/C++ programming for embedded systems, the Arduino platform, and the complete module structure.
long_description: This module introduces the module curriculum for learning C/C++ for embedded systems development. It covers the Arduino ecosystem, the development environment, and provides an overview of all topics to be covered.
estimated_time_in_minutes: 30

@learning_objectives  
    - Understand why C/C++ is used for embedded systems
    - Learn about the Arduino platform and ecosystem
    - Understand the differences between embedded and general-purpose programming
    - Navigate the module curriculum and learning path
    - Set up the development environment

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
import: https://raw.githubusercontent.com/LiaTemplates/aframe/0.0.6/README.md

import: ../assets/macros.md
-->

# Introduction to C/C++ for Embedded Systems

```html @AFRAME.scene
<a-scene>
  <a-assets>
    <a-asset-item id="myModel" src="assets/media/arduino_r4.glb"></a-asset-item>
  </a-assets>
  
  <!-- Very bright overall illumination -->
  <a-light type="ambient" color="#FFFFFF" intensity="3"></a-light>

  <a-gltf-model
    src="#myModel"
    position="0 0 -0.7"
    rotation="65 0  0"
    scale="10 10 10"
    animation="property: rotation; to: 65 360 0; dur: 20000; loop: true; easing: linear">
  </a-gltf-model>

  <a-entity
    camera
    position="0 0 0"
    rotation="0 0 0"
    look-controls="enabled: false">
  </a-entity>
</a-scene>
```

## Why Learn C/C++ for Embedded Systems?

C and C++ are the dominant programming languages for embedded systems development. Understanding them will give you:

- **Control**: Direct access to hardware registers and memory
- **Efficiency**: Small code size and fast execution - essential for resource-constrained devices
- **Portability**: Open-source compilers available for every processor architecture
- **Desirable skills**: Required knowledge for electronics engineering and systems programming

The Arduino platform provides a beginner-friendly entry point into embedded systems development, but learning "real" C/C++ skills will allow you to work with professional tools and advanced hardware.

### Embedded vs General Development

This course emphasizes that embedded C/C++ differs from general-purpose programming:

| Aspect | General Programming | Embedded Systems |
|--------|-------------------|------------------|
| **Memory** | Abundant (GB) | Limited (KB-MB) |
| **CPU** | Fast, multi-core | Modest, often single-core |
| **Allocation** | Dynamic (malloc) | Static (compile-time) |
| **Errors** | Log and recover | Must not crash |
| **Tools** | Rich IDE with debugging | Specialized embedded tools |
| **Code size** | Less critical | Critical - must fit in flash |
| **Latency** | Predictability not required | Must be deterministic |


## The Arduino Ecosystem

Arduino is an open-source platform consisting of:

1. **Arduino Boards**: Microcontroller development boards with standard pinouts
   - Arduino Uno (ATmega328P) - Most popular, easy to learn
   - Arduino Mega (ATmega2560) - More I/O pins and memory
   - Arduino Zero (SAMD21) - ARM processor, more powerful
   - Arduino Due (SAM3X) - High-performance ARM applications

2. **Arduino IDE / PlatformIO**: Development environments for writing and uploading code

3. **Arduino Libraries**: Pre-written code for common tasks (Serial, PWM, I2C, etc.)

4. **Arduino Community**: Vast collection of tutorials, examples, and compatible hardware

## Course Structure and Learning Path

This course is organized into distinct modules, each covering a specific topic. The recommended learning order is:

### Foundation Modules (Understanding the Language)

1. **[Basics](/basics/)** - Arduino sketch structure, data types, simple I/O
2. **[Compilation](/compilation/)** - How code is compiled into machine code
3. **[C++ Foundations](/cpp_foundations/)** - Variables, data types, and fixed-width integers
4. **[Operators](/operators/)** - Arithmetic, logical, and bitwise operations
5. **[Control Flow](/control_flow/)** - Conditionals and loops
6. **[Functions](/functions/)** - Writing reusable, modular code
7. **[Arrays and Strings](/arrays_strings/)** - Collections and text handling
8. **[Pointers](/pointers/)** - Memory addressing and indirection
9. **[Advanced Types](/advanced_types/)** - Structs, unions, and enumerations
10. **[Memory Management](/memory/)** - Dynamic memory and best practices

### Embedded Systems Modules (Practical Applications)

11. **[Bit Twiddling](/bit_twiddling/)** - Bit manipulation for hardware control
12. **[Error Handling](/error_handling/)** - Robust error detection and recovery
13. **[Interrupt Service Routines](/isr/)** - Responding to hardware events
14. **[Finite State Machines](/fsm/)** - Organizing complex control logic
15. **[Communication](/communication/)** - Serial, I2C, and other protocols

## Development Environment Setup

While the Arduino IDE is simple, we recommend using **Visual Studio Code with PlatformIO** for several advantages:

- **Code completion** and intelligent editing
- **Multi-file projects** organized professionally
- **Debugging support** built in
- **Version control** integration (Git)
- **AI assistance** through GitHub Copilot
- **Professional tools** matching industry practice

### Why NOT just Arduino IDE?

The Arduino IDE lacks:
- Project organization for larger code bases
- Professional debugging tools
- Version control integration
- Professional-grade code editing

For university education, learning professional development practices is as important as learning the language itself.

## Important Concepts Throughout the Course

### 1. Resource Constraints

Always consider:
- **Flash memory**: Limited space for code (16 KB on Arduino Uno)
- **RAM**: Limited space for variables (2 KB on Arduino Uno!)
- **CPU speed**: Modest processor speeds require efficient code
- **Power consumption**: Battery-powered devices need low-power code

### 2. Real-Time Behavior

Embedded code often must:
- Respond to inputs within specific time limits
- Avoid blocking operations that prevent responsiveness
- Handle timing-critical tasks (like reading time-sensitive sensors)

### 3. Hardware Interaction

Unlike general programming, embedded code directly:
- Reads from hardware pins and sensor inputs
- Controls hardware pins and actuators
- Manages hardware registers for peripheral control
- Coordinates timing and synchronization

### 4. Defensive Programming

Embedded systems must be robust:
- Check all return code and sensor inputs
- Design systems that fail safely
- Handle errors without crashing
- Test edge cases thoroughly

### 5. No Dynamic Allocation (Usually)

Unlike general programming:
- Avoid `malloc()` and `new` (memory allocation at runtime)
- Use static arrays allocated at compile time
- Plan memory usage ahead of time
- Reason about memory layout and lifetime

## Differences Between C and C++

This course teaches **modern C++ (C++11 and later)** while maintaining compatibility with C. Key differences:

| Feature | C | C++ Arduino |
|---------|---|----------|
| **String handling** | C-style strings (char arrays) | `String` class |
| **Functions** | Procedural | Can use OOP but often procedural |
| **Safety** | Manual everything | Some built-in safety |
| **Code organization** | Less structured | Classes and namespaces |
| **Compilation** | gcc | g++ |

For embedded systems, we often use a **subset of C++11** that includes useful features (auto, nullptr, range-based for loops) while avoiding heavy features (exceptions, RTTI) that add overhead.

## Hello World on Arduino

Here's your first embedded C++ program:

```cpp
void setup() {
    Serial.begin(9600);  // Initialize serial at 9600 baud
}

void loop() {
    Serial.println("Hello, Embedded World!");
    delay(1000);  // Wait 1 second
}
```

But before you run it, understand what happens:

1. **Compilation**: Your code is compiled using AVR-GCC (for Arduino Uno) or ARM-GCC (for other boards)
2. **Linking**: Standard libraries are linked in
3. **Upload**: The resulting binary is uploaded to the Arduino via serial/USB
4. **Execution**: The Arduino's bootloader starts your code
5. **Output**: Serial monitor shows your messages

## Where This Fits in Your Education

Understanding C/C++ for embedded systems provides:

- **Foundation for electronics**: Essential knowledge for control systems, robotics, IoT
- **Low-level thinking**: Understanding memory, hardware, and performance
- **Professional skills**: Used in industry for real products
- **Gateway to other languages**: Most languages are influenced by C/C++
- **Systems understanding**: Learn how computers actually work

## What You'll Be Able to Do

By the end of this module series, you will be able to:

- Write safe, efficient C/C++ code for embedded systems
- Understand how code compiles and runs on a microcontroller
- Design applications using modular, testable code
- Handle hardware interactions and timing-critical operations
- Debug and optimize embedded software
- Understand the trade-offs between embedded and general programming

## Next Steps

1. **Set up your development environment** (VSCode + PlatformIO)
2. **Start with [Basics](/basics/)** to understand Arduino sketch structure
3. **Progress through foundation modules** in order
4. **Apply concepts** in the embedded systems modules
5. **Build projects** combining multiple concepts

Each module is self-contained but builds on previous knowledge. Don't skip ahead - each foundation module is essential for understanding later topics.

---

**Remember**: Embedded systems programming is about:
- Making code **small** and **fast**
- Making code **reliable** and **predictable**
- Understanding **hardware** and **resources**
- Writing **code that works** when it's the only code on the device

Welcome to embedded systems development!
