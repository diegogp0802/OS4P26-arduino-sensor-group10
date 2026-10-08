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
7. Measure, then read the SD card on a computer and copy `data.csv` into `data/raw/` (naming rules in [`data/README.md`](data/README.md)).
8. Plot with the script in [`analysis/`](analysis/).

Something not working? See [`troubleshooting.md`](troubleshooting.md). 

## Repository map

| Path | Contents |
|---|---|
| [`hardware/`](hardware/) | Bill of materials, wiring tables and diagram, photos |
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

## Results

_TODO: link the figures from `analysis/figures/` and the observed ranges._

## Limitations

- The time column of `co2_logger` is **inferred** (reading number × 10 s), not
  wall-clock time: a failed reading writes no row, so later timestamps fall
  behind. Always record the real start time of a run in
  [`data/README.md`](data/README.md).
- _TODO: calibration status of the CO₂ sensor._


## License

Copyright © 2026 OS4P26 Group 10

- Code in `code/` and `analysis/`: [MIT](licenses/LICENSE)
- Documentation, diagrams, photos and data: [CC BY 4.0](licenses/LICENSE-CC-BY-4.0.md)
