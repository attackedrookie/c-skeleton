from data import Data
from plot_manager import PlotManager

if __name__ == "__main__":
    # 示例数据：二维数据
    x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    y = [1, 4, 9, 16, 25, 36, 49, 64, 81, 100] 
    data = [(x[i], y[i]) for i in range(len(x))]
    # 创建数据对象
    data = Data(data)
    
    # 归一化和标准化
    data.normalize()
    data.standardize()
    
    # 创建绘图管理器
    manager = PlotManager(data)
    
    # 绘制折线图
    manager.plot('line', title="Normalized and Standardized Line Plot", xlabel="X", ylabel="Y")
    
    # 绘制散点图
    manager.plot('scatter', title="Scatter Plot", xlabel="X", ylabel="Y")
    
    # 绘制分贝图
    manager.plot('dB', title="Decibel Plot", xlabel="X", ylabel="Amplitude (dB)")
