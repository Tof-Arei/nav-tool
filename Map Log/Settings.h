#pragma once
#define OLDSETTINGS "navsettings.txt"
#define NEWSETTINGS "map log.cfg"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace MapLog {

	public ref class Settings : public System::Windows::Forms::Form
	{
		// variables
		public:
		System::String^ strGameLogFile;
		System::String^ strMapLogFile;
		int intInterval;
		System::String^ strDMapInFile;
		System::String^ strDMapOutFile;
		int intFontSize;
		System::String^ strFontColor;
		System::String^ strJmpLinesColor;
		System::String^ strSystemColor;
		System::String^ strURL;
		System::String^ strSaveDataFormat;

	public: 

	public: 
		int intPort;
		
		// functions
		Settings(void);
		protected:
		~Settings();
		public:
		System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void btnGameLogFile_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void btnMapInputFile_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void btnMapLogFile_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void btnMapOutputFile_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnOK_Click(System::Object^  sender, System::EventArgs^  e);
		
		void LoadSettings();
		void SaveSettings();
		
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::Button^  btnOK;
	private: System::Windows::Forms::TabPage^  tabMap;
	private: System::Windows::Forms::TabPage^  tabConnection;
	private: System::Windows::Forms::Button^  btnGetProcessing;
	private: System::Windows::Forms::TextBox^  txtSavedataFormat;


	private: System::Windows::Forms::TextBox^  txtPort;
	private: System::Windows::Forms::TextBox^  txtURL;
	private: System::Windows::Forms::Label^  lblProcessing;
	private: System::Windows::Forms::Label^  lblPortComment;
	private: System::Windows::Forms::Label^  lblConnectionDescription;
	private: System::Windows::Forms::Label^  lblPort;
	private: System::Windows::Forms::Label^  lblURL;
	private: System::Windows::Forms::TabControl^  tabcSettings;
	private: System::Windows::Forms::TabPage^  tabGeneral;
	private: System::Windows::Forms::Label^  lblMapLogFile;
	private: System::Windows::Forms::TextBox^  txtMapLogFile;
	private: System::Windows::Forms::TextBox^  txtGameLogFile;
	private: System::Windows::Forms::TextBox^  txtGameLogUpdate;
	private: System::Windows::Forms::Label^  lblGameLogFile;
	private: System::Windows::Forms::Label^  lblGameLogUpdate;
	private: System::Windows::Forms::Label^  lblGeneralDescription;
	private: System::Windows::Forms::Button^  btnMapLogFile;
	private: System::Windows::Forms::Button^  btnGameLogFile;



	private: System::Windows::Forms::Button^  btnMapOutputFile;
	private: System::Windows::Forms::TextBox^  txtMapOutputFile;
	private: System::Windows::Forms::Label^  lblMapOutputFile;
	private: System::Windows::Forms::Button^  btnMapInputFile;
	private: System::Windows::Forms::TextBox^  txtMapInputFile;
	private: System::Windows::Forms::Label^  lblMapInputFile;
	
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->tabMap = (gcnew System::Windows::Forms::TabPage());
			this->btnMapOutputFile = (gcnew System::Windows::Forms::Button());
			this->txtMapOutputFile = (gcnew System::Windows::Forms::TextBox());
			this->lblMapOutputFile = (gcnew System::Windows::Forms::Label());
			this->btnMapInputFile = (gcnew System::Windows::Forms::Button());
			this->txtMapInputFile = (gcnew System::Windows::Forms::TextBox());
			this->lblMapInputFile = (gcnew System::Windows::Forms::Label());
			this->tabConnection = (gcnew System::Windows::Forms::TabPage());
			this->btnGetProcessing = (gcnew System::Windows::Forms::Button());
			this->txtSavedataFormat = (gcnew System::Windows::Forms::TextBox());
			this->txtPort = (gcnew System::Windows::Forms::TextBox());
			this->txtURL = (gcnew System::Windows::Forms::TextBox());
			this->lblProcessing = (gcnew System::Windows::Forms::Label());
			this->lblPortComment = (gcnew System::Windows::Forms::Label());
			this->lblConnectionDescription = (gcnew System::Windows::Forms::Label());
			this->lblPort = (gcnew System::Windows::Forms::Label());
			this->lblURL = (gcnew System::Windows::Forms::Label());
			this->tabcSettings = (gcnew System::Windows::Forms::TabControl());
			this->tabGeneral = (gcnew System::Windows::Forms::TabPage());
			this->btnMapLogFile = (gcnew System::Windows::Forms::Button());
			this->btnGameLogFile = (gcnew System::Windows::Forms::Button());
			this->lblMapLogFile = (gcnew System::Windows::Forms::Label());
			this->txtMapLogFile = (gcnew System::Windows::Forms::TextBox());
			this->txtGameLogFile = (gcnew System::Windows::Forms::TextBox());
			this->txtGameLogUpdate = (gcnew System::Windows::Forms::TextBox());
			this->lblGameLogFile = (gcnew System::Windows::Forms::Label());
			this->lblGameLogUpdate = (gcnew System::Windows::Forms::Label());
			this->lblGeneralDescription = (gcnew System::Windows::Forms::Label());
			this->tabMap->SuspendLayout();
			this->tabConnection->SuspendLayout();
			this->tabcSettings->SuspendLayout();
			this->tabGeneral->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnCancel
			// 
			this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnCancel->Location = System::Drawing::Point(229, 337);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(72, 25);
			this->btnCancel->TabIndex = 1;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Click += gcnew System::EventHandler(this, &Settings::btnCancel_Click);
			// 
			// btnOK
			// 
			this->btnOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnOK->Location = System::Drawing::Point(307, 337);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(59, 25);
			this->btnOK->TabIndex = 2;
			this->btnOK->Text = L"OK";
			this->btnOK->UseVisualStyleBackColor = true;
			this->btnOK->Click += gcnew System::EventHandler(this, &Settings::btnOK_Click);
			// 
			// tabMap
			// 
			this->tabMap->Controls->Add(this->btnMapOutputFile);
			this->tabMap->Controls->Add(this->txtMapOutputFile);
			this->tabMap->Controls->Add(this->lblMapOutputFile);
			this->tabMap->Controls->Add(this->btnMapInputFile);
			this->tabMap->Controls->Add(this->txtMapInputFile);
			this->tabMap->Controls->Add(this->lblMapInputFile);
			this->tabMap->Location = System::Drawing::Point(4, 22);
			this->tabMap->Name = L"tabMap";
			this->tabMap->Padding = System::Windows::Forms::Padding(3);
			this->tabMap->Size = System::Drawing::Size(353, 304);
			this->tabMap->TabIndex = 2;
			this->tabMap->Text = L"Dynamic Map";
			this->tabMap->UseVisualStyleBackColor = true;
			// 
			// btnMapOutputFile
			// 
			this->btnMapOutputFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnMapOutputFile->Location = System::Drawing::Point(319, 56);
			this->btnMapOutputFile->Name = L"btnMapOutputFile";
			this->btnMapOutputFile->Size = System::Drawing::Size(24, 20);
			this->btnMapOutputFile->TabIndex = 17;
			this->btnMapOutputFile->Text = L"...";
			this->btnMapOutputFile->UseVisualStyleBackColor = true;
			this->btnMapOutputFile->Click += gcnew System::EventHandler(this, &Settings::btnMapOutputFile_Click);
			// 
			// txtMapOutputFile
			// 
			this->txtMapOutputFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtMapOutputFile->Location = System::Drawing::Point(106, 56);
			this->txtMapOutputFile->Name = L"txtMapOutputFile";
			this->txtMapOutputFile->Size = System::Drawing::Size(207, 20);
			this->txtMapOutputFile->TabIndex = 15;
			// 
			// lblMapOutputFile
			// 
			this->lblMapOutputFile->AutoSize = true;
			this->lblMapOutputFile->Location = System::Drawing::Point(7, 59);
			this->lblMapOutputFile->Name = L"lblMapOutputFile";
			this->lblMapOutputFile->Size = System::Drawing::Size(82, 13);
			this->lblMapOutputFile->TabIndex = 16;
			this->lblMapOutputFile->Text = L"Map Output File";
			// 
			// btnMapInputFile
			// 
			this->btnMapInputFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnMapInputFile->Location = System::Drawing::Point(319, 30);
			this->btnMapInputFile->Name = L"btnMapInputFile";
			this->btnMapInputFile->Size = System::Drawing::Size(24, 20);
			this->btnMapInputFile->TabIndex = 14;
			this->btnMapInputFile->Text = L"...";
			this->btnMapInputFile->UseVisualStyleBackColor = true;
			this->btnMapInputFile->Click += gcnew System::EventHandler(this, &Settings::btnMapInputFile_Click);
			// 
			// txtMapInputFile
			// 
			this->txtMapInputFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtMapInputFile->Location = System::Drawing::Point(106, 30);
			this->txtMapInputFile->Name = L"txtMapInputFile";
			this->txtMapInputFile->Size = System::Drawing::Size(207, 20);
			this->txtMapInputFile->TabIndex = 12;
			// 
			// lblMapInputFile
			// 
			this->lblMapInputFile->AutoSize = true;
			this->lblMapInputFile->Location = System::Drawing::Point(7, 33);
			this->lblMapInputFile->Name = L"lblMapInputFile";
			this->lblMapInputFile->Size = System::Drawing::Size(74, 13);
			this->lblMapInputFile->TabIndex = 13;
			this->lblMapInputFile->Text = L"Map Input File";
			// 
			// tabConnection
			// 
			this->tabConnection->Controls->Add(this->btnGetProcessing);
			this->tabConnection->Controls->Add(this->txtSavedataFormat);
			this->tabConnection->Controls->Add(this->txtPort);
			this->tabConnection->Controls->Add(this->txtURL);
			this->tabConnection->Controls->Add(this->lblProcessing);
			this->tabConnection->Controls->Add(this->lblPortComment);
			this->tabConnection->Controls->Add(this->lblConnectionDescription);
			this->tabConnection->Controls->Add(this->lblPort);
			this->tabConnection->Controls->Add(this->lblURL);
			this->tabConnection->Location = System::Drawing::Point(4, 22);
			this->tabConnection->Name = L"tabConnection";
			this->tabConnection->Padding = System::Windows::Forms::Padding(3);
			this->tabConnection->Size = System::Drawing::Size(353, 304);
			this->tabConnection->TabIndex = 1;
			this->tabConnection->Text = L"Connection";
			this->tabConnection->UseVisualStyleBackColor = true;
			// 
			// btnGetProcessing
			// 
			this->btnGetProcessing->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnGetProcessing->Enabled = false;
			this->btnGetProcessing->Location = System::Drawing::Point(243, 103);
			this->btnGetProcessing->Name = L"btnGetProcessing";
			this->btnGetProcessing->Size = System::Drawing::Size(102, 23);
			this->btnGetProcessing->TabIndex = 8;
			this->btnGetProcessing->Text = L"Get from Server";
			this->btnGetProcessing->UseVisualStyleBackColor = true;
			// 
			// txtSavedataFormat
			// 
			this->txtSavedataFormat->AcceptsReturn = true;
			this->txtSavedataFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtSavedataFormat->Location = System::Drawing::Point(6, 129);
			this->txtSavedataFormat->Multiline = true;
			this->txtSavedataFormat->Name = L"txtSavedataFormat";
			this->txtSavedataFormat->Size = System::Drawing::Size(339, 167);
			this->txtSavedataFormat->TabIndex = 7;
			// 
			// txtPort
			// 
			this->txtPort->Location = System::Drawing::Point(44, 81);
			this->txtPort->Name = L"txtPort";
			this->txtPort->Size = System::Drawing::Size(50, 20);
			this->txtPort->TabIndex = 1;
			// 
			// txtURL
			// 
			this->txtURL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtURL->Location = System::Drawing::Point(44, 55);
			this->txtURL->Name = L"txtURL";
			this->txtURL->Size = System::Drawing::Size(301, 20);
			this->txtURL->TabIndex = 0;
			// 
			// lblProcessing
			// 
			this->lblProcessing->AutoSize = true;
			this->lblProcessing->Location = System::Drawing::Point(3, 113);
			this->lblProcessing->Name = L"lblProcessing";
			this->lblProcessing->Size = System::Drawing::Size(120, 13);
			this->lblProcessing->TabIndex = 6;
			this->lblProcessing->Text = L"Savedata upload format";
			// 
			// lblPortComment
			// 
			this->lblPortComment->AutoSize = true;
			this->lblPortComment->Location = System::Drawing::Point(100, 84);
			this->lblPortComment->Name = L"lblPortComment";
			this->lblPortComment->Size = System::Drawing::Size(137, 13);
			this->lblPortComment->TabIndex = 5;
			this->lblPortComment->Text = L"Generally, this should be 80";
			// 
			// lblConnectionDescription
			// 
			this->lblConnectionDescription->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblConnectionDescription->Location = System::Drawing::Point(6, 3);
			this->lblConnectionDescription->Name = L"lblConnectionDescription";
			this->lblConnectionDescription->Size = System::Drawing::Size(339, 45);
			this->lblConnectionDescription->TabIndex = 4;
			this->lblConnectionDescription->Text = L"This section is used to configure a HTTP connection with a web server. Discoverie" 
				L"s can be uploaded along with player information.";
			// 
			// lblPort
			// 
			this->lblPort->AutoSize = true;
			this->lblPort->Location = System::Drawing::Point(6, 84);
			this->lblPort->Name = L"lblPort";
			this->lblPort->Size = System::Drawing::Size(26, 13);
			this->lblPort->TabIndex = 3;
			this->lblPort->Text = L"Port";
			// 
			// lblURL
			// 
			this->lblURL->AutoSize = true;
			this->lblURL->Location = System::Drawing::Point(6, 58);
			this->lblURL->Name = L"lblURL";
			this->lblURL->Size = System::Drawing::Size(38, 13);
			this->lblURL->TabIndex = 2;
			this->lblURL->Text = L"http://";
			// 
			// tabcSettings
			// 
			this->tabcSettings->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabcSettings->Controls->Add(this->tabGeneral);
			this->tabcSettings->Controls->Add(this->tabConnection);
			this->tabcSettings->Controls->Add(this->tabMap);
			this->tabcSettings->Location = System::Drawing::Point(5, 5);
			this->tabcSettings->Name = L"tabcSettings";
			this->tabcSettings->SelectedIndex = 0;
			this->tabcSettings->Size = System::Drawing::Size(361, 330);
			this->tabcSettings->TabIndex = 0;
			// 
			// tabGeneral
			// 
			this->tabGeneral->Controls->Add(this->btnMapLogFile);
			this->tabGeneral->Controls->Add(this->btnGameLogFile);
			this->tabGeneral->Controls->Add(this->lblMapLogFile);
			this->tabGeneral->Controls->Add(this->txtMapLogFile);
			this->tabGeneral->Controls->Add(this->txtGameLogFile);
			this->tabGeneral->Controls->Add(this->txtGameLogUpdate);
			this->tabGeneral->Controls->Add(this->lblGameLogFile);
			this->tabGeneral->Controls->Add(this->lblGameLogUpdate);
			this->tabGeneral->Controls->Add(this->lblGeneralDescription);
			this->tabGeneral->Location = System::Drawing::Point(4, 22);
			this->tabGeneral->Name = L"tabGeneral";
			this->tabGeneral->Padding = System::Windows::Forms::Padding(3);
			this->tabGeneral->Size = System::Drawing::Size(353, 304);
			this->tabGeneral->TabIndex = 0;
			this->tabGeneral->Text = L"General";
			this->tabGeneral->UseVisualStyleBackColor = true;
			// 
			// btnMapLogFile
			// 
			this->btnMapLogFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnMapLogFile->Location = System::Drawing::Point(323, 91);
			this->btnMapLogFile->Name = L"btnMapLogFile";
			this->btnMapLogFile->Size = System::Drawing::Size(24, 20);
			this->btnMapLogFile->TabIndex = 13;
			this->btnMapLogFile->Text = L"...";
			this->btnMapLogFile->UseVisualStyleBackColor = true;
			this->btnMapLogFile->Click += gcnew System::EventHandler(this, &Settings::btnMapLogFile_Click);
			// 
			// btnGameLogFile
			// 
			this->btnGameLogFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnGameLogFile->Location = System::Drawing::Point(323, 39);
			this->btnGameLogFile->Name = L"btnGameLogFile";
			this->btnGameLogFile->Size = System::Drawing::Size(24, 20);
			this->btnGameLogFile->TabIndex = 11;
			this->btnGameLogFile->Text = L"...";
			this->btnGameLogFile->UseVisualStyleBackColor = true;
			this->btnGameLogFile->Click += gcnew System::EventHandler(this, &Settings::btnGameLogFile_Click);
			// 
			// lblMapLogFile
			// 
			this->lblMapLogFile->AutoSize = true;
			this->lblMapLogFile->Location = System::Drawing::Point(11, 94);
			this->lblMapLogFile->Name = L"lblMapLogFile";
			this->lblMapLogFile->Size = System::Drawing::Size(68, 13);
			this->lblMapLogFile->TabIndex = 10;
			this->lblMapLogFile->Text = L"Map Log File";
			// 
			// txtMapLogFile
			// 
			this->txtMapLogFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtMapLogFile->Location = System::Drawing::Point(110, 91);
			this->txtMapLogFile->Name = L"txtMapLogFile";
			this->txtMapLogFile->Size = System::Drawing::Size(207, 20);
			this->txtMapLogFile->TabIndex = 9;
			// 
			// txtGameLogFile
			// 
			this->txtGameLogFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtGameLogFile->Location = System::Drawing::Point(110, 39);
			this->txtGameLogFile->Name = L"txtGameLogFile";
			this->txtGameLogFile->Size = System::Drawing::Size(207, 20);
			this->txtGameLogFile->TabIndex = 7;
			// 
			// txtGameLogUpdate
			// 
			this->txtGameLogUpdate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtGameLogUpdate->Location = System::Drawing::Point(110, 65);
			this->txtGameLogUpdate->Name = L"txtGameLogUpdate";
			this->txtGameLogUpdate->Size = System::Drawing::Size(207, 20);
			this->txtGameLogUpdate->TabIndex = 0;
			// 
			// lblGameLogFile
			// 
			this->lblGameLogFile->AutoSize = true;
			this->lblGameLogFile->Location = System::Drawing::Point(11, 42);
			this->lblGameLogFile->Name = L"lblGameLogFile";
			this->lblGameLogFile->Size = System::Drawing::Size(89, 13);
			this->lblGameLogFile->TabIndex = 8;
			this->lblGameLogFile->Text = L"Game Output File";
			// 
			// lblGameLogUpdate
			// 
			this->lblGameLogUpdate->AutoSize = true;
			this->lblGameLogUpdate->Location = System::Drawing::Point(11, 68);
			this->lblGameLogUpdate->Name = L"lblGameLogUpdate";
			this->lblGameLogUpdate->Size = System::Drawing::Size(93, 13);
			this->lblGameLogUpdate->TabIndex = 6;
			this->lblGameLogUpdate->Text = L"Update (Seconds)";
			// 
			// lblGeneralDescription
			// 
			this->lblGeneralDescription->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblGeneralDescription->Location = System::Drawing::Point(3, 3);
			this->lblGeneralDescription->Name = L"lblGeneralDescription";
			this->lblGeneralDescription->Size = System::Drawing::Size(347, 19);
			this->lblGeneralDescription->TabIndex = 5;
			this->lblGeneralDescription->Text = L"Specify files and main settings";
			// 
			// Settings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->btnCancel;
			this->ClientSize = System::Drawing::Size(372, 368);
			this->ControlBox = false;
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->tabcSettings);
			this->Name = L"Settings";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Settings";
			this->TopMost = true;
			this->tabMap->ResumeLayout(false);
			this->tabMap->PerformLayout();
			this->tabConnection->ResumeLayout(false);
			this->tabConnection->PerformLayout();
			this->tabcSettings->ResumeLayout(false);
			this->tabGeneral->ResumeLayout(false);
			this->tabGeneral->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion




};
}
