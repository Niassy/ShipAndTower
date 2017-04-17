#ifndef _COORDINATE_

#define _COORDINATE_



class Coordinate
{
protected:

	// coordinate x
	int m_iX;

	// coordinate y
	int m_iY;


public :
	
	Coordinate(int x, int y);


	void setX(int x){ m_iX = x; }
	int getX(){ return m_iX; }

	void setY(int y){ m_iY = y; }
	int getY(){ return m_iY; }
};
#endif