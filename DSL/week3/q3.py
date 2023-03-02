import numpy as np 

l = [1,2,3,4,5,6]
t = (9,8,7,6,5,4)

arr = np.array(l, dtype = float)
print(arr)

arr_tup = np.array(t)
print(arr_tup)

zer = np.zeros((3,4))
print(zer)

ar_step = np.arange(0, 20, 5)
print(ar_step)

arr5 = np.arange(12).reshape((3,4))
arr5 = arr5.reshape((2,2,3))
print(arr5)

arr6 = np.arange(20).reshape((5,4))
print(arr6)
print(arr6.max(), arr6.min(), arr6.max(axis = 0), arr6.min(axis = 0), arr6.max(axis = 1), arr6.min(axis = 1), arr6.sum())