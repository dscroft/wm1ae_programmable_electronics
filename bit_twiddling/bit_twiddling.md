<!--
module_id: isr
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Interrupt Service Routines
comment:  This module introduces the the concepts of 
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

import: https://raw.githubusercontent.com/LiaScript/CodeRunner/master/README.md
import: https://raw.githubusercontent.com/liaTemplates/AVR8js/main/README.md
script: https://unpkg.com/@wokwi/elements@0.22.1/dist/wokwi-elements.bundle.min.js

import: ../assets/macros.md

@bit
<script input="checkbox" value="true" output="@0">Number(@input)</script>
@end

@nit
<script input="checkbox" value="false" output="@0">Number(@input)</script>
@end

@bita
<script output="a@0@1">
Number(@input(`@0`) && @input(`@1`))
</script>
@end

@bito
<script output="o@0@1">
Number(@input(`@0`) || @input(`@1`))
</script>
@end

@bitx
<script output="x@0@1">
Number(@input(`@0`) ^ @input(`@1`))
</script>
@end

@bitn
<script output="n@0">
Number(!@input(`@0`))
</script>
@end

@biti
<script>
let val = Number(@input(`@0`))*8 + Number(@input(`@1`))*4 + Number(@input(`@2`))*2 + Number(@input(`@3`))*1;
val;
</script>
@end

@bitb
<script>
"" + @input(`@0`) + @input(`@1`) + @input(`@2`) + @input(`@3`)
</script>
@end


-->


## Bitwise Operations

Bitwise operations have obvious parallels with logical operations, i.e. `&&`, `||` and `!`.

- However, bitwise operations work on the individual bits of a variable rather than the variable value as a whole.

<!-- data-type="none" data-sortable="false" -->
| Variables | Integer value | Binary representation |
|-|----:|:----:|:----:|
| `a`      | @biti(a3,a2,a1,a0) | @bit(a3) @bit(a2) @nit(a1) @nit(a0) | 
| `b`      | @biti(b3,b2,b1,b0) | @bit(b3) @bit(b2) @bit(b1) @bit(b0) |
| **Operation** |
| `a & b`  | @biti(aa3b3,aa2b2,aa1b1,aa0b0) | @bita(a3,b3) @bita(a2,b2) @bita(a1,b1) @bita(a0,b0) |
| `a | b`  | @biti(oa3b3,oa2b2,oa1b1,oa0b0) | @bito(a3,b3) @bito(a2,b2) @bito(a1,b1) @bito(a0,b0) |
| `a ^ b`  | @biti(xa3b3,xa2b2,xa1b1,xa0b0) | @bitx(a3,b3) @bitx(a2,b2) @bitx(a1,b1) @bitx(a0,b0) |
| `~a`     | @biti(na3,na2,na1,na0) | @bitn(a3) @bitn(a2) @bitn(a1) @bitn(a0) |


## a



# Bit fields

Bit fields are a C/C++ language feature that enables programmers to access memory in non-byte-aligned sections or subsections smaller than a byte. 
While rarely used in general programming, bit fields are useful in embedded systems programming for accessing hardware registers that often have specific bits or groups of bits that control different functions.


```cpp +statusregister.h
struct StatusRegister 
{
    uint8_t enabled : 1;    // bit 0: enable flag
    uint8_t ready : 1;      // bit 1: ready status
    uint8_t error : 2;      // bit 2: error flag
    uint8_t mode : 4;       // bits 4-7: operation mode
};

StatusRegister status;
status.enabled = 1; // Set the enable flag
status.ready = 0;   // Clear the ready status
status.error = 0;   // Clear the error flag
status.mode = 15;   // Set the operation mode to 15 (binary 1111)

// Output as binary
std::cout << "0b" << std::bitset<8>(*(reinterpret_cast<uint8_t*>(&status))) << std::endl;
```
```cpp main.cpp
#include <bitset>
#include <cstdint>
#include <iostream>

int main() 
{
    #include "statusregister.h"
    
    return 0;
}
```
@LIA.eval(`["statusregister.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)

@hidecode("main.cpp")
@headlesscode("statusregister.h")


The colon in the struct definiton separates the field name from its width in bits, not bytes. 
This makes it important to understand what values can fit in fields of different lengths. 
For example, the `enabled` and `ready` fields are each 1 bit wide, so they can only store boolean values (0 or 1). 
The `error` field is 2 bits wide, allowing it to represent values from 0 to 3 (00, 01, 10, 11 in binary).
The `mode` field is 4 bits wide, allowing values from 0 to 15 (a single hexadecimal digit).

Once defined, we can create an instance of the `StatusRegister` struct and manipulate its fields as though it was a regular struct, but under the hood, it is still just a single byte of memory where each field corresponds to specific bits.

In this example, we define a `StatusRegister` struct that represents an 8-bit hardware register. Each member of the struct corresponds to specific bits in the register, allowing us to easily access and manipulate individual bits without needing to perform manual bitwise operations.

The total size of the `StatusRegister` struct is 1 byte (8 bits), so the same amount of memory is used as a single `uint8_t`, but we can access the individual bits in a more intuitive way.

The alternative to bit fields would be to use bitwise operations to manipulate the bits directly, which can be more error-prone and less readable, e.g.:

```cpp
uint8_t status = 0; // Initialize the status register
status |= (1 << 0); // Set the enable flag 
status &= ~(1 << 1); // Clear the ready status
status &= ~(3 << 2); // Clear the error flag (2 bits)
status |= (15 << 4); // Set the operation mode to 15 (binary 1111)
```

Care needs to be taken when using bit fields, as the exact layout of the bits in memory can be implementation-defined and may vary between different compilers or platforms.
For example certain platforms may choose to use LSB or MSB ordering for the bits, which can affect how the fields are accessed and manipulated.
Especially when working with external hardware via, e.g. I2C or SPI, it is important to ensure that the bit field definitions match the expected layout of the hardware registers to avoid unintended consequences.





# `const`

The `const` qualifier in C/C++ is used to indicate that a variable's value cannot be changed after it has been initialized. 
When applied to a variable, it tells the compiler that the value of that variable should not be modified, and any attempt to do so will result in a compile-time error.

In embedded systems programming, `const` is often used to define constants that represent fixed values, such as hardware register addresses, configuration parameters, or lookup tables.
Importantly when using `const` in embedded programming, the compiler can optimize the code by storing these constants in read-only memory (ROM) instead of RAM, which can save valuable RAM space on resource-constrained microcontrollers.

The majority of microcontroller architectures have separate memory spaces for program code (ROM) and data (RAM); substantially more ROM than RAM.


# `const volatile`

At first glance, the `const volatile` qualifier may seem contradictory, as `const` indicates that a variable's value cannot be changed, while `volatile` suggests that the value can change unexpectedly.
However, in embedded systems programming, `const volatile` is used to indicate that a variable's value is constant from the perspective of the program, but it can be modified by external factors such as hardware or interrupts.

For example, consider a hardware register that represents the status of a sensor.
The sensor reading cannot be modified by the program itself, so it is declared as `const`.
But the value can change due to the sensor's operation, so it is also declared as `volatile`.





# Evil hacks

```cpp +statusregister.h
struct StatusRegister 
{
    uint8_t enabled : 1;    // bit 0: enable flag
    uint8_t ready : 1;      // bit 1: ready status
    uint8_t error : 2;      // bit 2: error flag
    uint8_t mode : 4;       // bits 4-7: operation mode
};

StatusRegister status;
status.enabled = 1; // Set the enable flag
status.ready = 0;   // Clear the ready status
status.error = 0;   // Clear the error flag
status.mode = 15;   // Set the operation mode to 15 (binary 1111)

// Output as binary
std::cout << "0b" << std::bitset<8>(*(reinterpret_cast<uint8_t*>(&status))) << std::endl;
```
```cpp main.cpp
#include <bitset>
#include <cstdint>
#include <iostream>

int main() 
{
    #include "statusregister.h"
    
    return 0;
}
```
@LIA.eval(`["statusregister.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)

@hidecode("main.cpp")
@headlesscode("statusregister.h")
