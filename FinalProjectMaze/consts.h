#pragma once

const int MSZ = 100;


const int SPACE = 0;
const int WALL = 1;
const int START = 2;
const int TARGET = 3;
const int PATH = 4; // belongs to the path to target
const int GRAY = 5; 
const int BLACK = 6; // VISITED
const int PACMAN = 7;
const int ENEMY = 8;
const int COIN = 9;

const int WIDTH = 800;	// Windows Width
const int HEIGHT = 800;	// Window Height

const int NUM_ROOMS = 9;	// The number of rooms in the dungeon
const int COINS_NUM = 10;
const int MIN_ROOM_WIDTH = 8;
const int MIN_ROOM_HEIGHT = 8;

const int ENEMIES_NUM = 3;

const int UP = 4;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;

const int ESCAPE_DISTANCE = 50;

const enum playerType {pacman=PACMAN,enemy=ENEMY};

