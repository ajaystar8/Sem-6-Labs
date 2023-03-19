password = input("Enter password to check: ")
lower_case, upper_case, special_case, number = 0, 0, 0, 0

for char in password:
    if char.islower():
        lower_case += 1
    if char.isupper():
        upper_case += 1
    elif char.isnumeric():
        number += 1
    else:
        special_case += 1

print(lower_case, upper_case, special_case, number)
