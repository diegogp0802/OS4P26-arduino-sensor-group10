# Components

The original course handout lists the parts only by generic name ("CO₂ sensor", "SD card reader"). That is not enough to reproduce anything: different modules use different protocols, voltages and pin orders. This file records the exact
hardware we used.

## Bill of materials

| # | Component | Exact model we used | Notes |
|---|---|---|---|
| 1 | Microcontroller board | Arduino Uno Rev3? | |
| 2 | CO₂ sensor | MH-Z19 (_TODO: is yours MH-Z19, MH-Z19B or MH-Z19C?_) | |
| 3 | P/T/RH sensor |  |  |
| 4 | SD card reader | _TODO: model/brand_ | |
| 5 | SD card | _TODO: capacity_ |  |
| 6 | Breadboard | Size ? | |
| 7 | Jumper cables | Male-to-male, male-to-female as needed | |
| 8 | Powerbank? | _TODO: model and capacity_ |  |
| 9 | USB cable | USB-A to USB-B | Must be a **data** cable, not charge-only |

## Voltage warning

The Arduino Uno's logic runs at 5 V. 

_TODO: record which type yours is and which supply pin you connected it to._

The MH-Z19 requires 5 V on `Vin`; its UART lines are 3.3 V logic but are tolerant of the Uno's 5 V output in practice, which is why the sketch connects them directly.


