from sklearn.feature_extraction.text import TfidfVectorizer
from nltk.stem import SnowballStemmer
from sklearn import preprocessing
from sklearn import svm
from stop_words import get_stop_words
from sklearn.metrics import f1_score
import unicodedata

import re
import numpy as np

porter_stemmer = SnowballStemmer("romanian")


def modify_labels_document(file):
    labels = [file[x].split('\t')[1].replace("\n", '') for x in range(len(file))]
    labels = [int(label) for label in labels]
    return labels


# Function that opens a file (path) and returns a list of strings
def read(path):
    with open(path, encoding="utf-8") as file:
        x = file.readlines()
    return x


##############################

def replace_ne(line):
    return line.replace("$NE$", '')


def remove_accents(input_str):
    nfkd_form = unicodedata.normalize('NFKD', input_str)
    return u"".join([c for c in nfkd_form if not unicodedata.combining(c)])


stop_words = get_stop_words('romanian')


def model_stop_words(stop_words):
    new_stop_words = []
    for word in stop_words:
        new_stop_words.append(remove_accents(word))
    return new_stop_words


stop_words = model_stop_words(stop_words)


def process_sample(line):
    string_without_ne = replace_ne(line)
    string_without_ne = re.sub(r'[@„!?:#/”„&;”,\-\"\'.’’01234566789\s»>)(<%…“\n]\s*', " ", string_without_ne)
    string_without_accents = remove_accents(string_without_ne)
    string_without_numbers = re.sub(r'\d+', ' ', string_without_accents)
    lower_string = string_without_numbers.lower()
    words = re.split("\\s+", lower_string)
    stemmed_words = [porter_stemmer.stem(word=word) for word in words]
    last_string = ' '.join(stemmed_words)
    return lower_string



###############################
# Reads the samples

file = open('/content/drive/My Drive/data/train_samples.txt', encoding="utf8")
train_samples = file.readlines()
file = open('/content/drive/My Drive/data/test_samples.txt', encoding="utf8")
test_samples = file.readlines()

# Gets the ids for the test samples
indexes = [x for x in test_samples]
indexes = [int(x.split('\t')[0]) for x in indexes]

file = open('/content/drive/My Drive/data/validation_source_samples.txt', encoding="utf8")
validation_source_samples = file.readlines()
file = open('/content/drive/My Drive/data/validation_target_samples.txt', encoding="utf8")
validation_target_samples = file.readlines()

# Reads the labels, too, and generates a list of them
train_labels = read('/content/drive/My Drive/data/train_labels.txt')
train_labels = modify_labels_document(train_labels)

validation_source_labels = read('/content/drive/My Drive/data/validation_source_labels.txt')
validation_source_labels = modify_labels_document(validation_source_labels)

validation_target_labels = read('/content/drive/My Drive/data/validation_target_labels.txt')
validation_target_labels = modify_labels_document(validation_target_labels)

print("Converting the samples")

# Concaternates the training, validation and targets samples into one
train_samples = np.concatenate((train_samples, validation_source_samples, validation_target_samples))
train_labels = np.concatenate((train_labels, validation_source_labels, validation_target_labels))

print("l1 = " + str(len(train_samples)))
print("l2 = " + str(len(train_labels)))

# CountVectorizer used for the Bag Of Words
print("Started generating the dictionary")

cv = TfidfVectorizer(preprocessor=process_sample, max_features=40000, stop_words=stop_words, min_df=3, max_df=0.45,
                     norm='l1')  # token_pattern = r'\b[^\d\W]+\b'
train_data_vect = cv.fit_transform(train_samples)
print(cv.vocabulary_)

# process test_data

test_data_vect = []
for line in test_samples:
    test_data_vect.append(process_sample(line))
print("passed")
# transform test_data
test_data_vect = cv.transform(test_data_vect).toarray()

# process validation_source
validation_source_samples_vect = []
for line in validation_source_samples:
    validation_source_samples_vect.append(process_sample(line))
print("vs ", len(validation_source_samples_vect))

validation_source_samples_vect = cv.transform(validation_source_samples_vect).toarray()
'''
#scale data
scaler = preprocessing.Normalizer(norm = 'l1')
scaler.fit(train_data_vect)
scaled_train = scaler.transform(train_data_vect)
scaled_test = scaler.transform(test_data_vect)
#scale validation_source
scaled_validation_source = scaler.transform(validation_source_samples_vect)

print("after normalize")
'''

svm_model = svm.LinearSVC(C=50)
svm_model.fit(train_data_vect, train_labels)

print("after fit")
# predicted_labels_vt_svm = svm_model.predict(scaled_validation_target)
# print(predicted_labels_vt_svm)
print("after predicted 1")
predicted_labels_vs_svm = svm_model.predict(validation_source_samples_vect)

# predict test_data labels
predicted_labels_test_svm = svm_model.predict(test_data_vect)
print(predicted_labels_test_svm)

from sklearn.metrics import f1_score

# print('f1 score ' , f1_score(np.asarray(validation_target_labels) , predicted_labels_vt_svm))
print('f1 score ', f1_score(np.asarray(validation_source_labels), predicted_labels_vs_svm))

from google.colab import files  ### TREBUIE IMPORTAT

answer = [str(a) + "," + str(int(b)) for (a, b) in
          zip(indexes, predicted_labels_test_svm)]  # creeaza vector de stringuri, a = id, b = eticheta

file = open('/content/drive/My Drive/data/resulttfidf.csv', 'w')  # creez fisier de tip csv
file.write('id,label\n')  # scriu in fisier "id" si "label"

for i in answer:
    file.write(i + "\n")  # scriu cate o linie

file.close()
files.download('/content/drive/My Drive/data/resulttfidf.csv')  # downloadez fisierul
