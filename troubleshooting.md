# Troubleshooting

Problems we actually hit, and what fixed them. Add new entries as you find them. 

---

## Upload fails: `not in sync: resp=0x00` / `unable to open port COM3`

```
Sketch uses 13750 bytes (42%) of program storage space. Maximum is 32256 bytes.
Global variables use 1356 bytes (66%) of dynamic memory...
Warning: attempt 1 of 10: not in sync: resp=0x00
...
Error: unable to open port COM3 for programmer arduino
Failed uploading: uploading error: exit status 1
```

---
## CO2 sensor troubleshooting symptom and likely cause/fix
| Symptom | Likely cause / fix |
|---|---|
| Always -1 | Tx and Rx swapped (sensor Tx → Arduino RX pin, sensor Rx → Arduino TX pin, see [`hardware/wiring.md`](hardware/wiring.md)), wrong baud rate (must be 9600), or not powered |
| -2 | Wiring noise or loose connection; check the checksum |
| Reads exactly 400 or 410 ppm | Still warming up |
| Reads 0 or very low | Zero calibration was done in the wrong environment (e.g. an indoor room with high CO₂) or the HD pin touched GND by accident. Redo calibration outdoors (step B of the [experimental protocol](README.md#experimental-protocol)) |
| Readings jump around by hundreds of ppm | Sensor in a breath path or drafts |
| Upload fails | Something is attached to D0/D1; disconnect it |


## Template for new entries

```markdown
## Short description of the symptom

**Exact error message or observation:**

**Cause:**

**Fix:**

**Reported by / date:**
```
