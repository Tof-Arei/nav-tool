#pragma once
#include "navdata.h"
#include "log.h"
#include "route.h"
#include "settings.h"

#define SAVEFILE "navdata.txt"
#define LOGFILE "logdata.txt"
#define SETTINGS "navsettings.txt"
const int EXPLORERANGE = SECTORSIZE*30;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace MapLog {
	/// <summary>
	/// Summary for Navigation
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Navigation : public System::Windows::Forms::Form
	{
	public:
		Navigation(void);
		void RefreshForm(void);
	protected:
		~Navigation();
	private: 
		// variables
		NavEntry* navMove;
		NavEntry* navSelected;
		NavEntry* navClosest;
		NavData* currentUniverse;
		NavData* currentLog;
		LogEntry* logImport;
		Route* routeCalc;
		Settings^ frmSettings;
		System::DateTime logDate;
		System::DateTime navDate;
		System::Windows::Forms::ImageList^  imgTree;
		System::Windows::Forms::TreeView^  treeObjects;
		System::Windows::Forms::TextBox^  txtValue;

		System::Windows::Forms::TextBox^  txtDisplayPos;
		System::Windows::Forms::Timer^  timRefresh;
		System::Windows::Forms::SplitContainer^  splitInterface;












		System::Windows::Forms::CheckBox^  chkLoadNav;
		System::Windows::Forms::CheckBox^  chkUpdateNav;
		System::Windows::Forms::CheckBox^  chkLoadLog;

	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  btnDelete;
	private: System::Windows::Forms::ToolStripButton^  btnPromote;
	private: System::Windows::Forms::ToolStripButton^  btnMove;
	private: System::Windows::Forms::ToolStripButton^  btnClone;
	private: System::Windows::Forms::ToolStripButton^  btnRefresh;
	private: System::Windows::Forms::ToolStripSplitButton^  toolStripSplitButton2;
	private: System::Windows::Forms::ToolStripMenuItem^  nameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  typeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rangeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  btnDeleteWaypoints;
	private: System::Windows::Forms::ToolStripSplitButton^  btnTools;
	private: System::Windows::Forms::ToolStripMenuItem^  appendNewEntriesToToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  topLevelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  selectedNodeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  attemptTrilaterationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hideLowerPaneToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  linkJumpGatesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newSystemNotificationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  txtSearch;
	private: System::Windows::Forms::ComboBox^  cboType;















		System::ComponentModel::IContainer^  components;
		
		// function declarations
		System::Windows::Forms::TreeNode^ BuildNode(NavEntry* inNav);
		private: System::Void attemptTrilaterationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnClone_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnDelete_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnDeleteWaypoints_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnHideLowerPanel_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnMove_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnPromote_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnRefresh_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void cboType_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void DisplayTree(NavData* navData);
		void DisplayTree(NavData* navData, System::String^ searchText);
		void DisplayTree(NavData* navData, System::Windows::Forms::TreeNode^ currentNode);
		void ExpandTree(System::Windows::Forms::TreeNode^ currentNode);
		System::Void hideLowerPaneToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void linkJumpGatesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void nameToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void Navigation_Activated(System::Object^  sender, System::EventArgs^  e);
		System::Void optionsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void rangeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void selectedNodeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void timRefresh_Tick(System::Object^  sender, System::EventArgs^  e);
		System::Void topLevelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void treeObjects_AfterCollapse(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
		System::Void treeObjects_AfterExpand(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
		System::Void treeObjects_AfterLabelEdit(System::Object^  sender, System::Windows::Forms::NodeLabelEditEventArgs^  e);
		System::Void treeObjects_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
		System::Void treeObjects_DoubleClick(System::Object^  sender, System::EventArgs^  e) ;
		System::Void txtLogFile_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void txtNavFile_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void txtSearch_DoubleClick(System::Object^  sender, System::EventArgs^  e);
		System::Void txtSearch_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void txtValue_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void typeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Navigation::typeid));
			this->treeObjects = (gcnew System::Windows::Forms::TreeView());
			this->imgTree = (gcnew System::Windows::Forms::ImageList(this->components));
			this->txtValue = (gcnew System::Windows::Forms::TextBox());
			this->txtDisplayPos = (gcnew System::Windows::Forms::TextBox());
			this->timRefresh = (gcnew System::Windows::Forms::Timer(this->components));
			this->splitInterface = (gcnew System::Windows::Forms::SplitContainer());
			this->cboType = (gcnew System::Windows::Forms::ComboBox());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->btnDelete = (gcnew System::Windows::Forms::ToolStripButton());
			this->btnPromote = (gcnew System::Windows::Forms::ToolStripButton());
			this->btnMove = (gcnew System::Windows::Forms::ToolStripButton());
			this->btnClone = (gcnew System::Windows::Forms::ToolStripButton());
			this->btnRefresh = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSplitButton2 = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->nameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->typeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rangeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->btnDeleteWaypoints = (gcnew System::Windows::Forms::ToolStripButton());
			this->btnTools = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->appendNewEntriesToToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->topLevelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->selectedNodeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->attemptTrilaterationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hideLowerPaneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->linkJumpGatesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newSystemNotificationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->txtSearch = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->chkLoadNav = (gcnew System::Windows::Forms::CheckBox());
			this->chkUpdateNav = (gcnew System::Windows::Forms::CheckBox());
			this->chkLoadLog = (gcnew System::Windows::Forms::CheckBox());
			this->splitInterface->Panel1->SuspendLayout();
			this->splitInterface->Panel2->SuspendLayout();
			this->splitInterface->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// treeObjects
			// 
			this->treeObjects->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeObjects->HideSelection = false;
			this->treeObjects->ImageIndex = 0;
			this->treeObjects->ImageList = this->imgTree;
			this->treeObjects->LabelEdit = true;
			this->treeObjects->Location = System::Drawing::Point(4, 31);
			this->treeObjects->Margin = System::Windows::Forms::Padding(0);
			this->treeObjects->Name = L"treeObjects";
			this->treeObjects->SelectedImageIndex = 0;
			this->treeObjects->ShowNodeToolTips = true;
			this->treeObjects->Size = System::Drawing::Size(309, 210);
			this->treeObjects->TabIndex = 0;
			this->treeObjects->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Navigation::treeObjects_AfterCollapse);
			this->treeObjects->AfterLabelEdit += gcnew System::Windows::Forms::NodeLabelEditEventHandler(this, &Navigation::treeObjects_AfterLabelEdit);
			this->treeObjects->DoubleClick += gcnew System::EventHandler(this, &Navigation::treeObjects_DoubleClick);
			this->treeObjects->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Navigation::treeObjects_AfterSelect);
			this->treeObjects->AfterExpand += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Navigation::treeObjects_AfterExpand);
			// 
			// imgTree
			// 
			this->imgTree->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imgTree.ImageStream")));
			this->imgTree->TransparentColor = System::Drawing::Color::Red;
			this->imgTree->Images->SetKeyName(0, L"Planet");
			this->imgTree->Images->SetKeyName(1, L"Environment");
			this->imgTree->Images->SetKeyName(2, L"PolyClosed");
			this->imgTree->Images->SetKeyName(3, L"PolyOpen");
			this->imgTree->Images->SetKeyName(4, L"Station");
			this->imgTree->Images->SetKeyName(5, L"Deselected");
			this->imgTree->Images->SetKeyName(6, L"Selected");
			this->imgTree->Images->SetKeyName(7, L"Jump");
			this->imgTree->Images->SetKeyName(8, L"NavLog");
			this->imgTree->Images->SetKeyName(9, L"City");
			this->imgTree->Images->SetKeyName(10, L"Waypoints");
			this->imgTree->Images->SetKeyName(11, L"Asteroid Cave");
			this->imgTree->Images->SetKeyName(12, L"Asteroids");
			this->imgTree->Images->SetKeyName(13, L"Moon");
			this->imgTree->Images->SetKeyName(14, L"Folder");
			this->imgTree->Images->SetKeyName(15, L"System");
			this->imgTree->Images->SetKeyName(16, L"Container");
			this->imgTree->Images->SetKeyName(17, L"Jumpgate");
			this->imgTree->Images->SetKeyName(18, L"Wormhole");
			this->imgTree->Images->SetKeyName(19, L"Black Hole");
			// 
			// txtValue
			// 
			this->txtValue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtValue->Location = System::Drawing::Point(4, -1);
			this->txtValue->Multiline = true;
			this->txtValue->Name = L"txtValue";
			this->txtValue->Size = System::Drawing::Size(309, 65);
			this->txtValue->TabIndex = 1;
			this->txtValue->TextChanged += gcnew System::EventHandler(this, &Navigation::txtValue_TextChanged);
			// 
			// txtDisplayPos
			// 
			this->txtDisplayPos->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtDisplayPos->Location = System::Drawing::Point(4, 70);
			this->txtDisplayPos->Name = L"txtDisplayPos";
			this->txtDisplayPos->Size = System::Drawing::Size(309, 20);
			this->txtDisplayPos->TabIndex = 3;
			// 
			// timRefresh
			// 
			this->timRefresh->Enabled = true;
			this->timRefresh->Tick += gcnew System::EventHandler(this, &Navigation::timRefresh_Tick);
			// 
			// splitInterface
			// 
			this->splitInterface->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitInterface->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitInterface->Location = System::Drawing::Point(0, 0);
			this->splitInterface->Name = L"splitInterface";
			this->splitInterface->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitInterface.Panel1
			// 
			this->splitInterface->Panel1->AutoScrollMargin = System::Drawing::Size(0, 4);
			this->splitInterface->Panel1->Controls->Add(this->cboType);
			this->splitInterface->Panel1->Controls->Add(this->treeObjects);
			this->splitInterface->Panel1->Controls->Add(this->toolStrip1);
			this->splitInterface->Panel1->Padding = System::Windows::Forms::Padding(4, 4, 4, 0);
			// 
			// splitInterface.Panel2
			// 
			this->splitInterface->Panel2->Controls->Add(this->txtValue);
			this->splitInterface->Panel2->Controls->Add(this->txtDisplayPos);
			this->splitInterface->Panel2->Controls->Add(this->chkLoadNav);
			this->splitInterface->Panel2->Controls->Add(this->chkUpdateNav);
			this->splitInterface->Panel2->Controls->Add(this->chkLoadLog);
			this->splitInterface->Panel2->Padding = System::Windows::Forms::Padding(4, 0, 4, 4);
			this->splitInterface->Size = System::Drawing::Size(317, 387);
			this->splitInterface->SplitterDistance = 263;
			this->splitInterface->TabIndex = 9;
			// 
			// cboType
			// 
			this->cboType->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboType->FormattingEnabled = true;
			this->cboType->Items->AddRange(gcnew cli::array< System::Object^  >(17) {L"Asteroid Cave", L"Asteroids", L"Black Hole", L"Carrier", 
				L"City", L"Comment", L"Container", L"Environment", L"Group", L"Jump", L"Jump Gate", L"Moon", L"Nebula", L"Planet", L"Station", 
				L"System", L"Worm Hole"});
			this->cboType->Location = System::Drawing::Point(4, 242);
			this->cboType->Margin = System::Windows::Forms::Padding(0);
			this->cboType->Name = L"cboType";
			this->cboType->Size = System::Drawing::Size(309, 21);
			this->cboType->TabIndex = 2;
			this->cboType->TextChanged += gcnew System::EventHandler(this, &Navigation::cboType_TextChanged);
			// 
			// toolStrip1
			// 
			this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {this->btnDelete, this->btnPromote, 
				this->btnMove, this->btnClone, this->btnRefresh, this->toolStripSplitButton2, this->btnDeleteWaypoints, this->btnTools, this->txtSearch});
			this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->toolStrip1->Location = System::Drawing::Point(4, 4);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(309, 25);
			this->toolStrip1->Stretch = true;
			this->toolStrip1->TabIndex = 2;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// btnDelete
			// 
			this->btnDelete->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->btnDelete->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnDelete.Image")));
			this->btnDelete->ImageTransparentColor = System::Drawing::Color::White;
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(23, 22);
			this->btnDelete->Text = L"Delete selected entry";
			this->btnDelete->Click += gcnew System::EventHandler(this, &Navigation::btnDelete_Click);
			// 
			// btnPromote
			// 
			this->btnPromote->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->btnPromote->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnPromote.Image")));
			this->btnPromote->ImageTransparentColor = System::Drawing::Color::Red;
			this->btnPromote->Name = L"btnPromote";
			this->btnPromote->Size = System::Drawing::Size(23, 22);
			this->btnPromote->Text = L"Promote selected entry to top level";
			this->btnPromote->Click += gcnew System::EventHandler(this, &Navigation::btnPromote_Click);
			// 
			// btnMove
			// 
			this->btnMove->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->btnMove->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnMove.Image")));
			this->btnMove->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->btnMove->Name = L"btnMove";
			this->btnMove->Size = System::Drawing::Size(41, 22);
			this->btnMove->Text = L"Move";
			this->btnMove->ToolTipText = L"Move selected entry";
			this->btnMove->Click += gcnew System::EventHandler(this, &Navigation::btnMove_Click);
			// 
			// btnClone
			// 
			this->btnClone->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->btnClone->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnClone.Image")));
			this->btnClone->ImageTransparentColor = System::Drawing::Color::White;
			this->btnClone->Name = L"btnClone";
			this->btnClone->Size = System::Drawing::Size(23, 22);
			this->btnClone->Text = L"Clone entry as child";
			this->btnClone->Click += gcnew System::EventHandler(this, &Navigation::btnClone_Click);
			// 
			// btnRefresh
			// 
			this->btnRefresh->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->btnRefresh->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnRefresh.Image")));
			this->btnRefresh->ImageTransparentColor = System::Drawing::Color::Red;
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(23, 22);
			this->btnRefresh->Text = L"Refresh List";
			this->btnRefresh->Click += gcnew System::EventHandler(this, &Navigation::btnRefresh_Click);
			// 
			// toolStripSplitButton2
			// 
			this->toolStripSplitButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripSplitButton2->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->nameToolStripMenuItem, 
				this->typeToolStripMenuItem, this->rangeToolStripMenuItem});
			this->toolStripSplitButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripSplitButton2.Image")));
			this->toolStripSplitButton2->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripSplitButton2->Name = L"toolStripSplitButton2";
			this->toolStripSplitButton2->Size = System::Drawing::Size(32, 22);
			this->toolStripSplitButton2->Text = L"Sort entries by...";
			// 
			// nameToolStripMenuItem
			// 
			this->nameToolStripMenuItem->Name = L"nameToolStripMenuItem";
			this->nameToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->nameToolStripMenuItem->Text = L"Name";
			this->nameToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::nameToolStripMenuItem_Click);
			// 
			// typeToolStripMenuItem
			// 
			this->typeToolStripMenuItem->Name = L"typeToolStripMenuItem";
			this->typeToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->typeToolStripMenuItem->Text = L"Type";
			this->typeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::typeToolStripMenuItem_Click);
			// 
			// rangeToolStripMenuItem
			// 
			this->rangeToolStripMenuItem->Name = L"rangeToolStripMenuItem";
			this->rangeToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->rangeToolStripMenuItem->Text = L"Range";
			this->rangeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::rangeToolStripMenuItem_Click);
			// 
			// btnDeleteWaypoints
			// 
			this->btnDeleteWaypoints->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->btnDeleteWaypoints->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnDeleteWaypoints.Image")));
			this->btnDeleteWaypoints->ImageTransparentColor = System::Drawing::Color::White;
			this->btnDeleteWaypoints->Name = L"btnDeleteWaypoints";
			this->btnDeleteWaypoints->Size = System::Drawing::Size(23, 22);
			this->btnDeleteWaypoints->Text = L"Delete Waypoints";
			this->btnDeleteWaypoints->Click += gcnew System::EventHandler(this, &Navigation::btnDeleteWaypoints_Click);
			// 
			// btnTools
			// 
			this->btnTools->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->btnTools->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->appendNewEntriesToToolStripMenuItem, 
				this->attemptTrilaterationToolStripMenuItem, this->hideLowerPaneToolStripMenuItem, this->linkJumpGatesToolStripMenuItem, this->newSystemNotificationToolStripMenuItem, 
				this->saveToolStripMenuItem, this->optionsToolStripMenuItem});
			this->btnTools->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnTools.Image")));
			this->btnTools->ImageTransparentColor = System::Drawing::Color::Red;
			this->btnTools->Name = L"btnTools";
			this->btnTools->Size = System::Drawing::Size(32, 22);
			this->btnTools->Text = L"Tools";
			this->btnTools->ToolTipText = L"Tools and Options";
			// 
			// appendNewEntriesToToolStripMenuItem
			// 
			this->appendNewEntriesToToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->topLevelToolStripMenuItem, 
				this->selectedNodeToolStripMenuItem});
			this->appendNewEntriesToToolStripMenuItem->Name = L"appendNewEntriesToToolStripMenuItem";
			this->appendNewEntriesToToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->appendNewEntriesToToolStripMenuItem->Text = L"Append New Entries to...";
			// 
			// topLevelToolStripMenuItem
			// 
			this->topLevelToolStripMenuItem->Checked = true;
			this->topLevelToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->topLevelToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"topLevelToolStripMenuItem.Image")));
			this->topLevelToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Red;
			this->topLevelToolStripMenuItem->Name = L"topLevelToolStripMenuItem";
			this->topLevelToolStripMenuItem->Size = System::Drawing::Size(150, 22);
			this->topLevelToolStripMenuItem->Text = L"Top Level";
			this->topLevelToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::topLevelToolStripMenuItem_Click);
			// 
			// selectedNodeToolStripMenuItem
			// 
			this->selectedNodeToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"selectedNodeToolStripMenuItem.Image")));
			this->selectedNodeToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Red;
			this->selectedNodeToolStripMenuItem->Name = L"selectedNodeToolStripMenuItem";
			this->selectedNodeToolStripMenuItem->Size = System::Drawing::Size(150, 22);
			this->selectedNodeToolStripMenuItem->Text = L"Selected Node";
			this->selectedNodeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::selectedNodeToolStripMenuItem_Click);
			// 
			// attemptTrilaterationToolStripMenuItem
			// 
			this->attemptTrilaterationToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"attemptTrilaterationToolStripMenuItem.Image")));
			this->attemptTrilaterationToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Red;
			this->attemptTrilaterationToolStripMenuItem->Name = L"attemptTrilaterationToolStripMenuItem";
			this->attemptTrilaterationToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->attemptTrilaterationToolStripMenuItem->Text = L"Attempt Trilateration";
			this->attemptTrilaterationToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::attemptTrilaterationToolStripMenuItem_Click);
			// 
			// hideLowerPaneToolStripMenuItem
			// 
			this->hideLowerPaneToolStripMenuItem->CheckOnClick = true;
			this->hideLowerPaneToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"hideLowerPaneToolStripMenuItem.Image")));
			this->hideLowerPaneToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Red;
			this->hideLowerPaneToolStripMenuItem->Name = L"hideLowerPaneToolStripMenuItem";
			this->hideLowerPaneToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->hideLowerPaneToolStripMenuItem->Text = L"Hide Lower Pane";
			this->hideLowerPaneToolStripMenuItem->ToolTipText = L"Toggle the lower pane on and off";
			this->hideLowerPaneToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::hideLowerPaneToolStripMenuItem_Click);
			// 
			// linkJumpGatesToolStripMenuItem
			// 
			this->linkJumpGatesToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"linkJumpGatesToolStripMenuItem.Image")));
			this->linkJumpGatesToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Red;
			this->linkJumpGatesToolStripMenuItem->Name = L"linkJumpGatesToolStripMenuItem";
			this->linkJumpGatesToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->linkJumpGatesToolStripMenuItem->Text = L"Link Jump Gates";
			this->linkJumpGatesToolStripMenuItem->ToolTipText = L"Attempts to link jump gates between known systems";
			this->linkJumpGatesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::linkJumpGatesToolStripMenuItem_Click);
			// 
			// newSystemNotificationToolStripMenuItem
			// 
			this->newSystemNotificationToolStripMenuItem->CheckOnClick = true;
			this->newSystemNotificationToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"newSystemNotificationToolStripMenuItem.Image")));
			this->newSystemNotificationToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::White;
			this->newSystemNotificationToolStripMenuItem->Name = L"newSystemNotificationToolStripMenuItem";
			this->newSystemNotificationToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->newSystemNotificationToolStripMenuItem->Text = L"New System Notification";
			this->newSystemNotificationToolStripMenuItem->ToolTipText = L"Application ";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"saveToolStripMenuItem.Image")));
			this->saveToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::White;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::saveToolStripMenuItem_Click);
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"optionsToolStripMenuItem.Image")));
			this->optionsToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::White;
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->optionsToolStripMenuItem->Text = L"Options";
			this->optionsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Navigation::optionsToolStripMenuItem_Click);
			// 
			// txtSearch
			// 
			this->txtSearch->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->txtSearch->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->txtSearch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtSearch->Name = L"txtSearch";
			this->txtSearch->Size = System::Drawing::Size(75, 25);
			this->txtSearch->DoubleClick += gcnew System::EventHandler(this, &Navigation::txtSearch_DoubleClick);
			this->txtSearch->TextChanged += gcnew System::EventHandler(this, &Navigation::txtSearch_TextChanged);
			// 
			// chkLoadNav
			// 
			this->chkLoadNav->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->chkLoadNav->AutoSize = true;
			this->chkLoadNav->Enabled = false;
			this->chkLoadNav->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->chkLoadNav->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->chkLoadNav->ImageKey = L"Folder";
			this->chkLoadNav->Location = System::Drawing::Point(7, 96);
			this->chkLoadNav->Name = L"chkLoadNav";
			this->chkLoadNav->Size = System::Drawing::Size(78, 17);
			this->chkLoadNav->TabIndex = 9;
			this->chkLoadNav->Text = L"Import Nav";
			this->chkLoadNav->UseVisualStyleBackColor = true;
			// 
			// chkUpdateNav
			// 
			this->chkUpdateNav->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->chkUpdateNav->AutoSize = true;
			this->chkUpdateNav->Enabled = false;
			this->chkUpdateNav->Location = System::Drawing::Point(91, 96);
			this->chkUpdateNav->Name = L"chkUpdateNav";
			this->chkUpdateNav->Size = System::Drawing::Size(84, 17);
			this->chkUpdateNav->TabIndex = 11;
			this->chkUpdateNav->Text = L"Update Nav";
			this->chkUpdateNav->UseVisualStyleBackColor = true;
			// 
			// chkLoadLog
			// 
			this->chkLoadLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->chkLoadLog->AutoSize = true;
			this->chkLoadLog->Enabled = false;
			this->chkLoadLog->Location = System::Drawing::Point(181, 96);
			this->chkLoadLog->Name = L"chkLoadLog";
			this->chkLoadLog->Size = System::Drawing::Size(44, 17);
			this->chkLoadLog->TabIndex = 12;
			this->chkLoadLog->Text = L"Log";
			this->chkLoadLog->UseVisualStyleBackColor = true;
			// 
			// Navigation
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(317, 387);
			this->Controls->Add(this->splitInterface);
			this->Name = L"Navigation";
			this->Text = L"Navigation";
			this->Activated += gcnew System::EventHandler(this, &Navigation::Navigation_Activated);
			this->splitInterface->Panel1->ResumeLayout(false);
			this->splitInterface->Panel1->PerformLayout();
			this->splitInterface->Panel2->ResumeLayout(false);
			this->splitInterface->Panel2->PerformLayout();
			this->splitInterface->ResumeLayout(false);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion



};
}
