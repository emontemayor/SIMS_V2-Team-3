### BACnet MS/TP on RobotDyn SAMD21 Platform

The RobotDyn SAMD21 M0 represents a powerful,
32-bit extension of the Arduino UNO platform.
The board is powered by Atmel�s SAMD21 MCU,
featuring a 32-bit ARM Cortex� M0 core
ATSAMD21G18 48pins LQFP at clock frequency of 48MHz.

To create a BACnet MS/TP project, we use:

1) Atmel-ICE - a powerful development tool for debugging
   and programming ARM� Cortex�-M based SAM and AVR microcontrollers
   with on-chip debug capability.

2) SAMD21 with Arduino Pinout headers

3) Arduino Uno V3 compatible RS485 shield (DFR0259)

### RobotDyn SAMD21 Arduino Uno V3 Pin Mapping

| SAMD21      | Arduino     | RobotDyn    | RS485 DFR0259
|:------------|:------------|:------------|:------------
| NC          | NC          | NC          |
| IOREF       | IOREF       | IOREF       |
| RESET       | RESET       | RESET       | RST BUTTON
| +3V3        | +3V3        | +3V3        |
| +5V         | +5V         | +5V         | +5V
| GND         | GND         | GND         | GND
| GND         | GND         | GND         | GND
| VIN         | VIN         | VIN         |
|             |             |             |
| PA02        | A0          | A0          |
| PB08        | A1          | A1          |
| PB09        | A2          | A2          |
| PA04        | A3          | A3          |
| PA05        | A4          | A4          |
| PB02        | A5          | A5          |
|             |             |             |
| PA23/SCL    | SCL         | SCL         |
| PA22/SDA    | SDA         | SDA         |
| PA03/AREF   | AREF        | AREF        |
| GND         | GND         | GND         |
| PA17        | D13         | D13         | LED-L ANODE (+)
| PA19        | D12         | D12         |
| PA16        | D11         | D11         |
| PA18        | D10         | D10         |
| PA07        | D9          | D9          |
| PA06        | D8          | D8          |
|             |             |             |
| PA21        | D7          | D7          |
| PA20        | D6          | D6          |
| PA15        | D5          | D5          |
| PA08        | D4          | D4          |
| PA09        | D3          | D3          |
| PA14        | D2          | D2          | CE/RTS - note: shared with USB!
| PA10        | D1          | D1          | TXD
| PA11        | D0          | D0          | RXD
|             |             |             |
| PA27        |             |TX_LED (-)   |
| PB03        |             |RX_LED (-)   |
| PA17/SCK    |             |TCC2 LED (+) |


### ATSAMD21G18 Fuses

The ATSAMD21G18 use fuses to configure some of the internal
workings of the microcontroller.  Clocks, calibrations, boot size,
EEPROM size, brown-out-detection levels, etc.
If programming fails, reset the following fuses to their defaults:

| Fuse                 | Value  |
|:---------------------|:-------|
| NVMCTRL_BOOTPROT     | 0x07   |
| NVMCTRL_REGION_LOCKS | 0xFFFF |

# RobotDyn SAMD21 Specifications

| Specification            | Value                    |
|:-------------------------|:-------------------------|
| Microcontroller          | ATSAMD21G18 48pins LQFP  |
| Power Out                | 3.3V-800mA               |
| Power IN. USB            | 5V                       |
| Power IN. VIN/DC Jack    | 5V                       |
| Power Consumption        | 3.3V 220mA               |
| Logic Level              | 3.3V                     |
| USB                      | Micro USB                |
| Clock Frequency          | 48MHz                    |
| Operating Supply Voltage | 3.3V                     |
| GPIO                     | 25                       |
| Digital I/O              | 19(12-PWM)               |
| Analog I/O               | 6                        |
| Data RAM Type/Size       | 32Kb                     |
| Data ROM Type/Size       | 256Kb                    |
| Interface Type           | ISP/SWD                  |
| Operating temperature    | -40C +85C                |
| Length-Width             | 56.5-18mm                |
