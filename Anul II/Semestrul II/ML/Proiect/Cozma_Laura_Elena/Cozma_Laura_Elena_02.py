from sklearn.feature_extraction.text import TfidfVectorizer
import re
import numpy as np


#preprocessor for TfidfVectorizer
def process_data(line):
    #remove the index at the beginning of the tweet
    string_without_index = re.sub(r'\d+', ' ', line)
    return string_without_index

def extract_indexes_for_test(file):
   indexes = []
   for line in file:
       indexes.append(line.split('\t' , 1)[0])
   return indexes

#extract the predictions from a document
def extract_predictions(file):
    labels = []
    for line in file:
      label = line.split('\t' , 1)[1]
      #every number has in the end a '\n' and we want to remove it
      label = label.replace('\n' , '')
      label_number = int(label)
      labels.append(label_number)
    return labels


print("Read the data...")

#read the train samples
file = open('/content/drive/My Drive/data/train_samples.txt')
train_samples = file.readlines()          #train_samples is now an array of tweets

#read the test samples
file = open('/content/drive/My Drive/data/test_samples.txt')
test_samples = file.readlines()           #test_samples is now an array of tweets

#read the validation samples
file = open('/content/drive/My Drive/data/validation_samples.txt')
validation_samples = file.readlines()     #validation_samples is now an array of tweets

# get the ids of the tweets from test_samples
#will help us to create the csv document
indexes = extract_indexes_for_test(test_samples)

# read the train labels
file = open('/content/drive/My Drive/data/train_labels.txt')
train_labels = file.readlines()          #train_labels is now an array of "id prediction"
#extract the predictions
train_labels = extract_predictions(train_labels)

# read the validation labels
file = open('/content/drive/My Drive/data/validation_labels.txt')
validation_labels = file.readlines()     #validation_labels is now an array of "id prediction"
#extract the predictions
validation_labels = extract_predictions(validation_labels)


# Concatenate train_samples and validation_samples for a better fit
#train_samples = np.concatenate((train_samples, validation_samples))
#train_labels = np.concatenate((train_labels, validation_labels))

print("Generate the dictionary...")

# Tfidf to create a dictionary
tfidf = TfidfVectorizer(preprocessor = process_data, lowercase = False, token_pattern = r"\S\S+")
#process_data to remove the ids of the tweets
#lowercase = False because the data is encrypted(a and A can represent different letters and we want to distinguish between them)
#token_pattern = r"\S\S+" ignore the groups of 2 or more spaces
#default norm is l2

#fit the data. tokenize and build vocabulary
tfidf.fit(train_samples)
#encode train_samples
train_samples_transformed = tfidf.transform(train_samples)

print("The vocabulary is:\n" , tfidf.vocabulary_)

# process test_data
test_samples_transformed = tfidf.transform(test_samples)           #now test_samples_transformed is a matrix of features
print("Shape of test_samples_transformed: ", test_samples_transformed.shape)

# process validation_samples
validation_samples_transformed= tfidf.transform(validation_samples) #now validation_samples_transformed is a matrix of features

#classifier
from sklearn.naive_bayes import ComplementNB

complement_nb = ComplementNB(alpha = 0.2)
complement_nb.fit(train_samples_transformed, train_labels)

print("Predict the labels...")

predicted_labels_validation = complement_nb.predict(validation_samples_transformed)
predicted_labels_test = complement_nb.predict(test_samples_transformed)

#compute f1 score on validation_samples
from sklearn.metrics import f1_score
print('f1 score ' , f1_score(np.asarray(validation_labels) , predicted_labels_validation))

#create csv file for results
from google.colab import files

#create an array with each line of the answer
answer = []
for (index, predicted_label_test) in zip(indexes, predicted_labels_test):
  answer.append(str(index) + "," + str(int(predicted_label_test)))

#create csv file
file = open('/content/drive/My Drive/data/results.csv', 'w')
#write in file the title for columns "id,label"
file.write('id,label\n')

#write each line containing the predictions in file
for line in answer:
    file.write(line + "\n")

file.close()
#files.download('/content/drive/My Drive/data/results.csv')
