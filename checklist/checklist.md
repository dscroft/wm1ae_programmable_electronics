<!--
module_id: basics
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Module box checklist

link:  ../assets/styles.css
import: ../assets/macros.md

@hoveritem
<span class="image-hover" data-image="@1"> 
[[X]] @0
</span>
@end
-->

# Module kit

For the duration of the module you will be supplied with a module kit.

<div class="important">
@boxheader(Important)

You are expected to take care of your kit and to return it in good condition with all parts at the end of the module.

If your kit is missing any of the listed parts, you need to inform the teaching staff **during** the handout session.
By taking the kit you are accepting that the kit is complete with all listed parts. 

Taking parts from other student's kit/s without their knowledge and permission is an academic offense and will be referred.

Replacing list parts using other student's kit/s is an academic offense and will be referred.

In the event that part of your kit breaks, contact the module teaching staff.
</div>

You will require this kit to be able to complete your coursework.

-----------------------------------------

<div style="display: flex; gap: 20px;">
<div style="width: 300px">
@hoveritem(`Numbered Project Box`, https://upload.wikimedia.org/wikipedia/commons/c/cb/RBG-LED.jpg)
@hoveritem(`Breadboard`, https://thumb.wikimedia.org/wikipedia/commons/thumb/e/e8/Breadboard.png/250px-Breadboard.png)
@hoveritem(`Arduino Uno R4 Wifi`, https://store.arduino.cc/cdn/shop/files/ABX00087_00.front_494x371.jpg)
@hoveritem(`Arduino R3 Motor Shield`, https://store.arduino.cc/cdn/shop/files/A000079_01.iso_494x392.jpg)
@hoveritem(`SR04 Ultrasonic sensor`, https://mm.digikey.com/Volume0/opasdata/d220001/medias/images/6032/MFG_SEN-24049.jpg)
[[X]] Servo motor with arm
@hoveritem(`Blue DG01D-­E motor with encoder`, https://mm.digikey.com/Volume0/opasdata/d220001/medias/images/496/MFG_ROB-16413.jpg)
@hoveritem(`Encoder cable for DG01D-E motor`, https://mm.digikey.com/Volume0/opasdata/d220001/medias/images/496/MFG_ROB-16413.jpg)
@hoveritem(`Multiple LEDs`, https://upload.wikimedia.org/wikipedia/commons/9/90/Electronic-Component-Red-LED.jpg)
@hoveritem(`Multiple Male-to-male jumper wires`, checklist/media/m2m.jpg)
@hoveritem(`Multiple Make-to-female jumper wires`, checklist/media/m2f.jpg)
@hoveritem(`USB A to USB C, male-to-male cable`, https://mm.digikey.com/Volume0/opasdata/d220001/medias/images/4566/MFG_DH-20Mseries.jpg)
</div>
<div id="image-container" style="width: 400px">
    <img id="hover-image" src="" alt="">
</div>
</div>

<script run-once>
  const container = document.getElementById('image-container');
  const image = document.getElementById('hover-image');

  document.querySelectorAll('.image-hover').forEach(text => {
    text.addEventListener('mouseenter', () => {
      image.src = text.dataset.image.trim();
      container.style.display = 'block';
      console.log(text.dataset.image)
    });

    text.addEventListener('mouseleave', () => {
      container.style.display = 'none';
      console.log("leave")
    });
  });
</script>

<script>
    document.querySelectorAll(".lia-quiz__control").forEach((item) => {
        item.style.display = "none";
    });
</script>

# Confirmation

<!-- style="display: none" -->
<iframe src="https://forms.cloud.microsoft/Pages/ResponsePage.aspx?id=vc-6Ce9HZUSSZTVG8ur2vCNBHc6R-IRFqapLtLMY9gZUQVRaRlo4QU5TS1M4VzlYTlpLQUlZMDFEVC4u">

<iframe id="form" 
    src="https://forms.cloud.microsoft/Pages/ResponsePage.aspx?id=vc-6Ce9HZUSSZTVG8ur2vCNBHc6R-IRFqapLtLMY9gZUQVRaRlo4QU5TS1M4VzlYTlpLQUlZMDFEVC4u&embed=true" 
    style="border: none; width:100%; height: 1000px; overflow: hidden;"></iframe>

