# Data

## Rules

- Files in `data/` are **exactly** as they came off the SD card. Never edit them,
  not even to fix a header or delete a bad row. Corrections belong in
  `analysis/`, where they are visible and reversible.
- Rename each file descriptively when you copy it in — every run produces a file
  called `data.csv`, so they must be renamed or they overwrite each other.
- Every file gets a row in the inventory below. A `.csv` with no description is
  not data, it is a mystery.

## Naming convention

```
<sensor>_<YYYYMMDD>_<short-description>.csv
```

Examples: `co2_20261005_classroom-minn011.csv`

## Column definitions

### CO₂ logger

| Column | Unit | Notes |
|---|---|---|
| `Time (seconds)` | s | **Inferred**, not measured: reading number × 10 s. Drifts behind real time if any reading fails |
| `CO2 (ppm)` | ppm | Parts per million by volume. Uncalibrated |


## Inventory

| File | Sensor | Date | Start time | Location | Duration | Conditions and events |
|---|---|---|---|---|---|---|
| `co_2_20261005_room.csv` | MH-Z19 | 05/10/2026 | 15:19 | Bedroom | 5:19:35 | Warm up time of 120s visible in data. One person in room at 0.5-1m distance, window & door closed. Sensor calibrated inside around 30 minutes before start of measurement. Breathed on sensor around t = 19157s (5:19:17) |

## Metadata to record for every run

Anything you cannot recover from the CSV afterwards:

- Date and **clock time** the run started (the CSV only has relative seconds)
- Room, building, and where in the room the sensor sat (height, distance from
  people, windows, radiators, ventilation outlets)
- Windows and doors open or closed
- Warm-up time allowed before the run
- Any deliberate perturbation, with its approximate timestamp
- Anything unusual: the board resetting, the LED stopping, cables being knocked
