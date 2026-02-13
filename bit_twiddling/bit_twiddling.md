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

