# OS4P Reproducibility Challenge — Arduino CO₂

Low-cost CO₂ with an Arduino Uno.

**Course:** Open Science for Physicists (NS-PH500M), 2026–2027, Utrecht University
**Group:** 10


**Members:** 

- Niels Franke 
- Daniel Rouschop Dror
- Dave Dewdath
- Joram Vliem
- Paolo Dioni
- Diego Gomez
- Ime Rasenberg

---

## What this repository is

An **Arduino Uno** stand-alone data logger that records **CO₂** (ppm,
MH-Z19C infrared sensor) to a `.csv` file on an SD card, so it can run untethered from a powerbank.

The goal is that a physics master's student who has never seen this setup can
rebuild it, re-run it and obtain comparable data using only this repository.

## Quick start

1. Install the Arduino IDE ([download](https://www.arduino.cc/en/software/), we used 2.3.10).
2. Gather the parts: [`hardware/components.md`](hardware/components.md).
3. Wire everything: [`hardware/wiring.md`](hardware/wiring.md) (includes the diagram).
4. Check the board responds: upload [`code/connection_test`](code/connection_test/connection_test.ino).
5. Clear the SD card: upload [`code/erase_sd`](code/erase_sd/erase_sd.ino).
6. Upload the logger: [`code/co2_logger`](code/co2_logger/co2_logger.ino).
7. Measure, then read the SD card on a computer and copy `data.csv` into `data/` (naming rules in [`data/README.md`](data/README.md)).
8. Plot with the script in [`analysis/`](analysis/).

Something not working? See [`troubleshooting.md`](troubleshooting.md). 

## Repository map

| Path | Contents |
|---|---|
| [`hardware/`](hardware/) | Bill of materials, wiring tables and diagram |
| [`code/`](code/) | Arduino sketches, with a walkthrough in [`code/README.md`](code/README.md) |
| [`data/`](data/) | Raw measurements and an inventory of every run |
| [`analysis/`](analysis/) | Script that reproduces the figures from the raw data |
| [`troubleshooting.md`](troubleshooting.md) | Errors we hit and their fixes |
| [`logbook.md`](logbook.md) | Chronological diary of the build |

## Software environment

| Item | Version we used |
|---|---|
| Arduino IDE | 2.3.10 |
| Board selected in IDE | Arduino Uno |
| Operating system | Windows 11 |
| Python (analysis) | Python 3.13 |

## Experimental protocol

_TODO: what you actually did, in enough detail to repeat it._ Cover: warm-up
time, whether the CO₂ sensor was calibrated, sensor location, run duration, and
any deliberate perturbation with its clock time.

This protocol covers the **MH-Z19C** sensor. Pin assignments for the whole
logger (sensor and SD module) are in [`hardware/wiring.md`](hardware/wiring.md);
that file is the single source of truth. The sensor pins are only summarised
here by *name*.

### Sensor specifications

| Property | Value |
|---|---|
| Measurement principle | Non-dispersive infrared (NDIR) |
| Range | 0–5000 ppm |
| Accuracy | about ±(50 ppm + 5 % of reading) |
| Supply voltage | 4.5–5.5 V (peak current about 150 mA during warm-up) |
| Logic level | 3.3 V on Tx/Rx |
| Interface used | UART, 9600 baud |
| Minimum warm-up (datasheet) | 3 minutes |

### A. Before wiring: what to disconnect

1. **Unplug the USB cable and any powerbank** before touching any wire.
2. Remove everything else from the pins that the sensor will use (see `hardware/wiring.md`) as well as from 5 V and GND (shields, spare sensors).
3. Keep **D6/D7 free**. These are the hardware serial pins shared with the USB connection; anything on them blocks uploads.
4. Keep the sensor pins **HD**, **PWM/Vo** and **Vout (3.3 V out)** unconnected during normal logging:

### B. Warm-up and calibration

The MH-Z19C measures against an internal 400 ppm "zero point". Because the
logger sketch does not send calibration commands, we use the **hardware (HD pin)
method**, which needs no code.

**Zero-point calibration (400 ppm):**

1. Take the powered logger **outdoors**, upwind of people, vehicles and exhausts. Keep your own breath away from the sensor.
2. Let it **warm up and stabilise for more than 20 minutes**, until the reading is flat (within about ±20 ppm). The datasheet minimum is 3 minutes, but the early readings are unreliable.
3. With the logger still powered, connect the **HD pin to GND for at least 7 seconds**, then remove the wire.
4. Wait 1–2 minutes. The reading should settle at about 400 ppm.

### C. Validation check (before every campaign)

1. **Ambient check:** outdoors, the reading should sit at about 400–450 ppm.
2. **Response check:** breathe gently towards the sensor from about 30 cm and step away. The reading should climb to thousands of ppm within seconds to a minute and then decay. This confirms the sensor responds; it is not a quantitative test.

### D. Handling cautions

- Avoid condensation, water, strong vibration and shock.
- Do not open or touch the sensor housing after calibration.
- A reading that is constantly 0, constantly 400/410, or far outside 300–5000 ppm usually indicates warm-up, wiring or calibration problems; see [`troubleshooting.md`](troubleshooting.md).

## Results

Our results [`Graph.pdf`](analysis/figures/Graph.pdf). Further explenation of the values in the graph can be found here [`Inventory table`](data/README.md). The CO₂ PPM range from around 500 to 2000 at its peak.  

## Limitations

- The time column of `co2_logger` is **inferred** (reading number × 1 s), not
  wall-clock time: a failed reading writes no row, so later timestamps fall
  behind. Always record the real start time of a run in
  [`data/README.md`](data/README.md).
- In our run, the CO2 sensor was calibrated inside, meaning the measurement was not properly calibrated. We recommend calibrating it outside if possible to get accurate readings.


## License

Copyright © 2026 OS4P26 Group 10

- Code in `code/` and `analysis/`: [MIT](licenses/LICENSE)
- Documentation, diagrams, photos and data: [CC BY 4.0](licenses/LICENSE-CC-BY-4.0.md)
