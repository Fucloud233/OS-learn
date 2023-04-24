import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import pprint 

# sep 控制分隔符
def draw_img(path:str) -> None:
    # 读取数据
    df = pd.read_csv(path, sep='\s+', dtype=float, header=None)
    data = df.to_numpy()
    sample_len = data.shape[1]

    num = data[:, 0]
    thread_type = np.unique(num)
    n = data[:, 1]
    
    # var = np.var(data[:, 2:len], axis=1)
    # pprint.pprint(var)
    time = np.mean(data[:, 2:sample_len], axis=1)

    max_n = int(len(time) / len(thread_type))
    # max_n = 5

    lines = []
    for i in thread_type:
        x = n[num==i][0:max_n]
        y = time[num==i][0:max_n]
        
        line,  = plt.plot(x, y, '.-', markersize=4)
        lines.append(line)
    
    plt.legend(handles=lines, labels=['num='+str(int(i)) for i in thread_type], loc='best')

    plt.ylim(0, )
    plt.xlim(0, )
    plt.xlabel("n")
    plt.ylabel("time/ms")

    plt.show()

if __name__ == '__main__':
    draw_img('./record.log')

    