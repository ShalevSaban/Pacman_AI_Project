#pragma once
#include "Point.h"

class Room
{
public:
	// Constructors
	Room();
	Room(int row, int col, int width, int height);

	// Destructor
	~Room();

	// Getters
	Point getLeftTop();
	Point getRightBottom();
	Point getCenter();

	bool IsOverlap(Room* other);
	void toString();

private:
	Point left_top_, right_bottom_, center_;
	int width_, height_;
};
