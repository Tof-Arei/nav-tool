#include "StdAfx.h"
#include <stdlib.h>
#include <vector>
#include "pos.h"

Pos::Pos()
{	// plain constructor
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Pos::Pos(double inX, double inY, double inZ)
{ // copy from existing position
	this->x = inX;
	this->y = inY;
	this->z = inZ;
}

Pos Pos::operator+(const Pos& inPos)
{
	return Pos
	(
		this->x + inPos.x,
		this->y + inPos.y,
		this->z + inPos.z
	);
}

Pos Pos::operator-(const Pos& inPos)
{
	return Pos
	(
		this->x - inPos.x,
		this->y - inPos.y,
		this->z - inPos.z
	);
}

Pos Pos::operator*(double scale)
{ // multiply vector by number
	return Pos(this->x*scale, this->y*scale, this->z*scale);
}

Pos Pos::operator/(double scale)
{ // multiply vector by number
	return Pos(this->x/scale, this->y/scale, this->z/scale);
}

Pos Pos::Cross(const Pos& inPos)
{ 
	return Pos
	(
		this->y * inPos.z - this->z * inPos.y,
		this->z * inPos.x - this->x * inPos.z,
		this->x * inPos.y - this->y * inPos.x
	);
}

double Pos::Dot(const Pos &inPos)
{ // dot product with another vector
	double returnValue = 0;
	returnValue = this->x * inPos.x;
	returnValue += this->y * inPos.y;
	returnValue += this->z * inPos.z;
	return returnValue;
}

double Pos::ENorm(void)
{
	return System::Math::Sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}
double Pos::Range(const Pos& inPos)
{ // return range to another position
	double returnValue = 
		(inPos.x-this->x)*(inPos.x-this->x) 
		+ (inPos.y-this->y)*(inPos.y-this->y)
		+ (inPos.z-this->z)*(inPos.z-this->z);
	returnValue = System::Math::Sqrt(returnValue);
	return returnValue;
}