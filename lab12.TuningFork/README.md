## Description
- This lab has these major objectives: 
    1) the understanding and implementing of interrupt software;
    2) interfacing an output pin to the speaker, so that the software can generate a quiet buzzing sound at 440 Hz; and 
    3) the study the accuracy of the pitch created with interrupts.

## Preparation
- You will need a `LaunchPad`, a `1kΩ resistor`, the `headphone jack`, and `headphones`.
- If you don't have a `headphone jack` you will see an alternative 
[here](https://learning.edx.org/course/course-v1:UTAustinX+UT.6.20x+3T2019/block-v1:UTAustinX+UT.6.20x+3T2019+type@sequential+block@4592f18d18f8479f9ec87c8708c5fcf1/block-v1:UTAustinX+UT.6.20x+3T2019+type@vertical+block@750958b0290341109269cae9066c8ed4)

## How to Run
- This lab is somehow tricky to run using PlatformIO. So, to keep the naming convension
identical to the other labs, I modified some files in 
`$HOME/.platformio/packages/framework-libopencm3/`
- You will have to change the name for `SysTick` handler to `SysTick_Handler`
- Open `lib/cm3/vector.c` and `include/libopencm3/cm3/nvic.h` then replace 
`sys_tick_handler` with `SysTick_Handler`
