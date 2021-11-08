import numpy as np

a = np.array([])

print(a)
print(a.shape)
b = np.array(["3as" , 4])
print(b)
print(b.shape) #dimensiunile, in caz ca e matrice, ambele dimensiuni
print(b.dtype)

c = np.array(b)
print(c)
#in argumente la np.array putem pune un vector creat pe loc cu [ ]
#sau un vector existent

zero_array = np.zeros((3 , 4))
print(zero_array) #o matrice cu 3 linii si 4 coloane
print("un vector de 2 elemente egale cu 0")
zero_a = np.zeros(2)
print(zero_a)
print("vector tridimensional ")
zero_ar= np.zeros((3 , 4 , 5))
print(zero_ar)

const_a = np.full(5 , 4)
print("un vector constant numai din 4\n" , const_a)

id_m = np.eye(3)
print("matricea identitate de 3 pe 3\n" , id_m)

rand_mat = np.random.random((4 , 3))
print("matrice de 4*3 cu valori random intre 0 si 1\n" , rand_mat)

rand_mat = np.random.random((4 , 3)) + 3  # INTRE 3 si 4
print("matrice de 4*3 cu valori random intre 3 si 4\n" , rand_mat)
mu , sigma = 0 , 0.1
rand_norm = np.random.normal(0 ,  0.1 , 3)
print("\nVector de 3 elem cu valori repartizate normal\n" , rand_norm)

#Slicing
a_sl = np.array([1 , 2, 3 , 4, 5])
slice = a_sl[2:]
print("vector initial\n" , a_sl)
print("Vector sectionat incepand cu indicele 2\n" , slice)

array_to_slice = np.array([[1,2,3,4], [5,6,7,8], [9,10,11,12]])
slice = array_to_slice[1 , 0:3]
print("sectionat\n" , slice)
#atentie. modifici slice, se modifica si vectorul initial
slice[0] = 100
print("modificat\n" , array_to_slice)

#np.copy ca sa nu se mai modifice
slice_copy = np.copy(array_to_slice[:, 0:3])
slice_copy[0][0] = 100
print(slice_copy[0][0]) # => 100
print(array_to_slice[0][0])

#Produsul scalar -- dot
print("Produsul scalar")
x = np.array([[1, 2],[3, 4]])
y = np.array([[5, 6],[7, 8]])
v = np.array([9, 10])
w = np.array([11, 12])
# vector x vector => 219
print(v.dot(w))
print(np.dot(v, w))

#Matrice
mat = np.array([[1, 2, 3], [4, 5, 6]])
m_aux = mat.T;
print(mat)
print("Transpisa\n" , m_aux)
#-- inversa --
my_array = np.array([[1., 2.], [3., 4.]])
print(np.linalg.inv(my_array))

#Operatii pe dimensiuni
x = np.array([[1, 2 , 3],[3, 4 , 5]])
print("Se aduna toate elem:" , np.sum(x))
print("Se aduna elem pe coloane, adica 3 elem: " , np.sum(x , axis = 0))

y = np.array([[[1, 2, 3, 4], [5, 6, 7, 8]], [[1, 2, 3, 4], [5, 6, 7, 8]], [[1, 2, 3,
4], [5, 6, 7, 8]]])
print(y.shape) # => (3, 2, 4)
print(y)
print("Suma " , np.sum(y, axis=0))
#axa 0, adica se elimina ultima dimensiune?
print("Suma " , np.sum(y, axis=1))
#axa 1, suma pe coloane
print("Medie:")
print(np.mean(y, axis=2))