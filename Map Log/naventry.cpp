#include "StdAfx.h"
#include "naventry.h"
using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;	// for String->char* conversion :)

NavEntry::NavEntry(void)
{
	this->id = 0;
	this->recorded = System::DateTime::Now.Ticks;
	this->visited = 0;
	this->navPos = NULL;
	this->sectPos = NULL;
	this->parent = NULL;
	this->lngParent = -1;
	this->name = NULL;
	this->type = NULL;
	this->value = NULL;
	this->expanded = false;
}

NavEntry::NavEntry(NavEntry& navSource)
{
	this->navPos = new Pos(navSource.navPos->x, navSource.navPos->y, navSource.navPos->z);
	this->sectPos = new Pos(navSource.sectPos->x, navSource.sectPos->y, navSource.sectPos->z);
	this->parent = navSource.parent;
	this->type = NULL;
	this->name = NULL;
	this->value = NULL;
	this->visited = navSource.visited;
	this->recorded = System::DateTime::Now.Ticks;
	this->SetType(navSource.type);
	this->SetName(navSource.name);
	this->SetValue(navSource.value);
	this->expanded = navSource.expanded;
}

bool NavEntry::Equals(NavEntry* navCompare, unsigned int intComparison)
{ // for some reason, operator overloading does not want to work
	// hard coded enumeration for the time being
	bool returnValue = true;
	if (intComparison & NAVPOS)
		returnValue = returnValue 
		&& this->navPos->x == navCompare->navPos->x 
		&& this->navPos->y == navCompare->navPos->y
		&& this->navPos->z == navCompare->navPos->z;
	if (intComparison & NAVSECTOR)
		returnValue = returnValue
		&& this->sectPos->x == navCompare->sectPos->x 
		&& this->sectPos->y == navCompare->sectPos->y
		&& this->sectPos->z == navCompare->sectPos->z;
	if (intComparison & NAVTYPE)
		returnValue = returnValue && (strcmp(this->type, navCompare->type)==0);
	if (intComparison & NAVNAME)
		returnValue = returnValue && (strcmp(this->name,navCompare->name)==0);
	if (intComparison & NAVVALUE)
		returnValue = returnValue && (strcmp(this->value,navCompare->value)==0);
	if (intComparison & NAVPARENT)
		returnValue = returnValue && this->parent==navCompare->parent;
	if (intComparison & NAVID)
		returnValue = returnValue && this->id==navCompare->id;
	return returnValue;
}

double NavEntry::RangeTo(NavEntry* inTarget)
{
	double returnValue = -1; // default failure
	if (inTarget!=NULL)
	{ // target object exists
		if (this->navPos!=NULL && this->sectPos!=NULL && inTarget->navPos!=NULL && inTarget->sectPos!=NULL)
		{ // valid co-ordinates exist
			double dbldx = ((inTarget->sectPos->x - this->sectPos->x) * SECTORSIZE) + (inTarget->navPos->x - this->navPos->x);
			double dbldy = ((inTarget->sectPos->y - this->sectPos->y) * SECTORSIZE) + (inTarget->navPos->y - this->navPos->y);
			double dbldz = ((inTarget->sectPos->z - this->sectPos->z) * SECTORSIZE) + (inTarget->navPos->z - this->navPos->z);
			returnValue = Math::Sqrt((dbldx*dbldx)+(dbldy*dbldy)+(dbldz*dbldz));
		}
	}
	return returnValue;
}
void NavEntry::SetData(Pos* inNav, Pos* inSect, char* inType, char* inName, char* inValue)
{ // create new entry in nav data array
	this->id = 0;
	//this->date = 0;
	this->navPos = inNav;
	this->sectPos = inSect;
	this->parent = NULL;
	this->SetName(inName);
	this->SetType(inType);
	this->SetValue(inValue);
}

void NavEntry::SetNavPos(Pos* inPos)
{
	if (this->navPos!=NULL) delete this->navPos;
	this->navPos=inPos;
}

bool NavEntry::SetPosition(char* inPosition)
{
	bool returnValue = true;
	String^ strPosition;
	array<wchar_t>^ strSeparators;
	array<System::String^>^ strTokens;

	strSeparators = gcnew array<wchar_t>(3); // two entry array
	strSeparators[0]=' '; // user can use alternative delimiters
	strSeparators[1]=',';
	strSeparators[1]=';';
	
	strPosition = gcnew String(inPosition);
	strTokens = strPosition->Split(strSeparators);
	if (strTokens->Length>=6)
	{
		this->SetNavPos(new Pos(
			System::Convert::ToInt32(strTokens[0]),
			System::Convert::ToInt32(strTokens[1]),
			System::Convert::ToInt32(strTokens[2])
		));
		this->SetSectPos(new Pos(
			System::Convert::ToInt32(strTokens[3]),
			System::Convert::ToInt32(strTokens[4]),
			System::Convert::ToInt32(strTokens[5])
		));
	}
	else
		returnValue = false;
	
	delete strPosition;
	return returnValue;
}

void NavEntry::SetSectPos(Pos* inPos)
{
	if (this->sectPos!=NULL) delete this->sectPos;
	this->sectPos=inPos;
}

void NavEntry::SetName(char* inName)
{
	if (inName!=NULL)
	{
		if (this->name!=NULL) delete[] this->name;
		this->name = new char[strlen(inName)+2];
		strcpy_s(this->name, strlen(inName)+1, inName);
	}
}

void NavEntry::SetType(char* inType)
{
	if (inType!=NULL)
	{
		if (this->type!=NULL) delete[] this->type;
		this->type = new char[strlen(inType)+2];
		strcpy_s(this->type, strlen(inType)+1, inType);
	}
}

void NavEntry::SetValue(char* inValue)
{
	if (inValue!=NULL)
	{
		if (this->value!=NULL) delete[] this->value;
		this->value = new char[strlen(inValue)+2];
		strcpy_s(this->value, strlen(inValue)+1, inValue);
	}
}

NavEntry::~NavEntry()
{	// destructor
	if (this->navPos!=NULL) delete this->navPos;
	if (this->sectPos!=NULL) delete this->sectPos;
	if (this->type!=NULL) delete[] this->type;
	if (this->value!=NULL) delete[] this->value;
}

void NavEntry::SetParent(NavEntry* inParent)
{
	// check to ensure new parent is not a descendant first!
	bool booCheck = false;
	NavEntry* navScan = inParent;
	
	while (navScan!=NULL && !booCheck)
	{
		navScan = navScan->parent; // move up a level
		if (navScan==this) booCheck=true; // 
	}
	if (!booCheck)
	{
		this->parent = inParent;
		if (inParent!=NULL)
			this->lngParent = inParent->id;
		else
			this->lngParent = -1;
	}
}
