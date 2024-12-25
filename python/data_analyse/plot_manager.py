from typing import List
from plotter import *
from data import Data

class PlotManager:
    def __init__(self, data: Data):
        self.data = data
        self.plotters = {
            'line': LinePlotter(),
            'scatter': ScatterPlotter(),
            'dB': DecibelPlotter()
        }

    def plot(self, plot_type: str, **kwargs) -> None:
        if plot_type in self.plotters:
            self.plotters[plot_type].plot(self.data, **kwargs)
        else:
            print(f"Unsupported plot type: {plot_type}")
