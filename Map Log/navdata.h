#pragma once
#include <stdlib.h>
#include <vector>
#include "pos.h"
#include "naventry.h"

class NavData
{
	public:
		NavData(void);
		~NavData(void);
		bool AddEntry(NavEntry* newEntry);
		NavData* BuildTrilateration(char*, NavData* navUniverse);
		void DeleteEntry(NavEntry* delEntry);
		void DeleteNavOutput(void);
		NavEntry* FindEntry(NavEntry* inEntry, unsigned int intComparison);
		NavEntry* GetEntry(int index);
		int GetEntryCount();
		void IndexEntries(void);
		void LinkGates(void);
		bool LoadFile(System::String^ inFileName);
		bool LoadNavLogFile(System::String^ inFileName);
		bool LoadNavLogFile(System::String^ inFileName, NavEntry* inParent);
		bool SaveFile(System::String^ inFileName, bool overwrite);
		bool SaveNavLogFile(System::String^ inFileName);
		void Sort(int comparison);
		void SortRange(NavEntry* navCompare);
		NavData* Trilateration();
		int Trilateration(NavEntry*, NavEntry*, NavEntry*, Pos*, Pos*);
	private:
		std::vector<NavEntry*> allEntries;

};
