
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

## Start the program
Using the terminal you would first need to type in `g++ -o <program name> main.cpp`
Then type in the command `./program_name.exe`
Note: Program name is not what you need to type in. You must type in the program name that you have named it

## Using the program
Once the terminal is opened you will see the starting message. 
![Begin Program](https://cdn.discordapp.com/attachments/830297455660236814/839440512103481385/unknown.png)

Follow the instructions and type 1 for the default puzzle or 2 to enter your own. Then hit enter. Depending on what choice you enter different options should pop up.

If you typed in 1. You should get the following message.
![Option 1](https://cdn.discordapp.com/attachments/830297455660236814/839442308268949564/unknown.png)

If you typed in 2. You should get the following message.
![Option 2](https://cdn.discordapp.com/attachments/830297455660236814/839441588857733141/unknown.png)
