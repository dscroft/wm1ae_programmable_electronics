<!--
module_id: ecosystem
author:   David Croft
email:    david.croft@warwick.ac.uk
version: 0.0.1

language: en
narrator: UK English Female

mode: Textbook

title: Development Ecosystem
comment:  This module provides an overview of the development ecosystem for embedded systems programming, with a focus on the Arduino platform and Visual Studio Code as the primary development environment.

@learning_objectives  
    - Understand the components of the development ecosystem for embedded systems programming.
    - Familiarize with the Arduino platform and its features.
    - Learn about Visual Studio Code and its advantages for software development.
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

# Development Ecosystem

This module assumes and recommends that you use the PlatformIO IDE within Visual Studio Code for your development work. 
You are free to chose other development environments if you wish but you are wholly responsible to adapting the supplied instructions and materials to your chosen alternative.


## Arduino

The Arduino platform is a popular open-source electronics platform based on easy-to-use hardware and software.
It consists of a range of microcontroller boards, such as the Arduino Uno, Nano, and Mega, which are designed for prototyping and development of embedded systems.

It's use in an industry context is often limited to prototyping and education as opposed to production.
However it's wide range of supporting libraries and large community make it an excellent choice for learning about embedded systems development, especially for those new to the field.

The Arduino software ecosystem does support a number of production grade microcontrollers such as the SAMD21, STM32 ESP8266 and ESP32. 
So transitioning to a more industry relevant microcontroller is supported down the line.

R4 Wifi
=======

This this module we will be primarily using the Arduino Uno R4 Wifi, which is the latest addition to the Arduino family and features a more powerful microcontroller and built-in Wi-Fi capabilities.
However alternative boards are available if needed.

The primary reason for choosing the R4 Wifi is its built in debugging capabilities. Although the built in wifi is a benefit.


## Visual Studio Code

Visual Studio Code (vscode) is a free, open-source code editor developed by Microsoft. 
It is widely used for various programming languages and offers a rich ecosystem of extensions that enhance its functionality. 
VS Code provides the standard features such as syntax highlighting, code completion, debugging tools, and integrated terminal support, making it an excellent choice for software systems development.


<div class="important">
<b style="color: rgb(var(--color-highlight));">Important note</b><br>

Vscode is open sourced under the MIT License and is available for Windows, macOS, and Linux.
However the default pre-compiled binaries of vscode include telemetry and other Microsoft services.
If you prefer to use a version of vscode without telemetry, you can use the open-source version called [VSCodium](https://vscodium.com/).
If you encounter anywhere that the instructions do not work with VSCodium please let the module leader know.

</div>


## PlatformIO

PlatformIO provides a powerful and user-friendly environment for embedded systems programming, with support for a wide range of microcontrollers.

It is separate and distinct from VSCode, but it can also integrate with it as an extension.


## Justification

We will be using PlatformIO within VSCode as our development environment for this module over the official Arduino IDE for several reasons:

- **Advanced Features**: VSCode offers advanced features such as intelligent code completion, debugging tools, and integrated terminal support, which can enhance the development experience and productivity.
- **Project Configuration**: PlatformIO uses a configuration file (`platformio.ini`) that allows you to easily manage project settings, dependencies, and build options. This can help streamline the development process and make it easier to share projects with others.
- **Generative Code**: Various VSCode extensions support generative AI code generation. Use of these tools can significantly speed up development and responsible use of these tools is increasingly expected in industry.
- **Version Control Integration**: VSCode has built-in support for version control systems like Git, which can help you manage changes to your code and collaborate with others more effectively. This module will introduce and *will require* version control for various aspects, including coursework submission.

While the official Arduino IDE is simpler and may be more approachable for beginners, it lacks many of the features needed to support professional software development practices that will be introduced in this module.


# Version Control

Version control is a system that records changes to files over time so that you can recall specific versions later.
It is an essential tool for software development, allowing developers to track changes, collaborate with others,

The specifics of version control will be covered later in module, but we will be using Git on this module.
You will be required to upload your coursework to an online Git repository. 

Online repository hosting
=========================

You are not required to use any specific repository hosting service.

WMG has an [institutional instance](https://mygit.wmg.warwick.ac.uk/) that you can use for this purpose, but you are free to use any online hosting service such as GitHub or GitLab if you prefer.

<div class = "cool-fact">
<b style="color: rgb(var(--color-highlight));">Free!</b><br>

While you are in education, Github will give you a free [Pro account](https://github.com/education/students) that includes unlimited private repositories and extra features. 
This is normally a paid service but you are signing up with a 3rd party (GitHub), so please read their terms of service and privacy policy carefully before signing up.

</div>


# AI Coding agents

You are free to use AI coding agents such as Copilot for certain aspects of this module subject to documentation requirements which will be specified.
However it is not required.

As such the specific agents that you may choose to use are up to you.
This module will not be supplying licenses for specific agents.
If you choose to use an agent, then there is almost certainly an extension to integrate them with your VSCode environment.
For example if you have signed up for a Github education account and have access to Copilot, then you can install the [Copilot extension](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot).

Alternatively you can run your own local agents using Ollama and integrate with VSCode using CLine, Ollama Autocoder or alternatives.


# Checklist

1. Install Visual Studio Code.
2. Install the PlatformIO extension in Visual Studio Code.
3. Create account on an online Git repository hosting service (e.g. WMG's MyGit, GitHub or GitLab).
4. Collect your Arduino Uno R4 Wifi and accessories.
   