#include "kaynakcayonetimi.h"
#include "eklekitap.h"
#include "eklemakale.h"
#include "bulisbn.h"
#include "buldoi.h"
#include "ekleliste.h"
#include "gosterliste.h"
#include "ekleajanda.h"

KaynakcaYonetimi::KaynakcaYonetimi(const wxString& title)
	: wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(960,700),wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER|wxMAXIMIZE_BOX))
{
	wxSize mainSize = this->GetSize();

	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap toolbarLibrary(appLocation+wxT("resource/toolbar/add.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarBook(appLocation+wxT("resource/toolbar/book.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarArticle(appLocation+wxT("resource/toolbar/contract2.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarDocument(appLocation+wxT("resource/toolbar/document1.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarFile(appLocation+wxT("resource/toolbar/file.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarList(appLocation+wxT("resource/toolbar/list2.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarISBN(appLocation+wxT("resource/toolbar/barcode.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarDOI(appLocation+wxT("resource/toolbar/serial-number.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarSearch(appLocation+wxT("resource/toolbar/zoom.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarAbout(appLocation+wxT("resource/toolbar/info.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarHelp(appLocation+wxT("resource/toolbar/help.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarQuit(appLocation+wxT("resource/toolbar/gateway.png"),wxBITMAP_TYPE_PNG);
	wxBitmap iconBook(appLocation+wxT("resource/icons/book.png"),wxBITMAP_TYPE_PNG);
	wxBitmap iconArticle(appLocation+wxT("resource/icons/contract2.png"),wxBITMAP_TYPE_PNG);
	wxBitmap iconDocument(appLocation+wxT("resource/icons/document1.png"),wxBITMAP_TYPE_PNG);
	wxBitmap iconFile(appLocation+wxT("resource/icons/file.png"),wxBITMAP_TYPE_PNG);
	
	
	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *file = new wxMenu;
	wxMenu *fromfile = new wxMenu;
	fromfile->Append(wxID_FILE1,wxT("Kitap Olarak"));
	fromfile->Append(wxID_FILE2,wxT("Makale Olarak"));
	fromfile->Append(wxID_FILE3,wxT("Doküman Olarak"));
	fromfile->Append(wxID_FILE4,wxT("Dosya Olarak"));
	file->Append(wxID_FILE,wxT("Dosya Ekle"),fromfile);
	file->AppendSeparator();
	file->Append(wxID_EXIT,wxT("Kapat"));
	menubar->Append(file,wxT("Dosya"));
	wxMenu *add = new wxMenu;
	add->Append(ID_ADDMENU_BOOK,wxT("Kitap"));
	add->Append(ID_ADDMENU_ARTICLE,wxT("Makale"));
	add->Append(ID_ADDMENU_DOCUMENT,wxT("Doküman"));
	add->Append(ID_ADDMENU_FILE,wxT("Dosya"));
	add->Append(ID_ADDMENU_LIST,wxT("Liste"));
	menubar->Append(add,wxT("Ekle"));
	wxMenu *tool = new wxMenu;
	tool->Append(ID_TOOLMENU_FINDISBN,wxT("ISBN Bul"));
	tool->Append(ID_TOOLMENU_FINDDOI,wxT("DOI Bul"));
	menubar->Append(tool,wxT("Araçlar"));
	wxMenu *help = new wxMenu;
	help->Append(wxID_HELP,wxT("Yardım"));
	help->AppendSeparator();
	help->Append(wxID_ABOUT,wxT("Hakkında"));
	menubar->Append(help,wxT("Yardım"));
	SetMenuBar(menubar);
	
	wxStatusBar *statusbar = new wxStatusBar(this,wxID_ANY,wxST_SIZEGRIP);
	this->SetStatusBar(statusbar);
	statusbar->SetStatusText(wxT("Kaynakça Yönetimi - Pardus Yazılım Kampı 2013"));

	////////////////////////////
	wxPanel *mainpanel = new wxPanel(this,-1);
	wxBoxSizer *mainvbox = new wxBoxSizer(wxVERTICAL);
	
	
	wxPanel *toolbarpanel = new wxPanel(mainpanel,-1);
	wxBoxSizer *toolbarhbox = new wxBoxSizer(wxHORIZONTAL);
	wxToolBar *lefttoolbar = new wxToolBar(toolbarpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxTB_TEXT);
	lefttoolbar->AddTool(ID_TOOLBAR_ADDBOOK,wxT("Kitap Ekle"),toolbarBook);
	lefttoolbar->AddTool(ID_TOOLBAR_ADDARTICLE,wxT("Makale Ekle"),toolbarArticle);
	lefttoolbar->AddTool(ID_TOOLBAR_ADDDOCUMENT,wxT("Doküman Ekle"),toolbarDocument);
	lefttoolbar->AddTool(ID_TOOLBAR_ADDFILE,wxT("Dosya Ekle"),toolbarFile);
	lefttoolbar->AddTool(ID_TOOLBAR_ADDLIST,wxT("Liste Ekle"),toolbarList);
	lefttoolbar->AddSeparator();
	lefttoolbar->AddTool(ID_TOOLBAR_FINDISBN,wxT("ISBN Bul"),toolbarISBN);
	lefttoolbar->AddTool(ID_TOOLBAR_FINDDOI,wxT("DOI Bul"),toolbarDOI);
	lefttoolbar->AddSeparator();
	lefttoolbar->Realize();
	wxToolBar *righttoolbar = new wxToolBar(toolbarpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxTB_TEXT);
	wxSearchCtrl *toolbarSearchBox = new wxSearchCtrl(righttoolbar,-1,wxT(""),wxPoint(-1,-1),wxSize(-1,-1),wxTE_PROCESS_ENTER);
	wxMenu *searchMenu = new wxMenu;
	searchMenu->Append(-1,wxT("Genel Arama"));
	searchMenu->Append(-1,wxT("Yazar Arama"));
	searchMenu->Append(-1,wxT("ISBN Numarası ile Arama"));
	searchMenu->Append(-1,wxT("DOI Numarası ile Arama"));
	toolbarSearchBox->SetMenu(searchMenu);
	righttoolbar->AddControl(toolbarSearchBox);
	righttoolbar->AddTool(-1,wxT("Ara"),toolbarSearch);
	righttoolbar->Realize();

	wxToolBar *lasttoolbar = new wxToolBar(toolbarpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxTB_TEXT);
	lasttoolbar->AddSeparator();
	lasttoolbar->AddTool(wxID_ABOUT,wxT("Hakkında"),toolbarAbout);
	lasttoolbar->AddTool(wxID_EXIT,wxT("Çıkış"),toolbarQuit);
	lasttoolbar->Realize();

	toolbarhbox->Add(lefttoolbar,1,wxALIGN_LEFT);
	toolbarhbox->Add(righttoolbar,0,wxALIGN_RIGHT);
	toolbarhbox->Add(lasttoolbar,0,wxALIGN_RIGHT);
	toolbarpanel->SetSizer(toolbarhbox);
	mainvbox->Add(toolbarpanel,0,wxEXPAND);
	
	wxPanel *middlepanel = new wxPanel(mainpanel,-1);
	wxBoxSizer *middlehbox = new wxBoxSizer(wxHORIZONTAL);

	wxNotebook *middlenb = new wxNotebook(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1));
	wxPanel *middlesub0 = new wxPanel(middlenb,-1);

	wxPanel *middlesub1 = new wxPanel(middlenb,-1);
	
	wxBoxSizer *bookhbox = new wxBoxSizer(wxHORIZONTAL);
	wxListCtrl *booklist = new wxListCtrl(middlesub1,wxID_ANY,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(wxT("Sutun 1"));
	booklist->InsertColumn(0, col0);
	booklist->SetColumnWidth(0,120);
	wxListItem col1;
	col1.SetId(1);
	col1.SetText(wxT("Sutun 2"));
	booklist->InsertColumn(1, col1);
	booklist->SetColumnWidth(1,120);
	wxListItem col2;
	wxString boraaa;
	boraaa << mainSize.GetWidth() << wxT(" ") << mainSize.GetHeight();
	col2.SetId(2);
	col2.SetText(boraaa);
	booklist->InsertColumn(2, col2);
	booklist->SetColumnWidth(2,mainSize.GetWidth()-240-240);
	for(int n=0;n<30;n++)
	{
		wxListItem item;
		item.SetId(n);
		if(n%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		booklist->InsertItem(item);
		booklist->SetItem(n,0,wxT("bilgi 1"));
		booklist->SetItem(n,1,wxT("bilgi 2"));
		booklist->SetItem(n,2,wxT("bilgi 3"));
	}
	bookhbox->Add(booklist,1,wxALIGN_CENTER|wxEXPAND);
	middlesub1->SetSizer(bookhbox);

	wxPanel *middlesub2 = new wxPanel(middlenb,-1);
	wxBoxSizer *paperhbox = new wxBoxSizer(wxHORIZONTAL);
	paperlistcolumns = new wxArrayString();
	paperlistcolumndesc = new wxArrayString();
	int paperlistcolumnwidths[] = {100,40,200,120,120,60,40,40,40,40,120,120,120};
	paperlistcolumns->Add(wxT("doi"));paperlistcolumndesc->Add(wxT("DOI Numarası"));
	paperlistcolumns->Add(wxT("star"));paperlistcolumndesc->Add(wxT("Beğeni"));
	paperlistcolumns->Add(wxT("title"));paperlistcolumndesc->Add(wxT("Makale Başlığı"));
	paperlistcolumns->Add(wxT("authors"));paperlistcolumndesc->Add(wxT("Yazarlar"));
	paperlistcolumns->Add(wxT("journal"));paperlistcolumndesc->Add(wxT("Dergi"));
	paperlistcolumns->Add(wxT("published"));paperlistcolumndesc->Add(wxT("Tarih"));
	paperlistcolumns->Add(wxT("volume"));paperlistcolumndesc->Add(wxT("Cilt"));
	paperlistcolumns->Add(wxT("issue"));paperlistcolumndesc->Add(wxT("Sayı"));
	paperlistcolumns->Add(wxT("firstpage"));paperlistcolumndesc->Add(wxT("İlk Sf."));
	paperlistcolumns->Add(wxT("lastpage"));paperlistcolumndesc->Add(wxT("Son Sf."));
	paperlistcolumns->Add(wxT("link"));paperlistcolumndesc->Add(wxT("Link"));
	paperlistcolumns->Add(wxT("subject"));paperlistcolumndesc->Add(wxT("Konu"));
	paperlistcolumns->Add(wxT("refid"));paperlistcolumndesc->Add(wxT("Ref."));
	paperlist = new wxListView(middlesub2,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	for(int i=0;i<13;i++)
	{
		wxListItem paperlistcol;
		paperlistcol.SetId(i);
		paperlistcol.SetText(paperlistcolumndesc->Item(i));
		paperlist->InsertColumn(i,paperlistcol);
		paperlist->SetColumnWidth(i,paperlistcolumnwidths[i]);
	}
	KaynakcaYonetimi::MakaleleriYukle(wxT(""));
	paperhbox->Add(paperlist,1,wxALIGN_CENTER|wxEXPAND);
	middlesub2->SetSizer(paperhbox);

	wxPanel *middlesub3 = new wxPanel(middlenb,-1);
	wxPanel *middlesub4 = new wxPanel(middlenb,-1);

	wxPanel *middlesub5 = new wxPanel(middlenb,-1);
	wxBoxSizer *listhbox = new wxBoxSizer(wxHORIZONTAL);
	listlistcolumns = new wxArrayString();
	listlistcolumndesc = new wxArrayString();
	int listlistcolumnwidths[] = {0,120,240,80};
	listlistcolumns->Add(wxT("id"));listlistcolumndesc->Add(wxT("Id"));
	listlistcolumns->Add(wxT("name"));listlistcolumndesc->Add(wxT("Liste Adı"));
	listlistcolumns->Add(wxT("desc"));listlistcolumndesc->Add(wxT("Liste Açıklaması"));
	listlistcolumns->Add(wxT("style"));listlistcolumndesc->Add(wxT("Referans Stili"));
	listlist = new wxListView(middlesub5,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	for(int i=0;i<4;i++)
	{
		wxListItem listlistcol;
		listlistcol.SetId(i);
		listlistcol.SetText(listlistcolumndesc->Item(i));
		listlist->InsertColumn(i,listlistcol);
		listlist->SetColumnWidth(i,listlistcolumnwidths[i]);
	}
	KaynakcaYonetimi::ListeleriYukle(wxT(""));
	listhbox->Add(listlist,1,wxALIGN_CENTER|wxEXPAND);
	middlesub5->SetSizer(listhbox);

	middlenb->AddPage(middlesub0,wxT("Kütüphane"),true);
	middlenb->AddPage(middlesub1,wxT("Kitaplar"),false);
	middlenb->AddPage(middlesub2,wxT("Makaleler"),false);
	middlenb->AddPage(middlesub3,wxT("Dokümanlar"),false);
	middlenb->AddPage(middlesub4,wxT("Dosyalar"),false);
	middlenb->AddPage(middlesub5,wxT("Listeler"),false);
	middlehbox->Add(middlenb,1,wxALIGN_LEFT|wxEXPAND);

	wxStaticLine *middlehboxSEP = new wxStaticLine(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL);
	middlehbox->Add(middlehboxSEP,0,wxEXPAND);

	wxPanel *rightpanel = new wxPanel(middlepanel,-1);
	wxBoxSizer *rightvbox = new wxBoxSizer(wxVERTICAL);
	todocal = new wxCalendarCtrl();
	todocal->Create(rightpanel,-1,wxDefaultDateTime,wxPoint(-1,-1),wxSize(-1,-1),wxCAL_MONDAY_FIRST|wxCAL_SHOW_SURROUNDING_WEEKS|wxCAL_SEQUENTIAL_MONTH_SELECTION);
	todocal->SetHeaderColours(wxColour(125,125,125),todocal->GetHeaderColourBg());
	rightvbox->Add(todocal,0,wxALIGN_CENTER);
	todolist = new wxListView(rightpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	wxListItem todolistcol0;
	todolistcol0.SetId(0);
	todolistcol0.SetText(wxT("Id"));
	todolist->InsertColumn(0,todolistcol0);
	todolist->SetColumnWidth(0,0);
	wxListItem todolistcol1;
	todolistcol1.SetId(1);
	todolistcol1.SetText(wxT("Günlük Notlar"));
	todolist->InsertColumn(1,todolistcol1);
	wxSize rightSize = todocal->GetSize();
	todolist->SetColumnWidth(1,rightSize.GetWidth());
	KaynakcaYonetimi::AjandayiYukle();
	rightvbox->Add(todolist,1,wxALIGN_CENTER|wxEXPAND);

	wxPanel *droppervpanel = new wxPanel(rightpanel,-1);
	wxBoxSizer *droppervbox = new wxBoxSizer(wxVERTICAL);
	droppervbox->Add(-1,5);
	wxPanel *dropperhpanel1 = new wxPanel(droppervpanel,-1);
	wxBoxSizer *dropperhbox1 = new wxBoxSizer(wxHORIZONTAL);
	dropperhbox1->Add(new wxStaticText(dropperhpanel1,-1,wxT("")),1,wxEXPAND);
	wxStaticBitmap *dropperlogo1 = new wxStaticBitmap(dropperhpanel1,-1,iconBook);
	dropperlogo1->DragAcceptFiles(true);
	dropperhbox1->Add(dropperlogo1,0,wxALIGN_RIGHT);
	dropperhbox1->Add(new wxStaticLine(dropperhpanel1,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL),0,wxEXPAND);
	wxStaticBitmap *dropperlogo2 = new wxStaticBitmap(dropperhpanel1,-1,iconArticle);
	dropperhbox1->Add(dropperlogo2,0,wxALIGN_LEFT);
	dropperhbox1->Add(new wxStaticText(dropperhpanel1,-1,wxT("")),1,wxEXPAND);
	dropperhpanel1->SetSizer(dropperhbox1);
	droppervbox->Add(dropperhpanel1,0,wxALIGN_CENTER|wxEXPAND);
	droppervbox->Add(new wxStaticLine(droppervpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	wxPanel *dropperhpanel2 = new wxPanel(droppervpanel,-1);
	wxBoxSizer *dropperhbox2 = new wxBoxSizer(wxHORIZONTAL);
	dropperhbox2->Add(new wxStaticText(dropperhpanel2,-1,wxT("")),1,wxEXPAND);
	wxStaticBitmap *dropperlogo3 = new wxStaticBitmap(dropperhpanel2,-1,iconDocument);
	dropperhbox2->Add(dropperlogo3,0,wxALIGN_RIGHT);
	dropperhbox2->Add(new wxStaticLine(dropperhpanel2,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL),0,wxEXPAND);
	wxStaticBitmap *dropperlogo4 = new wxStaticBitmap(dropperhpanel2,-1,iconFile);
	dropperhbox2->Add(dropperlogo4,0,wxALIGN_LEFT);
	dropperhbox2->Add(new wxStaticText(dropperhpanel2,-1,wxT("")),1,wxEXPAND);
	dropperhpanel2->SetSizer(dropperhbox2);
	droppervbox->Add(dropperhpanel2,0,wxALIGN_CENTER|wxEXPAND);
	droppervbox->Add(-1,5);
	droppervpanel->SetSizer(droppervbox);
	rightvbox->Add(droppervpanel,0,wxALIGN_CENTER|wxALIGN_BOTTOM|wxEXPAND);
	/////////////////////////////

	rightpanel->SetSizer(rightvbox);
	middlehbox->Add(rightpanel,0,wxALIGN_RIGHT|wxEXPAND);

	middlepanel->SetSizer(middlehbox);
	
	mainvbox->Add(middlepanel,1,wxEXPAND);
	
	mainpanel->SetSizer(mainvbox);
	
	Connect(wxID_FILE1,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleKitapDialog));
	Connect(wxID_FILE2,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleMakaleDialog));
	Connect(ID_ADDMENU_BOOK,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleKitapDialog));
	Connect(ID_ADDMENU_ARTICLE,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleMakaleDialog));
	Connect(ID_TOOLBAR_ADDBOOK,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleKitapDialog));
	Connect(ID_TOOLBAR_ADDARTICLE,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleMakaleDialog));
	Connect(ID_TOOLMENU_FINDISBN,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::BulISBNDialog));
	Connect(ID_TOOLMENU_FINDDOI,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::BulDOIDialog));
	Connect(ID_TOOLBAR_FINDISBN,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::BulISBNDialog));
	Connect(ID_TOOLBAR_FINDDOI,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::BulDOIDialog));
	Connect(ID_TOOLBAR_ADDLIST,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleListeDialog));
	Connect(wxID_ABOUT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::Hakkinda));
	Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::Kapat));
	Connect(paperlist->GetId(),wxEVT_COMMAND_LIST_COL_CLICK,wxListEventHandler(KaynakcaYonetimi::MakaleSirala));
	Connect(paperlist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::MakaleSagTik));
	Connect(listlist->GetId(),wxEVT_COMMAND_LIST_COL_CLICK,wxListEventHandler(KaynakcaYonetimi::ListeSirala));
	Connect(listlist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::ListeSagTik));
	Connect(listlist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(KaynakcaYonetimi::GosterListeDialog));
	Connect(todolist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::AjandaSagTik));
	Connect(todolist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(KaynakcaYonetimi::EkleAjandaDialog));
	Connect(todocal->GetId(),wxEVT_CALENDAR_SEL_CHANGED,(wxObjectEventFunction)&KaynakcaYonetimi::AjandayiYenile, NULL, this);
	dropperlogo1->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(KaynakcaYonetimi::OnDropFiles), NULL, this);

	Connect(toolbarSearchBox->GetId(),wxEVT_COMMAND_TEXT_ENTER,wxCommandEventHandler(KaynakcaYonetimi::AramaKurtarma));
	
	SetIcon(wxIcon(appLocation+wxT("resource/icons/kaynakcayonetimi.xpm")));
	Centre();

	int frameSize = mainSize.GetWidth();
	int blockSize = rightSize.GetWidth()+20;
	listlist->SetColumnWidth(1,150);
	listlist->SetColumnWidth(2,300);
	listlist->SetColumnWidth(3,frameSize-blockSize-450);
}

void KaynakcaYonetimi::MakaleleriYukle(const wxString& sorter)
{
	paperlist->DeleteAllItems();
	wxSQLite3Database *paperlistretriever = new wxSQLite3Database();
	paperlistretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString paperlistretrievesql;
	paperlistretrievesql << wxT("SELECT * FROM papers");
	if(sorter != wxT("")) paperlistretrievesql << wxT(" ORDER BY ") << sorter << wxT(" DESC ");
	wxSQLite3ResultSet paperlistretrieveSet = paperlistretriever->ExecuteQuery(paperlistretrievesql);
	int paperlistcount = 0;
	while(paperlistretrieveSet.NextRow())
	{
		wxListItem item;
		item.SetId(0);
		if(paperlistcount%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		int textcolorfromstar;
		textcolorfromstar = 150-wxAtoi(paperlistretrieveSet.GetAsString(wxT("star")))*30;
		item.SetTextColour(wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
		paperlist->InsertItem(item);
		for(int i=0;i<13;i++)
			paperlist->SetItem(0,i,paperlistretrieveSet.GetAsString(paperlistcolumns->Item(i)));
		paperlistcount++;
	}
	paperlistretrieveSet.Finalize();
	paperlistretriever->Close();
	delete paperlistretriever;
	if(paperlist->GetItemCount() > 0)
		paperlist->RefreshItems(0,paperlist->GetItemCount()-1);
}

void KaynakcaYonetimi::MakaleSirala(wxListEvent& event)
{
	KaynakcaYonetimi::MakaleleriYukle(paperlistcolumns->Item(event.GetColumn()));
}

void KaynakcaYonetimi::ListeleriYukle(const wxString& sorter)
{
	listlist->DeleteAllItems();
	wxSQLite3Database *listlistretriever = new wxSQLite3Database();
	listlistretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString listlistretrievesql;
	listlistretrievesql << wxT("SELECT * FROM lists");
	if(sorter != wxT("")) listlistretrievesql << wxT(" ORDER BY ") << sorter << wxT(" DESC ");
	wxSQLite3ResultSet listlistretrieveSet = listlistretriever->ExecuteQuery(listlistretrievesql);
	int listlistcount = 0;
	while(listlistretrieveSet.NextRow())
	{
		wxListItem item;
		item.SetId(0);
		if(listlistcount%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		listlist->InsertItem(item);
		for(int i=0;i<4;i++)
			listlist->SetItem(0,i,listlistretrieveSet.GetAsString(listlistcolumns->Item(i)));
		listlistcount++;
	}
	listlistretrieveSet.Finalize();
	listlistretriever->Close();
	delete listlistretriever;
	if(listlist->GetItemCount() > 0)
		listlist->RefreshItems(0,listlist->GetItemCount()-1);
}

void KaynakcaYonetimi::ListeSirala(wxListEvent& event)
{
	KaynakcaYonetimi::ListeleriYukle(listlistcolumns->Item(event.GetColumn()));
}

void KaynakcaYonetimi::AjandayiYenile(wxCommandEvent& event)
{
	KaynakcaYonetimi::AjandayiYukle();
}

void KaynakcaYonetimi::AjandayiYukle()
{
	wxString date;
	date << todocal->GetDate().FormatISODate();
	todolist->DeleteAllItems();
	wxSQLite3Database *todolistretriever = new wxSQLite3Database();
	todolistretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString todolistretrievesql;
	todolistretrievesql << wxT("SELECT * FROM todos WHERE date=='") << date << wxT("'");
	wxSQLite3ResultSet todolistretrieveSet = todolistretriever->ExecuteQuery(todolistretrievesql);
	int todolistcount = 0;
	while(todolistretrieveSet.NextRow())
	{
		wxListItem item;
		item.SetId(0);
		if(todolistcount%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		todolist->InsertItem(item);
		todolist->SetItem(0,0,todolistretrieveSet.GetAsString(wxT("id")));
		todolist->SetItem(0,1,todolistretrieveSet.GetAsString(wxT("title")));
		todolistcount++;
	}
	todolistretrieveSet.Finalize();
	todolistretriever->Close();
	delete todolistretriever;
	wxListItem item;
	item.SetId(0);
	if(todolistcount%2==1) item.SetBackgroundColour(wxColour(245,245,255));
	todolist->InsertItem(item);
	todolist->SetItem(0,0,wxT("0"));
	todolist->SetItem(0,1,wxT("Eklemek için çift tıklayın.."));
	if(todolist->GetItemCount() > 0)
		todolist->RefreshItems(0,todolist->GetItemCount()-1);
}

void KaynakcaYonetimi::EkleKitapDialog(wxCommandEvent& event)
{
	EkleKitap eklekitap(wxT("Yeni Kitap Ekle"),wxT(""));
	if(eklekitap.ShowModal() == wxID_OK) {
		wxString tempstring;
		tempstring << wxT("Eklendi:") << eklekitap.GetNewBookISBN();
		wxMessageDialog *dial = new wxMessageDialog(NULL,tempstring,wxT("Info"),wxOK);
		dial->ShowModal();
		eklekitap.Destroy();
	}
}

void KaynakcaYonetimi::EkleMakaleDialog(wxCommandEvent& event)
{
	EkleMakale eklemakale(wxT("Yeni Makale Ekle"),wxT(""));
	if(eklemakale.ShowModal() == wxID_OK) {
		eklemakale.SavePaper();
		KaynakcaYonetimi::MakaleleriYukle(wxT(""));
		eklemakale.Destroy();
	}
}

void KaynakcaYonetimi::BulISBNDialog(wxCommandEvent& event)
{
	BulISBN bulisbn(wxT("ISBN Numarası Bulma Aracı"));
	if(bulisbn.ShowModal() == wxID_OK) {
		EkleKitap eklekitap(wxT("Yeni Kitap Ekle"),bulisbn.GetISBN());
		if(eklekitap.ShowModal() == wxID_OK) {
			eklekitap.Destroy();
		}
		bulisbn.Destroy();
	}
}

void KaynakcaYonetimi::BulDOIDialog(wxCommandEvent& event)
{
	BulDOI buldoi(wxT("DOI Numarası Bulma Aracı"));
	if(buldoi.ShowModal() == wxID_OK) {
		EkleMakale eklemakale(wxT("Yeni Makale Ekle"),buldoi.GetDOI());
		if(eklemakale.ShowModal() == wxID_OK) {
			eklemakale.SavePaper();
			KaynakcaYonetimi::MakaleleriYukle(wxT(""));
			eklemakale.Destroy();
		}
		buldoi.Destroy();
	}
}

void KaynakcaYonetimi::EkleListeDialog(wxCommandEvent& event)
{
	EkleListe ekleliste(wxT("Yeni Liste Ekle"),wxT(""));
	if(ekleliste.ShowModal() == wxID_OK) {
		ekleliste.SaveList();
		KaynakcaYonetimi::ListeleriYukle(wxT(""));
		ekleliste.Destroy();
	}
}

void KaynakcaYonetimi::GosterListeDialog(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(listlist->GetFocusedItem());
	item.SetColumn(0);
	listlist->GetItem(item);
	GosterListe gosterliste(wxT("Liste Görüntüleme"),listlist->GetItemText(item));
	gosterliste.ShowModal();
	gosterliste.Destroy();
}

void KaynakcaYonetimi::EkleAjandaDialog(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(todolist->GetFocusedItem());
	item.SetColumn(0);
	todolist->GetItem(item);
	if(todolist->GetItemText(item)==wxT("0"))
	{
		EkleAjanda ekleajanda(wxT("Yeni Ajanda Notu Ekle"),wxT(""),todocal->GetDate().FormatISODate());
		if(ekleajanda.ShowModal() == wxID_OK) {
			ekleajanda.SaveTodo();
			KaynakcaYonetimi::AjandayiYukle();
			ekleajanda.Destroy();
		}
	}
}

void KaynakcaYonetimi::Hakkinda(wxCommandEvent& WXUNUSED(event))
{
	wxAboutDialogInfo info;
	info.SetName(wxT("Kaynakça Yönetimi"));
	info.SetVersion(wxT("0.0.1"));
	info.SetDescription(wxT("Kaynakça öğelerini barındıran bir veritabanını yönetecek ve tez veya makalelerde kullanılmak üzere seçilen öğeleri barındıran kaynakça listelerini istenilen biçimde otomatik oluşturan bir program."));
	info.SetCopyright(wxT("Pardus Yazılım Kampı 2013 (C) Bora CANBULA <bora.canbula@cbu.edu.tr>"));
	wxAboutBox(info);
}

void KaynakcaYonetimi::Kapat(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void KaynakcaYonetimi::AramaKurtarma(wxCommandEvent& WXUNUSED(event))
{
	wxMessageDialog dial(NULL,wxT("Arama fonksiyonunu henüz kodlamadım."),wxT("Arama"),wxOK);
	dial.ShowModal();
}

void KaynakcaYonetimi::MakaleSagTikList(wxCommandEvent &event)
{
	void *data=static_cast<wxMenu *>(event.GetEventObject())->GetClientData();
	wxListItem item;
	item.SetId(paperlist->GetFocusedItem());
	item.SetColumn(0);
	paperlist->GetItem(item);
	if(event.GetId() < 7200)
	{
		wxString starstring;
		starstring << event.GetId()-7190;
		wxSQLite3Database *starupdater = new wxSQLite3Database();
		starupdater->Open(appLocation+wxT("db/Kaynakca.db"));
		wxSQLite3Statement starupdatersql = starupdater->PrepareStatement(wxT("UPDATE papers SET star=? WHERE doi=?"));
		starupdatersql.Bind(1,starstring);
		starupdatersql.Bind(2,paperlist->GetItemText(item));
		starupdatersql.ExecuteUpdate();
		starupdatersql.ClearBindings();
		starupdatersql.Reset();
		starupdater->Close();
		delete starupdater;
		int textcolorfromstar;
		textcolorfromstar = 150-wxAtoi(starstring)*30;
		paperlist->SetItem(paperlist->GetFocusedItem(),1,starstring);
		paperlist->SetItemTextColour(item,wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
	}
	else
	{
		if(event.GetId() > 8200)
		{
			wxSQLite3Database *listrefremover = new wxSQLite3Database();
			listrefremover->Open(appLocation+wxT("db/Kaynakca.db"));
			wxSQLite3Statement listrefremoversql = listrefremover->PrepareStatement(wxT("DELETE FROM listrefs WHERE listid==? AND isbndoi==?"));
			listrefremoversql.Bind(1,event.GetId()-8200);
			listrefremoversql.Bind(2,paperlist->GetItemText(item));
			listrefremoversql.ExecuteUpdate();
			listrefremoversql.ClearBindings();
			listrefremoversql.Reset();
			listrefremover->Close();
			delete listrefremover;
		}
		else
		{
			wxString listrefnumbersql;
			listrefnumbersql << wxT("SELECT * FROM listrefs WHERE listid=='") << event.GetId()-7200 << wxT("' ORDER BY number DESC");
			vtcevap listrefnumber;
			listrefnumber = Vt(listrefnumbersql);
			wxString yenisira = wxT("001");
			if(listrefnumber.satir>0)
			{
				int yenii = wxAtoi(listrefnumber.sonuc.Item(1));
				yenisira = wxString::Format(wxT("%03d"),yenii+1);
			}
			wxArrayString listrefsave;
			wxString idstring;
			idstring << event.GetId()-7200;
			listrefsave.Add(idstring);
			listrefsave.Add(yenisira);
			listrefsave.Add(wxT("paper"));
			listrefsave.Add(paperlist->GetItemText(item));
			VtEkleSilGuncelle(wxT("INSERT INTO listrefs VALUES (?,?,?,?);"),listrefsave);
		}
	}
}

void KaynakcaYonetimi::MakaleSagTikTik(wxCommandEvent &event)
{
	void *data=static_cast<wxMenu *>(event.GetEventObject())->GetClientData();
	wxListItem item;
	item.SetId(paperlist->GetFocusedItem());
	item.SetColumn(0);
	paperlist->GetItem(item);
	switch(event.GetId())
	{
		case ID_PAPERRCMENU_EDIT:
		{
			wxMessageDialog dial(NULL,wxT("Makale düzenleme fonksiyonları henüz tamamlanmadı."),wxT("Info"),wxOK);
			dial.ShowModal();
		}
		break;
		case ID_PAPERRCMENU_DELETE:
		{
			wxMessageDialog *dial = new wxMessageDialog(NULL,wxT("Bu makaleyi silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
			if(dial->ShowModal() == wxID_YES) {
				wxSQLite3Database *paperremover = new wxSQLite3Database();
				paperremover->Open(appLocation+wxT("db/Kaynakca.db"));
				wxSQLite3Statement paperremoversql = paperremover->PrepareStatement(wxT("DELETE FROM papers WHERE doi==?"));
				paperremoversql.Bind(1,paperlist->GetItemText(item));
				paperremoversql.ExecuteUpdate();
				paperremoversql.ClearBindings();
				paperremoversql.Reset();
				paperremover->Close();
				delete paperremover;
				KaynakcaYonetimi::MakaleleriYukle(wxT(""));
			}
		}
		break;
	}
}

void KaynakcaYonetimi::MakaleSagTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(paperlist->GetFocusedItem());
	item.SetColumn(0);
	paperlist->GetItem(item);
	
	wxSQLite3Database *makalesagtikpaperretriever = new wxSQLite3Database();
	makalesagtikpaperretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString makalesagtikpaperretrieversql;
	makalesagtikpaperretrieversql << wxT("SELECT * FROM papers WHERE doi == '") << paperlist->GetItemText(item) << wxT("';");
	wxSQLite3ResultSet makalesagtikpaperretrieveSet = makalesagtikpaperretriever->ExecuteQuery(makalesagtikpaperretrieversql); 
	int makalesagtikstarid = 7190 + wxAtoi(makalesagtikpaperretrieveSet.GetAsString(wxT("star")));
	makalesagtikpaperretrieveSet.Finalize();
	makalesagtikpaperretriever->Close();
	delete makalesagtikpaperretriever;
	wxMenu makalesagtikmenu;
	makalesagtikmenu.SetClientData(data);
	makalesagtikmenu.Append(ID_PAPERRCMENU_EDIT,wxT("Düzenle"));
	makalesagtikmenu.Append(ID_PAPERRCMENU_DELETE,wxT("Sil"));
	makalesagtikmenu.AppendSeparator();
	wxMenu *makalesagtiksubmenu1 = new wxMenu;
	wxSQLite3Database *makalesagtiklistretriever = new wxSQLite3Database();
	makalesagtiklistretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxSQLite3ResultSet makalesagtiklistretrieveSet = makalesagtiklistretriever->ExecuteQuery(wxT("SELECT * FROM lists ORDER BY id DESC"));
	while(makalesagtiklistretrieveSet.NextRow())
	{
		wxString makalesagtiklistrefsql;
		makalesagtiklistrefsql << wxT("SELECT * FROM listrefs WHERE listid == '") << makalesagtiklistretrieveSet.GetAsString(wxT("id")) << wxT("' AND isbndoi=='") << paperlist->GetItemText(item) << wxT("';");
		wxSQLite3ResultSet makalesagtiklistrefSet = makalesagtiklistretriever->ExecuteQuery(makalesagtiklistrefsql);
		int makalesagtiklistrefid = 7200;
		if(makalesagtiklistretrieveSet.GetAsString(wxT("id"))==makalesagtiklistrefSet.GetAsString(wxT("listid")))
			makalesagtiklistrefid = 8200;
		makalesagtiklistrefSet.Finalize();
		int makalesagtiklistid = makalesagtiklistrefid + wxAtoi(makalesagtiklistretrieveSet.GetAsString(wxT("id")));
		makalesagtiksubmenu1->AppendCheckItem(makalesagtiklistid,makalesagtiklistretrieveSet.GetAsString(wxT("name")));
		if(makalesagtiklistid > 8200)
			makalesagtiksubmenu1->Check(makalesagtiklistid,TRUE);
		Connect(makalesagtiklistid, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::MakaleSagTikList, NULL, this);
	}
	makalesagtiklistretrieveSet.Finalize();
	makalesagtiklistretriever->Close();
	delete makalesagtiklistretriever;
	makalesagtikmenu.Append(-1,wxT("Listeler"), makalesagtiksubmenu1);
	makalesagtikmenu.AppendSeparator();
	wxMenu *makalesagtiksubmenu2 = new wxMenu;
	makalesagtiksubmenu2->AppendCheckItem(7190,wxT("0"));
	makalesagtiksubmenu2->AppendCheckItem(7191,wxT("1"));
	makalesagtiksubmenu2->AppendCheckItem(7192,wxT("2"));
	makalesagtiksubmenu2->AppendCheckItem(7193,wxT("3"));
	makalesagtiksubmenu2->AppendCheckItem(7194,wxT("4"));
	makalesagtiksubmenu2->AppendCheckItem(7195,wxT("5"));
	makalesagtiksubmenu2->Check(makalesagtikstarid,TRUE);
	Connect(7190, 7195, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::MakaleSagTikList, NULL, this);
	makalesagtikmenu.Append(-1,wxT("Beğeni"), makalesagtiksubmenu2);
	makalesagtikmenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::MakaleSagTikTik, NULL, this);
	PopupMenu(&makalesagtikmenu);
 }

void KaynakcaYonetimi::ListeSagTikTik(wxCommandEvent &event)
{
	void *data=static_cast<wxMenu *>(event.GetEventObject())->GetClientData();
	wxListItem item;
	item.SetId(listlist->GetFocusedItem());
	item.SetColumn(0);
	listlist->GetItem(item);
	switch(event.GetId())
	{
		case ID_LISTRCMENU_EDIT:
		{
			EkleListe ekleliste(wxT("Liste Düzenle"),listlist->GetItemText(item));
			if(ekleliste.ShowModal() == wxID_OK) {
				ekleliste.UpdateList(listlist->GetItemText(item));
				KaynakcaYonetimi::ListeleriYukle(wxT(""));
				ekleliste.Destroy();
			}
		}
		break;
		case ID_LISTRCMENU_DELETE:
		{
			wxMessageDialog *dial = new wxMessageDialog(NULL,wxT("Bu listeyi silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
			if(dial->ShowModal() == wxID_YES) {
				wxSQLite3Database *listremover = new wxSQLite3Database();
				listremover->Open(appLocation+wxT("db/Kaynakca.db"));
				wxSQLite3Statement listremoversql = listremover->PrepareStatement(wxT("DELETE FROM lists WHERE id==?"));
				listremoversql.Bind(1,listlist->GetItemText(item));
				listremoversql.ExecuteUpdate();
				listremoversql.ClearBindings();
				listremoversql.Reset();
				listremover->Close();
				delete listremover;
				KaynakcaYonetimi::ListeleriYukle(wxT(""));
			}
		}
		break;
	}
}

void KaynakcaYonetimi::ListeSagTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxMenu listesagtikmenu;
	listesagtikmenu.SetClientData(data);
	listesagtikmenu.Append(ID_LISTRCMENU_EDIT,wxT("Düzenle"));
	listesagtikmenu.Append(ID_LISTRCMENU_DELETE,wxT("Sil"));
	listesagtikmenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::ListeSagTikTik, NULL, this);
	PopupMenu(&listesagtikmenu);
 }

void KaynakcaYonetimi::AjandaSagTikTik(wxCommandEvent &event)
{
	void *data=static_cast<wxMenu *>(event.GetEventObject())->GetClientData();
	wxListItem item;
	item.SetId(todolist->GetFocusedItem());
	item.SetColumn(0);
	todolist->GetItem(item);
	switch(event.GetId())
	{
		case ID_TODORCMENU_EDIT:
		{
			EkleAjanda ekleajanda(wxT("Ajanda Notu Düzenle"),todolist->GetItemText(item),todocal->GetDate().FormatISODate());
			if(ekleajanda.ShowModal() == wxID_OK) {
				ekleajanda.UpdateTodo(todolist->GetItemText(item));
				KaynakcaYonetimi::AjandayiYukle();
				ekleajanda.Destroy();
			}
		}
		break;
		case ID_TODORCMENU_DELETE:
		{
			wxMessageDialog *dial = new wxMessageDialog(NULL,wxT("Bu ajanda notunu silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
			if(dial->ShowModal() == wxID_YES) {
				wxSQLite3Database *todoremover = new wxSQLite3Database();
				todoremover->Open(appLocation+wxT("db/Kaynakca.db"));
				wxSQLite3Statement todoremoversql = todoremover->PrepareStatement(wxT("DELETE FROM todos WHERE id==?"));
				todoremoversql.Bind(1,todolist->GetItemText(item));
				todoremoversql.ExecuteUpdate();
				todoremoversql.ClearBindings();
				todoremoversql.Reset();
				todoremover->Close();
				delete todoremover;
				KaynakcaYonetimi::AjandayiYukle();
			}
		}
		break;
	}
}

void KaynakcaYonetimi::AjandaSagTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(todolist->GetFocusedItem());
	item.SetColumn(0);
	todolist->GetItem(item);
	if(todolist->GetItemText(item)!=wxT("0"))
	{
		wxMenu ajandasagtikmenu;
		ajandasagtikmenu.SetClientData(data);
		ajandasagtikmenu.Append(ID_TODORCMENU_EDIT,wxT("Düzenle"));
		ajandasagtikmenu.Append(ID_TODORCMENU_DELETE,wxT("Sil"));
		ajandasagtikmenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::AjandaSagTikTik, NULL, this);
		PopupMenu(&ajandasagtikmenu);
	}
 }

void KaynakcaYonetimi::NaberBora(wxCommandEvent& event)
{
	wxMessageDialog *dial = new wxMessageDialog(NULL,todocal->GetDate().FormatISODate(),wxT("Info"),wxOK);
	dial->ShowModal();
}

void KaynakcaYonetimi::OnDropFiles(wxDropFilesEvent& event)
{
	wxMessageDialog *dial = new wxMessageDialog(NULL,wxT("Tamam kaptim"),wxT("Info"),wxOK);
	dial->ShowModal();
}
