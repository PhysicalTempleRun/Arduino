
import numpy as np
import matplotlib.pyplot as plt
import serial
import time
sr = serial.Serial('COM5', 9600, timeout=1)
time.sleep(2)
t = np.linspace(0, 99, 100)
data = np.zeros(100)
plt.ion() #figure will be shown on creation
figure, ax = plt.subplots(figsize=(10, 4))
#ax.set_ylim([200000, 600000]) #왼발발판용
ax.set_ylim([400000, 900000]) #왼발발판용

#ax.set_ylim([-100, 100]) #오른발발판용
chart, = ax.plot(t, data)

while True :
    sr.flushInput() # flush old data
    line = sr.readline() # read a line
    if line:
        string = line.decode()
        string = string.strip()
        if string != "":
            num = int(string)
            
            #아래는 자이로 센서 테스트할때 사용
            #num = float(string)
            data = np.append(data[1:], num)
            chart.set_xdata(t)
            chart.set_ydata(data)
            figure.canvas.draw()
            figure.canvas.flush_events()
            print(num)
            time.sleep(0.05)