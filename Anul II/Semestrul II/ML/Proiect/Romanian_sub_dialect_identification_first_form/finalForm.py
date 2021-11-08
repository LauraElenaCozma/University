from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn import preprocessing
from sklearn import svm
from sklearn.metrics import f1_score
from sklearn.svm import SVC


import re
import numpy as np


def modify_labels_document(file):
    labels = [file[x].split('\t')[1].replace("\n", '') for x in range(len(file))]
    labels = [int(label) for label in labels]
    return labels


def process_sample(line):
    string_without_index = re.sub(r'\d+', ' ', line)  #remove the index
    #words = re.split("\\s+", string_without_index) #split by regular expression #r"[ \s]\s*"
    #converted_line = ' '.join(words) #recreate the line
    return string_without_index


# Reads the samples

file = open('/content/drive/My Drive/data/train_samples.txt', encoding="utf8")
train_samples = file.readlines()
file = open('/content/drive/My Drive/data/test_samples.txt', encoding="utf8")
test_samples = file.readlines()

# Gets the ids for the test samples
indexes = []
for index in test_samples:
  indexes.append(index.split('\t' , 1)[0])

file = open('/content/drive/My Drive/data/validation_samples.txt', encoding="utf8")
validation_samples = file.readlines()

# Reads the labels, too, and generates a list of them
file = open('/content/drive/My Drive/data/train_labels.txt', encoding="utf8")
train_labels = file.readlines()
train_labels = modify_labels_document(train_labels)

file = open('/content/drive/My Drive/data/validation_labels.txt', encoding="utf8")
validation_labels = file.readlines()
validation_labels = modify_labels_document(validation_labels)

print("Converting the samples")

# Concaternates the training, validation and targets samples into one
train_samples = np.concatenate((train_samples, validation_samples))
train_labels = np.concatenate((train_labels, validation_labels))

print("l1 = " + str(len(train_samples)))

# Tfidf for Bag of Words
print("Started generating the dictionary...")
cv = TfidfVectorizer(preprocessor = process_sample , norm='l2' , lowercase = False , token_pattern = r"\S\S+")  #(?u) token_pattern captures consecutive non white space characters as a single word
train_data_vect = cv.fit_transform(train_samples)
print(cv.vocabulary_)

# process test_data
'''
test_data_vect = []
for line in test_samples:
    test_data_vect.append(process_sample(line))
'''
test_data_vect = cv.transform(test_samples)
test_data_vect = test_data_vect.toarray() #now test_data_vect is a matrix of features

# process validation_target
'''
validation_samples_vect = []
for line in validation_samples:
    validation_samples_vect.append(process_sample(line))
print("vs ", len(validation_samples_vect))
'''
validation_samples_vect = cv.transform(validation_samples)
validation_samples_vect = validation_samples_vect.toarray()
print(validation_samples_vect)

from sklearn.naive_bayes import ComplementNB
clf = ComplementNB(alpha = 0.2)
clf.fit(train_data_vect, train_labels)
predicted_labels_vt_svm = clf.predict(validation_samples_vect)
predicted_labels_test_svm = clf.predict(test_data_vect)


from sklearn.metrics import f1_score

print('f1 score target ' , f1_score(np.asarray(validation_labels) , predicted_labels_vt_svm))

from google.colab import files  ### TREBUIE IMPORTAT

answer = [str(a) + "," + str(int(b)) for (a, b) in
          zip(indexes, predicted_labels_test_svm)]  # creeaza vector de stringuri, a = id, b = eticheta

file = open('/content/drive/My Drive/data/test3.csv', 'w')  # creez fisier de tip csv
file.write('id,label\n')  # scriu in fisier "id" si "label"

for i in answer:
    file.write(i + "\n")  # scriu cate o linie

file.close()
files.download('/content/drive/My Drive/data/test3.csv')  # downloadez fisierul

#####0.74343 for alpha = 0.2