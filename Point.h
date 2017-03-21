#ifndef JHHWANG_POINT_H
#define JHHWANG_POINT_H

class Point 
{
public :
	Point(int x = -1, int y = -1);
	int GetX() const { return x_; }
	int GetY() const { return y_; }
	void SetX(int x) { x_ = x; }
	void SetY(int y) { y_ = y; }
	Point operator+(const Point &pt);

	static void GotoXY(int x, int y);
	static void GotoXY(Point pos);
	static Point GetScrPosFromCurPos(const Point &pos);

private :
	int x_;
	int y_;
};

#endif