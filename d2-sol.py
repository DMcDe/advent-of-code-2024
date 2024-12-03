with open('d2-input.txt', 'r') as f:
    # ----- PART A -----
    # Store number of safe levels
    safe_reports = 0

    for line in f:
        # Read each level as integers
        levels = [int(num) for num in line.split()]
        # print(levels)

        # Track whether first step is an increase
        increasing = (levels[1] > levels[0])

        safe = True

        # Check each step for safety conditions
        for i in range(1, len(levels)):
            dif = levels[i] - levels[i - 1]
            if (increasing and (dif < 1 or dif > 3)) or (not increasing and (dif > -1 or dif < -3)):
                # print("NOT SAFE WITH DIF", dif)
                safe = False
                break

        # Increment number of safe levels if safe
        if safe:
            # print("Incrementing safe")
            safe_reports += 1
        
    print('Number of safe reports:', safe_reports)

    # ----- PART B -----

def checkValidity(levs, skip=None):
    if skip != None:
        levels = levs[:skip] + levs[skip + 1:]
    else:
        levels = levs

    # Track whether first step is an increase
    increasing = (levels[1] > levels[0])

    safe = True

    # Check each step for safety conditions
    for i in range(1, len(levels)):
        dif = levels[i] - levels[i - 1]
        if (increasing and (dif < 1 or dif > 3)) or (not increasing and (dif > -1 or dif < -3)):
            # print("NOT SAFE WITH DIF", dif)
            safe = False
            break
    
    return safe

    
with open('d2-input.txt', 'r') as f:
    # ----- PART A -----
    # Store number of safe levels
    safe_reports = 0

    for line in f:
        # Read each level as integers
        levels = [int(num) for num in line.split()]

        # Check full list for safety conditions
        safe = checkValidity(levels)

        # Check each step for safety conditions
        i = 0
        while i < len(levels) and not safe:
            safe = safe or checkValidity(levels, i)
            i += 1

        # Increment number of safe levels if safe
        if safe:
            # print("Incrementing safe")
            safe_reports += 1
        
    print('Number of safe reports:', safe_reports)



# ----- Original, failed part B solution -----
        # Store number of safe levels
# with open('d2-input.txt', 'r') as f:
#     safe_reports = 0

#     for line in f:
#         # Read each level as integers
#         levels = [int(num) for num in line.split()]
#         # print(levels)

#         # Track whether first step is an increase
#         increasing = (levels[1] > levels[0])

#         # Start with safe = 2, if it gets to 0 then unsafe
#         safe = 3

#         # Check each step for safety conditions
#         i = 1
#         removed = -1
#         removed_index = -1
#         while i < len(levels):
#             dif = levels[i] - levels[i - 1]
#             if (increasing and (dif < 1 or dif > 3)) or (not increasing and (dif > -1 or dif < -3)):
#                 safe -= 1
#                 if safe == 2:
#                     if i == len(levels) - 1:
#                         # Can just remove the last one in this case, know we're safe
#                         break
#                     print("---")
#                     print(levels, "REMOVING", levels[i], "at", i)
#                     removed = levels[i]
#                     del levels[i]

#                     if i == 1:
#                         # Reset whether increasing
#                         increase = (levels[1] > levels[0])
#                     i -= 1
#                     removed_index = i
#                 elif safe == 1:
#                     # Try removing other num
#                     print(levels, "STILL UNSAFE, replacing", levels[removed_index], "at", removed_index, end=' ')
#                     levels[removed_index - 1] = removed
#                     i = removed_index
#                     if i == 0:
#                         # Reset whether increasing
#                         increase = (levels[1] > levels[0])
#                     print(levels)
#                 else:
#                     print("STILL UNSAFE:", levels, dif, "DISCOUNTING")
#                     break
#             i += 1

#         # Increment number of safe levels if safe
#         if safe:
#             safe_reports += 1
        
#     print('Number of safe reports, accounting for safety systems:', safe_reports)