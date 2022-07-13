## Description

- In Lab11 you will learn how to write software that converts numbers into ASCII 
strings and display the string on the display connected to UART0.

## How to get started

- If you are using linux, follow these steps:
    - Install [`PUTTY`](https://www.putty.org/) terminal.
    - Click on `Session` category.
    - Set `Connection type` option to `serial`.
    - Set `Serial line` option `/dev/ttyACM0` or whatever serial port your 
Launchpad is connected to.
    - Set `Speed` option to `115200` or whatever baudrate you want.
    - Click open, and now you can communicate with your Launchpad.
    - ***NOTE***: you can use it on Windows as well.

- If you want a terminal program, follow these steps:
    - Install [`PICOCOM`](https://github.com/npat-efault/picocom)
    - Run `picocom -b <baudrate> /dev/tty<COM_port>`
        - e,g. `picocom -b 115200 /dev/ttyACM0`
