# Pacman_AI_Project

https://user-images.githubusercontent.com/74130405/198837419-c248a99d-4844-4927-a233-dcabd3a5ca2d.mp4

Final project in AI course.

##Game Description

-There are 3 enemies and 1 pacman .

-Pacman's goal is to escape the enemy and collect all the coins .
-Playing the game is completely automatic, without any intervention from the user.
-The maze consists of 9 rooms with the option of moving from one room to another.
-In every game run, the rooms are built differently - in different sizes, locations  and passages.
-The starting point of Pacman, enemies and coins is randomly chosen.

## Implementation
-The surface is built of a 100x100 matrix .
-The rooms and passages are given the identity SPACE, the rest -SPACE. 
-Transitions between rooms are constructed using the ** A* algorithm **.
 Access must be provided from each room to another, but there is no need to build all of them.
 Therefore, existing passageways between rooms are given priority over building new ones.
 
 


## Decision Making 
![image](https://user-images.githubusercontent.com/74130405/199086452-f977668a-32a3-40a5-84ab-190ef3f4d629.png)


