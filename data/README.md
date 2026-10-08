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

_TODO: one row per file. Fill in as you collect data._

| File | Sensor | Date | Start time | Location | Duration | Conditions and events |
|---|---|---|---|---|---|---|
| `TODO.csv` | MH-Z19 | TODO | TODO | TODO | TODO | e.g. "exhaled onto sensor at t ≈ 180 s; 4 people in room, window closed" |
| `TODO.csv` | P/T/RH logger  | TODO | TODO | TODO | TODO | TODO |

## Metadata to record for every run

Anything you cannot recover from the CSV afterwards:

- Date and **clock time** the run started (the CSV only has relative seconds)
- Room, building, and where in the room the sensor sat (height, distance from
  people, windows, radiators, ventilation outlets)
- Windows and doors open or closed
- Warm-up time allowed before the run
- Any deliberate perturbation, with its approximate timestamp
- Anything unusual: the board resetting, the LED stopping, cables being knocked
