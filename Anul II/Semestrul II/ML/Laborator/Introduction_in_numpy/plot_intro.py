import matplotlib.pyplot as plt
import numpy as np
x = np.arange(0, 3 * np.pi, 0.2) #valori intre 0 si 3pi cu pas 0.2
y = np.sin(x)
z = np.cos(x)

plt.plot(x , y)
plt.plot(x , z)
plt.title("Reprezentare sinus si cos")
plt.xlabel("x axis")
plt.ylabel("y axis")
plt.legend(["Sin" , "Cos"])
plt.show()


first_plot = plt.figure(1)
plt.plot(x , y)
second_plot = plt.figure(2)
plt.plot(x , z)
plt.show()