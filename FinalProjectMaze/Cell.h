#pragma once
#include <vector>
#include "Point.h"


class Cell
{
public:
	// Constructors
	Cell();
	Cell(Point& point, Point* target, int v, double g, Cell* parent);
	Cell(int r, int c, int tr, int tc, double h, double g, Cell* p);
	Cell(int r, int c, int tr, int tc, double h, Cell* p);
	Cell(Cell* other);

	// Destructor
	~Cell();

	// Getters
	int getRoomIndex();
	int getIdentity();
	int getSearchIdentity();
	double getG();
	double getGVal();
	double getFVal(); //change that
	double getF();
	double getH();
	double getDanger();
	double computeH();
	bool getVist();
	Point getPoint();
	Point* getTarget();
	Cell* getParent();

	// Setters
	void setRoomIndex(int index);
	void setIdentity(int identity);
	void setFVal(double val);
	void setGVal(double val);
	void setDanger(double danger);
	void setSearchIdentity(int identity);
	void setPoint(int x, int y);
	void setParent(Cell* parent);
	void setH(double val) { h_ = val; };
	void setVisted(bool visited) { isVisted = visited; }
	

	// Operator Overloading
	bool operator == (const Cell& other) {
		return point_ == other.point_;
	}

	// Class functions
	bool Equals(Cell* other);
	bool Walkable();

private:
	int cell_identity_, room_index_, search_identity_;
	double h_, g_,f_;
	double danger_, f_val_, g_val_;
	Cell* parent_;
	Point point_;
	Point* target_point_;
	bool isVisted;
};

