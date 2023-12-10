import numpy as np
import matplotlib.pyplot as plt
import serial
import time


sr = serial.Serial('COM5', 9600, timeout=1)
time.sleep(2)

t = np.linspace(0, 99, 100)
data0=np.zeros(100)
data1=np.zeros(100)
time.sleep(2)

plt.ion() #figure will be shown on creation
figure, ax = plt.subplots(figsize=(10, 4))
ax.set_ylim([200000, 900000])
chart0, = ax.plot(t, data0)
chart1, = ax.plot(t, data1)
time.sleep(1)

while True :
    sr.flushInput() # flush old dSata
    line = sr.readline() # read a line
    if line:
        string = line.decode()
        string = string.strip().split()
        
        if len(string)==2:
            val0,val1=int(string[0]),int(string[1])
            data0 = np.append(data0[1:], val0)
            data1 = np.append(data1[1:], val1)
            
            chart0.set_xdata(t)
            chart0.set_ydata(data0)
            
            chart1.set_xdata(t)
            chart1.set_ydata(data1)
            
            figure.canvas.draw()
            figure.canvas.flush_events()
            print(val0,"",val1)
            time.sleep(0.05)



#메모리에 그래프 그려라
#메모리에 그린 그래프 화면에 출력해라
