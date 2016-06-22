#include "StdAfx.h"
#include "navdata.h"
#include "log.h"
#include "route.h"
#include "mapgraphics.h"
#include "Navigation.h"
#include "uploader.h"
#include "settings.h"
#include "debug.h"

using namespace MapLog;
using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;	// for String->char* conversion :)
	
Navigation::Navigation(void)
{	// constructor and test
	this->navMove = NULL;
	navSelected = NULL;
	navClosest = NULL;
	InitializeComponent();
	currentUniverse = new NavData();
	logImport = NULL;
	currentLog = new NavData();

	frmSettings = gcnew Settings();
	if (File::Exists(SAVEFILE))
		currentUniverse->LoadFile(SAVEFILE);
	
	this->DisplayTree(currentUniverse);	
	routeCalc = new Route();

}

Navigation::~Navigation()
{	// destructor
	if (components)
	{
		delete components;
	}
	
	delete frmSettings;
	currentUniverse->SaveFile(SAVEFILE, true);
	
	if (currentLog->GetEntryCount() > 0) currentLog->SaveFile(LOGFILE, false); // append log data to log file
	if (this->logImport!=NULL) delete this->logImport;
	delete currentUniverse;
	delete currentLog;
	delete routeCalc;
}

System::Void Navigation::attemptTrilaterationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (this->currentLog)
	{ // save remainder of log if any exists
		if (this->currentLog->GetEntryCount()>0)
		{
			this->currentLog->SaveFile(LOGFILE, false);
			delete this->currentLog;
			this->currentLog = new NavData();
		}
	}
	
	if (this->logImport)
	{
		NavData* navLogData = new NavData();
		navLogData->LoadFile(LOGFILE);
		NavData* navTrilat = navLogData->BuildTrilateration(logImport->systemName, currentUniverse);
		//NavData* navTrilat = navLogData->BuildTrilateration("H424", currentUniverse);
		delete navLogData;
		NavData* navEstimates = navTrilat->Trilateration();
		for (int intIndex=0; intIndex<navEstimates->GetEntryCount(); intIndex++)
		{
			System::String^ strTemp;
			strTemp = System::String::Concat
			(
				gcnew System::String(logImport->systemName),
				" - Possible Location"
			);
			navEstimates->GetEntry(intIndex)->SetName((char*)(Marshal::StringToHGlobalAnsi(strTemp).ToPointer()));
			this->currentUniverse->AddEntry(new NavEntry(*navEstimates->GetEntry(intIndex)));
		}
		delete navEstimates;
		
		// update nav log file if allowed
		if (File::Exists(this->frmSettings->strMapLogFile->Replace("\\","\\\\")) && this->chkUpdateNav->Checked)
			this->currentUniverse->SaveNavLogFile(this->frmSettings->strMapLogFile->Replace("\\","\\\\"));
		
		this->DisplayTree(this->currentUniverse);
	}
}
System::Void Navigation::btnClone_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->navSelected!=NULL)
	{
		NavEntry* newEntry = new NavEntry(*navSelected);
		newEntry->SetParent(navSelected);
		this->currentUniverse->AddEntry(newEntry);
		this->DisplayTree(currentUniverse);
	}
}

System::Void Navigation::btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
{ // deletes node
	if (this->navSelected != NULL)
	{
		this->currentUniverse->DeleteEntry(this->navSelected);
		this->navSelected = NULL;
		this->DisplayTree(this->currentUniverse);
	}
}
System::Void Navigation::btnDeleteWaypoints_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (this->currentUniverse!=NULL)
	{ // universe is available for processing
		this->currentUniverse->DeleteNavOutput();
		
		if (File::Exists(this->frmSettings->strMapLogFile->Replace("\\","\\\\")) && this->chkUpdateNav->Checked)
		{ // update map log file approved by user, refresh nav file contents
			this->currentUniverse->SaveNavLogFile(this->frmSettings->strMapLogFile->Replace("\\","\\\\"));
		}
		this->DisplayTree(this->currentUniverse);
	}
}
System::Void Navigation::btnHideLowerPanel_Click(System::Object^  sender, System::EventArgs^  e)
{ // toggle visibility of lower detail panel
	this->splitInterface->Panel2Collapsed = !this->splitInterface->Panel2Collapsed;
}

System::Void Navigation::btnMove_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->navSelected!=NULL)
	{
		if (this->navSelected!=this->navMove)
			this->navMove = this->navSelected;
		else
			this->navMove = NULL;
	}
	else
		this->navMove = NULL;
		
	this->RefreshForm();
}

System::Void Navigation::btnPromote_Click(System::Object^ sender, System::EventArgs^ e)
{ // returns node to top level
	//System::Windows::Forms::WebBrowser^ webTest = gcnew System::Windows::Forms::WebBrowser();
	//webTest->Navigate("http://evochron.junholt.se/objectdescriptions/gatesobject.htm",true);
	//webTest->Url = "http://evochron.junholt.se/objectdescriptions/gatesobject.htm"
	if (this->navSelected!=NULL)
	{
		this->navSelected->SetParent(NULL);
		this->DisplayTree(this->currentUniverse);
	}
}

System::Void Navigation::btnRefresh_Click(System::Object^ sender, System::EventArgs^ e)
{ // refresh button clicked, update tree
	this->DisplayTree(this->currentUniverse);
}

System::Windows::Forms::TreeNode^ Navigation::BuildNode(NavEntry* inNav)
{
	System::Windows::Forms::TreeNode^ returnValue = gcnew System::Windows::Forms::TreeNode;

	returnValue->ImageKey = "Deselected";
	if (strcmp(inNav->type,"City")==0) returnValue->ImageKey = "City";
	if (strcmp(inNav->type,"Planet")==0) returnValue->ImageKey = "Planet";
	if (strcmp(inNav->type,"Station")==0) returnValue->ImageKey = "Station";
	if (strcmp(inNav->type,"Waypoint")==0) returnValue->ImageKey = "Waypoints";
	if (strcmp(inNav->type,"Nav Log")==0) returnValue->ImageKey = "NavLog";
	if (strcmp(inNav->type,NAVOUT)==0) returnValue->ImageKey = "Waypoints";
	if (strcmp(inNav->type,"Environment")==0) returnValue->ImageKey = "Environment";
	if (strcmp(inNav->type,"Jump")==0) returnValue->ImageKey = "Jump";
	if (strcmp(inNav->type,"Jump Gate")==0) returnValue->ImageKey = "Jumpgate";
	if (strcmp(inNav->type,"Worm Hole")==0) returnValue->ImageKey = "Wormhole";
	if (strcmp(inNav->type,"Moon")==0) returnValue->ImageKey = "Moon";
	if (strcmp(inNav->type,"Asteroids")==0) returnValue->ImageKey = "Asteroids";
	if (strcmp(inNav->type,"Asteroid Cave")==0) returnValue->ImageKey = "Asteroid Cave";
	if (strcmp(inNav->type,"Group")==0) returnValue->ImageKey = "Folder";
	if (strcmp(inNav->type,"Black Hole")==0) returnValue->ImageKey = "Black Hole";
	if (strcmp(inNav->type,"System")==0) returnValue->ImageKey = "System";
	if (strcmp(inNav->type,"Container")==0) returnValue->ImageKey = "Container";
	
	
	returnValue->SelectedImageKey=returnValue->ImageKey;
	returnValue->Name = inNav->id.ToString();
	returnValue->Text = gcnew System::String(inNav->name);
	returnValue->ToolTipText = System::String::Concat(System::Convert::ToString(inNav->navPos->x), "x ");
	returnValue->ToolTipText = System::String::Concat(returnValue->ToolTipText, System::Convert::ToString(inNav->navPos->y), "y ");
	returnValue->ToolTipText = System::String::Concat(returnValue->ToolTipText, System::Convert::ToString(inNav->navPos->z), "z ");
	returnValue->ToolTipText = System::String::Concat(returnValue->ToolTipText, System::Convert::ToString(inNav->sectPos->x), "sx ");
	returnValue->ToolTipText = System::String::Concat(returnValue->ToolTipText, System::Convert::ToString(inNav->sectPos->y), "sy ");
	returnValue->ToolTipText = System::String::Concat(returnValue->ToolTipText, System::Convert::ToString(inNav->sectPos->z), "sz");
	if (inNav->recorded>1)
		returnValue->ToolTipText = System::String::Concat(returnValue->ToolTipText, "\nRecorded: ", System::DateTime(inNav->recorded).ToString());
	if (inNav->visited>1)
		returnValue->ToolTipText = System::String::Concat(returnValue->ToolTipText, "\nLast Visited: ", System::DateTime(inNav->visited).ToString());
	return returnValue;
}

Void Navigation::cboType_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	using namespace System::Runtime::InteropServices;	// for String->char* conversion :)
	if (this->navSelected!=NULL)
		this->navSelected->SetType((char*)(Marshal::StringToCoTaskMemAnsi((((System::Windows::Forms::ComboBox^)(sender)))->Text).ToPointer()));
}

void Navigation::DisplayTree(NavData* navData, System::Windows::Forms::TreeNode^ inNode)
{
	NavEntry* currentNav;
	System::Windows::Forms::TreeNode^ currentNode;
	for (int lngIndex=0; lngIndex < navData->GetEntryCount(); lngIndex++)
	{
		currentNav = navData->GetEntry(lngIndex);
		NavEntry* navTemp = navData->GetEntry(System::Convert::ToInt32(inNode->Name));
		if (currentNav->parent == navTemp)
		{	// current node has selected parent
			currentNode = this->BuildNode(currentNav);
			inNode->Nodes->Add(currentNode);
			this->DisplayTree(navData, currentNode);	// recursively descend into tree madness
			
		}
	}
}

void Navigation::DisplayTree(NavData* navData, System::String^ searchText)
{
	// initial pass
	System::String^ strName;
	System::Windows::Forms::TreeNode^ currentNode;
	NavEntry* currentNav;
	
	navData->IndexEntries(); // ensure entries are indexed correctly
	this->treeObjects->Nodes->Clear();
	
	for (int lngIndex=0; lngIndex < navData->GetEntryCount(); lngIndex++)
	{ // rebuild tree
		try
		{
			currentNav = navData->GetEntry(lngIndex);
			strName = gcnew System::String(currentNav->name);
			if (strName->ToUpper()->Contains(searchText->ToUpper()))
			{
				currentNode = this->BuildNode(currentNav);
				this->treeObjects->Nodes->Add(currentNode);
				this->ExpandTree(currentNode);
			}
		}
		catch(...)
		{
			DebugFile("Tree display error (" + currentNav->id + " " + gcnew System::String(currentNav->name) + ")");
		}
	}
}
void Navigation::DisplayTree(NavData* navData)
{
	// initial pass
	System::Windows::Forms::TreeNode^ currentNode;
	NavEntry* currentNav;
	
	navData->IndexEntries(); // ensure entries are indexed correctly
	this->treeObjects->Nodes->Clear();
	
	for (int lngIndex=0; lngIndex < navData->GetEntryCount(); lngIndex++)
	{ // rebuild tree
		try
		{
			currentNav = navData->GetEntry(lngIndex);
			if (currentNav->parent == NULL)
			{
				currentNode = this->BuildNode(currentNav);
				this->treeObjects->Nodes->Add(currentNode);
				this->DisplayTree(navData, currentNode);
				this->ExpandTree(currentNode);
			}
		}
		catch(...)
		{
			DebugFile("Tree display error (" + currentNav->id + " " + gcnew System::String(currentNav->name) + ")");
		}
	}
}

void Navigation::ExpandTree(System::Windows::Forms::TreeNode^ currentNode)
{
	for (int intIndex=0; intIndex<currentNode->Nodes->Count; intIndex++)
	{ // expand children
		this->ExpandTree(currentNode->Nodes[intIndex]);
	}
	// perform expansion
	if (this->currentUniverse->GetEntry(System::Convert::ToInt32(currentNode->Name))->expanded)
		currentNode->Expand();
	else
		currentNode->Collapse();
}

System::Void Navigation::hideLowerPaneToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->splitInterface->Panel2Collapsed = this->hideLowerPaneToolStripMenuItem->Checked;
}

System::Void Navigation::linkJumpGatesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{ // link jump gates button clicked, attempt to link gates
	if (this->currentUniverse)
	{
		this->currentUniverse->LinkGates();
		this->DisplayTree(this->currentUniverse);
	}
}

System::Void Navigation::nameToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->currentUniverse->Sort(NAVNAME);
	this->currentUniverse->IndexEntries();
	this->DisplayTree(currentUniverse);
}

System::Void Navigation::Navigation_Activated(System::Object^  sender, System::EventArgs^  e)
{ // when form gains focus, perform checks
	this->RefreshForm();
}

System::Void Navigation::optionsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->frmSettings->Show();
}

System::Void Navigation::rangeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	//NavEntry* currentPos;
	LogEntry* currentPos = new LogEntry();
	if (File::Exists(this->frmSettings->strGameLogFile->Replace("\\","\\\\")))
	{ // log file exists
		if (currentPos->LoadFile(this->frmSettings->strGameLogFile->Replace("\\","\\\\"), frmSettings->strSaveDataFormat))
		{ // file loaded correctly
			this->currentUniverse->SortRange(currentPos->position);
			this->currentUniverse->IndexEntries();
			this->DisplayTree(currentUniverse);
		}
	}
}
void Navigation::RefreshForm(void)
{
	double dblRange;
	
	if (this->navMove!=NULL)
		this->btnMove->BackColor = System::Drawing::Color::SteelBlue;
	else
		this->btnMove->BackColor = this->btnDelete->BackColor;
		
	if (this->navSelected!=NULL)
	{
		this->cboType->Text = gcnew System::String(navSelected->type);
		this->txtValue->Text = gcnew System::String(navSelected->value);
	}
	else
	{
		this->cboType->Text = "";
		this->txtValue->Text = "";
	}
	
	if (this->navClosest!=NULL && logImport!=NULL)
	{ // unvisited entry identified, calculate colour
		unsigned int intRGB;
		unsigned int intFade = 100;
		this->txtSearch->ToolTipText = gcnew System::String(navClosest->name);
		dblRange = logImport->position->RangeTo(navClosest);
		if (dblRange>EXPLORERANGE) dblRange = EXPLORERANGE; // 
		dblRange = dblRange/EXPLORERANGE;
		dblRange = Math::Floor(dblRange*(255-intFade));
		unsigned int intColour = System::Convert::ToUInt32(dblRange);
		intRGB = 0xFF00;
		intRGB |= 255-intColour;
		intRGB *= 256;
		intRGB |= (255-intColour > intFade + intColour) ? intFade + intColour: 255-intColour;
		intRGB *= 256;
		intRGB |= intFade + intColour;
		this->txtSearch->BackColor = System::Drawing::Color::FromArgb(intRGB);
	}
	else
	{ // no search
		this->txtSearch->ToolTipText = "";
		this->txtSearch->BackColor = System::Drawing::Color::FromArgb(192, 255, 192);
	}
	
	// perform file checks
	if (File::Exists(frmSettings->strMapLogFile->Replace("\\","\\\\")))
	{
		this->chkLoadNav->Enabled = true;
		this->chkUpdateNav->Enabled = true;
	}
	else
	{ // unable to locate nav file, disable checkboxes
		this->chkLoadNav->Enabled = false;
		this->chkLoadNav->Checked = false; // disable nav loading
		this->chkUpdateNav->Enabled = false;
		this->chkUpdateNav->Checked = false; // disable nav updating
	}
	if (File::Exists(this->frmSettings->strGameLogFile->Replace("\\","\\\\")))
		this->chkLoadLog->Enabled = true;
	else
	{ // unable to locate log file, disable checkbox
		this->chkLoadLog->Enabled = false;
		this->chkLoadLog->Checked = false; // disable log loading
	}
}

System::Void Navigation::saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	currentUniverse->SaveFile(SAVEFILE, true);
	float scaleX = 12250.0f;
	float scaleY = 12250.0f;
	MapGraphics^ mapTest = gcnew MapGraphics(0.1f,0.1f,-scaleX/2.0f,-scaleY/2,scaleX,scaleY);
	//mapTest->RenderMap(currentUniverse, "Background.jpg", "S:\\sw3dg\\EvochronMercenary\\hud\\map.png");
	if (File::Exists(frmSettings->strDMapInFile->Replace("\\", "\\\\")))
	{
		mapTest->RenderMap(
			currentUniverse,
			frmSettings->strDMapInFile->Replace("\\", "\\\\"), 
			frmSettings->strDMapOutFile->Replace("\\", "\\\\"),
			frmSettings->intFontSize,
			frmSettings->strFontColor,
			frmSettings->strJmpLinesColor,
			frmSettings->strSystemColor
		);
	}
	
}

System::Void Navigation::selectedNodeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->topLevelToolStripMenuItem->Checked = false;
	this->selectedNodeToolStripMenuItem->Checked = true;
}
System::Void Navigation::timRefresh_Tick(System::Object^ sender, System::EventArgs^ e)
{
	System::Drawing::Color colOriginal = this->txtDisplayPos->BackColor;
	String^ strFileName;
	bool booChanged = false;
	bool booNewSystem = false;

	if (this->chkLoadNav->Checked)
	{
		strFileName = this->frmSettings->strMapLogFile->Replace("\\", "\\\\");
		if (File::Exists(strFileName) && this->navDate!=File::GetLastWriteTime(strFileName))
		{
			this->navDate=File::GetLastWriteTime(strFileName);
			if (this->currentUniverse!=NULL) 
			{
				if (this->selectedNodeToolStripMenuItem->Checked)
					booChanged = this->currentUniverse->LoadNavLogFile(strFileName, this->navSelected);
				else // no entry selected, top level output
					booChanged = this->currentUniverse->LoadNavLogFile(strFileName, NULL);
				
				this->DisplayTree(currentUniverse);
			}
		}

		// perform nav updates if requested
		if (File::Exists(strFileName) && this->chkUpdateNav->Checked && booChanged)
			this->currentUniverse->SaveNavLogFile(strFileName);
	}

	// process log file
	strFileName = this->frmSettings->strGameLogFile->Replace("\\","\\\\");
	if (File::Exists(strFileName) && this->logDate != File::GetLastWriteTime(strFileName))
	{
		try
		{
			// pre-load file contents if upload URL is specified
			System::String^ strUpload;
			StreamReader^ inFile = File::OpenText(strFileName);
			strUpload = inFile->ReadToEnd(); // read entire file into upload string
			inFile->Close();
			
			// perform visiting check
			if (logImport==NULL) logImport = new LogEntry();
			NavEntry* navIndex = NULL;
			double dblRange;

			this->logDate = File::GetLastWriteTime(strFileName);
			logImport->LoadFile(strFileName, frmSettings->strSaveDataFormat);

			if (this->chkLoadLog->Checked)
			{ // append data to log file
				logImport->position->SetType("Flight Log");
				logImport->position->SetName("Log");
				logImport->position->SetValue(logImport->systemName);
				this->currentLog->AddEntry(new NavEntry(*(logImport->position)));
				if (this->currentLog->GetEntryCount() > 10)
				{
					this->currentLog->SaveFile(LOGFILE, false);
					delete this->currentLog;
					this->currentLog = new NavData();
				}
				
				// transmit log data to server if specified
				if (this->frmSettings->strURL!="")
				{ // url specified
					try
					{
						Uploader^ uploadData = gcnew Uploader();
						if (this->frmSettings->strSaveDataFormat!="")
						{
							array<wchar_t>^ strSeparators;
							array<System::String^>^ strTokens;
							strSeparators = gcnew array<wchar_t>(1); // one entry array
							strSeparators[0] = '\n';
							strTokens = strUpload->Split(strSeparators);
							strUpload = this->frmSettings->strSaveDataFormat;
							for(int intIndex=strTokens->Length-1; intIndex>=0; intIndex--)
							{ // this must be in REVERSE order otherwise it will cock up
								strUpload = strUpload->Replace("@"+intIndex,uploadData->ToHTML(strTokens[intIndex]->Trim()));
							}
						}
						
						String^ httpData = uploadData->SocketSend(this->frmSettings->strURL,this->frmSettings->intPort,strUpload + "\r\n"); // ensure line feed at end!
						delete uploadData;
						// dump response to HTML file for checking!
						//System::IO::StreamWriter^ outFile = File::CreateText("response.html");
						//outFile->Write(httpData);
						//outFile->Close();
					}
					catch(...)
					{ // file debug code to go here...
						DebugFile("Transmission to http://" + this->frmSettings->strURL + ":" + this->frmSettings->intPort + " failed");
					}
				}
			}

			if (logImport->position->navPos!=NULL && logImport->position->sectPos!=NULL)
			{
				navClosest = NULL;
				for (int intIndex=0; intIndex<this->currentUniverse->GetEntryCount(); intIndex++)
				{
					navIndex = this->currentUniverse->GetEntry(intIndex);
					dblRange = logImport->position->RangeTo(navIndex);
					if (navIndex->visited==0)
					{ // this object has not been visited before
						if (navClosest!=NULL)
						{ // test against existing closest entry
							if (dblRange < logImport->position->RangeTo(navClosest))
								navClosest = navIndex; // this is the closest unvisited object
						}
						else // no known entries yet, use current
							navClosest = navIndex;
					}

					if (dblRange>=0 && dblRange<=VISITRANGE)
					{	// pilot is in close proximity to object
						_int64 intDate = System::DateTime::Now.Ticks;
						while (navIndex != NULL)
						{ // iterate up through tree and set visit time to all parent objects
							navIndex->visited = intDate;
							navIndex = navIndex->parent;
						}
					}
				}
			}

			booNewSystem = false;
			if (logImport->systemName)
			{ // system name extracted from flight log successfully, search for existence
				NavEntry* navSearch = new NavEntry();
				navSearch->SetName(logImport->systemName);
				navSearch->SetType("Planet");
				if (this->currentUniverse->FindEntry(navSearch, NAVNAME+NAVTYPE)==NULL)
				{ // unable to find planet with specified name
					navSearch->SetType("System"); // attempt searching for type 'system'
					if (this->currentUniverse->FindEntry(navSearch, NAVNAME+NAVTYPE)==NULL)	booNewSystem = true;
				}
				delete navSearch;
			}

			if (booNewSystem)
			{ // indicate new system and optionally bring application to front
				System::String^ strText = System::String::Concat("Entered new system ", gcnew System::String(logImport->systemName));
				if (this->Text != strText) this->Text = strText;
				if (!this->TopMost && this->newSystemNotificationToolStripMenuItem->Checked) 
					this->TopMost = true;
				else
					this->TopMost = false;
			}
			else
			{ // returned to known system, resume normal priority
				if (this->TopMost) this->TopMost = false;
				this->Text = "Navigation";
			}
			
			
			
			this->RefreshForm();
		}
		catch(...)
		{
			DebugFile("Error loading log data from "+strFileName);
		}
	}
}


System::Void Navigation::topLevelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->topLevelToolStripMenuItem->Checked = true;
	this->selectedNodeToolStripMenuItem->Checked = false;
}

System::Void Navigation::treeObjects_AfterCollapse(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e)
{ // tree node collapsed, update nav entry to remember state
	this->currentUniverse->GetEntry(System::Convert::ToInt32(e->Node->Name))->expanded = false;
}

System::Void Navigation::treeObjects_AfterExpand(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e)
{ // tree node expanded, update nav entry to remember state
	this->currentUniverse->GetEntry(System::Convert::ToInt32(e->Node->Name))->expanded = true;
}

System::Void Navigation::treeObjects_AfterLabelEdit(System::Object^ sender, System::Windows::Forms::NodeLabelEditEventArgs^ e)
{
	try
	{
		NavEntry* navEdit = this->currentUniverse->GetEntry(System::Convert::ToInt32(e->Node->Name));	
		navEdit->SetName((char*)(Marshal::StringToCoTaskMemAnsi(e->Label).ToPointer()));
	}
	catch (...)
	{ // squeak about errors here
		DebugFile("Tree label edit unsuccessful");
	}
}

System::Void Navigation::treeObjects_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e)
{
	navSelected = this->currentUniverse->GetEntry(System::Convert::ToInt32(e->Node->Name));	
	String^ strPos;
	if (this->navMove != NULL)
	{
		if (navMove != navSelected)
			navMove->SetParent(navSelected);
		else
			navMove->SetParent(NULL);
		this->currentUniverse->IndexEntries();
		navMove = NULL;
		this->DisplayTree(currentUniverse);
		navSelected = NULL;
	}
	else
	{ // nav move not taking place
		strPos = System::String::Concat(System::Convert::ToString(navSelected->navPos->x), " ");
		strPos = System::String::Concat(strPos, System::Convert::ToString(navSelected->navPos->y), " ");
		strPos = System::String::Concat(strPos, System::Convert::ToString(navSelected->navPos->z), " ");
		strPos = System::String::Concat(strPos, System::Convert::ToString(navSelected->sectPos->x), " ");
		strPos = System::String::Concat(strPos, System::Convert::ToString(navSelected->sectPos->y), " ");
		strPos = System::String::Concat(strPos, System::Convert::ToString(navSelected->sectPos->z));
		this->txtDisplayPos->Text = strPos;
	}
	this->RefreshForm();
}

System::Void Navigation::treeObjects_DoubleClick(System::Object^ sender, System::EventArgs^ e)	 
{ // node double clicked, calculate
	if (File::Exists(this->frmSettings->strGameLogFile->Replace("\\","\\\\")))
	{ // valid input 
		LogEntry* navStart = new LogEntry;
		navStart->LoadFile(this->frmSettings->strGameLogFile->Replace("\\","\\\\"), frmSettings->strSaveDataFormat);
		navStart->position->SetName("Start Position");
		if (this->navSelected!=NULL)
		{
			// factor in jump drive range for optimal calculation
			if (navStart->jumpRange < 1) // no jump drive, set jump gate to minimal weight
				this->routeCalc->jumpWeight = 1;
			else // jump drive fitted, use as jump weighting
				this->routeCalc->jumpWeight = navStart->jumpRange;
				
			this->routeCalc->BuildEdges(this->currentUniverse);
			this->routeCalc->Calculate(navStart->position, this->navSelected);
			std::vector<NavEntry*> bestRoute = this->routeCalc->GetPath(this->navSelected);
			this->currentUniverse->DeleteNavOutput(); // delete any previous waypoints
			for (int intIndex = int(bestRoute.size()-1); intIndex>=0; intIndex--)
			{
				int intWaypoint = int(bestRoute.size())-intIndex;
				String^ strTemp;
				NavEntry* newEntry = new NavEntry(*(bestRoute[intIndex]));
				newEntry->SetType(NAVOUT);
				newEntry->SetParent(NULL); // or the waypoints could appear ANYWHERE!
				strTemp = String::Concat
				(
					gcnew String("Waypoint "), 
					intWaypoint.ToString(),
					gcnew String(" - "),
					gcnew String(bestRoute[intIndex]->name)
				);
				strTemp = String::Concat
				(
					strTemp,
					gcnew String(" "),
					gcnew String(bestRoute[intIndex]->type)
				);
				newEntry->SetName((char*)(Marshal::StringToHGlobalAnsi(strTemp).ToPointer()));
				this->currentUniverse->AddEntry(newEntry);
			}
			if (File::Exists(this->frmSettings->strMapLogFile->Replace("\\","\\\\")) && this->chkUpdateNav->Checked)
				this->currentUniverse->SaveNavLogFile(this->frmSettings->strMapLogFile->Replace("\\","\\\\"));
			this->DisplayTree(this->currentUniverse);
			
		}
	}
}


System::Void Navigation::txtLogFile_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (File::Exists((((System::Windows::Forms::TextBox^)(sender)))->Text->Replace("\\","\\\\")))
	{
		this->chkLoadLog->Enabled = true;
	}
	else
	{
		this->chkLoadLog->Checked = false;
		this->chkLoadLog->Enabled = false;
	}
}

System::Void Navigation::txtNavFile_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (File::Exists((((System::Windows::Forms::TextBox^)(sender)))->Text->Replace("\\","\\\\")))
	{
		this->chkLoadNav->Enabled = true;
		this->chkUpdateNav->Enabled = true;
	}
	else
	{
		this->chkLoadNav->Checked = false;
		this->chkUpdateNav->Checked = false;
		this->chkLoadNav->Enabled = false;
		this->chkUpdateNav->Enabled = false;
	}
}

System::Void Navigation::txtSearch_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	if (this->navClosest!=NULL)
	{
		navClosest->visited = 1;
		this->RefreshForm();
	}
}
System::Void Navigation::txtSearch_TextChanged(System::Object^  sender, System::EventArgs^  e) 
{
	System::String^ strSearch = (((System::Windows::Forms::TextBox^)((((System::Windows::Forms::ToolStripTextBox^)(sender)))->TextBox)))->Text;
	if (System::String::IsNullOrEmpty(strSearch))
		this->DisplayTree(this->currentUniverse);
	else
		this->DisplayTree(this->currentUniverse,strSearch);
}

System::Void Navigation::txtValue_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (this->navSelected!=NULL)
		this->navSelected->SetValue((char*)(Marshal::StringToCoTaskMemAnsi((((System::Windows::Forms::TextBox^)(sender)))->Text).ToPointer()));
}

System::Void Navigation::typeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	this->currentUniverse->Sort(NAVTYPE);
	this->currentUniverse->IndexEntries();
	this->DisplayTree(currentUniverse);
}