#pragma once

#include <string>

class Point
{
public:
	// Constructor
	Point();
	Point(int row, int col);
	Point(Point* other);

	// Destructor
	~Point();

	// Getters
	int getRow();
	int getCol();

	// Setters
	void setRow(int r);
	void setCol(int c);

	/// Operators Overloading
	bool operator == (const Point& other)
	{
		return other.row_ == row_ && other.col_ == col_;
	}

	// Class Functions
	bool equals(Point* other);
	std::string toString();

protected:
	int row_, col_;
};
