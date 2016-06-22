// Map Log.cpp : main project file.

#include "stdafx.h"
#include "pos.h"
#include "navdata.h"
#include "route.h"
#include "Navigation.h"

using namespace MapLog;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Navigation());
	return 0;
}
