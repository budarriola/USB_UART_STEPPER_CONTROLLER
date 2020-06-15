# USB_UART_STEPPER_CONTROLLER
Simple cheep usb controle of a stepper motor for rapid prototyping applications
i am useing a tmc2208 module set in uart mode with a psoc 5 lp development, but i am not currently useing the uart functions of the tmc2208

usb uart commands

//set 60rpm
@R60

//turn 360 degrees
@T360

//turn 360 degrees the other way
@T-360
