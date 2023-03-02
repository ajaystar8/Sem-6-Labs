import pandas as pd

students = {"Name": ["Ajay", "Yash", "Shyam", "Parv", "Aayush"], "Height": [190, 175, 170, 180, 185], "Qualification":["ML", "CS", "CS", "Dev", "FinTech"]}
df = pd.DataFrame(students)

Address = ["Abad", "Mumbai", "Chennai", "Alwar", "Bangalore"]
df["Address"] = Address

print(df)