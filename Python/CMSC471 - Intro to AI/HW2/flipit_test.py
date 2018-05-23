from math import sqrt
import sys
import time
import search

import flipit

tests2 = [ '0011', '0111', '0001', '0100']
tests3 = ['011100010', '100100010', '001110000', '110100010']
tests4 = ['1110110011001000', '0010110011110110', '1101000001111110', '1111111001000010']
tests5 = ['0000001000101001010001000', '0000001100100100111000111', '0100011110110111010010100', '0000101011111001111110111']


def run_tests():
    """run all of the tests"""
    print("Testing 2x2 problem", flush=True)
    for test in tests2:
        flipit_solve(2, initial=test)
    print("Testing 3x3 problem", flush=True)
    for test in tests3:
        flipit_solve(3, initial=test)
    print("Testing 4x4 problem", flush=True)
    for test in tests4:
        flipit_solve(4, initial=test)
    print("Testing 5x5 problem", flush=True)
    for test in tests5:
        flipit_solve(5, initial=test)        

def flipit_solve(size, initial):
    """ Solve a flip problem and print the result """
    problem =  search.InstrumentedProblem(flipit.FlipIt_optimal(size=size, initial=initial))
    print("Solving {} => {} optimal".format(problem.initial, problem.goal), flush=True)
    time0 = time.time()
    solution = search.astar_search(problem)
    elapsed = time.time() - time0
    show_solution(solution, problem, elapsed)

    problem =  search.InstrumentedProblem(flipit.FlipIt_aggressive(size=size, initial=initial))
    print("Solving {} => {} aggressive".format(problem.initial, problem.goal), flush=True)
    time0 = time.time()
    solution = search.astar_search(problem)
    elapsed = time.time() - time0
    show_solution(solution, problem, elapsed)
    

def show_solution(solution_node, ip, time=0):
    """ Print a flipit solution """
    if solution_node:
        path = solution_node.path()
        print("Solution of length {} found after {:.4f} seconds and adding {} states and {} successors".format(len(path) - 1, time, ip.states, ip.succs, flush=True))
        actions = [None] + solution_node.solution()
        for action, node in zip(actions, path):
            print("flip {} =>".format(action) if action != None else 'initial', flush=True)
            print_state(node.state)
    else:
        print("No solution found", flush=True)
    print(" ", flush=True)

    
def print_state(state):
    """ print a flipit state """
    out = sys.stdout
    size = sqrt(len(state))
    out.write('  ')
    for i, char in enumerate(state):
        if i % size == 0 and i:
            out.write('\n  ')
        out.write(char)
    out.write('\n')

# if called from the command line, call run_tests
if __name__ == "__main__":
    run_tests()
        
