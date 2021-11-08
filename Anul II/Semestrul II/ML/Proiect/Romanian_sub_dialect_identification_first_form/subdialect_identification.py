import numpy as np
import re
from sklearn import preprocessing
from sklearn import svm
import unicodedata
#pip install stop_words
indexes = []
import unicodedata
def remove_accents(input_str):
    nfkd_form = unicodedata.normalize('NFKD', input_str)
    return u"".join([c for c in nfkd_form if not unicodedata.combining(c)])

from stop_words import get_stop_words
stop_words = get_stop_words('romanian')
def model_stop_words(stop_words):
    new_stop_words = []
    for word in stop_words:
        new_stop_words.append(remove_accents(word))
    return new_stop_words

stop_words = model_stop_words(stop_words)

def normalize_data(train_data, test_data, type=None):
  scaler = None
  if type == 'standard':
      scaler = preprocessing.StandardScaler()
  elif type == 'min_max':
      scaler = preprocessing.MinMaxScaler()
  elif type == 'l1':
      scaler = preprocessing.Normalizer(norm='l1')
  elif type == 'l2':
      scaler = preprocessing.Normalizer(norm='l2')

  if scaler is not None:
      scaler.fit(train_data)
      scaled_train_data = scaler.transform(train_data)
      scaled_test_data = scaler.transform(test_data)
      return (scaled_train_data, scaled_test_data)
  else:
      print("No scaling was performed. Raw data is returned")
      return (train_data, test_data)


def split_into_words(list):
    copy_list = list[:]

    words = re.split(r"[”„“\"\'’;.,%!?#*&()$»><~`…€\s\n|$NE$]\s*" , copy_list)
    selected_words = []
    for word in words:
        if len(word) > 1 and word.isspace() == False:
            selected_words.append(word)

    return selected_words

def modify_labels_document(file):
    for lines in file:
        lines[0] = lines[1]
    file = np.resize(np.resize(file , (file.shape[0] , 1)) , file.shape[0]) [:]
    return file

class Bag_of_words:

  def __init__(self):
      self.vocabulary = {}
      self.words = []
      self.vocabulary_length = 0

  def build_vocabulary(self, data):
      for line in data:
          line = remove_accents(line)
          arr_of_words = split_into_words(line)

          for word in arr_of_words:
                  word = word.lower()
                  if word.isnumeric() == False and word not in self.vocabulary.keys() and word not in stop_words:
                      self.vocabulary[word] = len(self.vocabulary)
                      self.words.append(word)
      self.vocabulary_length = len(self.vocabulary)
      self.words = np.array(self.words)


  def get_features(self , data):
      features = np.zeros((len(data) , self.vocabulary_length) , dtype = 'uint8')
      i = 0
      for line in data:
          line = remove_accents(line)
          arr_of_words = split_into_words(line)
          arr_of_words.pop(0)
          for word in arr_of_words:
               word = word.lower()
               if word in self.vocabulary.keys():
                   features[i][self.vocabulary[word]] += 1
          i += 1
      return features




file = open('data/train_samples.txt' , encoding="utf8")
train_data = file.readlines()
bag_of_words = Bag_of_words()
bag_of_words.build_vocabulary(train_data)
print(bag_of_words.vocabulary_length)
#print("pe" in bag_of_words.words)
#print(train_features)

train_labels = np.loadtxt('data/train_labels.txt' , dtype = int)
train_labels = modify_labels_document(train_labels)[:30]

file = open('data/test_samples.txt' , encoding="utf8")
test_indexes = file.readlines()
file.close()
#file = open('/content/drive/My Drive/data/test_samples.txt' , encoding="utf8")
#validation_source_samples = file.readlines()
for line in test_indexes:
    arr = line.split()
    indexes.append(arr[0])

file = open('data/validation_target_samples.txt' , encoding="utf8")
validation_target_samples = file.readlines()
validation_target_labels = np.loadtxt('data/validation_target_labels.txt')
validation_target_labels = modify_labels_document(validation_target_labels)
#validation_source_labels = np.loadtxt('/content/drive/My Drive/data/validation_source_labels.txt' , dtype = int)
#validation_source_labels = modify_labels_document(validation_source_labels)

features_train = bag_of_words.get_features(train_data[:30])
features_test = bag_of_words.get_features(validation_target_samples)

normalized_train, normalized_test = normalize_data(features_train , features_test , "l2")
del features_train
del features_test
features_train = []
features_test = []

print("after normalize")
svm_model = svm.SVC(C = 1 , kernel = 'linear')
svm_model.fit(normalized_train , train_labels)
print("after fit")
predicted_labels_svm = svm_model.predict(normalized_test)
print(predicted_labels_svm)
print("after predicted")
'''
from google.colab import files  ### TREBUIE IMPORTAT

answer = [a + "," + str(b) for (a, b) in zip(indexes , predicted_labels_svm)]  # creeaza vector de stringuri, a = id, b = eticheta

file = open('answer.csv', 'w')  # creez fisier de tip csv
file.write('id,label\n')  # scriu in fisier "id" si "label"

for i in answer:
    file.write(i + "\n")  # scriu cate o linie

file.close()
files.download('answer.csv')  # downloadez fisierul
'''
from sklearn.metrics import f1_score
print('f1 score ' , f1_score(np.asarray(validation_target_labels) , predicted_labels_svm))









