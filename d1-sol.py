# Process input
l1 = []
l2 = []

with open('d1-input.txt', 'r') as f:
    for line in f:
        words = line.split()
        l1.append(int(words[0]))
        l2.append(int(words[1]))

l1.sort()
l2.sort()

# Part A
distance = 0

for loc1, loc2 in zip(l1, l2):
    distance += abs(loc1 - loc2)

print("The distance is:", distance)

# Part B
simscore = 0
l = 0
r = 0

while l < len(l1) and r < len(l2):
    sim = 0
    if l1[l] < l2[r]:
        l += 1
    elif l1[l] > l2[r]:
        r += 1
    else:
        lastr = r
        while (r < len(l2) and l1[l] == l2[r]):
            sim += l1[l]
            r += 1
        simscore += sim
        r = lastr
        l += 1

print("The similarity score is:", simscore)