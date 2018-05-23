"""
Classic two water jugs problem: given two jugs J0 and J1 with
capacities C0 and C1, initially filled with W1 and W2.  Can you end up
with exactly G0 liters in J0 and G1 liters in J1?  You're allowed the
following actions: dump the contents of either jug onto the floor, or
pour the contents of one jug into the other untill either the jug from
which you are pouring is empty or the one you are filling is full.
"""

import search as s

class WJ(s.Problem):
    """
    STATE: tuple like (3,2) if jug J0 has 3 liters and J1 2 liters
    GOAL: a state except that a value of '*' is a 'don't care', so
      valid goals include (1,1) and (*,2).
    PROBLEM: Specify capacities of each jug, initial state and goal """

    def __init__(self, capacities=(5,2), initial=(5,0), goal=(0,1)):
        self.capacities = capacities
        self.initial = initial
        self.goal = goal

    def __repr__(self):
        """ Returns a string representing the object """
        return "WJ({},{},{})".format(self.capacities, self.initial, self.goal)

    def goal_test(self, state):
        """ Returns true if state is a goal state """
        g = self.goal
        return (state[0] == g[0] or g[0] == '*' ) and \
               (state[1] == g[1] or g[1] == '*')

    def h(self, node):
        """ Estimate of cost of shortest path from node to a goal """
        return 0 if self.goal_test(node.state) else 1
    
    def actions(self, state):
        """ generates legal actions for state """
        (J0, J1) = state
        (C0, C1) = self.capacities
        if J0 > 0: yield 'dump0'
        if J1>0: yield 'dump1'
        if J1<C1 and J0>0: yield 'pour_0_1'
        if J0<C0 and J1>0: yield 'pour_1_0'

    def result(self, state, action):
        """ Returns the successor of state after doing action """
        (J0, J1) = state
        (C0, C1) = self.capacities
        if action == 'dump0':
            return (0, J1)
        elif action == 'dump1':
            return (J0, 0)
        elif action == 'pour_0_1':
            delta = min(J0, C1-J1)
            return (J0-delta, J1+delta)
        elif action == 'pour_1_0':
            delta = min(J1, C0-J0)
            return (J0+delta, J1-delta)
        else:
            raise ValueError('Unrecognized action: ' + action)

    def path_cost(self, c, state1, action, state2):
        """ Cost of path from start node to state1 assuming cost c to
        get to state1 and doing action to get to state2 """
        return c + 1
