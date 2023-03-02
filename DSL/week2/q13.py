my_list = [-1, 2, 3, 4,-3, 2,-7]
pos, neg = 0, 0

for num in my_list:
    if num < 0:
        neg = neg + 1
    else:
        pos = pos + 1

print(f"Number of positives = {pos}, Number of negatives = {neg}")