# Components

The original course handout lists the parts only by generic name ("CO₂ sensor", "Arduino Uno"). That is not enough to reproduce anything: different modules use different protocols, voltages and pin orders. This file records the exact
hardware we used.

## Bill of materials

| # | Component | Exact model we used | Notes |
|---|---|---|---|
| 1 | Microcontroller board | Arduino Uno R3 | Named in our wiring diagram. [Instruction manual](https://agelectronica.lat/pdfs/textos/A/A000066.PDF) |
| 2 | CO₂ sensor | MH-Z19C | Named in our wiring diagram. [Instruction manual](https://www.tinytronics.nl/product_files/003109_MH-Z19C-DZ-terminal%20type%20CO2%20Manual(Ver1.21)-202103.pdf) |
| 3 | SD card reader | microSD card adapter | Named in our wiring diagram. [SD connection guide](https://docs.arduino.cc/learn/programming/sd-guide/)|
| 4 | SD card | 32Gb |  |
| 5 | Breadboard | 400-tie-point, half-size solderless breadboard. | [Guide for breadboard and wiring diagram](https://www.sciencebuddies.org/science-fair-projects/references/how-to-use-a-breadboard#breadboard-diagram) |
| 6 | Jumper cables | Male-to-male, male-to-female as needed | |
| 7 | External battery (laptop) | Laptop connection (5 V by default) | If one uses a powerbank or similar inputs, make sure this powerbank and cable DO NOT exceed the 5 V limit. |
| 8 | USB cable | USB-A to USB-B | Must be a **data** cable, not charge-only |

## Voltage warning

The Arduino Uno's logic runs at 5 V. 

The MH-Z19 requires 5 V on `Vin`; its UART lines are 3.3 V logic but are tolerant of the Uno's 5 V output in practice, which is why the sketch connects them directly.


