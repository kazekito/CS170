
# CS 170 - 8 puzzle problem
Authors: \<[Jessie Lu](https://github.com/Jess-say)\> \<[Bao Lam Le](https://github.com/kazekito)\> 

## Project Description
We are going to solve the 8 puzzle problem using 3 different algorithms:
  * Uniform Cost Search
  * A* with the Misplaced Tile heuristic
  * A* with the Euclidean Distance heuristic
Uniform Cost Search chooses the cheapest node, g(n), to expand and h(n) is hardcoded to 0. 
A* with the Misplaced Tile heuristic will also choose the cheapest node, g(n), to expand. However, g(n) in this case would be the number of misplaced tiles in the puzzle. 
A* with the Euclidean Distance heuristic will choose the node that also has the cheapest node. The g(n) in this heuristic would be found by using the pythagorean theorem.

## 
