import sys
import math
import copy

def checkValidityA(target: int, inputs: list):
    # Bound
    tot = sum(inputs)
    prod = math.prod(inputs)

    if target < min(tot, prod) - len(inputs) or target > max(tot, prod) + max(inputs) * inputs.count(1):
        # if target == 136144 and target > max(tot, prod):
        #     print(target, inputs, max(tot, prod))
        return False
    elif target == prod or target == tot:
        return True
    
    if len(inputs) == 1:
        return tot == target
    
    # Branch
    add = copy.deepcopy(inputs)
    mult = copy.deepcopy(inputs)
    back = add.pop()
    add[-1] += back
    back = mult.pop()
    mult[-1] *= back

    return checkValidityA(target, mult) or checkValidityA(target, add)

def checkValidityB(target: int, inputs: list):
    if len(inputs) == 1:
        return inputs[0] == target
    
    add = copy.deepcopy(inputs)
    mult = copy.deepcopy(inputs)
    back = add.pop()
    add[-1] += back
    back = mult.pop()
    mult[-1] *= back
    # print(inputs)
    back = inputs.pop()
    # print(inputs[-1], back, int(str(inputs[-1]) + str(back)), str(inputs[-1]) + str(back))
    inputs[-1] = int(str(back) + str(inputs[-1]))

    return checkValidityB(target, inputs) or checkValidityB(target, add) or checkValidityB(target, mult)

totalA = 0
totalB = 0
# count = 0
for l in sys.stdin:
    eqn = l.partition(':')
    target = int(eqn[0])
    inputs = eqn[2].split()
    inputs = [int(i) for i in inputs]
    #print(target, inputs, end=' ')
    inputs.reverse()

    if checkValidityA(target, inputs):
        # print(target)
        totalA += target
        # count += 1

    # print(inputs)
    if checkValidityB(target, inputs):
        totalB += target

# print(count)
print("The total calibration result is:", totalA)
print("The total calibration result, including concatenation, is:", totalB)

# Horribly inefficient, but does the job
    
