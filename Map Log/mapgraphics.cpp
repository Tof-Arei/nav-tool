#include "StdAfx.h"
#include "mapgraphics.h"

Pos MapGraphics::CalculateScale(Pos inPos)
{
	Pos returnValue = inPos;
	returnValue.x -= this->xStart;
	returnValue.x *= (this->sourceImage->Width / this->xScale);
	returnValue.y -= this->yStart;
	returnValue.y *= (this->sourceImage->Height / this->yScale);
	returnValue.y = this->sourceImage->Height - returnValue.y;
	return returnValue;
}
MapGraphics::MapGraphics(float inXBorder, float inYBorder, float inXStart, float inYStart, float inXScale, float inYScale)
{
	this->xBorder = inXBorder;
	this->yBorder = inYBorder;
	this->xStart = inXStart;
	this->yStart = inYStart;
	this->xScale = inXScale;
	this->yScale = inYScale;
}

MapGraphics::~MapGraphics(void)
{
}

void MapGraphics::RenderMap(NavData* inNav, System::String^ sourceFile, System::String^ destFile,
							System::String^ fontStyle, int fontSize, System::String^ fontColor, System::String^ jmpLinesColor, System::String^ systemColor)
{ // note that the game Z axis maps onto the display Y axis
	
	System::Drawing::Brush^ currentBrush;
	System::Drawing::Pen^ currentPen;
	System::Drawing::Font^ currentFont;
	System::Drawing::SizeF textSize;
	System::String^ currentText;
	Pos pos1;
	Pos pos2;
	NavEntry* currentEntry;
	NavEntry* navDest = new NavEntry();
	
	currentFont = gcnew System::Drawing::Font(fontStyle,(float)fontSize);
	this->sourceImage = System::Drawing::Image::FromFile(sourceFile);
	this->canvas = System::Drawing::Graphics::FromImage(this->sourceImage);
	
	currentPen = gcnew System::Drawing::Pen(System::Drawing::ColorTranslator::FromHtml(jmpLinesColor));
	
	for (int intIndex = 0; intIndex<inNav->GetEntryCount(); intIndex++)
	{ // display jump lines
		currentEntry = inNav->GetEntry(intIndex);
		if (strcmp(currentEntry->type, "Jump")==0)
		{ // retrieved co-ordinates from jump
			if (navDest->SetPosition(currentEntry->value))
			{
				pos1.x = currentEntry->sectPos->x;
				pos1.y = currentEntry->sectPos->z;
				pos2.x = navDest->sectPos->x;
				pos2.y = navDest->sectPos->z;
				pos1 = this->CalculateScale(pos1);
				pos2 = this->CalculateScale(pos2);
				this->canvas->DrawLine(currentPen, float(pos1.x), float(pos1.y), float(pos2.x), float(pos2.y));
			}
		}
	}
		
	for (int intIndex = 0; intIndex<inNav->GetEntryCount(); intIndex++)
	{ // display systems
		currentEntry = inNav->GetEntry(intIndex);
		if (strcmp(currentEntry->type,"System")==0)
		{
			pos1.x = currentEntry->sectPos->x;
			pos1.y = currentEntry->sectPos->z;
			
			pos1 = this->CalculateScale(pos1);
			
			currentBrush = gcnew System::Drawing::SolidBrush(System::Drawing::ColorTranslator::FromHtml(systemColor));
			this->canvas->FillEllipse(
				currentBrush,
				float(pos1.x)-5,
				float(pos1.y)-5,
				10.0f, 10.0f
			);
			
			currentText = gcnew System::String(currentEntry->name);
			textSize = this->canvas->MeasureString(currentText, currentFont);
			
			currentBrush = gcnew System::Drawing::SolidBrush(System::Drawing::ColorTranslator::FromHtml(fontColor));
			this->canvas->DrawString(
				currentText, currentFont, currentBrush, 
				float(pos1.x) - (textSize.Width/2), 
				float(pos1.y)-(textSize.Height)-5
			);
		}
	}

	delete navDest;
	this->canvas->Save();
	this->sourceImage->Save(destFile);
}
