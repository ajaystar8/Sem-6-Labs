import numpy as np

a = np.arange(25).reshape(5,5)

# row_sums = []
# col_sums = []

# for row in a: 
#     row_sums.append(np.sum(row))

# for row in a.T: 
#     col_sums.append(np.sum(row))

# print("Row sums: ")
# print(row_sums)

# print("Column sums: ")
# print(col_sums)

print(a.sum(axis = 0)) #row
print(a.sum(axis = 1)) #column