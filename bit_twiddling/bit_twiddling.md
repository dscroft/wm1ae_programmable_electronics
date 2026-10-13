<!--
module_id: bit_twiddling
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Bit Twiddling
comment:  This module introduces the concepts of bitwise operations and bit fields in embedded systems programming.
estimated_time_in_minutes: 20

@learning_objectives  
- Understand the concept of bitwise operations and their importance in embedded systems.
- Learn how to implement basic bitwise operations in Arduino.
- Gain hands-on experience with using bit fields in Arduino projects.
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


# Bitwise Operations

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


## Bit masks

TODO

## C++ stl

It is worth mentioning that these operators are from C.
With modern C++, if cannot remember the bit operator syntax and you have access to them, there are STL functions to do the same.

See the [documentation](https://en.cppreference.com/cpp/header/functional) for `std::bit_and`, `std::bit_or`, `std::bit_xor` and `std::bit_not`;

```cpp
const uint8_t a = 5;
const uint8_t b = 9;

std::cout << std::bit_or{}(a, b) << std::endl;
std::cout << std::bit_and{}(a, b) << std::endl;
```
```cpp -main.cpp
#include <cstdint>
#include <iostream>
#include <functional>
int main() { 
  #include "visible.h"
}
```
@LIA.eval(`["visible.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)
@hidecode("main.cpp")


# Bit shifting

The left-shift operator `<<` and right-shift operator `>>` move the bits of an integer by a chosen number of positions. For example, shifting `00001101` left by one place gives `00011010`; shifting it right by one gives `00000110`. 
Bits that move beyond the end are discarded. Right shifts fill the newly opened positions with zeros.

When the result fits, shifting an unsigned value left by one place is equivalent to multiplying it by 2, while shifting right by one place is equivalent to unsigned integer division by 2. More generally, shifting by `n` places multiplies or divides by `2^n` (division discards any remainder). In embedded programs, shifts are especially useful for building bit masks, setting or checking individual flags, and packing or extracting fields in hardware registers.

```cpp
int var = 1;
for( int i=0; i<sizeof(var)*8; ++i ) // loop over all the bits in var
{
  const int result = var << i;
  std::cout << var << " << " << i << " = " << result << std::endl;
}
```
```cpp -main.cpp
#include <iostream>
int main() { 
  #include "visible.h"
}
```
@LIA.eval(`["visible.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)
@hidecode("main.cpp")

<div class="important">
@boxheader(Important)

Notice that `<<` is used for both the stream insertion operator *and* bit shifting.
This can cause problems if you are trying to bit shift and stream at the same time.

E.g. `std::cout << 1 << 8 << std::endl;`

If you run into this issue, put your bit shift code inside brackets.

I.e. `std::cout << ( 1 << 8 ) << std::endl;`
</div>



## Signed/Unsigned

It is worth highlighting that while left shifting behaves the same way for both signed and unsigned integers, the same cannot be said for right shifting. The key difference is that signed integers are stored using two's-complement representation on most systems. 

Two's complement
=================

With signed integers the naive way to represent positive and negative values is to have 1 bit that represents the sign directly. 
E.g. 0 is positive and 1 is negative. So 00000101 could be +5 and 10000101 could be -5.
This approach would have several issues, including that it allows for +0 and -0 and that +0 does not equal -0.

Much more common is to represent the values using two's complement.
In two's complement to convert a number to a negative you take the positive representation, flip all the bits, then add 1.

The top bit still represents the sign, the double 0 issue is avoided.

```cpp
const uint8_t var = 5;

std::cout << " " << static_cast<int>( var )                // print as an int
          << " = " << std::bitset<8>( var )  << std::endl; // display as binary
std::cout << static_cast<int>(-var ) 
          << " = " << std::bitset<8>( -var ) << std::endl;
```
```cpp -main.cpp
#include <cstdint>
#include <bitset>
#include <iostream>
int main() { 
  #include "visible.h"
}
```
@LIA.eval(`["visible.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)
@hidecode("main.cpp")

-------------------------

The consequence for us of signed values being represented as two's complement is that when you right shift a signed value, the processor often fills the new left-hand bits with copies of the sign bit (arithmetic right shift). This keeps negative numbers negative. For unsigned values, the empty bits are filled with zeros instead.

Because of this, bitwise shifts are often used with unsigned types when a mask or flag field is being manipulated, since the code is then clearer, more predictable and avoids surprises from signed sign extension.

```cpp
const int8_t signed_var =   -42; // typical two's-complement: 11010110
const uint8_t unsigned_var = 42; // typical binary:           00101010

std::cout << "signed_var        = " << static_cast<int>(signed_var)
          << " = " << std::bitset<8>(signed_var) << std::endl;
std::cout << "signed_var >> 1   = " << static_cast<int>(signed_var>>1) 
          << " = " << std::bitset<8>(signed_var >> 1) << std::endl;

std::cout << "unsigned_var      = " << static_cast<int>(unsigned_var)
          << " = " << std::bitset<8>(unsigned_var) << std::endl;
std::cout << "unsigned_var >> 1 = " << static_cast<int>(unsigned_var>>1) 
          << " = " << std::bitset<8>(unsigned_var >> 1) << std::endl;          
```
```cpp -main.cpp
#include <cstdint>
#include <bitset>
#include <iostream>
int main() { 
  #include "visible.h"
}
```
@LIA.eval(`["visible.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)
@hidecode("main.cpp")



# Uno R4 LED matrix example

Will come back to bitwise operations in a bit, first we are going to look at the LED matrix on your Arduino Uno R4 Wifi board.

This is a 12x8 matrix with individually addressable LEDs.

![](media/105f533b3e76905e506ea94bb0e41d16.webp "LED matrix")

The matrix can be programmed in a few different ways depending on your requirements. 
For the moment we are going to focus on setting the values of the individual LEDs manually, specifically the different ways in which we can represent the LED information in our source code.

## Library

Using your Arduino, quickly test that the matrix is working. 
The LED matrix is controlled using the [ArduinoLEDMatrix](https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix/#api) library.

```cpp
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() 
{
  Serial.begin(9600);
  matrix.begin();
}

void loop()
{
  matrix.loadFrame(LEDMATRIX_LIKE);
}
```

<div class="pass-task">
@boxheader(On the hardware)

Run the example on your Arduino.
</div>

### Byte frames

The simplest option is to declare an 8x12 array, with one element for each LED.
This approach makes the image easy to see directly in the source code.

Each `uint8_t` element occupies 8 bits, even though each LED has only two possible states (on or off). The array therefore uses 96 bytes (768 bits) to represent 96 on/off values; those values could theoretically be encoded in 96 bits.
 
Not really an issue for us and a single frame but imagine you wanted to have an animation, 84 bytes wasted per frame starts to add up.

```cpp Byte example
#include "Arduino_LED_Matrix.h"

uint8_t byte_frame[8][12] = {
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }
};

ArduinoLEDMatrix matrix;

void setup() 
{
  matrix.begin();
}

void loop()
{
  matrix.renderBitmap(frame, 8, 12);
}
``` 

<div class="pass-task">
@boxheader(On the hardware)

Adjust the frame to design your own pattern.
</div>

### Integer frames

A much more efficient way to represent the LED states is as individual bits.
Unfortunately there are no 96 bit long integer variables in C/C++ so we will do the next best thing, 3x32 bit integers.

```cpp Int example
#include "Arduino_LED_Matrix.h"

uint32_t uint_frame[3] = {
  2863311530,
  2863311530,
  2863311530
};

ArduinoLEDMatrix matrix;

void setup() 
{
  matrix.begin();
}

void loop()
{
  matrix.loadFrame(uint_frame);
}
``` 

Of course this approach does have the disadvantage of not being able to see the image within our code.


<div class="pass-task">
@boxheader(On the hardware)

Adjust the integer values and see how the pattern changes.

In particular try incrementing or decrementing of the the values by 1, you may find it helpful to do this automatically using a loop.
</div>

<div class="good-task">
@boxheader(On the hardware)

Try and adjust the integer values to get a checker board pattern instead of vertical lines.
</div>


### Hex frames

Of course we have multiple ways to represent specific integer values.
We are all familiar with the base10 (denary) representation.
But we could use base16 (hexadecimal, or just hex) or base8 (octal, or just oct).

In case you are not familiar with the systems.

```ascii
Base  2 | 0 | 1 | 10 | 11 | 100 | 101 | 110 | 111 | 1000 | 1001 | 1010 | 1011 | 1100 | 1101 | 1110 | 1111 | 10000 |
Base  8 | 0 | 1 |  2 |  3 |   4 |   5 |   6 |   7 |   10 |   11 |   12 |   13 |   14 |   15 |   16 |   17 |    20 | 
Base 10 | 0 | 1 |  2 |  3 |   4 |   5 |   6 |   7 |    8 |    9 |   10 |   11 |   12 |   13 |   14 |   15 |    16 |
Base 16 | 0 | 1 |  2 |  3 |   4 |   5 |   6 |   7 |    8 |    9 |    A |    B |    C |    D |    E |    A |    10 |
```

<section class="flex-container">
<div class="flex-child">
```cpp Hexadecimal example
uint32_t hex_frame[3] = {
  0xAAAAAAAA,
  0xAAAAAAAA,
  0xAAAAAAAA
};
```

Notice the leading 0x, this tells C/C++ that this is a hexadecimal value. 
</div>

<div class="flex-child">
```cpp Octal example
uint32_t oct_frame[3] = {
  025252525252,
  025252525252,
  025252525252
};
``` 

Notice the leading 0, this tells C/C++ that this is an octal value.
</div>
</section>

The benefit of working with hex in particular when working with C/C++ is that hexadecimal values neatly align to the underlying bytes.
1 hexadecimal characters exactly equals 4 bits so 2 characters equal 1 byte of data.

Octal has some uses as it neatly to 3 bits.

Denary does not align at all.

```ascii
        <---------- 1 byte -----------> <---------- 1 byte ----------->
       +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
Binary | 1 | 0 | 1 | 0 | 1 | 0 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 
       +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
Octal  | 1 |     2     |     5     |     3     |     7     |     7     |
       +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
Hex    |       5       |       5       |       F       |       F       |
       +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
Denary |                             22015                             |
       +---------------------------------------------------------------+
```

<div class="important">
@boxheader(Important)

The key point to understand is that the values and therefore 1s and 0s being stored in memory are the same.
We are only changing the representation of the value, not the actual value.
</div>


### Binary frames

This finally brings up to binary representations. If we are dealing with individual bits in C/C++ then why not just work with binary representations?
Yes, C and C++ do allow you to specific values in binary. Binary values need to be prefixed with `0b` otherwise they will be interpreted as either denary or octal.

```cpp
std::cout << 0b101010 << std::endl;
```
```cpp -main.cpp
#include <iostream>
int main() {
  #include "visible.h"
}
```
LIA.eval(`["visible.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)
hidecode("main.cpp")

<div class="pass-task">
@boxheader(In the browser)

Change the example to output <script run-once="true">Math.floor(Math.random()*101)+10</script>, making sure to specify the value as binary.
</div>

------------------------------------------

This ultimately means that we can specify our LED matrix frames directly as binary values. Memory efficiency *and* code clarity.
The only remaining issue is that a 12 LED wide matrix does not map cleanly onto 32bit integers. 
We need to use a combination of bit shifting (`<<`) and bitwise or (`|`) or assemble the final values.

```cpp Incomplete binary example
uint32_t binary_frame[3] = {
  0b101010101010           << 20 | 
  0b101010101010           <<  8 | 
  0b10101010, 0b1010       << 28 | // boundary between 2 32bit integers
  0b101010101010           << 16
  // incomplete
};
``` 

<!-- style="display:none" -->
```cpp Answer
uint32_t binary_frame[3] = {
  0b101010101010           << 20 | 
  0b101010101010           <<  8 | 
  0b10101010, 0b1010       << 28 |
  0b101010101010           << 16 |
  0b101010101010           <<  4 |
  0b1010, 0b10101010       << 24 |
  0b101010101010           << 12 |
  0b101010101010           <<  0
};
```

<div class="good-task">
@boxheader(On the hardware)

Complete the frame specification using binary values. 
You will need to figure out the correct amount of bit shifting and where the boundaries between integer values are.
</div>


# Bit fields

Setting individual bit using bitwise operations and bit shifting does work and it does provide direct control of the smallest pieces of memory. 
However, the resulting code is not particularly readable or comprehensible, it is far too easy to make a small error or to introduce one whilst changing the code.
There are alternative options in C/C++ for addressing individual bits or collections of bits that are much clearer for the programming or maintainer.

Bit fields are a feature that enables programmers to access memory in non-byte-aligned sections or subsections smaller than a byte. 
While rarely used in general programming, bit fields are useful in embedded systems programming for accessing hardware registers that often have specific bits or groups of bits that control different functions.

Bit fields are also useful when working on memory constrained systems if you have multiple small values needing to be stored.


```cpp
// definition of our StatusRegister
struct StatusRegister 
{
    uint8_t enabled : 1;    // bit 0: enable flag
    uint8_t ready : 1;      // bit 1: ready status
    uint8_t error : 2;      // bit 2-3: error flag
    uint8_t mode : 4;       // bits 4-7: operation mode
};

StatusRegister status;
status.enabled = 1; // Set the enable flag
status.ready = 0;   // Clear the ready status
status.error = 0;   // Clear the error flag
status.mode = 15;   // Set the operation mode to 15 (binary 1111)

// Output as binary
std::cout << std::bitset<sizeof(StatusRegister)*8>(*reinterpret_cast<uint8_t*>(&status)) << std::endl;
```
```cpp -main.cpp
#include <bitset>
#include <cstdint>
#include <iostream>
int main() {
    #include "statusregister.h"
    return 0;
}
```
@LIA.eval(`["statusregister.h", "main.cpp"]`, `g++ main.cpp`, `./a.out`)
@hidecode("main.cpp")


The colon in the struct definition separates the field name from its width in bits, not bytes. 
This makes it important to understand what values can fit in fields of different lengths. 
For example, the `enabled` and `ready` fields are each 1 bit wide, so they can only store boolean values (0 or 1). 
The `error` field is 2 bits wide, allowing it to represent values from 0 to 3 (00, 01, 10, 11 in binary).
The `mode` field is 4 bits wide, allowing values from 0 to 15 (a single hexadecimal digit).

Once defined, we can create an instance of the `StatusRegister` struct and manipulate its fields as though it was a regular struct, but under the hood, it is still just a single byte of memory where each field corresponds to specific bits.

In this example, we define a `StatusRegister` struct that represents an 8-bit hardware register. Each member of the struct corresponds to specific bits in the register, allowing us to easily access and manipulate individual bits without needing to perform manual bitwise operations.

The total size of the `StatusRegister` struct is 1 byte (8 bits), so the same amount of memory is used as a single `uint8_t`, but we can access the individual bits in a more intuitive way.

<div class="good-task">
@boxheader(In the browser)

Adjust the values of the elements of `status` and see how the binary values change as you do so.

What happens if you try and assign a value which will not fit in the number of bits available?

</div>

----------------------------------------

The alternative to bit fields in this example would be to use bitwise operations to manipulate the bits directly, which can be more error-prone and less readable, e.g.:

```cpp
uint8_t status = 0; // Initialize the status register
status |= (1 << 0); // Set the enable flag 
status &= ~(1 << 1); // Clear the ready status
status &= ~(3 << 2); // Clear the error flag (2 bits)
status |= (15 << 4); // Set the operation mode to 15 (binary 1111)
```

<div class="important">
@boxheader(Important)

Care needs to be taken when using bit fields, because the C/C++ standard does not guarantee a specific layout for bit-field members in memory. Their ordering, allocation, and padding are implementation-defined and may vary between compilers, ABIs, and architectures.
For example, one implementation may assign bit 0 to the least-significant bit of the underlying storage, while another may order the fields differently or insert padding between them. This can affect how the register is accessed and interpreted.
This is especially important when working with external hardware registers over interfaces such as I2C or SPI, where the register bit order must match the device datasheet exactly. If the mapping is wrong, the software may read or write incorrect bits, leading to subtle hardware faults.

</div>


