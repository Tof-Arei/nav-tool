#pragma once
#include "navdata.h"
ref class MapGraphics
{
private:
	System::Drawing::Graphics^ canvas;
	System::Drawing::Image^ sourceImage;
	float xBorder, yBorder, xStart, yStart, xScale, yScale;
public:
	MapGraphics(float inXBorder, float inYBorder, float inXStart, float inYStart, float inXScale, float inYScale);
	void RenderMap(NavData*, System::String^, System::String^, int, System::String^, System::String^, System::String^);
	Pos CalculateScale(Pos inPos);
	~MapGraphics(void);
};
