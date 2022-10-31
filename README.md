# Pacman_AI_Project


Final project in AI course.

## Game Description

-There are 3 enemies and 1 pacman .

-Pacman's goal is to escape the enemy and collect all the coins .<br/>
-Playing the game is completely automatic, without any intervention from the user.<br/>
-The maze consists of 9 rooms with the option of moving from one room to another.<br/>
-In every game run, the rooms are built differently - in different sizes, locations  and passages.<br/>
-The starting point of Pacman, enemies and coins is randomly chosen.<br/>

## Implementation
-The surface is built of a 100x100 matrix .<br/>
-The rooms and passages are given the identity SPACE, the rest -SPACE.<br/> 
-Transitions between rooms are constructed using the ** A* algorithm **.<br/>
 Access must be provided from each room to another, but there is no need to build all of them.<br/>
 Therefore, existing passageways between rooms are given priority over building new ones.<br/>
 
 


## Decision Making 
![image](https://user-images.githubusercontent.com/74130405/199086452-f977668a-32a3-40a5-84ab-190ef3f4d629.png)


