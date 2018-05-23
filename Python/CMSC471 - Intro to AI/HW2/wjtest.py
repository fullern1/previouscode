import sys
import argparse
import wj
import search as a

# default searchers from aima.search to use
default_searchers = [a.breadth_first_tree_search,
                     a.breadth_first_search,
                     a.depth_first_graph_search,
                     a.iterative_deepening_search,
                     a.astar_search]

def wjsolve(capacities, start, goal, searchers=default_searchers):
    
    print("Solving WJ(%s,%s,%s)"  % (capacities, start, goal))
    for s in searchers:
        sol = s(wj.WJ(capacities, start, goal))
        print(" %s cost %s: %s"  % (s.__name__, sol.path_cost, ' '.join([str(n.state) for n in sol.path()])))

    print("SUMMARY: successors/goal tests/states generated/solution")
    a.compare_searchers([wj.WJ(capacities, start, goal)], [], searchers)

def convert(g1_g2):
    """ Returns tuple (g1,g2) after converting g1 and g2 to integers
    unless they are * """
    g1, g2 = (g1_g2)
    return (g1 if g1=='*' else int(g1),
            g2 if g2=='*' else int(g2))

# if called from the command line, call main()
if __name__ == "__main__":
    p = argparse.ArgumentParser(description='Test wj problem with several search algorithms')
    p.add_argument ('-c', '--capacities', nargs=2, type=int, default=[5,2])
    p.add_argument ('-s', '--start', nargs=2, type=int, default=[5,0])
    p.add_argument ('-g', '--goal', nargs=2, type=str, default=['0','*'])
    args = p.parse_args()
        
    wjsolve(tuple(args.capacities), tuple(args.start), convert(tuple(args.goal)))
        

