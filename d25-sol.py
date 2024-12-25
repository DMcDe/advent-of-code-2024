import sys

lvl = -1
keys = []
locks = []
isLock = False
vec = [-1] * 5

# Read in keys/locks
for l in sys.stdin:
    if lvl == -1:
        if l[0] == '\n':
            continue
        elif l[0] == '#':
            isLock = True
        else:
            isLock = False
    elif isLock:
        for i in range(5):
            if l[i] == "." and vec[i] == -1:
                vec[i] = lvl
    else:
        for i in range (5):
            if l[i] == "#" and vec[i] == -1:
                vec[i] = 5 - lvl

    # Reset for new key/lock
    if lvl == 5:
        lvl = -1
        locks.append(vec) if isLock else keys.append(vec)
        vec = [-1] * 5
    else:
        lvl += 1

# Brute force
pairs = 0
for k in keys:
    for l in locks:
        fits = True
        for i in range(5):
            if k[i] + l[i] > 5:
                fits = False
                break
        
        if fits: pairs += 1

print(f"There are {pairs} working combos")
