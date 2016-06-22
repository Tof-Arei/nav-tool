#pragma once

class Pos
{
	public:
	Pos();
	Pos(double, double, double);
	Pos operator+(const Pos&);
	Pos operator-(const Pos&);
	Pos operator*(double);
	Pos operator/(double);
	double Dot(const Pos&);
	Pos Cross(const Pos&);
	double ENorm(void);
	double Range(const Pos&);
	double x;
	double y;
	double z;
};