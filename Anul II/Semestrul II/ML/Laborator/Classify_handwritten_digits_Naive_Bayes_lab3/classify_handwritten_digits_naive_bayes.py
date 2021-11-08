import numpy as np
import matplotlib.pyplot as plt



#image = train_images[23, :] # prima imagine = prima linie a matricei
#image = np.reshape(image, (28, 28))
#plt.imshow(image.astype(np.uint8), cmap='gray') #cmap = 'gray' ca sa fie alb negru
#plt.show()


#1. Știind că valoarea minimă a unui pixel este 0, iar valoarea maximă este 255,
#calculați capetele a num_bins intervale (utilizați funcția linspace). Definiți
#metoda values_to_bins care primește o matrice de dimensiune (n_samples,
#n_features) și capetele intervalelor calculate anterior, iar pentru fiecare
#exemplu și fiecare atribut calculează indexul intervalului corespunzător(utilizați funcția np.digitize).

def intervals(num_bins):
    bins = np.linspace(start = 0, stop = 255, num = num_bins)  # divide into intervals
    return bins

def values_to_bins(image , bins):
    x_to_bins = np.digitize(image , bins) - 1 # returneaza pentru fiecare element intervalul corespunzator
    #daca un pixel ar avea o valoare mai mica ca 0, atunci ar returna 0
    #daca pixel > 255, returneaza num
    # Atentie! In cazul nostru indexarea elementelor va
    # incepe de la 1, intrucat nu avem valori < 0
    return x_to_bins

num_bins = 5
bins = intervals(num_bins)

#pentru np.loadtxt fisierul trebuie sa aiba aceeasi dimensiune pe fiecare linie
train_images = np.loadtxt('data/train_images.txt') # incarcam imaginile
train_labels = np.loadtxt('data/train_labels.txt', 'int') # incarcam etichetele avand
# tipul de date int(implicit e float)
test_images = np.loadtxt('data/test_images.txt')
test_labels = np.loadtxt('data/test_labels.txt' , 'int')

train_to_bins = values_to_bins(train_images , bins) #vector cu pixelii incadrati in intervale
print(train_to_bins)

test_to_bins = values_to_bins(test_images , bins)
print(test_to_bins)

#2. Calculați acuratețea pe mulțimea de testare a clasificatorul Multinomial Naive
# Bayes, împărținând intervalul pixelilor în 5 sub-intervale
#pip install scikit-learn
#trebuie sa calculam P(c/X) pentru fiecare c = clasa
#adica probabilitatea ca X sa apartina clasei c
#P(x/c) probabilitatea de a avea atributul x in clasa c = numarul exemplelor din clasa c care sunt egale cu x/nr exemple clasa c
#P(c) probabilitatea ca un exemplu sa se afle in clasa c = numarul exemplelor din clasa c/numarul total de exemple
from sklearn.naive_bayes import MultinomialNB
naive_bayes_model = MultinomialNB() #am definit un model
naive_bayes_model.fit(train_to_bins, train_labels) #antrenam modelul; learns the vocabulary of the training data
print("etichete " , naive_bayes_model.predict(test_to_bins)) #prezicem etichetele
print("accuracy " , naive_bayes_model.score(test_to_bins , test_labels)) #calculam acuratetea

#3. Testați clasificatorul Multinomial Naive Bayes pe subsetul MNIST folosind𝑛𝑢𝑚_𝑏𝑖𝑛𝑠 ∈ {3, 5, 7, 9, 11}
def multinomNB(num_bins , train_images , train_labels , test_images , test_labels):
    bins = intervals(num_bins)
    train_to_bins = values_to_bins(train_images, bins)  # vector cu pixelii incadrati in intervale
    test_to_bins = values_to_bins(test_images , bins)
    naive_bayes_model = MultinomialNB()
    naive_bayes_model.fit(train_to_bins, train_labels)
    prediction = naive_bayes_model.predict(test_to_bins)
    score = naive_bayes_model.score(test_to_bins, test_labels)
    return score , prediction

num_bins = np.array([3 , 5 , 7 , 9 , 11])
print("The accuracy scores are: ")
for value in num_bins:
    score , pred = multinomNB(value , train_images , train_labels , test_images , test_labels)
    print(score)

#4. Folosind numărul de sub-intervale care obține cea mai bună acuratețe la
# exercițiul anterior, afișați cel puțin 10 exemple misclasate.
def printWrongAnswers(bestBin):
    stop = 10
    score , pred = multinomNB(bestBin, train_images, train_labels, test_images, test_labels)
    for index in range(len(test_labels)):
        if stop!= 0:
            if test_labels[index] != pred[index]:
                print("Predicted as " + str(pred[index]) + " and the real value is " + str(test_labels[index]))
                image = test_images[index , :] # prima imagine = prima linie a matricei
                image = np.reshape(image, (28, 28))
                plt.imshow(image.astype(np.uint8), cmap='gray') #cmap = 'gray' ca sa fie alb negru
                plt.show()
                stop -= 1

bestBin = 11
printWrongAnswers(bestBin)

#5. Definiți metoda confusion_matrix(y_true, y_pred) care calculează matricea de
#confuzie. Calculați matricea de confuzie folosind predicțiile clasificatorului anterior.

def confusion_matrix(y_true , y_pred):
    num_classes = max(y_true.max(), y_pred.max()) + 1
    matrix = np.zeros((num_classes, num_classes))
    for index in range(len(y_true)):
        matrix[int(y_true[index]) , int(y_pred[index])] += 1

    return matrix

score , pred_labels = multinomNB(bestBin, train_images, train_labels, test_images, test_labels)
print(confusion_matrix(test_labels , pred_labels))