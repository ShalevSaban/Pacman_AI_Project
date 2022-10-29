#include <string>
#include "Point.h"

// Constructors
Point::Point()
{
}

Point::Point(Point* other)
{
	this->col_ = other->col_;
	this->row_ = other->row_;
}

Point::Point(int row, int col)
{
	this->col_ = row;
	this->row_ = col;
}


Point::~Point()
{
}

// Getters
int Point::getRow()
{
	return row_;
}

int Point::getCol()
{
	return col_;
}

// Setters
void Point::setRow(int r) {
	row_ = r;
}

void Point::setCol(int c)
{
	col_ = c;
}

std::string Point::toString()
{
	std::string str;
	str.append("(");
	str.append(std::to_string(this->row_));
	str.append(";");
	str.append(std::to_string(this->col_));
	str.append(")");
	return str;
}


bool Point::equals(Point* p)
{
	return this->row_ == p->row_ && this->col_ == p->col_;
}