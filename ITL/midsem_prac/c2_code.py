word_list = []

# read words from file
with open("./c2_text.txt") as my_file:
    line = my_file.readline()
    while line:
        data = line.split()
        for word in data:
            word_list.append(word)
        line = my_file.readline()


# sort the words
for i in range(len(word_list)-1):
    for j in range(0, len(word_list)-i-1):
        if word_list[j] > word_list[j+1]:
            word_list[j], word_list[j+1] = word_list[j+1], word_list[j]
print(f"Sorted words: {word_list}")

# removal of duplicates
my_set = list(set(word_list))
print(f"Unique word list: {my_set}")
