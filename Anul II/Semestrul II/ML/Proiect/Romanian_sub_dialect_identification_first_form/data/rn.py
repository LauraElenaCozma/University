from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn import preprocessing
from sklearn.metrics import f1_score
from sklearn.neural_network import MLPClassifier  # importul clasei


import re
import numpy as np


def modify_labels_document(file):
    labels = [file[x].split('\t')[1].replace("\n", '') for x in range(len(file))]
    labels = [int(label) for label in labels]
    return labels


# Function that opens a file (path) and returns a list of strings
def read(path):
    with open(path, encoding="utf-8") as file:
        x = file.readlines()
    return x



def process_sample(line):
    string_without_index = re.sub(r'\d+', ' ', line)  #remove the index
    words = re.split("\\s+", string_without_index) #split by regular expression #r"[ \s]\s*"
    converted_line = ' '.join(words) #recreate the line
    return converted_line


# Reads the samples

file = open('/content/drive/My Drive/data/train_samples.txt', encoding="utf8")
train_samples = file.readlines()
file = open('/content/drive/My Drive/data/test_samples.txt', encoding="utf8")
test_samples = file.readlines()

# Gets the ids for the test samples
indexes = [x for x in test_samples]
indexes = [int(x.split('\t')[0]) for x in indexes]

file = open('/content/drive/My Drive/data/validation_samples.txt', encoding="utf8")
validation_samples = file.readlines()

# Reads the labels, too, and generates a list of them
train_labels = read('/content/drive/My Drive/data/train_labels.txt')
train_labels = modify_labels_document(train_labels)

validation_labels = read('/content/drive/My Drive/data/validation_labels.txt')
validation_labels = modify_labels_document(validation_labels)

print("Converting the samples")

# Concaternates the training, validation and targets samples into one
#train_samples = np.concatenate((train_samples, validation_samples))
#train_labels = np.concatenate((train_labels, validation_labels))

print("l1 = " + str(len(train_samples)))

# CountVectorizer used for the Bag Of Words
print("Started generating the dictionary")
cv = TfidfVectorizer(preprocessor = process_sample , norm='l2' , lowercase = False , token_pattern = r"(?u)\S\S+")  #
train_data_vect = cv.fit_transform(train_samples)
print(cv.vocabulary_)
print(len(cv.vocabulary_))

# process test_data

test_data_vect = []
for line in test_samples:
    test_data_vect.append(process_sample(line))
print("passed")
print(test_data_vect)

# transform test_data
test_data_vect = cv.transform(test_data_vect).toarray() #now test_data_vect is a matrix of features
print(test_data_vect)

# process validation_target
validation_samples_vect = []
for line in validation_samples:
    validation_samples_vect.append(process_sample(line))
print("vs ", len(validation_samples_vect))
validation_samples_vect = cv.transform(validation_samples).toarray()
print(validation_samples_vect)



def train_and_test_the_model(model, train_features, train_labels, test_features, test_labels):
    print('training...')
    model.fit(train_features, train_labels)
    print('testing...')
    print('plain - acuratetea pe multimea de antrenare este ', model.score(train_features, train_labels))
    print('acuratetea pe multimea de testare este ', model.score(test_features, test_labels))
    print('numarul de iteratii parcurse pana la convergenta %d' % model.n_iter_)


mlp_classifier_model = MLPClassifier(hidden_layer_sizes=(20), activation='relu', solver='sgd', learning_rate_init=0.006, momentum=0.9, max_iter=200, alpha=0.003)#, early_stopping = True, tol=1e-17, n_iter_no_change=50
train_and_test_the_model(mlp_classifier_model, train_data_vect, train_labels, validation_samples_vect, validation_labels)

predicted_labels_vt_svm = mlp_classifier_model.predict(validation_samples_vect)
predicted_labels_test_svm = mlp_classifier_model.predict(test_data_vect)


from sklearn.metrics import f1_score

print('f1 score target ' , f1_score(np.asarray(validation_labels) , predicted_labels_vt_svm))

from google.colab import files  ### TREBUIE IMPORTAT

answer = [str(a) + "," + str(int(b)) for (a, b) in
          zip(indexes, predicted_labels_test_svm)]  # creeaza vector de stringuri, a = id, b = eticheta

file = open('/content/drive/My Drive/data/resultrn.csv', 'w')  # creez fisier de tip csv
file.write('id,label\n')  # scriu in fisier "id" si "label"

for i in answer:
    file.write(i + "\n")  # scriu cate o linie

file.close()
#files.download('/content/drive/My Drive/data/result302.csv')  # downloadez fisierul
---------0.67 :(