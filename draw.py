import matplotlib.pyplot as plt
import pandas as pd

# sep 控制分隔符
def draw_img(path:str) -> None:
    # 读取数据
    df = pd.read_csv(path, sep='\s+', dtype=int, names=['process', 'time', 'schedule'])
    
    proc_type = df['process'].unique().tolist()
    # proc_type.sort()

    lines = []

    # 选择不同的线程进行绘图
    for i in proc_type:
        # 1. 筛选对应线程
        tmp_df = df[df['process']==i]
        # 2. 画图
        line,  = plt.plot(tmp_df['time'], tmp_df['schedule'], '.', markersize=4)
        lines.append(line)
    
    # 绘制图例
    plt.ylim((0, 100 + 5))
    plt.xlim(0)

    plt.xlabel('time')
    plt.ylabel('schedule')

    plt.legend(handles=lines, labels=['proc'+str(i) for i in proc_type], loc='best')
    plt.show()

if __name__ == '__main__':
    # draw_img('./core2-proc1.log')
    # draw_img('./core2-proc2.log')
    # draw_img('./core2-proc4.log')
    draw_img('./core2-proc2-nice5.log')

    