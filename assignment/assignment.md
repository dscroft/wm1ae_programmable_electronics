<!--
module_id: assign_morse
author:   David Croft
email:    david.croft@warwick.ac.uk
version:  0.0.1
module_type: standard
language: en
narrator: UK English Female
mode: Textbook

title: Morse code assignment support


@onload
window.chars_to_map = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ \n';
window.static_chars = 'ABCD\n';

window.sid_to_mapping = function(sid) 
{
    let mapping = {}
    const char_to_morse = (c) => c.toString(2).padStart(6, '0').replace(/0/g, '∙').replace(/1/g, '—')

    // map the static characters such that their mapping is always the same
    for (let c = 1; c <= window.static_chars.length; c++) {
        const i = window.static_chars[c - 1]
        mapping[i] = char_to_morse(c)
    }

    const to_shuffle = [...window.chars_to_map].filter(c => !window.static_chars.includes(c))

    let c = window.static_chars.length + 1
    while (to_shuffle.length !== 0) {
        const idx = sid % to_shuffle.length
        const i = to_shuffle.splice(idx, 1)[0]
        mapping[i] = char_to_morse(c)
        c += 1
    }

    return mapping
}
@end

import: ../assets/macros.md
-->

# Morse Code Mapping

Get your individual morse code encoding. You will need to enter your student ID. 
The mapping will be generated based on your student ID and will be unique to you. You can download the mapping for reference.

Student ID: <script value="1234567" min="1000000" max="9999999"input="number" output="sid">@input</script>

<script input="submit" default="Download mapping" >
    // test if window.mapping is defined, if not, alert the user to enter their student ID first
    if (window.mapping === undefined) 
    {
        alert("Please enter your student ID and click the button to download your mapping.")
    }
    else
    {
        // create a blob from the mapping table and download it as a .md file
        const blob = new Blob([window.mapping[1]], { type: 'text/markdown' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = `mapping_${window.mapping[0]}.md`;
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
    }
</script>

<script run-once="true" style="display: block">
    let sid = "@input(`sid`)"

    let mappings = window.sid_to_mapping(sid)

    let header = "<!-- data-type='none' data-sortable='false' data-title='Individual morse code mapping' -->\n"

    let table = "| Character | Pulses |\n"
    table +=    "| --------- | ------ |\n"
  
    const escape_chars = (c) => {
        if (c === "\n") return "*EOM*"
        else if (c === " ") return "*SPACE*"
        else return c
    }

    for (let c of window.chars_to_map) 
    {
        // pad the character display to 9 characters with spaces for alignment
        const charDisplay = String(escape_chars(c)).padEnd(9, ' ')
        table += "| " + charDisplay + " | " + mappings[c] + " |\n"
    }

    window.mapping = [sid, table];

    send.lia("LIASCRIPT: "+header+table)
</script>