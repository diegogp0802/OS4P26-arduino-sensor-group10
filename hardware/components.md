# Components

The original course handout lists the parts only by generic name ("CO₂ sensor", "SD card reader"). That is not enough to reproduce anything: different modules use different protocols, voltages and pin orders. This file records the exact
hardware we used.

## Bill of materials

| # | Component | Exact model we used | Notes |
|---|---|---|---|
| 1 | Microcontroller board | Arduino Uno Rev3? | _TODO: confirm revision, original or clone_ |
| 2 | CO₂ sensor | MH-Z19C | Named in our wiring diagram. _TODO: add a link to the instruction manual that matches your exact module_ [Instruction manual](https://www.tinytronics.nl/product_files/003109_MH-Z19C-DZ-terminal%20type%20CO2%20Manual(Ver1.21)-202103.pdf)|
| 3 | SD card reader | microSD card adapter | Named in our wiring diagram. _TODO: model/brand_ |
| 4 | SD card | _TODO: capacity_ |  |
| 5 | Breadboard | Size ? | |
| 6 | Jumper cables | Male-to-male, male-to-female as needed | |
| 7 | External battery (laptop) | _TODO: is it the laptop's USB, or a powerbank? Model and capacity_ |  |
| 8 | USB cable | USB-A to USB-B | Must be a **data** cable, not charge-only |

## Voltage warning

The Arduino Uno's logic runs at 5 V. 

The MH-Z19 requires 5 V on `Vin`; its UART lines are 3.3 V logic but are tolerant of the Uno's 5 V output in practice, which is why the sketch connects them directly.


