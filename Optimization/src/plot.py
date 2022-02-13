import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

from sys import argv

loss_x = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Output/loss_x.txt"
loss_xy = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Output/loss_xy.txt"
loss_rxy = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Output/loss_rotation.txt"
gradient_descent = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Output/gradient_descent.txt"
def one_parameter_plot(file,label):
    
    data = pd.read_table(file, sep = ",")
    data.plot(x = label, y = "loss", kind = 'line')
    
    plt.savefig("grad_descent_3_-25")
    plt.show();
    return

def two_parameter_plot(file):
    
    x,y,z = np.loadtxt(file, unpack=True)
    fig = plt.figure()
    ax = Axes3D(fig)
    surf = ax.plot_trisurf(x, y, z,linewidth=0.1)
    plt.savefig("Loss function")
    plt.show()
    return
    
# one_parameter_plot(loss_x,"tx")

# two_parameter_plot(loss_xy)

# one_parameter_plot(loss_rxy,"r")

one_parameter_plot(gradient_descent,"tx")