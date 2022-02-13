import numpy as np
import matplotlib.pyplot as plt



list = np.array(np.linspace(0,70,1000))

# plt.plot(list,1-pow(list/70,20) * (list<=70),label = 'best function with a = 70 and n = 30')
# plt.plot(list,np.exp(-pow(0.05*list,2)), label = 'gaussian')
plt.plot(list,(1/(pow(2*list,2*0.1)) + 1)/2.5, label = 'inverse')


plt.legend()
plt.savefig("gaussian.png")
plt.show()