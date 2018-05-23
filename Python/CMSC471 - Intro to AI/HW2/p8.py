
""" 8-Puzzle solution adapted from one by Matt Dailey (June 2004)
http://www.siit.tu.ac.th/mdailey/class/2004_s1/its216/data/8puzzle.py.

usage: python3 p8.py

"""

import sys
import search        # AIMA module for search problems
import random
import time

default_goal = '*12345678'
#default_goal = '1238*4765'

class P8(search.Problem):
    """A state is represented as a 9-character string with digits 1-8
    for tiles and '*' for a blank."""

    name = 'No Heuristic (NIL)'

    def __init__(self, goal=default_goal, initial=None, N=20):
        self.goal = goal
        self.initial = initial if initial else random_state(goal, N)

    def goal_test(self, s):
        """ Returns True iff s is a goal """
        return s == self.goal

    def actions(self, s):
        return actions8(s)

    def result(self, S, A):
        return result8(S,A)

    def path_cost(self, c, state1, action, state2):
        """Return the cost of a solution path that arrives at state2
        from state1 via action, assuming cost c to get up to
        state1. In tis case, the addional cost of every action is just
        1. """
        return c + 1

    def h(self, node):
        """Heuristic for 8 puzzle: returns 0 for a goal 1 otherwise """
        return 0 if node == self.goal else 1
    
def actions8(S):
    """ Returns list of action possible in state S """
    action_table = {
        0:['down', 'right'],
        1:['down', 'left', 'right'],
        2:['down', 'left'],
        3:['up','down','right'],
        4:['up','down','left','right'],
        5:['up','down','left'],
        6:['up','right'],
        7:['up','left','right'],
        8:['up','left']}
    return action_table[S.index('*')]

def result8(S, A):
    """ Returns 8puzzle state after doing action A in state S"""
    # blank position
    blank = S.index('*')
    if A == 'up':
        swap = blank - 3
        return S[0:swap] + '*' + S[swap+1:blank] + S[swap] + S[blank+1:]
    elif A == 'down':
        swap = blank + 3
        return S[0:blank] + S[swap] + S[blank+1:swap] + '*' + S[swap+1:]
    elif A == 'left':
        swap = blank - 1
        return S[0:swap] + '*' + S[swap] + S[blank+1:]
    elif A == 'right':
        swap = blank + 1
        return S[0:blank] + S[swap] + '*' + S[swap+1:]
    raise ValueError('Unrecognized action: ' + A)


class P8_h1(P8):
    """ Eight puzzle using a heuristic function that counts the number
    of tiles out of place"""

    name = 'Out of Place Heuristic (OOP)'

    def h(self, node):
        """8 puzzle heuristic: number of tiles 'out of place'
        between a node's state and the goal"""
        mismatches = 0
        for (t1,t2) in zip(node.state, self.goal):
            if  t1 != t2:
                mismatches += 1
        return mismatches

class P8_h2(P8):
    name = 'Manhattan Distance Heuristic (MHD)'

    def h(self, node):
        """8 Puzzle Heuristic: sum for each tile of manhattan distance
        between its position in node's state and goal """
        sum = 0
        for tile in '12345678':
            sum += mhd(node.state.index(tile), self.goal.index(tile))
        return sum

def mhd(n, m):
    """Returns manhattan-distance between two indices in a
       nine-character string corresponding to a 3x3 array"""

    # dict of x,y coordinates for each character position
    coordinates = {0:(0,0), 1:(1,0), 2:(2,0),
                   3:(0,1), 4:(1,1), 5:(2,1),
                   6:(0,2), 7:(1,2), 8:(2,2)}    
    x1, y1 = coordinates[n]
    x2, y2 = coordinates[m]
    return abs(x1-x2) + abs(y1-y2)

def random_state(s, n, unique=True):
    """ Returns state reached after a random walk of length n in the
    spate space starting from s.  If unique is True, each state on the
    walk should be unique."""
    return simple_random_state(s, n) if not unique else nodups_random_state(s, n)

def simple_random_state(s, n):
    """returns resulting state after a simple random walk of n steps
       starting with state s"""
    for _ in range(n):
        s = result8(s, random.choice(actions8(s)))
    return s

def nodups_random_state(s, n):
    """returns resulting state after a random walk of n steps
       starting with state s"""
    path = [s]
    for _ in range(n):
        last = path[-1]
        actions =  list(actions8(last))
        random.shuffle(actions)
        for act in actions:
            next = result8(last, act)
            if next not in path:
                break
        path.append(next)
    # return last state on path
    return path[-1]

def printsoln(goal):
    """shows solution to 8 puzzle"""
    # path is list of states from initial to goal
    path = goal.path()
    path.reverse()
    initial = path[-1]
    # print the solution
    print("%s steps from %s to %s" % (len(path), initial.state, goal.state))
    for n in path:
        print_state(n)

def print_state(n):
    """Print the action and resulting state"""
    a = n.action
    s = n.state
    print("%s\t%s\n\t%s\n\t%s\n" % (a,s[0:3],s[3:6],s[6:9]))

def solve(initial=None, verbose=True, n=10):
    """Solves a random 8 puzzle problem and prints info"""
    if initial:
        print("\nInitial state is %s" % initial)
        s = initial
    else:
        print("\nProblems using %s random steps from goal" % n)
        s = random_state(default_goal, n)
    
    for p in [P8(initial=s), P8_h1(initial=s), P8_h2(initial=s)]:
        if verbose: 
            print('%s => %s using %s' % (p.initial, p.goal, p.name))
        ip = search.InstrumentedProblem(p)
        begin_time = time.time()
        solution = search.astar_search(ip)
        elapsed = time.time() - begin_time
        if verbose:
            if solution:
                print("  Solution length {}".format(len(solution.path())))
            else:
                print("  No solution found :-(")
            print("  %s states, %s successors, %s goal tests (%9.6f sec)" % (ip.states, ip.succs, ip.goal_tests, elapsed))
                

def main(steps=[5,10,15,20]):
    """ Solve an instance of the 8 puzzle from an inital state reached
    by a random walk of N steps for each N in the list steps"""
    for n in steps:
        solve(n=n)

# if called from the command line, call main()
if __name__ == "__main__":
    if len(sys.argv) > 1:
        main([int(arg) for arg in sys.argv[1:]])
    else:
        main()
        
