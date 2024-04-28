import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import PercentFormatter
from matplotlib.pyplot import MultipleLocator, plot
from scipy.optimize import curve_fit
def exp_model(x, a):
    return np.array([1.0 - np.exp(a * (min_latency - i)) for i in x]).ravel()
filemeta = [
    {'name': './get_1.csv', 'client_num': 1, 'option': 'get'},
    {'name': './get_5.csv', 'client_num': 5, 'option': 'get'},
    {'name': './get_10.csv', 'client_num': 10, 'option': 'get'},
]
for f in filemeta:
    plt.clf()
    latency = pd.read_csv(f['name'],usecols=['latency']).apply(pd.to_numeric).values
    latency = (latency * 1000).ravel()
    latency.sort()
    min_latency = min(latency)
    # 设置百分位纵轴
    ax = plt.gca()
    # ax.xaxis.set_major_locator(MultipleLocator(5))
    ax.yaxis.set_major_formatter(PercentFormatter(xmax=1, decimals=1))
    # 避免横轴数据起始位置与纵轴重合，调整合适座标范围
    x_min = max(min(latency) * 0.8, min(latency) - 5)
    x_max = max(latency)
    plt.xlim(x_min, x_max)
    # 绘制实际百分位延迟
    # plt.hist(latency, color = f['color'], cumulative=True, histtype='step', weights=[1./ len(latency)] * len(latency))
    Percentage = np.array([1.0 * i / len(latency) for i in range(1, len(latency) + 1, 1)]) 
    # 排队论模型
    # F(t)=1-e^(-1*a*t)
    # alpha = 1.0 / np.mean(latency) #求平均值的倒数
    ideal_alpha = 1.0 / np.mean(latency)
    real_alpha, variance = curve_fit(exp_model, latency, Percentage)
    print("ideal_alpha: " + str(ideal_alpha))
    print("real_alpha: " + str(real_alpha))
    X_qt = np.arange(min(latency), max(latency), 1.)
    Y_qt = exp_model(X_qt, *real_alpha)
    # 绘制排队论模型拟合
    plt.scatter(latency, Percentage, marker='.')
    plt.plot(X_qt, Y_qt)
    plt.text(x_max - (x_max - x_min) / 5 , 0.2, 'variance: ' + '{:g}'.format(variance[0][0]), fontsize=10, color='black')
    plt.xlabel('Latency / ms')
    plt.ylabel('Percentage')
    plt.title(str(f['client_num']) + ' clients ' + f['option'] + ' tail latency')
    plt.grid()
    plt.savefig('./ClientNum' + str(f['client_num']) + '--TailLatency.png')

