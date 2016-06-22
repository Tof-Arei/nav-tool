#include "StdAfx.h"
#include "navdata.h"
#include "debug.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;	// for String->char* conversion :)

bool NavData::AddEntry(NavEntry* newEntry)
{
	allEntries.push_back(newEntry);
	return true;
}

NavData* NavData::BuildTrilateration(char* destination, NavData* navUniverse)
{ // create a trilateration table
	NavData* returnValue = new NavData();
	NavEntry* navCurrent = NULL;
	NavEntry* navLast = NULL;
	NavEntry* navDestination = NULL;
	NavEntry* navReference = NULL;
	NavEntry* navSource = NULL;
	NavEntry* navSearch = new NavEntry();
	
	for (int intIndex = 0; intIndex<this->GetEntryCount(); intIndex++)
	{
		navLast = navCurrent;
		navCurrent = this->GetEntry(intIndex);
		navDestination = NULL;
		navReference = NULL;
		navSource = NULL;
		
		if (navLast!=NULL)
		{
			if(strcmp(navCurrent->value,destination)==0 && strcmp(navLast->value,destination))
			{ // travelling from known to unknown
				navDestination = navCurrent;
				navReference = navLast;
			}
			
			if(strcmp(navCurrent->value,destination) && strcmp(navLast->value,destination)==0)
			{ // travelling from unknown to known
				navDestination = navLast;
				navReference = navCurrent;
			}
			
			if (navDestination && navReference)
			{ // traversed between systems
				navSearch->SetName(navReference->value);
				navSearch->SetType("Planet");
				if (navUniverse)
				{
					navSource = navUniverse->FindEntry(navSearch,NAVNAME+NAVTYPE);
					if (navSource)
					{ // reference is from an identifiable source
						NavEntry* navNew = new NavEntry();
						navNew->SetType("Trilateration");
						navNew->SetName(navDestination->value);
						navNew->SetValue(navReference->value);
						navNew->SetSectPos(new Pos(*navDestination->sectPos));
						navNew->SetNavPos(new Pos
						(
							navDestination->sectPos->Range(*navSource->sectPos), // trilateration range
							navReference->sectPos->Range(*navDestination->sectPos), // sector range from last entry
							0
						));
						returnValue->AddEntry(navNew);
					}
				}
			}
		}
	}
	return returnValue;
}
void NavData::DeleteEntry(NavEntry* delEntry)
{
	this->IndexEntries();
	
	if (this->allEntries[delEntry->id] == delEntry)
	{ // item exists on list
		for (int intIndex=0; intIndex<int(this->allEntries.size()); intIndex++)
		{ // check for child objects
			if (this->allEntries[intIndex]->parent == delEntry)
				this->allEntries[intIndex]->parent = delEntry->parent;
		}
		this->allEntries.erase(this->allEntries.begin()+delEntry->id);
		
		this->IndexEntries(); // sort out numbering
	}
}

void NavData::DeleteNavOutput(void)
{ // delete all generated waypoints
	NavEntry* navSearch = new NavEntry;
	navSearch->SetType(NAVOUT); // partially initialise this variable for searching
	NavEntry* navDel = this->FindEntry(navSearch, NAVTYPE);
	while (navDel!=NULL)
	{
		this->DeleteEntry(navDel);
		navDel = this->FindEntry(navSearch, NAVTYPE);
	}
	delete navSearch;
}

NavEntry* NavData::FindEntry(NavEntry* inEntry, unsigned int intComparison)
{
	NavEntry* returnValue = NULL;
	NavEntry* navIndex;
	for (int lngIndex=0; lngIndex<this->GetEntryCount() && returnValue==NULL; lngIndex++)
	{
		navIndex = this->GetEntry(lngIndex);
		if (navIndex->Equals(inEntry, intComparison))
			returnValue = navIndex;		
	}
	return returnValue;
}

NavEntry* NavData::GetEntry(int index)
{ // returns the navdata entry in position [index]
	NavEntry* returnValue = NULL;
	returnValue = allEntries[index];
	return returnValue;
}

int NavData::GetEntryCount()
{ // return the number of entries in the navdata list
	return (int)allEntries.size();
}

void NavData::IndexEntries()
{ // update all indexes to accurately reflect position in array
	for (unsigned int intIndex = 0; intIndex < allEntries.size(); intIndex++)
	{	// update id to current array position
		allEntries[intIndex]->id = intIndex;
	}
	
	for (unsigned int intIndex = 0; intIndex < allEntries.size(); intIndex++)
	{
		if (allEntries[intIndex]->parent == NULL)
			allEntries[intIndex]->lngParent = -1; // specify null parent
		else	// update correct parent id
			allEntries[intIndex]->lngParent = allEntries[intIndex]->parent->id;
	}
}

void NavData::LinkGates(void)
{
	NavEntry* navSearch = new NavEntry();
	NavEntry* navCurrent = NULL;
	NavEntry* navTarget = NULL;
	
	for (int intIndex=0; intIndex<this->GetEntryCount(); intIndex++)
	{
		navCurrent = this->GetEntry(intIndex);
		navSearch->SetType("Jump Gate");
		if (navCurrent->Equals(navSearch, NAVTYPE))
		{ // jump gate object type found
			navSearch->SetType("Jump");
			navSearch->SetParent(navCurrent); // look for children of this object
			navTarget = this->FindEntry(navSearch, NAVTYPE+NAVPARENT);
			if (navTarget == NULL)
			{ // this jump gate does not have any assigned jump co-ordinates
				navSearch->SetType("System");
				navSearch->SetName(navCurrent->name);
				navSearch->SetParent(this->FindEntry(navSearch, NAVNAME+NAVTYPE));
				if (navCurrent->parent!=NULL)
				{
					navSearch->SetName(navCurrent->parent->name); // retrieve sector name
					navSearch->SetType("Jump Gate");
					navTarget = this->FindEntry(navSearch, NAVNAME+NAVTYPE+NAVPARENT);
					if (navTarget!=NULL)
					{ // found destination jump gate!
						System::String^ strPos = System::String::Concat(System::Convert::ToString(navTarget->navPos->x), " ");
						strPos = System::String::Concat(strPos, System::Convert::ToString(navTarget->navPos->y), " ");
						strPos = System::String::Concat(strPos, System::Convert::ToString(navTarget->navPos->z), " ");
						strPos = System::String::Concat(strPos, System::Convert::ToString(navTarget->sectPos->x), " ");
						strPos = System::String::Concat(strPos, System::Convert::ToString(navTarget->sectPos->y), " ");
						strPos = System::String::Concat(strPos, System::Convert::ToString(navTarget->sectPos->z));
						navTarget = new NavEntry(*navCurrent);
						this->AddEntry(navTarget);
						navTarget->SetParent(navCurrent);
						navTarget->SetType("Jump");
						navTarget->SetValue((char*)(Marshal::StringToHGlobalAnsi(strPos).ToPointer()));
						navTarget=NULL; // immediately break link to new object pointer
					} 
				}
			}
		}
	}
}
bool NavData::LoadFile(System::String^ inFileName)
{ // populate data from source file
	using namespace System::Runtime::InteropServices;

	bool returnValue = true;
	bool booNewVersion = false;
	
	NavEntry* currentEntry = NULL;
	String^ strRead;
	array<wchar_t>^ strSeparators;
	array<System::String^>^ strTokens;
	this->allEntries.clear(); // clear entries
	
	strSeparators = gcnew array<wchar_t>(1); // one entry array
	strSeparators[0] = ',';
	
	// test to see if file is old version
	StreamReader^ inFile = File::OpenText(inFileName);
	if (!inFile->EndOfStream)
	{	
		strRead = inFile->ReadLine();
		strTokens = strRead->Split(strSeparators,14); // new style 14 entries
		if (strTokens->Length==14)
		{
			System::DateTime dateTest;
			if (System::DateTime::TryParse(strTokens[8]->Replace("\"",""), 
				dateTest) && System::DateTime::TryParse(strTokens[9]->Replace("\"",""), dateTest))
			{
				booNewVersion = true;
			}
		}
	}	
	inFile->Close();

	inFile = File::OpenText(inFileName); // reopen file for processing
	// initial pass to load main data
	while (!inFile->EndOfStream)
	{
		try
		{
			currentEntry = new NavEntry();
			strRead = inFile->ReadLine();
			strTokens = booNewVersion ? strRead->Split(strSeparators,14): strRead->Split(strSeparators,11);
			currentEntry->id = System::Convert::ToInt32(strTokens[0]);
			currentEntry->navPos = new Pos
			(
				System::Convert::ToInt32(strTokens[1]),
				System::Convert::ToInt32(strTokens[2]),
				System::Convert::ToInt32(strTokens[3])
			);
			currentEntry->sectPos = new Pos
			(
				System::Convert::ToInt32(strTokens[4]),
				System::Convert::ToInt32(strTokens[5]),
				System::Convert::ToInt32(strTokens[6])
			);
			currentEntry->lngParent = System::Convert::ToInt32(strTokens[7]);
			
			if (booNewVersion)
			{ // the file structure is in new version format
				currentEntry->recorded = System::DateTime::Parse(strTokens[8]->Replace("\"","")).Ticks;
				currentEntry->visited = System::DateTime::Parse(strTokens[9]->Replace("\"","")).Ticks;
				currentEntry->SetType(reinterpret_cast<char*>(Marshal::StringToHGlobalAnsi(strTokens[11]->Replace("\"","")).ToPointer()));
				currentEntry->SetName(reinterpret_cast<char*>(Marshal::StringToHGlobalAnsi(strTokens[12]->Replace("\"","")).ToPointer()));
				currentEntry->SetValue(reinterpret_cast<char*>(Marshal::StringToHGlobalAnsi(strTokens[13]->Replace("\"","")).ToPointer()));
			}
			else
			{
				currentEntry->SetType(reinterpret_cast<char*>(Marshal::StringToHGlobalAnsi(strTokens[8]->Replace("\"","")).ToPointer()));
				currentEntry->SetName(reinterpret_cast<char*>(Marshal::StringToHGlobalAnsi(strTokens[9]->Replace("\"","")).ToPointer()));
				currentEntry->SetValue(reinterpret_cast<char*>(Marshal::StringToHGlobalAnsi(strTokens[10]->Replace("\"","")).ToPointer()));
			}
			this->AddEntry(currentEntry);
		}
		catch(...)
		{
			DebugFile(inFileName + " read error line " + this->GetEntryCount()+1 + "(" + strRead + ")");
		}
	}
	inFile->Close();
	
	// second pass to set parent objects
	NavEntry* navSearch = new NavEntry();
	for (int lngIndex=0; lngIndex<this->GetEntryCount(); lngIndex++)
	{
		currentEntry = this->GetEntry(lngIndex);
		if (currentEntry->lngParent>=0)
		{
			navSearch->id = currentEntry->lngParent;
			currentEntry->SetParent(this->FindEntry(navSearch,NAVID));
		}	
	}
	delete navSearch;
	
	delete strSeparators;
	return returnValue; 
}

bool NavData::LoadNavLogFile(System::String^ inFileName)
{ // top level Nav Log file load
	return this->LoadNavLogFile(inFileName, NULL);
}

bool NavData::LoadNavLogFile(System::String^ inFileName, NavEntry* inParent)
{ // retrieve current entries from Nav Log file and saves them as child of inParent
	bool returnValue = false;
	NavEntry* newEntry;
	String^ strRead;
	array<wchar_t>^ strSeparators;
	array<System::String^>^ strTokens;
	array<System::String^>^ strSubTokens;

	StreamReader^ inFile = File::OpenText(inFileName);

	strSeparators = gcnew array<wchar_t>(1); // one entry array

	// initial pass to load main data
	while (!inFile->EndOfStream)
	{
		strRead = inFile->ReadLine();
		strSeparators[0] = ',';
		strTokens = strRead->Split(strSeparators,2);
		strSeparators[0] = ' ';
		strSubTokens = strTokens[0]->Split(strSeparators,7);
		if (strSubTokens->Length==7)
		{
			newEntry = new NavEntry();
			newEntry->navPos = new Pos
			(
				System::Convert::ToInt32(strSubTokens[1]->Replace("X=","")),
				System::Convert::ToInt32(strSubTokens[2]->Replace("Y=","")),
				System::Convert::ToInt32(strSubTokens[3]->Replace("Z=",""))
			);
			
			newEntry->sectPos = new Pos
			(
				System::Convert::ToInt32(strSubTokens[4]->Replace("SX=","")),
				System::Convert::ToInt32(strSubTokens[5]->Replace("SY=","")),
				System::Convert::ToInt32(strSubTokens[6]->Replace("SZ=",""))
			);
			
			if (strTokens->Length>=2)
			{
				newEntry->SetType("Nav Log");
				newEntry->SetValue("");
				newEntry->SetParent(inParent);
				newEntry->SetName(reinterpret_cast<char*>(Marshal::StringToHGlobalAnsi(strTokens[1]).ToPointer()));

				if (this->FindEntry(newEntry, NAVPOS+NAVSECTOR+NAVNAME) == NULL && strcmp(newEntry->name,"")!=0) // position and name check
				{
					this->AddEntry(newEntry);
					returnValue = true; // new entry added, return value is true
				}
			}
			else // for some reason, no text available
			{
				delete newEntry;
			}
		}
	}
	inFile->Close();
	delete strSeparators;
	return returnValue;
}

NavData::NavData(void)
{ // constructor
}

NavData::~NavData(void)
{
	allEntries.clear();
}

bool NavData::SaveFile(System::String^ inFileName, bool overwrite)
{
	NavEntry* currentEntry = NULL;
	NavEntry* navIndex = NULL;
	bool booFound = false;
	String^ strWrite;
	StreamWriter^ outFile;
	
	if (overwrite)
		outFile = File::CreateText(inFileName);
	else
		outFile = File::AppendText(inFileName);
		
	for (int lngIndex=0; lngIndex<this->GetEntryCount(); lngIndex++)
	{
		currentEntry = this->GetEntry(lngIndex);
		if (currentEntry->navPos!=NULL && currentEntry->sectPos!=NULL 
			&& currentEntry->name!=NULL && currentEntry->type!=NULL && currentEntry->value!=NULL)
		{ // navigation entry is in a state for writing to file
			outFile->Write(System::String::Concat(currentEntry->id.ToString(),","));
			outFile->Write(System::String::Concat(currentEntry->navPos->x.ToString(),","));
			outFile->Write(System::String::Concat(currentEntry->navPos->y.ToString(),","));
			outFile->Write(System::String::Concat(currentEntry->navPos->z.ToString(),","));
			outFile->Write(System::String::Concat(currentEntry->sectPos->x.ToString(),","));
			outFile->Write(System::String::Concat(currentEntry->sectPos->y.ToString(),","));
			outFile->Write(System::String::Concat(currentEntry->sectPos->z.ToString(),","));
			if (currentEntry->parent ==NULL) // handle null pointer (no parent)
				outFile->Write("-1");
			else
				outFile->Write(currentEntry->parent->id.ToString());
			outFile->Write(",");
			outFile->Write(System::String::Concat("\"",System::DateTime(currentEntry->recorded).ToString(),"\","));
			outFile->Write(System::String::Concat("\"",System::DateTime(currentEntry->visited).ToString(),"\","));
			navIndex = currentEntry;
			booFound = false;
			while (!booFound && navIndex!=NULL)
			{
				if (strcmp(navIndex->type,"System")==0)
					booFound = true;
				else
					navIndex = navIndex->parent; // move up a level
			}
			if (booFound)
				strWrite = System::String(navIndex->name).Replace("\"","");
			else strWrite = "";
			outFile->Write(System::String::Concat("\"", strWrite, "\","));
			strWrite = System::String(currentEntry->type).Replace("\"", "");
			outFile->Write(System::String::Concat("\"", strWrite, "\","));
			strWrite = System::String(currentEntry->name).Replace("\"", "");
			outFile->Write(System::String::Concat("\"", strWrite, "\","));
			strWrite = System::String(currentEntry->value).Replace("\"", "")->Replace("\n"," ")->Replace("\r", " ");
			outFile->Write(System::String::Concat("\"", strWrite,"\""));
			outFile->WriteLine();
			}
	}
	outFile->Close();
	this->IndexEntries();
	return true;
}

bool NavData::SaveNavLogFile(System::String^ inFileName)
{ // calling this will OVERWRITE the navigation log file - use carefully!
	bool returnValue = true;
	NavEntry* currentEntry = NULL;
	StreamWriter^ outFile = File::CreateText(inFileName);
	outFile->WriteLine(NAVHEADER); // standard file heading line
	for (int intIndex=0; intIndex<int(this->allEntries.size()); intIndex++)
	{
		currentEntry = this->GetEntry(intIndex);
		if (strcmp(currentEntry->type, NAVOUT)==0)
		{
			outFile->Write(System::String::Concat("> X=", currentEntry->navPos->x.ToString()));
			outFile->Write(System::String::Concat(" Y=", currentEntry->navPos->y.ToString()));
			outFile->Write(System::String::Concat(" Z=", currentEntry->navPos->z.ToString()));
			outFile->Write(System::String::Concat(" SX=", currentEntry->sectPos->x.ToString()));
			outFile->Write(System::String::Concat(" SY=", currentEntry->sectPos->y.ToString()));
			outFile->Write(System::String::Concat(" SZ=", currentEntry->sectPos->z.ToString()));
			outFile->WriteLine(System::String::Concat(",", gcnew System::String(currentEntry->name)));
		}
	}
	outFile->Close();
	return returnValue;
}
void NavData::Sort(int comparison)
{	// bubble sort for now because it's easy
	NavEntry* navSwap = NULL; // used as swap buffer
	NavEntry* navCurrent = NULL;
	bool booSwap = false;
	int intSwap = 0;
	
	for (int intIndex = 1; intIndex < this->GetEntryCount(); intIndex++)
	{ // iterate through all entries and compare to neighbour
		intSwap = intIndex-1;
		navCurrent = this->GetEntry(intIndex);
		booSwap = true;
		while (intSwap >=0 && booSwap)
		{
			navSwap = this->GetEntry(intSwap);
			if (comparison==NAVNAME)
				if (strcmp(navCurrent->name, navSwap->name)>=0) booSwap = false;
			if (comparison==NAVTYPE)
				if (strcmp(navCurrent->type, navSwap->type)>=0) booSwap = false;
			if (comparison==NAVTRILAT) // sort descending by trilateration score
				if (navCurrent->navPos->z < navSwap->navPos->z) booSwap = false;
			if (booSwap)
			{
				this->allEntries[intSwap+1] = this->allEntries[intSwap];
				this->allEntries[intSwap] = navCurrent;
			}
			intSwap--; // decrease the pointer
		}
	}
}

void NavData::SortRange(NavEntry* navCompare)
{
	NavEntry* navSwap = NULL; // used as swap buffer
	NavEntry* navCurrent = NULL;
	bool booSwap = false;
	int intSwap = 0;
	
	for (int intIndex = 1; intIndex < this->GetEntryCount() && navCompare != NULL; intIndex++)
	{ // iterate through all entries and compare to neighbour
		intSwap = intIndex-1;
		navCurrent = this->GetEntry(intIndex);
		booSwap = true;
		while (intSwap >=0 && booSwap)
		{
			navSwap = this->GetEntry(intSwap);
			if (navCurrent->RangeTo(navCompare) >= navSwap->RangeTo(navCompare)) booSwap = false;
			if (booSwap)
			{
				this->allEntries[intSwap+1] = this->allEntries[intSwap];
				this->allEntries[intSwap] = navCurrent;
			}
			intSwap--; // decrease the pointer
		}
	}
}
NavData* NavData::Trilateration()
{
	Pos result1 = Pos();
	Pos result2 = Pos();
	NavEntry* navNew = NULL;
	NavEntry* nav1 = NULL;
	NavEntry* nav2 = NULL;
	NavEntry* nav3 = NULL;
	
	NavEntry navTemplate = NavEntry();
	navTemplate.SetNavPos(new Pos());
	navTemplate.SetSectPos(new Pos());
	navTemplate.SetName("Debug");
	navTemplate.SetType("Trilateration");
	navTemplate.SetValue("No Value");
	int test = 0;
	NavData* navResults = new NavData();
	NavData* returnValue = new NavData();
	for (int intP1=0; intP1<this->GetEntryCount(); intP1++)
	{
		for (int intP2=intP1+1; intP2<this->GetEntryCount(); intP2++)
		{
			for (int intP3=intP2+1; intP3<this->GetEntryCount(); intP3++)
			{
				nav1 = this->GetEntry(intP1);
				nav2 = this->GetEntry(intP2);
				nav3 = this->GetEntry(intP3);
				if(!this->Trilateration(nav1, nav2, nav3, &result1, &result2))
				{
					// determine separation factor
					navTemplate.navPos->x = nav1->sectPos->Range(*nav2->sectPos);
					navTemplate.navPos->x *= nav2->sectPos->Range(*nav3->sectPos);
					navTemplate.navPos->x *= nav3->sectPos->Range(*nav1->sectPos);
					
					// determine inaccuracy percentage
					navTemplate.navPos->y = nav1->navPos->y/nav1->navPos->x;
					navTemplate.navPos->y *= nav2->navPos->y/nav2->navPos->x;
					navTemplate.navPos->y *= nav3->navPos->y/nav3->navPos->x;
					navTemplate.navPos->y *= 1000000;
					
					// determine overall accuracy ranking
					navTemplate.navPos->z = navTemplate.navPos->x / navTemplate.navPos->y;
					
					
					// handle results
					navNew = new NavEntry(navTemplate);
					result1.x = Math::Round(result1.x);
					result1.y = Math::Round(result1.y);
					result1.z = Math::Round(result1.z);
					result2.x = Math::Round(result2.x);
					result2.y = Math::Round(result2.y);
					result2.z = Math::Round(result2.z);
					navNew->SetSectPos(new Pos(result1));
					navResults->AddEntry(navNew);
					
					navNew = new NavEntry(navTemplate);
					navNew->SetSectPos(new Pos(result2));
					navResults->AddEntry(navNew);
					navNew=NULL; // remove active pointer link
				}
			}
		}
	}
	navResults->IndexEntries();
	navResults->Sort(NAVTRILAT);
	navResults->SaveFile(TRILATOUT,true); // output data for analysis

	for (int intIndex=0; intIndex<navResults->GetEntryCount() && returnValue->GetEntryCount()<5; intIndex++)
	{
		navNew = new NavEntry(*navResults->GetEntry(intIndex));
		navNew->SetNavPos(new Pos(0,0,0));
		navNew->SetType(NAVOUT);
		if (!returnValue->FindEntry(navNew,NAVTYPE+NAVSECTOR)) 
			returnValue->AddEntry(navNew);
		navNew = NULL;
	}
	delete navResults;
	return returnValue;
}

int NavData::Trilateration(NavEntry* nav1, NavEntry* nav2, NavEntry* nav3, Pos* result1, Pos* result2)
{ // code derived from Wikipedia
	Pos ex, ey, ez, t1, t2;
	double r1, r2, r3, h, i, j, x, y, z, t;
	
	Pos p1 = *nav1->sectPos;
	Pos p2 = *nav2->sectPos;
	Pos p3 = *nav3->sectPos;
	r1 = nav1->navPos->x; // x position of navpos co-ordinates contains r
	r2 = nav2->navPos->x;
	r3 = nav3->navPos->x;
	
	// test solution overrides data
	/*p1 = Pos(0,0,0);
	p2 = Pos(1,0,0);
	p3 = Pos(1,1,0);
	Pos solution = Pos(4,2,1);
	r1 = p1.Range(solution);
	r2 = p2.Range(solution);
	r3 = p3.Range(solution);*/
	
	// start calculation
	ex = p2 - p1;
	h = ex.ENorm();
	if (h<=MAXZERO) return -1; // p1 and p2 are concentric
	ex = ex/h;
	t1 = p3-p1;
	i = ex.Dot(t1);
	t2 = ex*i;
	ey = t1-t2;
	t = ey.ENorm();
	if (t > MAXZERO)
	{
		ey = ey/t;
		j = ey.Dot(t1);
	}
	else j = 0.0;
	
	if (System::Math::Abs(j)<=MAXZERO)
	{ // p1, p2 and p3 are colinear
		t2 = p1+(ex*r1);
		if (System::Math::Abs((p2-t2).ENorm()-r2)<=MAXZERO 
				&& System::Math::Abs((p3-t2).ENorm()-r2)<=MAXZERO)
		{ // t2 is the only intersection point
			if (result1) *result1 = t2;
			if (result2) *result2 = t2;
			return 0;
		}
		t2 = p1+(ex*-r1);
		if (System::Math::Abs((p2-t2).ENorm()-r2)<=MAXZERO 
				&& System::Math::Abs((p3-t2).ENorm()-r3)<=MAXZERO)
		{ // t2 is the only intersection point
			if (result1) *result1 = t2;
			if (result2) *result2 = t2;
			return 0;
		}
		return -2;
	}
	ez = ex.Cross(ey);
	x = (r1*r1 - r2*r2) / (2*h) + h/2;
	y = (r1*r1 - r3*r3 + i*i) / (2*j) + j/2 - x*i/j;
	z = r1*r1 - x*x - y*y;
	if (z<-MAXZERO) return -3; // solution is invalid
	if (z>0.0) 
		z = System::Math::Sqrt(z);
	else
		z = 0.0;
		
	t2 = p1+(ex*x);
	t2 = t2+(ey*y);
	
	Pos resulty1;
	Pos resulty2;
	if (result1)
		*result1 = t2+(ez*z);
	if (result2)
		*result2 = t2+(ez*-z);
	
	return 0;
}