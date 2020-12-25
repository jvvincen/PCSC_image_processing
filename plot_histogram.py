import numpy as np
import matplotlib.pyplot as plt


img_values = np.loadtxt("../histogram.txt", delimiter=",", dtype=str)
img_values = img_values[:-1].astype(int)


plt.hist(range(len(img_values)), weights=img_values, bins = 100)
plt.show()
