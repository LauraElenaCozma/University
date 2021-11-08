## EX 1

from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt
import pdb
from sklearn.linear_model import Perceptron


def plot3d_data(X, y):
    ax = plt.axes(projection='3d')
    ax.scatter3D(X[y == -1, 0], X[y == -1, 1], X[y == -1, 2], 'b');
    ax.scatter3D(X[y == 1, 0], X[y == 1, 1], X[y == 1, 2], 'r');
    plt.show()


def plot3d_data_and_decision_function(X, y, W, b):
    ax = plt.axes(projection='3d')
    # create x,y
    xx, yy = np.meshgrid(range(10), range(10))
    # calculate corresponding z
    # [x, y, z] * [coef1, coef2, coef3] + b = 0
    zz = (-W[0] * xx - W[1] * yy - b) / W[2]
    ax.plot_surface(xx, yy, zz, alpha=0.5)
    ax.scatter3D(X[y == -1, 0], X[y == -1, 1], X[y == -1, 2], 'b');
    ax.scatter3D(X[y == 1, 0], X[y == 1, 1], X[y == 1, 2], 'r');
    plt.show()


# load data
X = np.loadtxt('./data/3d-points/x_train.txt')
y = np.loadtxt('./data/3d-points/y_train.txt').astype(int)

# plot3d_data(X, y)

# train perceptron
perceptron_model = Perceptron(eta0=0.01, tol=1e-6, early_stopping=True, n_iter_no_change=5)
# antrenarea
perceptron_model.fit(X, y)

print('acuratetea pe multimea de antrenare este de:', perceptron_model.score(X, y))
print('ponderile invatate sunt:', perceptron_model.coef_)
print('bias-ul este: ', perceptron_model.intercept_)
print('epocile parcurse', perceptron_model.n_iter_)

X_test = np.loadtxt('./data/3d-points/x_test.txt')
y_test = np.loadtxt('./data/3d-points/y_test.txt').astype(int)
print('acuratetea pe multimea de testare este de:', perceptron_model.score(X_test, y_test))
print('_________________')
# plot3d_data_and_decision_function(X, y, np.squeeze(perceptron_model.coef_), perceptron_model.intercept_)

// // // // // // // // / ex2

import timeit
from numpy import linalg as LA
from sklearn import preprocessing

from sklearn.neural_network import MLPClassifier  # importul clasei
import numpy as np


def l2_normalization(X):
    norm = LA.norm(X, axis=1, keepdims=True)
    return np.divide(X, norm)


train_features = np.loadtxt('data/MNIST/train_images.txt')
train_labels = np.loadtxt('data/MNIST/train_labels.txt').astype(int)
# normalizare
scaler = preprocessing.StandardScaler()
scaler.fit(train_features)

train_features = scaler.transform(train_features)
test_features = np.loadtxt('data/MNIST/test_images.txt')
test_labels = np.loadtxt('data/MNIST/test_labels.txt').astype(int)
# normalizare
test_features = scaler.transform(test_features)
print(train_features.shape)


def train_and_test_the_model(model, train_features, train_labels, test_features, test_labels):
    print('training...')
    start_time = timeit.default_timer()
    model.fit(train_features, train_labels)
    end_time = timeit.default_timer()
    print('proccesing time: in seconds', (end_time - start_time))
    print('testing...')
    print('plain - acuratetea pe multimea de antrenare este ', model.score(train_features, train_labels))
    print('acuratetea pe multimea de testare este ', model.score(test_features, test_labels))
    print('numarul de iteratii parcurse pana la convergenta %d' % model.n_iter_)


# mlp_classifier_model = MLPClassifier(hidden_layer_sizes=(1), activation='tanh', solver='sgd', learning_rate_init=0.01, momentum=0)
# mlp_classifier_model = MLPClassifier(hidden_layer_sizes=(10), activation='tanh', solver='sgd', learning_rate_init=0.01, momentum=0)
# mlp_classifier_model = MLPClassifier(hidden_layer_sizes=(10), activation='tanh', solver='sgd', learning_rate_init=0.01, momentum=0, max_iter=20)

mlp_classifier_model = MLPClassifier(hidden_layer_sizes=(100), activation='tanh', solver='sgd', learning_rate_init=0.01,
                                     momentum=0, max_iter=200)
# mlp_classifier_model = MLPClassifier(hidden_layer_sizes=(100, 100), activation='relu', solver='sgd', learning_rate_init=0.01, momentum=0, max_iter=2000)
# mlp_classifier_model = MLPClassifier(hidden_layer_sizes=(100, 100), activation='relu', solver='sgd', learning_rate_init=0.01, momentum=0.9, max_iter=2000, alpha=0.005)
train_and_test_the_model(mlp_classifier_model, train_features, train_labels, test_features, test_labels)