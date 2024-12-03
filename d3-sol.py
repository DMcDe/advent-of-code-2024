import sys # used for reading input
import re # used for regex

def parseMatches(matches, indices, dos=[], donts=[]):
    sum = 0
    j = 0
    k = 0
    do = True
    lastdo = 0
    lastdont = 0
    for m, i in zip(matches, indices):
        while (j < len(dos) and dos[j] < i):
            lastdo = dos[j]
            j += 1
        while (k < len(donts) and donts[k] < i):
            lastdont = donts[k]
            k += 1
        if lastdont > lastdo:
            do = False
            # print("Toggling to dont before", i, "because of", k - 1)
        else:
            do = True
            # print("Toggling to do before", i, "because of", j - 1)
        if do:
            expr = m[4:-1].partition(',')
            # print(m, expr)
            n1 = int(expr[0])
            n2 = int(expr[2])
            sum += (n1 * n2)
    return sum

# ----- Part B -----
# Get all multiplication instructions
s = sys.stdin.read()
muls = re.findall(r'mul\(\d{1,3},\d{1,3}\)', s) 

# Get starting index of all multiplication structions
mul_indices = [m.start() for m in re.finditer(r'mul\(\d{1,3},\d{1,3}\)', s)]

# Get indices of all dos and don'ts
do_indices = [m.start() for m in re.finditer(r'do\(\)', s)]
dont_indices = [m.start() for m in re.finditer(r'don\'t\(\)', s)]

partA = parseMatches(muls, mul_indices)  
print("The sum of all valid multiplications is:", partA)
    
partB = parseMatches(muls, mul_indices, do_indices, dont_indices)
print("The sum accounting for dos and donts is:", partB)
# ----- Part A Only -----
# sum = 0
# for l in sys.stdin:
#     matches = re.findall(r'mul\(\d{1,3},\d{1,3}\)', l)
#     sum += parseMatches(matches)