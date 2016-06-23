#include "StdAfx.h"
#include "Settings.h"
#include "debug.h"

using namespace MapLog;
using namespace System;
using namespace System::IO;

Settings::Settings()
{
	this->strDMapInFile = "";
	this->strDMapOutFile = "";
	this->strGameLogFile = "";
	this->strMapLogFile = "";
	this->strFont = "GenericSansSerif";
	this->intFontSize = 10;
	this->strFontColor = "";
	this->strJmpLinesColor = "";
	this->strSystemColor = "";
	this->intInterval = 5000;
	this->strURL = "";
	this->intPort = 80; // standard TCP port
	this->strSaveDataFormat = "";
	InitializeComponent();
	this->LoadSettings(); // immediately load settings
}

Settings::~Settings()
{
	this->SaveSettings(); // immediately save settings
	if (components) delete components;
}

System::Windows::Forms::DialogResult Settings::LoadAndShow()
{
	this->RefreshComponents();
	return __super::ShowDialog();
}

unsigned int Settings::RgbToInteger(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

System::Void Settings::btnOK_Click(System::Object^  sender, System::EventArgs^  e) 
{
	this->strDMapInFile = this->txtMapInputFile->Text;
	this->strDMapOutFile = this->txtMapOutputFile->Text;
	this->strGameLogFile = this->txtGameLogFile->Text;
	this->strMapLogFile = this->txtMapLogFile->Text;
	try
	{ // attempt to calculate interval in ms
		this->intInterval = int(System::Convert::ToDouble(this->txtGameLogUpdate->Text) * 1000);
	}
	catch (...) 
	{ // conversion problem, default to 5 second refresh
		this->intInterval = 5000; // default to 5 seconds
		DebugFile("Invalid interval '" + this->txtGameLogUpdate->Text + "' specified, defaulted to 5000");
	}
	try
	{ // attempt to convert port number
		this->intPort = System::Convert::ToInt32(this->txtPort->Text);
	}
	catch (...)
	{ // converting port text failure, default to port 80
		this->intPort = 80;
		DebugFile("Invalid port '" + this->txtPort->Text + "' specified, defaulted to 80");
	}
	this->strURL = this->txtURL->Text;
	this->strSaveDataFormat = this->txtSavedataFormat->Text;
	this->DialogResult = System::Windows::Forms::DialogResult::OK;
	this->Hide();
}

System::Void Settings::btnGameLogFile_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::SaveFileDialog^ dlgSelect = gcnew(System::Windows::Forms::SaveFileDialog);
	if (File::Exists(this->txtGameLogFile->Text))
	{
		dlgSelect->InitialDirectory = Path::GetDirectoryName(this->txtGameLogFile->Text);
		dlgSelect->FileName = Path::GetFileName(this->txtGameLogFile->Text);
	}
	dlgSelect->Filter = "Text files (*.txt)|*.txt|Starwraith files (*.sw)|*.sw|All files (*.*)|*.*";
	dlgSelect->FilterIndex=1;
	if (dlgSelect->ShowDialog()==System::Windows::Forms::DialogResult::OK)
	{
		this->txtGameLogFile->Text = dlgSelect->FileName;
	}
}


System::Void Settings::btnMapInputFile_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::OpenFileDialog^ dlgSelect = gcnew(System::Windows::Forms::OpenFileDialog);
	if (File::Exists(this->txtMapInputFile->Text))
	{
		dlgSelect->InitialDirectory = Path::GetDirectoryName(this->txtMapInputFile->Text);
		dlgSelect->FileName = Path::GetFileName(this->txtMapInputFile->Text);
	}
	dlgSelect->Filter = "Portable Network Graphics (*.png)|*.png|JPEG (*.jpg)|*.jpg|All files (*.*)|*.*";
	if (dlgSelect->ShowDialog()==System::Windows::Forms::DialogResult::OK)
	{
		this->txtMapInputFile->Text = dlgSelect->FileName;
	}
}
System::Void Settings::btnMapLogFile_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::OpenFileDialog^ dlgSelect = gcnew(System::Windows::Forms::OpenFileDialog);
	if (File::Exists(this->txtMapLogFile->Text))
	{
		dlgSelect->InitialDirectory = Path::GetDirectoryName(this->txtMapLogFile->Text);
		dlgSelect->FileName = Path::GetFileName(this->txtMapLogFile->Text);
	}
	dlgSelect->Filter = "Text files (*.txt)|*.txt|Starwraith files (*.sw)|*.sw|All files (*.*)|*.*";
	dlgSelect->FilterIndex=2;
	if (dlgSelect->ShowDialog()==System::Windows::Forms::DialogResult::OK)
	{
		this->txtMapLogFile->Text = dlgSelect->FileName;
	}
}


System::Void Settings::btnMapOutputFile_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::SaveFileDialog^ dlgSelect = gcnew(System::Windows::Forms::SaveFileDialog);
	if (File::Exists(this->txtMapOutputFile->Text))
	{	
		dlgSelect->InitialDirectory = Path::GetDirectoryName(this->txtMapOutputFile->Text);
		dlgSelect->FileName = Path::GetFileName(this->txtMapOutputFile->Text);
	}
	dlgSelect->Filter = "Portable Network Graphics (*.png)|*.png|JPEG (*.jpg)|*.jpg|All files (*.*)|*.*";
	dlgSelect->FilterIndex=1;
	if (dlgSelect->ShowDialog()==System::Windows::Forms::DialogResult::OK)
	{
		this->txtMapOutputFile->Text = dlgSelect->FileName;
	}
}

System::Void Settings::btnCancel_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Hide();
}

System::Void Settings::btnFontStyle_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (dialFontStyle->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
		this->strFont = dialFontStyle->Font->Name;
		this->intFontSize = (int)dialFontStyle->Font->Size;
    }
}

System::Void Settings::btnFontColor_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (dialColor->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
		this->strFontColor = System::Drawing::ColorTranslator::ToHtml(dialColor->Color);
    }
}

System::Void Settings::btnLineColor_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (dialColor->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
		this->strJmpLinesColor = System::Drawing::ColorTranslator::ToHtml(dialColor->Color);
    }
}

System::Void Settings::btnSystemColor_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (dialColor->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
		this->strSystemColor = System::Drawing::ColorTranslator::ToHtml(dialColor->Color);
    }
}

void Settings::RefreshComponents()
{
	// apply settings to controls
	this->txtGameLogFile->Text = this->strGameLogFile;
	this->txtMapLogFile->Text = this->strMapLogFile;
	this->txtGameLogUpdate->Text = System::Convert::ToString(this->intInterval/1000.0);
	this->txtMapInputFile->Text = this->strDMapInFile;
	this->txtMapOutputFile->Text = this->strDMapOutFile;
	this->txtURL->Text = this->strURL;
	this->txtPort->Text = System::Convert::ToString(this->intPort);
	this->txtSavedataFormat->Text = this->strSaveDataFormat;
	this->btnFontColor->BackColor = System::Drawing::ColorTranslator::FromHtml(this->strFontColor);
	this->btnLineColor->BackColor = System::Drawing::ColorTranslator::FromHtml(this->strJmpLinesColor);
	this->btnSystemColor->BackColor = System::Drawing::ColorTranslator::FromHtml(this->strSystemColor);

	this->DialogResult = System::Windows::Forms::DialogResult::None;
	if (File::Exists(this->strDMapOutFile->Replace("\\", "\\\\")))
	{
		System::IO::FileStream^ imgStream = gcnew System::IO::FileStream(this->strDMapOutFile->Replace("\\", "\\\\"), System::IO::FileMode::Open, System::IO::FileAccess::Read);
		this->imgMap->Image = System::Drawing::Image::FromStream(imgStream);
		imgStream->Close();
	}
}

void Settings::LoadSettings()
{
	if (File::Exists(NEWSETTINGS))
	{
		array<wchar_t>^ strSeparators;
		array<System::String^>^ strTokens;
		strSeparators = gcnew array<wchar_t>(1); // one entry array
		strSeparators[0] = '=';
		System::String^ strCurrentLine;
		
		StreamReader^ inFile = File::OpenText(NEWSETTINGS);
		while (!inFile->EndOfStream)
		{
			strCurrentLine = inFile->ReadLine();
			strTokens = strCurrentLine->Split(strSeparators,2);

			if (strTokens[0] =="Game Output File" && strTokens->Length>=2) this->strGameLogFile = strTokens[1];
			if (strTokens[0] =="Map Log File" && strTokens->Length>=2) this->strMapLogFile = strTokens[1];
			if (strTokens[0] =="Dynamic Map Input File" && strTokens->Length>=2) this->strDMapInFile = strTokens[1];
			if (strTokens[0] =="Dynamic Map Output File" && strTokens->Length>=2) this->strDMapOutFile = strTokens[1];
			if (strTokens[0] =="Output Interval" && strTokens->Length>=2) this->intInterval = System::Convert::ToInt32(strTokens[1]);
			if (strTokens[0] =="URL" && strTokens->Length>=2) this->strURL = strTokens[1];
			if (strTokens[0] =="Port" && strTokens->Length>=2) this->intPort = System::Convert::ToInt32(strTokens[1]);
			if (strTokens[0] =="Font" && strTokens->Length>=2) this->strFont = strTokens[1];
			if (strTokens[0] =="Font Size" && strTokens->Length>=2) this->intFontSize = System::Convert::ToInt32(strTokens[1]);
			if (strTokens[0] =="Font Color" && strTokens->Length>=2) this->strFontColor = strTokens[1];
			if (strTokens[0] =="JmpLines Color" && strTokens->Length>=2) this->strJmpLinesColor = strTokens[1];
			if (strTokens[0] =="System Color" && strTokens->Length>=2) this->strSystemColor = strTokens[1];
			if (strTokens[0] =="[Save Data Format]")
			{
				strCurrentLine = inFile->ReadLine();
				if (!inFile->EndOfStream)
				{
					this->strSaveDataFormat = "";
					if (strCurrentLine!="[/Save Data Format]") this->strSaveDataFormat = strCurrentLine;
					while (strCurrentLine!="[/Save Data Format]" && !inFile->EndOfStream)
					{
						strCurrentLine = inFile->ReadLine();
						if (strCurrentLine!="[/Save Data Format]") this->strSaveDataFormat = this->strSaveDataFormat + "\r\n" + strCurrentLine;
					} 
				}
			}
		}
		inFile->Close();
	}
	else
	{ // new configuration file does not exist yet, attempt to use old style configuration file
		this->Show();
		// read in settings from old data file
		StreamReader^ inFile = File::OpenText(OLDSETTINGS);
		if (!inFile->EndOfStream) this->strMapLogFile = inFile->ReadLine();
		if (!inFile->EndOfStream) this->strGameLogFile = inFile->ReadLine();
		inFile->Close();
	}
	this->RefreshComponents();
}

void Settings::SaveSettings()
{
	System::IO::StreamWriter^ outFile = File::CreateText(NEWSETTINGS);
	outFile->WriteLine("[Files]");
	outFile->WriteLine("Game Output File=" + this->strGameLogFile);
	outFile->WriteLine("Map Log File=" + this->strMapLogFile);
	outFile->WriteLine("Dynamic Map Input File=" + this->strDMapInFile);
	outFile->WriteLine("Dynamic Map Output File=" + this->strDMapOutFile);
	outFile->WriteLine("[Settings]");
	outFile->WriteLine("Output Interval=" + this->intInterval);
	outFile->WriteLine("Font=" + this->strFont);
	outFile->WriteLine("Font Size=" + this->intFontSize);
	outFile->WriteLine("Font Color=" + this->strFontColor);
	outFile->WriteLine("JmpLines Color=" + this->strJmpLinesColor);
	outFile->WriteLine("System Color=" + this->strSystemColor);
	outFile->WriteLine("URL=" + this->strURL);
	outFile->WriteLine("Port=" + this->intPort);
	outFile->WriteLine("[Save Data Format]");
	outFile->WriteLine(this->strSaveDataFormat);
	outFile->WriteLine("[/Save Data Format]");
	outFile->Close();
}