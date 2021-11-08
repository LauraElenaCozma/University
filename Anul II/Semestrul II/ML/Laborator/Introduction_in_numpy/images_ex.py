import matplotlib.pyplot as plt
import numpy as np
#a. Read the images and save them into a np.array
def importImages():
    v = np.zeros((9 , 400 , 600))
    for i in range(0 , 9):
        path = "images/car_" + str(i) + ".npy"
        image = np.load(path)
        v[i] = image
    return v

images = importImages()
print("The pixels of the 9 images are:\n" , images)


#b. Compute sum of all pixel values
def sumAllPixels(images):
    sum = 0
    for i in range(0 , 9):
        sum += np.sum(images[i])
    return sum

print("The sum of all pixels is:" , sumAllPixels(images))

#v2
print(np.sum(images))

#c. Sum of all pixels for every image

def sumPixelsForEveryImage(images):
    sum = np.sum(images , axis = (1 , 2))
    return sum

sumPix = sumPixelsForEveryImage(images)
print("Sum for every image is:" , sumPix)

#d. Print the index of the image with the maaximum sum
def indexMaxElement(sum):
    return np.argmax(sum)

print("Index is: " , indexMaxElement(sumPix))

def averageImage(images):
    image = np.mean(images , axis = 0)
    return image

mean_image = averageImage(images)
print(mean_image.shape)
from skimage import io
io.imshow(mean_image.astype(np.uint8)) # petru a putea fi afisata
# astype cast to a specific type
# imaginea trebuie sa aiba
# tipul unsigned int
io.show() #display pending images

#Compute standard deviation
def standardDev(images):
    return np.std(images)
stDev = standardDev(images)
print("Standard deviation is:" , stDev)

#g. Normalize the images
def normalization(images , mean_image , std_dev):
    img = (images - mean_image) / std_dev
    for i in range(0 , 9):
        io.imshow(img[i].astype(np.uint8))
        io.show()

normalization(images , mean_image , stDev)

#h. Crop every image, lines between 200 and 300 and columns 280 - 400
def crop(images):
    sliced = images[: , 200 : 301 , 280 : 401]
    for i in range(0, 9):
        io.imshow(sliced[i].astype(np.uint8))
        io.show()

crop(images)