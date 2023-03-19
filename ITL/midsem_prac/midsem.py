import numpy as np

cgpa = []
with open("./marks.txt", "r") as my_file:
    line = my_file.readline()
    while line:
        if line.startswith("CGPA"):
            cgpa.append(float(line.split(" ")[-1].strip()))
        line = my_file.readline()

cgpa = np.array(cgpa)
print(f"The mean of the CGPAs is: {cgpa.mean()}")
