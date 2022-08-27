import random
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime
from matplotlib.animation import FuncAnimation

plt.style.use('dark_background')
dt = datetime.now()
dt = dt.strftime('%X %x')
fig = plt.gcf()


def animate(i):
	data = pd.read_csv('data.csv')

	x = data['current_time']
	y1 = data['temperature']

	
	plt.cla()
	plt.ylim(23, 28)
	plt.plot(x, y1, label='Temperature')
	plt.rc('xtick', labelsize=5) 
	plt.xticks(rotation=90)

	plt.xlabel("Commenced reading at: " + dt)

	plt.ylabel('Temperature in Celcius')
	plt.title('Sensor Temperature Reading')

	plt.legend(loc='upper left')


ani = FuncAnimation(fig, animate, interval=1000)

plt.show()
