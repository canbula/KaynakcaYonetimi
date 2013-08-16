#include "kaynakcayonetimi.h"
#include "eklekitap.h"
#include "eklemakale.h"
#include "bulisbn.h"
#include "buldoi.h"

KaynakcaYonetimi::KaynakcaYonetimi(const wxString& title)
	: wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(960,700))
{
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
	
	/*
	menubar = new wxMenuBar;
	file = new wxMenu;
	file->Append(wxID_EXIT,wxT("Kapat"));
	menubar->Append(file,wxT("Dosya"));
	add = new wxMenu;
	add->Append(ID_ADDMENU_BOOK,wxT("Kitap"));
	add->Append(ID_ADDMENU_ARTICLE,wxT("Makale"));
	add->Append(ID_ADDMENU_DOCUMENT,wxT("Doküman"));
	add->Append(ID_ADDMENU_FILE,wxT("Dosya"));
	add->Append(ID_ADDMENU_LIST,wxT("Liste"));
	menubar->Append(add,wxT("Ekle"));
	tool = new wxMenu;
	tool->Append(ID_TOOLMENU_FINDISBN,wxT("ISBN Bul"));
	tool->Append(ID_TOOLMENU_FINDDOI,wxT("DOI Bul"));
	menubar->Append(tool,wxT("Araçlar"));
	help = new wxMenu;
	//help->Append(ID_HELPMENU_ABOUT,wxT("Hakkında"));
	//menubar->Append(help,wxT("Yardım"));
	wxMenuItem *helpItem = new wxMenuItem(help,ID_HELPMENU_ABOUT,wxT("Hakkında"));
	helpItem->SetBitmap(toolbarAbout);
	help->Append(helpItem);
	menubar->Append(help,wxT("Yardım"));
	SetMenuBar(menubar);
	
	wxToolBar *toolbar = CreateToolBar(wxTB_TEXT);
	toolbar->AddTool(ID_TOOLBAR_LIBRARY,wxT("Kaynaklar"),toolbarLibrary);
	toolbar->AddTool(ID_TOOLBAR_BOOK,wxT("Kaynaklar"),toolbarBook);
	toolbar->AddSeparator();
	toolbar->AddTool(ID_TOOLBAR_ARTICLE,wxT("Makale"),toolbarArticle);
	toolbar->AddTool(ID_TOOLBAR_DOCUMENT,wxT("Doküman"),toolbarDocument);
	toolbar->AddTool(ID_TOOLBAR_FILE,wxT("Dosya"),toolbarFile);
	toolbar->AddTool(ID_TOOLBAR_LIST,wxT("Liste"),toolbarList);
	toolbar->Realize();
	*/
	
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
	wxTextCtrl *toolbarSearchTC = new wxTextCtrl(righttoolbar,wxID_ANY,wxT(""));
	righttoolbar->AddControl(toolbarSearchTC);
	righttoolbar->AddTool(-1,wxT("Ara"),toolbarSearch);
	righttoolbar->Realize();

	wxToolBar *lasttoolbar = new wxToolBar(toolbarpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxTB_TEXT);
	lasttoolbar->AddSeparator();
	lasttoolbar->AddTool(ID_TOOLBAR_HELP,wxT("Yardım"),toolbarHelp);
	lasttoolbar->AddTool(ID_TOOLBAR_ABOUT,wxT("Hakkında"),toolbarAbout);
	lasttoolbar->AddTool(wxID_EXIT,wxT("Çıkış"),toolbarQuit);
	lasttoolbar->Realize();

	toolbarhbox->Add(lefttoolbar,1,wxALIGN_LEFT);
	toolbarhbox->Add(righttoolbar,0,wxALIGN_RIGHT);
	toolbarhbox->Add(lasttoolbar,0,wxALIGN_RIGHT);
	toolbarpanel->SetSizer(toolbarhbox);
	mainvbox->Add(toolbarpanel,0,wxEXPAND);
	
	
	//wxStaticText *upperHolderST = new wxStaticText(mainpanel,-1,wxT("üst"));
	//mainvbox->Add(upperHolderST,0,wxEXPAND);
	
	wxPanel *middlepanel = new wxPanel(mainpanel,-1);
	wxBoxSizer *middlehbox = new wxBoxSizer(wxHORIZONTAL);

	//wxStaticText *leftHolderST = new wxStaticText(middlepanel,-1,wxT("Sol"));
	//middlehbox->Add(leftHolderST,1,wxALIGN_LEFT|wxEXPAND);

	wxNotebook *middlenb = new wxNotebook(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1));
	wxPanel *middlesub0 = new wxPanel(middlenb,-1);
	wxPanel *middlesub1 = new wxPanel(middlenb,-1);
	wxPanel *middlesub2 = new wxPanel(middlenb,-1);
	wxPanel *middlesub3 = new wxPanel(middlenb,-1);
	wxPanel *middlesub4 = new wxPanel(middlenb,-1);
	wxPanel *middlesub5 = new wxPanel(middlenb,-1);
	middlenb->AddPage(middlesub0,wxT("Kütüphane"),true);
	middlenb->AddPage(middlesub1,wxT("Kitaplar"),false);
	middlenb->AddPage(middlesub2,wxT("Makaleler"),false);
	middlenb->AddPage(middlesub3,wxT("Dokümanlar"),false);
	middlenb->AddPage(middlesub4,wxT("Dosyalar"),false);
	middlenb->AddPage(middlesub5,wxT("Listeler"),false);
	middlehbox->Add(middlenb,1,wxALIGN_LEFT|wxEXPAND);

	wxStaticLine *middlehboxSEP = new wxStaticLine(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL);
	middlehbox->Add(middlehboxSEP,0,wxEXPAND);

	wxStaticText *rightHolderST = new wxStaticText(middlepanel,-1,wxT("Sağ"),wxPoint(-1,-1),wxSize(200,-1));
	middlehbox->Add(rightHolderST,0,wxALIGN_RIGHT|wxEXPAND);

	middlepanel->SetSizer(middlehbox);
	
	mainvbox->Add(middlepanel,1,wxEXPAND);

	//wxStaticText *lowerHolderST = new wxStaticText(mainpanel,-1,wxT("alt"));
	//mainvbox->Add(lowerHolderST,0,wxEXPAND);
	
	mainpanel->SetSizer(mainvbox);
	
	//Define Main Layout
	//wxPanel *mainpanel = new wxPanel(this,-1);
	//wxBoxSizer *mainhbox = new wxBoxSizer(wxHORIZONTAL);
	
	//wxStaticText *leftholderst = new wxStaticText(mainpanel,-1,wxT("Sol"),wxPoint(-1,-1),wxSize(200,-1));
	//wxStaticLine *mainhboxsep = new wxStaticLine(mainpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL);
	//wxStaticText *rightholderst = new wxStaticText(mainpanel,-1,wxT("Sağ"));
	//mainhbox->Add(leftholderst,0,wxEXPAND);
	//mainhbox->Add(mainhboxsep,0,wxEXPAND);
	//mainhbox->Add(rightholderst,1,wxEXPAND);
	//mainpanel->SetSizer(mainhbox);
	
	Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::OnQuit));
	Connect(ID_TOOLBAR_ADDBOOK,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleKitapDialog));
	Connect(ID_TOOLBAR_ADDARTICLE,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleMakaleDialog));
	Connect(ID_TOOLBAR_FINDISBN,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::BulISBNDialog));
	Connect(ID_TOOLBAR_FINDDOI,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::BulDOIDialog));
	Connect(ID_TOOLBAR_ABOUT,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::OnAbout));
	
	SetIcon(wxIcon(appLocation+wxT("resource/icons/kaynakcayonetimi.xpm")));
	Centre();
}

void KaynakcaYonetimi::EkleKitapDialog(wxCommandEvent& event)
{
	EkleKitap eklekitap(wxT("Yeni Kitap Ekle"),wxT(""));
	if(eklekitap.ShowModal() == wxID_OK) {
		wxString tempstring;
		tempstring << wxT("Eklendi:") << eklekitap.GetNewBookISBN();
		//tempstring << wxT("Ekledim");
		wxMessageDialog *dial = new wxMessageDialog(NULL,tempstring,wxT("Info"),wxOK);
		dial->ShowModal();
		// buraya onaylanan verilerin veritabanına kaydı ile ilgili kodların yazılması gerekiyor
		eklekitap.Destroy();
	}
}

void KaynakcaYonetimi::EkleMakaleDialog(wxCommandEvent& event)
{
	EkleMakale eklemakale(wxT("Yeni Makale Ekle"),wxT(""));
	if(eklemakale.ShowModal() == wxID_OK) {
		wxString tempstring;
		tempstring << wxT("Ekledim");
		wxMessageDialog *dial = new wxMessageDialog(NULL,tempstring,wxT("Info"),wxOK);
		dial->ShowModal();
		// buraya onaylanan verilerin veritabanına kaydı ile ilgili kodların yazılması gerekiyor
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
			eklemakale.Destroy();
		}
		//wxMessageDialog *dial = new wxMessageDialog(NULL,replymessage,wxT("Info"),wxOK);
		//dial->ShowModal();
		buldoi.Destroy();
	}
}

void KaynakcaYonetimi::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxAboutDialogInfo info;
	info.SetName(wxT("Kaynakça Yönetimi"));
	info.SetVersion(wxT("0.0.1"));
	info.SetDescription(wxT("Kaynakça öğelerini barındıran bir veritabanını yönetecek ve tez veya makalelerde kullanılmak üzere seçilen öğeleri barındıran kaynakça listelerini istenilen biçimde otomatik oluşturan bir program."));
	info.SetCopyright(wxT("Pardus Yazılım Kampı 2013 (C) Bora CANBULA <bora.canbula@cbu.edu.tr>"));
	wxAboutBox(info);
}

void KaynakcaYonetimi::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}
