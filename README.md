# Door-locker-security-system


###### AVR-ATmega16 Door Security System with two ECU's

1. Human Machine Interface which is responsible for interfacing the user.
2. Control Machine Unit which is reponsible for handling all the logic.

## Routine
The User is asked to enter his initial password through out a 4x4 Keypad and all the visuals for easing
the user interaction are shown in a 16x2 LCD. Both connected to the 1st ECU.
The password is then sent to the 2nd ECU to handle all the logic of receiving it from the 1st ECU
by using UART serial communication protocol. Then, storing it in an external EEPROM which interfaces with the 2nd ECU using
I2C (Two wire Interface) serial communication protocol. Leaving both ECU's after in the Idle mode, waiting for the user
to either open the door (using DC-Motors) or change his password. Both cases requires the user to enter his already
stored password for verification. If the entered password is wrong for more than 3 times. The System shut downs itself
giving loud alarm that there might be a theft situation.

## Building the project
run the makefile through terminal with:
```bash
make -f makefile.mk
```

## Simulation
Any late version of Proteus would do. click on each controller and insert the executable files respectively.
