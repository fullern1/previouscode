
# HW2: State Space Search
## out 2/14, due 2/26 

This short assignment will give you some experience in developing heuristics for Algorithm A*.

### 1 The FlipIt Game

Your task is to use the aima-python search.py package to write a simple system to solve the flipit game using the A* search algorithm. In this game, you are given a NxN grid where each cell holds either a 0 or a 1. If you select a cell, its value "flips" (i.e., changes from from 0 to 1 or vice versa) along with the values of the cells immediately above, below, to the left and to the right. You will be given an initial configuration and must find a sequence of actions to produce a configuration in which all of then cell holds a 0. You will produce two versions, one that uses an admissible heuristic guaranteed to find a shortest solution and another with a more aggressive heuristic that may find a non-optimal solution faster. You must also answer a set of questions about the problem and your solutions.

### 2. Preliminaries

Start by cloning the aima python code and take a brief look at it. Then study the aima search.py file. You should look at the Problem class and its methods, in particular, and the search algorithms. Note that this code only works in Python3. You can find information here on how to use Python3 on gl.

If you want to install a version of python 3 on your own computer, you can do this without removing a version of python2, if you have one already installed. You should be able to find and download the latest version of python for your operating system here.

### 3. What to do 

Accept the HW2 assignment, which will create a repository for you on GitHub, which you should clone on the computer you will use to do the homework, e.g., your laptop or gl. This repository is self contained in that it already includes the aima-python packages search.py and utils.py, so you do not need any additional files from aima-python. It also includes examples of code that uses search.py to solve the 8-puzzle (p8.py) and water jug puzzle (wj.py, wjtest.py, wj.ipnb)

Complete versions of the FlipIt class that solves instances of the flipit problem given an initial and final configuration using the aima code for astar_search. We've created a stub file for flipit.py which is the only file you need to complete. To complete this stub, you must finish the generic FlipIt class by completing the init, actions, result, goal_test, and repr methods. You will probably need to write some auxiliary functions as well. We won't actually call this class when testing your homework.

You will see in the started file that we've defined two subclasses of FlipIt:

    
    class FlipIt_optimal(FlipIt):
        name = "optimal"
        def h(self, node):
            """ Returns an admissible estimate of cost of shortest path from node to a goal """
            #add your code here
            pass
    
    class FlipIt_aggressive(FlipIt):
        name = "aggressive"
        def h(self, node):
            """ aggressive, non-admissible estimate of cost of shortest path from node to a goal """
            #add your code here
            pass
    
The optimal heuristic should be one that depends on the state (use node.state to access it) and not a trivial value like 1. The aggressive heuristic should be an estimate that is probably more accurate in identifying states that are closer to the goal, but not always an underestimate of the number of steps from the goal.

### 4. Testing your code

Once you've written your code you can execute the python file flipit_test.py, which will try your solution for several test cases of size 2, 3, 4 and 5. You can see the results that our model solution generates for this test file in sample_output.txt. While your answers might differ from the ones we've given, they should be similar. Our model solution uses use an admissible heuristic, so the lengths of the solutions fund are the shortest ones possible. Do check your answers to see if they make sense. 

### 5. Some questions to answer

Complete your copy of the file questions.md by answering each of the questions.

### 6. What to hand in 

After writing and testing your flipit.py and completing questions.md, you should commit the files and push them back to GitHub.
