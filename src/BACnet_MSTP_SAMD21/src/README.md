# SAMD21 M0-Mini

The RobotDyn SAMD21 M0-Mini represents a powerful, 32-bit extension of the Arduino UNO platform, but to small size like Micro or Nano. The board is powered by Atmel’s SAMD21 MCU, featuring a 32-bit ARM Cortex® M0 core.
Compatible with Arduino M0.

The SAMD21 M0-Mini board expands the family by providing increased performance,enabling a variety of project opportunities for devices, and acts as a great educational tool for learning about 32-bit application development. 
The Zero applications span from smart IoT devices, wearable technology, high-tech automation, to crazy robotics. The board is powered by Atmel’s SAMD21 MCU, which features a 32-bit ARM Cortex® M0+ core.

# Specifications

The SAMD21 uses fuses, similar to AVR, that can lock out programming. If programming fails, reset the following fuses to their defaults:

| Fuse                 | Value  |
|:---------------------|:-------|
| NVMCTRL_BOOTPROT     | 0x07   |
| NVMCTRL_REGION_LOCKS | 0xFFFF |


# Specifications

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
| Interface Type           | ISP                      |
| Operating temperature    | −40С°/+85С°              |
| Length×Width             | 56.5×18mm                |

# SAM D21 MINI Pin Map

| Pin #    |  SAM D21 | Arduino Mini | SAM D21 MINI  |
|:--------:|:--------:|:------------:|:-------------:|
| 43/44    |          | VIN          | P2-1          |
| 18/35/42 |          | GND          | P2-2          |
|          |          | USB          | P2-3          |
|          |          | 3.3VDC       | P2-4          |
| 18/35/42 |          | GND          | P2-5          |
| 32       |  PA23    | SCL          | P2-6          |
| 31       |  PA22    | SDA          | P2-7          |
| 26       |  PA17    | D13/SCK      | P2-8          |
| 28       |  PA19    | D12/MISO     | P2-9          |
| 25       |  PA16    | D11/MOSI     | P2-10         |
| 27       |  PA18    | D10/SS       | P2-11         |
| 12       |  PA07    | D9           | P2-12         |
| 11       |  PA06    | D8           | P2-13         |
| 30       |  PA21    | D7           | P2-14         |
| 4        |  PA03    | AREF         | P3-1          |
| 3        |  PA02    | A0           | P3-2          |
| 7        |  PB08    | A1           | P3-3          |
| 8        |  PB09    | A2           | P3-4          |
| 9        |  PB04    | A3           | P3-5          |
| 10       |  PB05    | A4           | P3-6          |
| 47       |  PB02    | A5           | P3-7          |
| 15       |  PA10    | D1/TX0       | P3-8          |
| 16       |  PA11    | D0/RX1       | P3-9          |
| 13       |  PA08    | D4           | P3-10         |
| 14       |  PA09    | D3           | P3-11         |
| 23       |  PA14    | D2           | P3-12         |
| 24       |  PA15    | D5           | P3-13         |
| 29       |  PA20    | D6           | P3-14         |
