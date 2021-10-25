# MML bootloader

Based on MS UF2 for SAMD21.


## Flashing

### With microchip studio https://www.microchip.com/en-us/development-tools-tools-and-software/microchip-studio-for-avr-and-sam-devices

* Connect to the (external) debugger
* Select the elf file in the memories section
* Program

## Compiling

This fork contains the boards def for the MML board:

https://github.com/oxullo/uf2-samdx1

* Issue: make BOARD=mml
