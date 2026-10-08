"""Plot a CO2 logger CSV.

Run from the repository root:
    python analysis/plot_co2.py data/<file>.csv
The figure is saved to analysis/figures/<file>.png
"""
import sys
from pathlib import Path

import numpy as np
import matplotlib.pyplot as plt

path = Path(sys.argv[1])
time_s, co2_ppm = np.loadtxt(path, delimiter=",", skiprows=1, unpack=True)

plt.figure(figsize=(10, 4))
plt.plot(time_s / 60, co2_ppm, linewidth=1)
plt.xlabel("Time (min)")
plt.ylabel("CO$_2$ (ppm)")
plt.title(path.name)
plt.grid(alpha=0.3)
plt.tight_layout()

out = Path(__file__).resolve().parent / "figures" / f"{path.stem}.png"
out.parent.mkdir(exist_ok=True)
plt.savefig(out, dpi=150)
print("Saved", out)
