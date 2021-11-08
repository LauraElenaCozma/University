import numpy as np
import sklearn
import matplotlib.pyplot as plt
X = [ [0 , 0] , [0 , 1] , [1 , 0] , [1 , 1]]
Y = [-1 , 1 , 1 , -1]

X = np.array(X)
Y = np.array(Y)

num_epoch = 70
lr = 0.1
W = np.zeros((2 , 1))
B = 0 #bias
def compute_y(x, W, bias):
 # dreapta de decizie
 # [x, y] * [W[0], W[1]] + b = 0
 return (-x * W[0] - bias) / (W[1] + 1e-10)

def plot_decision_boundary(X, y , W, b, current_x, current_y):
 x1 = -0.5
 y1 = compute_y(x1, W, b)
 x2 = 0.5
 y2 = compute_y(x2, W, b)
 # sterge continutul ferestrei
 plt.clf()
 # ploteaza multimea de antrenare
 color = 'r'
 if(current_y == -1):
    color = 'b'
 plt.ylim((-1, 2))
 plt.xlim((-1, 2))
 plt.plot(X[y == -1, 0], X[y == -1, 1], 'b+')
 plt.plot(X[y == 1, 0], X[y == 1, 1], 'r+')
 # ploteaza exemplul curent
 plt.plot(current_x[0], current_x[1], color+'s')
 # afisarea dreptei de decizie
 plt.plot([x1, x2] ,[y1, y2], 'black')
 plt.show(block=False)
 plt.pause(0.3)

for ep in range(num_epoch):
    x , y = sklearn.utils.shuffle(X , Y)
    acc = 0
    for idx in range(len(y)): #trecem prin fievare sample
        yh = np.dot(x[idx] , W) + B
        if(np.sign(yh)[0] == y[idx]):
            acc += 1
        loss = (yh - y[idx]) ** 2 / 2
        W = W - lr * (yh - y[idx]) * x[idx]
        B = B - lr * (yh - y[idx])
        plot_decision_boundary(X, Y, W, B, x[idx] , y[idx])
   # accuracy = (np.sign(np.dot(x , W) + B) == y).mean()
    #calculam y si verificam daca e == y
    print('ep ' , ep)
    print('accuracy' , acc/4)
#acum vrem sa calculam si acuratetea

