# maze
【简单迷宫实现】

    の        三个固定案例，寻找出口
    のの      手动输入迷宫，寻找出口
    ののの    随机迷宫，寻找出口
    通过这三种实现简单的迷宫
    
【使用的技术】

    使用线程等待（表现出寻找的过程）
    使用定点刷新坐标（不是全屏刷新）
    使用基本数据结构--栈
    。。。。。。

【整体思路】

    ╋四个方向，从↖左上角  -----   ↘右下角
    先→  再↓  再←  最后↑
    其中 ▆表示：墙体
         の表示：路线
