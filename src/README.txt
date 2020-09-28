All code was written in Atmel Studio 7.0 and utilized Atmel Software
Framework (ASF). The ASF add-on must be installed on to Atmel Studio to
compile the SIM System code.

Other libraries used: ChaN's FatFs, FTDI/Bridgetek FT813 LCD controller
firmware (sourced from EVE Screen Design 4.0).

^^ Generic Atmel Legal Statement

vv Real talk from Sander Sieglaff

This code repository holds all the code that Team 3 (Sander Sieglaff, Emil Montemayor, Mikayla Schlegal) used to impliment the SIMS system.
While the system as a whole is incomplete, some parts of the code represent working aspects of the project. For instance, the vast majority
of the code for the control unit is working. A lot of the files in this directory are unimportant or from older iterations, and should mostly
be ignored. All the code presented here is intended to be used in Atmel Studio 7, Microchip's current (9/28/2020) development environment. To
work on this project, once you have Atmel Studio 7 installed you can navigate to the following locations from this directory and open the
following code projects:

Reciever code: rx board\rxboard_ex\rxboard_ex.atsln
Transmitter code: tx board\txboard\txboard.atsln
Control Unit code: BACnet_MSTP_SAMD21\BACnet_MSTP_SAMD21.atsln

It is recommended to clone this repository and use it to make your own, possibly also cleaning out the trash that exists within this current repository.

Good luck!
Sander Sieglaff, Capstone Team 3 Hardware Engineer Spring 2020
