Please answer the following questions using the git [markdown syntax](https://guides.github.com/features/mastering-markdown/).  You should view this file on your repo on GitHub after pushing it to make sure it looks the way you wanted it to.  You can also use a browser extension (like [this one](https://chrome.google.com/webstore/detail/markdown-preview-plus/febilkbfcbhebfnokafefeacimjdckgl) for Chrome) to view your local file.

### (1) For a square NxN flipit problem, what is a **simple** upper bound on the size of the search space (i.e., number of possible states)?  Explain your answer.**

2^(n*n) states. Every spot on the board is either a 0 or a 1 which gives the base of 2. (n*n) because that is the number of spots on the board.

### (2) What is a better upper bound for the number of possible states taking rotations and reflections into account? Explain your answer.**

(2^(n*n))/16. Divided by 16 to try to account for rotations and flipping. While this may not account for every case it still does a better job at a closer upper bound than the previous solution.

### (3) For a given NxN (for N>1) flipit problem, if a solution is possible, are more than one solutions always possible. Explain your answer.

I wouldn't think more than one solution is always possible. There are some situations that are extremely simple that only require one move in which case I think there's only one solution. Any other 'solution' in that case would involve using unneeded moves for the sole purpose of finding another solution.

### (4) Is every flipit problem on a 2x2 grid solvable?  Explain how you arrived at your answer.

Yes. There are very few unique states in a 2x2 grid so it can be proven with brute force. 
The only unique states are:
10 11 10 11 11
00 00 01 10 11
The first of which is solvable in 3 moves, the second in 2 moves, the third in 2, and the fourth in 1, and the fifth in 4.

### (5) Is every flipit action reversible.  That is if performing action A in state S1 yields state S2, will performing action A in state S2 yield S1?

Yes all actions are reversable as the current state doesn't change which points are being affected by the action A.

### (6) Describe the heuristic you used in your FlipIt_optimal problem in English and explain why it is admissible, i.e., never over-estimates the distance of a state to the nearest goal state.

The optimal solution was similar to the aggressive solution in that in counted the number of 1's left in the problem. Once it got the total number it took into consideration the maximum amount of ones that could be removed at a time (5) and divided the number by that, rounding up the result. This way any state with 5 or fewer 1's returned a value of 1 guaranteeing that it would not overestimate.

### (6) Describe the heuristic you used in your FlipIt_aggressive problem in English and explain why it is not admissible, i.e., it sometimes over-estimates the distance of a state to the nearest goal state.

The aggressive solution simpliy counted the number of 1's in the current board state and returned that number. It is not admissible because more than one of the 1's can be removed at a time. 
One example:
11
10
This solution would return 3 as there are 3 ones when there is only one move needed to solve the problem.

