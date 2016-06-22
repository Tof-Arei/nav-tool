#include "StdAfx.h"
#include "navdata.h"
#include "uploader.h"
#include "log.h"
#include "debug.h"
#include <iostream>

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;	// for String->char* conversion

bool LogEntry::LoadFile(System::String^ inFileName, System::String^ saveDataFormat)
{
	System::String^ strCurrent;
	System::String^ strUpload;
	bool returnValue = true;

	array<wchar_t>^ strSeparators;
	array<String^>^ strSaveTokens;
	strSeparators = gcnew array<wchar_t>(1); // one entry array
	strSeparators[0] = ',';
	strSaveTokens = saveDataFormat->Split(strSeparators, 2);

	if (File::Exists(inFileName))
	{
		try
		{
			StreamReader^ inFile = File::OpenText(inFileName);
			strUpload = inFile->ReadToEnd(); // read entire file into upload string
			inFile->Close();
			inFile = File::OpenText(inFileName);
			for (int intIndex=0; intIndex<System::Convert::ToInt32(strSaveTokens[0]); intIndex++) inFile->ReadLine(); // dump first set of lines according to saveDataFormat
			this->position->id = 0;
			this->position->SetNavPos(new Pos
			(
				System::Convert::ToInt32(inFile->ReadLine()),
				System::Convert::ToInt32(inFile->ReadLine()),
				System::Convert::ToInt32(inFile->ReadLine())
			));
			this->position->SetSectPos(new Pos
			(
				System::Convert::ToInt32(inFile->ReadLine()),
				System::Convert::ToInt32(inFile->ReadLine()),
				System::Convert::ToInt32(inFile->ReadLine())
			));
			
			// comment this line out if using version previous to 1.180
			this->SetName((char*)Marshal::StringToHGlobalAnsi(inFile->ReadLine()).ToPointer());
			
			for (int intIndex=0; intIndex<System::Convert::ToInt32(strSaveTokens[1]); intIndex++) inFile->ReadLine(); // dump next set of lines according to saveDataFormat
			this->jumpRange = 0;
			while (this->jumpRange<1 && !inFile->EndOfStream)
			{
				strCurrent = inFile->ReadLine();
	
				if (strCurrent == "Fulcrum Drive C1")	this->jumpRange = SECTORSIZE;
				if (strCurrent == "Fulcrum Drive C2")	this->jumpRange = SECTORSIZE*2;
				if (strCurrent == "Fulcrum Drive C3")	this->jumpRange = SECTORSIZE*3;
				if (strCurrent == "Fulcrum Drive C4")	this->jumpRange = SECTORSIZE*4;
				if (strCurrent == "Fulcrum Drive C5")	this->jumpRange = SECTORSIZE*5;
				if (strCurrent == "Mantis Jump Drive") this->jumpRange = SECTORSIZE*10;
			}
			inFile->Close();
		}
		catch(...)
		{
			DebugFile("Unable to load data from " + inFileName);
			returnValue = false;
		}
	}
	return returnValue;
}

LogEntry::LogEntry(void)
{ // constructor
	this->position = new NavEntry();
	this->systemName = NULL;
}

LogEntry::~LogEntry(void)
{ // destructor
	if (this->systemName != NULL) delete[] this->systemName;
}

void LogEntry::SetName(char* inName)
{ // sets the system name
	if (inName!=NULL)
	{
		if (this->systemName==NULL) delete[] this->systemName;
		this->systemName = new char[strlen(inName)+2];
		strcpy_s(this->systemName, strlen(inName)+1, inName);
	}
}