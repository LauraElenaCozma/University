import numpy as np
from sklearn import preprocessing
from sklearn import svm

np_load_old = np.load
np.load = lambda *a, **k: np_load_old(*a, allow_pickle=True, **k)

# loading data
training_data = np.load('data/training_sentences.npy')
training_labels = np.load('data/training_labels.npy')

test_data = np.load('data/test_sentences.npy')
test_labels = np.load('data/test_labels.npy')


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


#########
print(test_labels)
class Bag_of_words:

  def __init__(self):
      self.vocabulary = {}
      self.words = []
      self.vocabulary_length = 0

  def build_vocabulary(self, data):

      for document in data:
          for word in document:
              if word not in self.vocabulary.keys():
                  self.vocabulary[word] = len(self.vocabulary)
                  self.words.append(word)

      self.vocabulary_length = len(self.vocabulary)
      self.words = np.array(self.words)

  def get_features(self, data):
      features = np.zeros((len(data) , self.vocabulary_length))
      for i in range(len(data)):
        for word in data[i]:
          if word in self.words:
            features[i][self.vocabulary[word]] += 1
      return features


bow_model = Bag_of_words()
bow_model.build_vocabulary(training_data)
print(bow_model.get_features(training_data))

# get features
features_train = bow_model.get_features(training_data)
features_test = bow_model.get_features(test_data)

normalized_train, normalized_test = normalize_data(features_train, features_test, "l2")
print(normalized_train)
print(normalized_test)

svm_model = svm.SVC(C = 1 , kernel = 'linear')
svm_model.fit(normalized_train , training_labels)
predicted_labels_scm = svm_model.predict(normalized_test)

from sklearn.metrics import f1_score

def compute_accuracy(gt_labels , predicted_labels):
  accuracy = np.sum(predicted_labels == gt_labels) / len(predicted_labels)
  return accuracy


model_accuracy_svm = compute_accuracy(np.asarray(test_labels) , predicted_labels_scm)
print('f1 score ' , f1_score(np.asarray(test_labels) , predicted_labels_scm))
print("SVM model acc:" , model_accuracy_svm * 100)

coefs = np.squeeze(np.array(svm_model.coef_))
#e o lista cu alta lista inauntru; initial era 1 si 9522; acum e doar 9522
#pdb.set_trace()
idx = np.argsort(coefs)
print("First tent:" , bow_model.words[idx[:10]])
print("First tent:" , bow_model.words[idx[-10:]])