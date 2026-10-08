# Analysis

`plot_co2.py` plots a CO₂ log from `data/` (time in minutes vs ppm).

```bash
pip install -r analysis/requirements.txt
python analysis/plot_co2.py data/<file>.csv
```

The figure is saved to `analysis/figures/<file>.png`. Everything in `figures/`
is generated: never edit it by hand, re-run the script instead.

Tested with Python 3.13, numpy 2.5.3, matplotlib 3.11.2.
