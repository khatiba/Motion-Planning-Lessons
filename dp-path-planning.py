# ----------
# Given a car in grid with initial state init.
# Compute the car's optimal path to the position to the goal.
# The costs are given for each motion.
#
# There are four motion directions: up, left, down, and right.
# Increasing the index in this array corresponds to making a
# a left turn, and decreasing the index corresponds to making a
# right turn.

forward = [[-1,  0], # go up
           [ 0, -1], # go left
           [ 1,  0], # go down
           [ 0,  1]] # go right
forward_name = ['up', 'left', 'down', 'right']

# action has 3 values: right turn, no turn, left turn
action = [-1, 0, 1]
action_name = ['R', '#', 'L']

# EXAMPLE INPUTS:
# grid format:
#     0 = navigable space
#     1 = unnavigable space
grid = [[1, 1, 1, 0, 0, 0],
        [1, 1, 1, 0, 1, 0],
        [0, 0, 0, 0, 0, 0],
        [1, 1, 1, 0, 1, 1],
        [1, 1, 1, 0, 1, 1]]

init = [4, 3, 0] # given in the form [row, col, direction]
                 # direction = 0: up
                 #             1: left
                 #             2: down
                 #             3: right

goal = [2, 0] # given in the form [row, col]

cost = [2, 1, 20] # cost has 3 values, corresponding to making
                  # a right turn, no turn, and a left turn

# EXAMPLE OUTPUT:
# calling optimum_policy2D with the given parameters should return
# [[' ', ' ', ' ', 'R', '#', 'R'],
#  [' ', ' ', ' ', '#', ' ', '#'],
#  ['*', '#', '#', '#', '#', 'R'],
#  [' ', ' ', ' ', '#', ' ', ' '],
#  [' ', ' ', ' ', '#', ' ', ' ']]
# ----------

def optimum_policy2D(grid,init,goal,cost):
    value = [
        [[float('inf') for col in range(len(grid[0]))] for row in range(len(grid))],
        [[float('inf') for col in range(len(grid[0]))] for row in range(len(grid))],
        [[float('inf') for col in range(len(grid[0]))] for row in range(len(grid))],
        [[float('inf') for col in range(len(grid[0]))] for row in range(len(grid))],
    ]

    policy = [[' ' for col in range(len(grid[0]))] for row in range(len(grid))]

    changed = True
    while changed:
        changed = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                for i in range(len(forward)):
                    if r == goal[0] and c == goal[1] and value[i][r][c] > 0:
                        value[i][r][c] = 0
                        changed = True

                    for k in range(len(action)):
                        current_cost = value[i][r][c]

                        o2 = (i + action[k]) % 4
                        y2 = r + forward[o2][0]
                        x2 = c + forward[o2][1]

                        if x2 >= 0 and x2 < len(grid[0]) and y2 >= 0 and y2 < len(grid) and grid[r][c] != 1:
                            new_cost = cost[k] + value[o2][y2][x2]

                            if new_cost < current_cost:
                                value[i][r][c] = new_cost
                                changed = True

    policy[goal[0]][goal[1]] = '*'
    nodes = [init]
    while nodes:
        node = nodes.pop()

        y = node[0]
        x = node[1]
        o = node[2]

        current_cost = value[o][y][x]

        mincost = float('inf')
        for k in range(len(action)):
            o2 = (o + action[k]) % 4
            y2 = y + forward[o2][0]
            x2 = x + forward[o2][1]

            if x2 >= 0 and x2 < len(grid[0]) and y2 >= 0 and y2 < len(grid):
                next_cost = value[o2][y2][x2]
                if next_cost < current_cost:
                    policy[y][x] = action_name[k]
                    nodes.append([y2, x2, o2])

    return policy


if __name__ == '__main__':
    o = optimum_policy2D(grid, init, goal, cost)
    for r in o:
        print(r)

