import sys
from enum import Enum

class Dir(Enum):
    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3

# Create grid
grid = []

# Fill grid and find start location
row = 0
for line in sys.stdin:
    line = line.rstrip()
    grid.append([])
    col = 0
    for ch in line:
        grid[-1].append(ch)
        if ch == '^':
            start = (row, col)
        col += 1
    row += 1

m = len(grid)
n = len(grid[0])

# Track locations guard visits
locs = set()
locs.add(start)

# Track guard's current location
r = start[0]
c = start[1]
d = Dir.UP

while (r >= 0 and r < m and c >= 0 and c < n):
    # print(f"At ({r}, {c}), grid: {grid[r][c]}")
    if d == Dir.UP:
        if r == 0:
            break

        if grid[r - 1][c] == '#':
            d = Dir.RIGHT
        else:
            r -= 1
            locs.add((r, c))
    elif d == Dir.RIGHT:
        if c == n - 1:
            break

        if grid[r][c + 1] == '#':
            d = Dir.DOWN
        else:
            c += 1
            locs.add((r, c))
    elif d == Dir.DOWN:
        if r == m - 1:
            break

        if grid[r + 1][c] == '#':
            d = Dir.LEFT
        else:
            r += 1
            locs.add((r, c))
    else:
        if c == 0:
            break

        if grid[r][c - 1] == '#':
            d = Dir.UP
        else:
            c -= 1
            locs.add((r, c))

print(f"The guard visits {len(locs)} locations before exiting.")
        


