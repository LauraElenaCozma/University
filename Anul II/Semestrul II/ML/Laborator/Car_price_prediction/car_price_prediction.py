import numpy as np
from sklearn.utils import shuffle
from sklearn import preprocessing

# load training data
training_data = np.load('data/training_data.npy')
prices = np.load('data/prices.npy')
# print the first 4 samples
print('The first 4 samples are:\n ', training_data[:4])
print('The first 4 prices are:\n ', prices[:4])
# shuffle
#asa se face la cross validare
#nu vrem sa avem mereu aceleasi grupe
#facem o amestecare a datelor ca sa avem folduri diferite
training_data, prices = shuffle(training_data, prices, random_state=0)

# --- 1 ---
def normalize_data(training , testing = None):
      scaler = preprocessing.StandardScaler()
      scaler.fit(training)
      scaled_x_train = scaler.transform(training)
      if testing is None:
          return scaled_x_train
      scaled_x_test = scaler.transform(testing)
      return scaled_x_train , scaled_x_test
      scaled_test_data = scaler.transform(test_data)
      return (scaled_train_data, scaled_test_data)

# --- 2 ---
num_samples_fold = len(training_data) // 3
training_data_1 , prices_1 = training_data[:num_samples_fold] , prices[:num_samples_fold]
training_data_2 , prices_2 = training_data[num_samples_fold : 2 * num_samples_fold] , prices[num_samples_fold : 2 * num_samples_fold]
training_data_3 , prices_3 = training_data[2 * num_samples_fold:] , prices[2 * num_samples_fold:]

from sklearn.metrics import mean_squared_error , mean_absolute_error
from sklearn.linear_model import LinearRegression , Ridge , Lasso

def normalize_train_model(model , training_samples , labels , testing_data , testing_labels):
    training_samples , testing_data = normalize_data(training_samples , testing_data)
    model.fit(training_samples , labels)
    return mean_absolute_error(testing_labels , model.predict(testing_data)) , mean_squared_error(testing_labels , model.predict(testing_data))

model = LinearRegression()
mae_1 , mse_1 = normalize_train_model(model , np.concatenate((training_data_1 , training_data_2)) ,
                                      np.concatenate((prices_1 , prices_2)) , training_data_3 , prices_3)
mae_2 , mse_2 = normalize_train_model(model , np.concatenate((training_data_1 , training_data_3)) ,
                                      np.concatenate((prices_1 , prices_3)) , training_data_2 , prices_2)
mae_3 , mse_3 = normalize_train_model(model , np.concatenate((training_data_2 , training_data_3)) ,
                                      np.concatenate((prices_2 , prices_3)) , training_data_1 , prices_1)
print("Mean MAE " , (mae_1 + mae_2 + mae_3) / 3)
print("Mean MSE " , (mse_1 + mse_2 + mse_3) / 3)

# --- 3 ---

alpha = [1 , 10 , 100 , 1000] #am pus valorile lui alpha
mae = np.zeros(3)  #la fiecare pas in for mae va avea pe fiecare pozitie valoarea mediei
mse = np.zeros(3)
max = 0
maxAlpha = 0
for val in alpha:
    model = Ridge(val)  #facem un model ridge pentru alpha = val
    mae[0], mse[0] = normalize_train_model(model, np.concatenate((training_data_1, training_data_2)),
                                         np.concatenate((prices_1, prices_2)), training_data_3, prices_3)
    mae[1], mse[1] = normalize_train_model(model, np.concatenate((training_data_1, training_data_3)),
                                         np.concatenate((prices_1, prices_3)), training_data_2, prices_2)
    mae[2], mse[2] = normalize_train_model(model, np.concatenate((training_data_2, training_data_3)),
                                         np.concatenate((prices_2, prices_3)), training_data_1, prices_1)
    print("Alpha is " , val)
    print("Ridge mean MAE " , mae.mean()) #calculam la fiecare pas media din mae si o afisam
    print("Ridge mean MSE " , mse.mean()) #calculam la fiecare pas media din mse si o afisam
    if mse.mean() > max:
        max = mse.mean()
        maxAlpha = val

print(maxAlpha)

# --- 4 ---
ridge_regression_model = Ridge(alpha = 1000)

scaler = preprocessing.StandardScaler()
scaler.fit(training_data)
training_data = scaler.transform(training_data)
ridge_regression_model.fit(training_data , prices)

print("Bias " + str(ridge_regression_model.intercept_)) #bias

print("Coef: ")
print("Ridge regression model coefs " , ridge_regression_model.coef_)

indexes = np.argsort(ridge_regression_model.coef_)
descr = ["An fabricatie" , "Nr. km" , "consum" , "motor" , "putere" , "nr_locuri" , "nr_proprietari" , "combustibil" , "combustibil" , "combustibil" , "combustibil", "transmisie" , "transmisie"]
print("Cea mai semnificativa coloana: " + str(indexes[-1] + 1) + " " + str(descr[indexes[-1]]))
print("A doua cea mai semnificativa coloana: " +str(indexes[-2] + 1)+ str(descr[indexes[-2]]))
print("Cea mai nesemnificativa coloana: " + str(indexes[0] + 1) + str(descr[indexes[0]]))
