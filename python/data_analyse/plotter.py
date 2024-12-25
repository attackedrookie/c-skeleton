import matplotlib.pyplot as plt
from abc import ABC, abstractmethod
from data import Data
import numpy as np

class Plotter(ABC):
    @abstractmethod
    def plot(self, data: Data, title: str = "Plot", xlabel: str = "X", ylabel: str = "Y") -> None:
        """绘图的抽象方法"""
        pass


class LinePlotter(Plotter):
    """绘制折线图"""
    def plot(self, data: Data, title: str = "Line Plot", xlabel: str = "X", ylabel: str = "Y") -> None:
        x, y = data.get_data()
        plt.plot(x, y)
        plt.title(title)
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)
        plt.grid(True)
        plt.show()


class ScatterPlotter(Plotter):
    """绘制散点图"""
    def plot(self, data: Data, title: str = "Scatter Plot", xlabel: str = "X", ylabel: str = "Y") -> None:
        x, y = data.get_data()
        plt.scatter(x, y)
        plt.title(title)
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)
        plt.grid(True)
        plt.show()


class DecibelPlotter(Plotter):
    """ 绘制分贝图"""
    def plot(self, data: Data, title: str = "Decibel Plot", xlabel: str = "X", ylabel: str = "Amplitude (dB)") -> None:
        x, y = data.get_data()
        dB = 20 * np.log10(np.abs(y))
        plt.plot(x, dB)
        plt.title(title)
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)
        plt.grid(True)
        plt.show()
