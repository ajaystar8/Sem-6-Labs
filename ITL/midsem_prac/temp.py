file = open("./midsem_prac/file_yash.txt", "r")

lines = file.readlines()
for line in lines:
    if "CGPA" in line:
        lst = line.split(" ")
        list1 = float(lst[1].strip("\n"))
        print(type(list1))


