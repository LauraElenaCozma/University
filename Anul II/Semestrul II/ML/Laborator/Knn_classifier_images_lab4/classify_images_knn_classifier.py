import numpy as np
import matplotlib.pyplot as plt
class KnnClassifier:
    def __init__(self , train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels

    #function that classify a test_image
    def classify_image(self , test_image , num_neighbors = 3 , metric = 'l2'):
        # L1(𝑋, 𝑌) = ∑|𝑋𝑖 − 𝑌𝑖|
        # 𝐿2(𝑋, 𝑌) = √∑(𝑋𝑖 − 𝑌𝑖)^2
        if metric == 'l2':
            distances = np.sqrt(np.sum((self.train_images - test_image) ** 2 , axis = 1)) #adica ramanem cu un vector de 1000 de valori
            # reprezentand distantele dintre train si test, fiecare pereche
        elif metric == 'l1':
            distances = np.sum(abs(self.train_images - test_image) , axis = 1)
        else:
            print("Metric is not defined")
        ind_min_values = distances.argsort()[:num_neighbors] #the indexes of the first num_neighbors minimum values in distance
        #indicii cu cele mai mici distante
        #luam etichetele corespunzatoare acelor imagini de antrenare si vedem care apare cel mai des
        frequency = np.bincount(train_labels[ind_min_values]) #face un vector de frecventa
        classify = np.argmax(frequency) #returneaza indicele cu cea mai mare frecventa, deci cifra care aparea cel mai des
        return classify

    def classify_images(self , test_images , num_neighbors = 3 , metric = 'l2'):
        size = test_images.shape[0] #luam prima dimensiune, adica 500 de linii
        predictions = np.zeros(size)
        for i in range(size):
            predictions[i] = self.classify_image(test_images[i] , num_neighbors , metric)
        return predictions

    def accuracy(self , y_pred , y_test):
        return (y_pred == y_test).mean() #adica numarul cazurilor in care sunt prezise bine/numarul total de preziceri = aacuratete



#2. Calculați acuratețea metodei celor mai apropiați vecini pe mulțimea de testare
#având ca distanța ‘l2’ și numărul de vecini 3. Salvați predicțiile în fișierul predictii_3nn_l2_mnist.txt.
# incarcam imaginile
train_images = np.loadtxt('data/train_images.txt')
train_labels = np.loadtxt('data/train_labels.txt', 'int')
test_images = np.loadtxt('data/test_images.txt')
test_labels = np.loadtxt('data/test_labels.txt' , 'int')

classifier = KnnClassifier(train_images , train_labels)
predicted_labels = classifier.classify_images(test_images, 3, 'l2')
f = open("predictii_3nn_l2_mnist.txt", "w+")
f.write(str(predicted_labels))
accuracy_for_images = classifier.accuracy(predicted_labels , test_labels)
print(accuracy_for_images)

#3. Calculați acuratețea metodei celor mai apropiați vecini pe mulțimea de testare având ca distanța L2 și numărul de vecini ∈ [1, 3, 5, 7, 9].
#a. Plotați un grafic cu acuratețea obținuta pentru fiecare vecin și salvați scorurile în fișierul acuratete_l2.txt.
num_neighbors = np.array([1 , 3 , 5 , 7 , 9])
acc = np.zeros(num_neighbors.shape[0])
for i in range(len(num_neighbors)):
    pred_labels = classifier.classify_images(test_images , num_neighbors[i] , 'l2')
    acc[i] = classifier.accuracy(pred_labels , test_labels)
print(acc)
np.savetxt('acuratete_l2.txt', acc)
plt.plot(num_neighbors , acc)
plt.xlabel("Num. of neighbors")
plt.ylabel("Accuracy")
plt.title("Knn Classifier")
plt.show()

#Repetați punctul anterior pentru distanța L1. Plotați graficul de la punctul anterior în aceeași figură cu graficul curent
acc = np.zeros(num_neighbors.shape[0])
for i in range(len(num_neighbors)):
    pred_labels = classifier.classify_images(test_images , num_neighbors[i] , 'l1')
    acc[i] = classifier.accuracy(pred_labels , test_labels)

#afiseaza pe acelasi grafic
acc_l2 = np.loadtxt('acuratete_l2.txt')
np.savetxt('acuratete_l1' , acc)
plt.plot(num_neighbors , acc_l2)
plt.plot(num_neighbors , acc)
plt.xlabel("Num. of neighbors")
plt.ylabel("Accuracy")
plt.title("Knn Classifier")
plt.legend(["L2" , "L1"])
plt.show()

#IF YOU WANT TO PRINT AN IMAGE
#image = test_images[0]
#image = np.reshape(image, (28, 28))
#plt.imshow(image.astype(np.uint8), cmap='gray') #cmap = 'gray' ca sa fie alb negru
#plt.show()