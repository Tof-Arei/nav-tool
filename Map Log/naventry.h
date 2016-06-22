#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "pos.h"

class NavEntry
{
	public:
		int id; // position in vector
		NavEntry* parent;	
		int lngParent; // ID of parent object
		Pos* navPos; // position within current sector (X,Y,Z)
		Pos* sectPos; // current sector co-ordinates (SX, SY, SZ)
		char* type; // entry type
		char* name; // entry display name
		char* value; // value of entry
		_int64 recorded; // date entry made
		_int64 visited; // date last visited
		bool expanded; // used to indicate whether the tree is expanded for this entry
		NavEntry();
		NavEntry(NavEntry& navSource);
		bool Equals(NavEntry* navCompare, unsigned int intComparison);
		double RangeTo(NavEntry* inTarget);
		void SetNavPos(Pos* inPos);
		void SetSectPos(Pos* inPos);
		void SetData(Pos* inNav, Pos* inSect, char* inType, char* inName, char* inValue);
		void SetName(char* inName);
		bool SetPosition(char* inPosition);
		void SetType(char* inType);
		void SetValue(char* inValue);	
		void SetParent(NavEntry* inParent);
		~NavEntry();
};