import pandas as pd

l1 = {"Name":["Ram", "Diya", "Chandan", "James", "Alice"]}
l2 = {"Maths":[1,2,3,4,5], "Physics":[1,2,3,4,5], "Chemistry": [1,2,3,4,5], "Biology": [1,2,3,4,5]}

df1 = pd.DataFrame(l1)
df2 = pd.DataFrame(l2)

df3 = pd.concat([df1, df2], axis = 1)
df3["Total"] = df3.iloc[:, 1:].sum(axis = 1)

print(df3)
