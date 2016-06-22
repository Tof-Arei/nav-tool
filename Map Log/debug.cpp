#include "StdAfx.h"
#include "debug.h"

using namespace System::IO;
using namespace System;

bool DebugFile(System::String^ strDebug)
{
	bool booReturn = true; // default to success
	try
	{
		StreamWriter^ outFile = File::AppendText("Map Log Errors.txt");
		outFile->Write("[" + System::DateTime::Now.ToString());
		outFile->WriteLine("] " + strDebug);
		outFile->Close(); // done appending to error log!
	}
	catch(...)
	{ // some kind of error, return false
		booReturn = false;
	}
	return booReturn;
}