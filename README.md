# OS4P Reproducibility Challenge — Arduino CO₂ / P-T-RH Logger

**Course:** Open Science for Physicists (NS-PH500M), 2026–2027, Utrecht University
**Group:** 10
**Members:** _TODO: names + GitHub usernames_
**Phase 1 deadline:** 5 October 2026

---

## What this repository is

This repository documents an experiment in which an **Arduino Uno** is used to
build a stand-alone data logger that records either:

1. **CO₂ partial pressure** (ppm), using an MH-Z19 infrared sensor, or
2. **Temperature, pressure and relative humidity**, using a BME280 sensor

In both cases the measurements are written to a `.csv` file on an SD card, so
the logger can run untethered from a powerbank.

The goal is not the sensor itself. The goal is that a physics master's
student who has never seen this setup can rebuild it, re-run it, and obtain
comparable data using only the contents of this repository. 

## Quick start 
1. Read [`hardware/components.md`](hardware/components.md) and gather the parts.
2. Wire everything according to [`hardware/wiring.md`](hardware/wiring.md).
3. Verify your board connects: upload [`code/connection_test`](code/connection_test/connection_test.ino).
4. Clear the SD card: upload [`code/erase_sd`](code/erase_sd/erase_sd.ino).
5. Upload the logger you want: [`code/co2_logger`](code/co2_logger/co2_logger.ino) or [`code/bme280_logger`](code/bme280_logger/bme280_logger.ino).
6. Run the measurement following [Experimental protocol](#experimental-protocol) below.
7. Retrieve the data by reading the SD card directly on a computer.
8. Plot the results.

## Repository map

| Path | What is in it |
|---|---|
| [`hardware/components.md`](hardware/components.md) | Full bill of materials with exact models |
| [`hardware/wiring.md`](hardware/wiring.md) | Pin-by-pin wiring tables and why each pin was chosen |
| [`hardware/photos/`](hardware/photos/) | Photographs of the assembled setup |
| [`code/README.md`](code/README.md) | Line-by-line walkthrough of every sketch |
| [`code/`](code/) | All Arduino sketches (one folder per sketch, as the IDE requires) |
| [`data/README.md`](data/README.md) | What each dataset is, when and where it was recorded |
| [`data/raw/`](data/raw/) | Unmodified `.csv` files as they came off the SD card |
| [`analysis/`](analysis/) | Script to reproduce the figures from the raw data |
| [`troubleshooting.md`](troubleshooting.md) | Every error we hit, and how we fixed it |
| [`logbook.md`](logbook.md) | Chronological diary of the build |


## Software environment

Reproducibility depends on versions. Record what you actually used:

| Item | Version we used |
|---|---|
| Arduino IDE | _TODO: e.g. 2.3.2_ |
| Board selected in IDE | Arduino Uno |
| Operating system | _TODO: e.g. Windows 11 / macOS 14_ |
| Python (analysis) | _TODO: e.g. 3.11_ |



## Experimental protocol

_TODO: fill this in with what you actually did. The template below shows the
level of detail required — replace every placeholder._

### CO₂ measurement

1. 

### P/T/RH measurement

_TODO: same structure as above, for the BME280 run._

## Expected results

_TODO: replace with your own figures and observed ranges once you have data._


Figures produced from our data: _TODO: link them here, e.g._
`analysis/figures/co2_run1.png`.

