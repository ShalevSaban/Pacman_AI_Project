# Pacman_AI_Project


Final project in AI course.

## Game Description

-There are 3 enemies and 1 pacman .

- Pacman's goal is to escape the enemy and collect all the coins .<br/>
- Playing the game is completely automatic, without any intervention from the user.<br/>
- The maze consists of 9 rooms with the option of moving from one room to another.<br/>
- In every game run, the rooms are built differently - in different sizes, locations  and passages.<br/>
- The starting point of Pacman, enemies and coins is randomly chosen.<br/>

## Maze Implementation
- The surface is built of a 100x100 matrix .<br/>
- The rooms and passages are given the identity SPACE, the rest -WALL.<br/> 
- Transitions between rooms are constructed using the ** A* algorithm **.<br/>
 Access must be provided from each room to another, but there is no need to build all of them.<br/>
 Therefore, existing passageways between rooms are given priority over building new ones.<br/>
 
 ## Pacman Moving Implementation
 - Pacman has 2 states - collecting and escape.<br/>
 - Pacman checks every time if there are any enemies nearby.<br/>
 - BFS algorithm is used for scanning (checking for enemies).<br/>
 - During Pacman's collection of coins, the A* algorithm is used (every coin exists in the priority queue).<br/>
 - When the distance from the enemy is low, Pacman changes his state to an escape state.<br/>
 
 ## Enemy Moving Implementation
 
 


## Decision Making 
![image](https://user-images.githubusercontent.com/74130405/199086452-f977668a-32a3-40a5-84ab-190ef3f4d629.png)


