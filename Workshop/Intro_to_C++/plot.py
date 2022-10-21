import matplotlib
import matplotlib.pyplot as plt
from data1 import *

FS = 15
matplotlib.rcParams.update({'font.size': FS})

fig, axs = plt.subplots(1,1, figsize = [5,5])

axs.plot(x_range, fx_range)

axs.set_xlabel('$x$')
axs.set_ylabel('$f(x)$')
axs.xaxis.set_tick_params(direction= 'in', which='both', right =True, top = True)
axs.yaxis.set_tick_params(direction= 'in', which='both', right =True, top = True)


plt.savefig('test.png',bbox_inches = 'tight', pad_inches = 0.05)
