## UTAustinX UT.6.20x: Embedded Systems - Shape The World: Multi-Threaded Interfacing Labs

### Description
- This is my solution to the 
[UT.6.20x: Embedded Systems - Shape The World: Multi-Threaded Interfacing](https://learning.edx.org/course/course-v1:UTAustinX+UT.6.20x+3T2019/home) course.

### Tools and Technologies
- [PlatformIO](https://platformio.org/).
- [NeoVIM](https://neovim.io/) as an editor.
- [VS Code](https://code.visualstudio.com/) to debug the code.
- [Keil μVision V4.0](https://www.keil.com/demo/eval/armv4.htm) for edX grader.

### How to Run the Code
- Connect your LaunchPad to your computer.
- If you are using Linux, follow the steps in 
[here](https://docs.platformio.org/en/latest/core/installation/udev-rules.html) 
to be able to access the LaunchPad.

- Install PlatformIO CLI and VSCode extension.

- Clone the repository and run the following commands:
    ````
    git clone https://github.com/Alighorab/UT.6.20x.Labs.git
    cd UT.6.20x.Labs
    cd <lab_name>
    make
    make upload
    ````
    - Then push the reset button on the LaunchPad.
- To debug the code, run the following commands:
    ````
    cd <lab_name>
    code .
    ````
    - Hit `F5` to start the debugger.

- To get a grade for the lab, copy the code to Keil 
and follow the instructions in the course.
