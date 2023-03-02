import pandas as pd

l1 = {"Name":["Annie", "Diya", "Marie", "Hank"], "q1": [5,4,3,2], "i1": [9,8,3,6], "q2": [3,7,1,9], "i2": [7,2,9,4]}

df = pd.DataFrame(l1)

df["Total"] = df.iloc[:, 1:].sum(axis = 1)

means = df.iloc[:, 1:].mean(axis = 0)

df.loc["Mean"] = df.mean(axis = 0)

print(df)