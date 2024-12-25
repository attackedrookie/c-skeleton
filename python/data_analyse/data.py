import numpy as np
from typing import List, Tuple

class Data:
    def __init__(self,data:List[Tuple[float,float]]):
        self.x = np.array([d[0] for d in data])
        self.y = np.array([d[1] for d in data])

    def get_data(self) -> Tuple[np.ndarray, np.ndarray]:
        return self.x, self.y

    def normalize(self) -> None:
        """归一化数据到 [0, 1] 范围"""
        min_x, max_x = np.min(self.x), np.max(self.x)
        min_y, max_y = np.min(self.y), np.max(self.y)
        self.x = (self.x - min_x) / (max_x - min_x)
        self.y = (self.y - min_y) / (max_y - min_y)

    def standardize(self) -> None:
        """标准化数据到均值为0，方差为1"""
        mean_x, std_x = np.mean(self.x), np.std(self.x)
        mean_y, std_y = np.mean(self.y), np.std(self.y)
        self.x = (self.x - mean_x) / std_x
        self.y = (self.y - mean_y) / std_y

    def calculate_average(self) -> Tuple[float,float]:
        """计算数据的平均值"""
        return (self.x.sum/self.x.__len__,self.y.sum/self.y.__len__)

    def calculate_variance(self) -> float:
        """计算数据的方差"""
        return np.var(self.data)

    def calculate_slope(self) -> float:
        """计算数据的斜率"""
        x = np.arange(len(self.data))
        y = self.data
        slope, _ = np.polyfit(x, y, 1)  # 通过拟合直线计算斜率
        return slope

    # def remove_outliers(self) -> Tuple[float]:
    #     """莱利准则去除粗大误差"""
    #     beta = self.calculate_variance
    #     for(x,y in self.x,self.y)