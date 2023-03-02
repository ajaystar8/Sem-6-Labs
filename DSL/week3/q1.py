n = int(input("Enter a number: "))
print("The factors of the number are: ")
for i in range(1, n):
    if n % i == 0:
        print(i)