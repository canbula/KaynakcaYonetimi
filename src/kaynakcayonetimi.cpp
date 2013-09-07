/*
    This file is part of KaynakcaYonetimi.

    KaynakcaYonetimi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    KaynakcaYonetimi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with KaynakcaYonetimi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "kaynakcayonetimi.h"
#include "eklekitap.h"
#include "eklemakale.h"
#include "ekledokuman.h"
#include "ekledosya.h"
#include "ekleliste.h"
#include "gosterliste.h"
#include "ekleajanda.h"
#include "bulisbn.h"
#include "buldoi.h"
#include "arama.h"

KaynakcaYonetimi::KaynakcaYonetimi(const wxString& title)
	: wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(960,700))//,wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER|wxMAXIMIZE_BOX))
{
	wxSize mainSize = this->GetSize();
	// Burayi wxEVT_SIZE ile kontrol altinda tutmak gerekecek.

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
	wxBitmap toolbarAdobe(appLocation+wxT("resource/toolbar/adobe.png"),wxBITMAP_TYPE_PNG);
	wxBitmap iconBook(appLocation+wxT("resource/icons/book.png"),wxBITMAP_TYPE_PNG);
	wxBitmap iconArticle(appLocation+wxT("resource/icons/contract2.png"),wxBITMAP_TYPE_PNG);
	wxBitmap iconDocument(appLocation+wxT("resource/icons/document1.png"),wxBITMAP_TYPE_PNG);
	wxBitmap iconFile(appLocation+wxT("resource/icons/file.png"),wxBITMAP_TYPE_PNG);
	
	
	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *file = new wxMenu;
	wxMenu *fromfile = new wxMenu;
	fromfile->Append(wxID_FILE1,wxT("Kitap Olarak\tCtrl+1"));
	fromfile->Append(wxID_FILE2,wxT("Makale Olarak\tCtrl+2"));
	fromfile->Append(wxID_FILE3,wxT("Doküman Olarak\tCtrl+3"));
	fromfile->Append(wxID_FILE4,wxT("Dosya Olarak\tCtrl+4"));
	file->Append(wxID_FILE,wxT("Dosya Ekle"),fromfile);
	file->AppendSeparator();
	file->Append(wxID_EXIT,wxT("Kapat"));
	menubar->Append(file,wxT("Dosya"));
	wxMenu *add = new wxMenu;
	add->Append(ID_ADDMENU_BOOK,wxT("Kitap\tAlt+1"));
	add->Append(ID_ADDMENU_ARTICLE,wxT("Makale\tAlt+2"));
	add->Append(ID_ADDMENU_DOCUMENT,wxT("Doküman\tAlt+3"));
	add->Append(ID_ADDMENU_FILE,wxT("Dosya\tAlt+4"));
	add->Append(ID_ADDMENU_LIST,wxT("Liste\tAlt+5"));
	menubar->Append(add,wxT("Ekle"));
	wxMenu *tool = new wxMenu;
	tool->Append(ID_TOOLMENU_FINDISBN,wxT("ISBN Bul\tCtrl+I"));
	tool->Append(ID_TOOLMENU_FINDDOI,wxT("DOI Bul\tCtrl+D"));
	tool->Append(ID_TOOLMENU_SEARCH,wxT("Arama Yap\tCtrl+F"));
	menubar->Append(tool,wxT("Araçlar"));
	//help = new wxMenu;
	//help->Append(ID_HELPMENU_ABOUT,wxT("Hakkında"));
	//menubar->Append(help,wxT("Yardım"));
	//wxMenuItem *helpItem = new wxMenuItem(help,wxID_ABOUT,wxT("Hakkında"));
	//helpItem->SetBitmap(toolbarAbout);
	//help->Append(helpItem);
	//menubar->Append(help,wxT("Yardım"));
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
	lefttoolbar->AddTool(ID_TOOLBAR_SEARCH,wxT("Arama Yap"),toolbarSearch);
	lefttoolbar->AddSeparator();
	lefttoolbar->Realize();

	wxToolBar *lasttoolbar = new wxToolBar(toolbarpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxTB_TEXT);
	lasttoolbar->AddSeparator();
	lasttoolbar->AddTool(ID_TOOLBAR_HELP,wxT("Yardım"),toolbarHelp);
	lasttoolbar->AddTool(wxID_ABOUT,wxT("Hakkında"),toolbarAbout);
	lasttoolbar->AddTool(wxID_EXIT,wxT("Çıkış"),toolbarQuit);
	lasttoolbar->Realize();

	toolbarhbox->Add(lefttoolbar,1,wxALIGN_LEFT);
	toolbarhbox->Add(lasttoolbar,0,wxALIGN_RIGHT);
	toolbarpanel->SetSizer(toolbarhbox);
	mainvbox->Add(toolbarpanel,0,wxEXPAND);
	
	wxPanel *middlepanel = new wxPanel(mainpanel,-1);
	wxBoxSizer *middlehbox = new wxBoxSizer(wxHORIZONTAL);

	middlenb = new wxNotebook(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1));

	wxPanel *middlesub1 = new wxPanel(middlenb,-1);
	wxBoxSizer *bookhbox = new wxBoxSizer(wxHORIZONTAL);
	booklistcolumns = new wxArrayString();
	booklistcolumndesc = new wxArrayString();
	int booklistcolumnwidths[] = {120,55,20,200,120,100,100,100};
	booklistcolumns->Add(wxT("isbn"));booklistcolumndesc->Add(wxT("ISBN Numarası"));
	booklistcolumns->Add(wxT("star"));booklistcolumndesc->Add(wxT("Beğeni"));
	booklistcolumns->Add(wxT(""));booklistcolumndesc->Add(wxT(""));
	booklistcolumns->Add(wxT("title"));booklistcolumndesc->Add(wxT("Kitap İsmi"));
	booklistcolumns->Add(wxT("authors"));booklistcolumndesc->Add(wxT("Yazarlar"));
	booklistcolumns->Add(wxT("publisher"));booklistcolumndesc->Add(wxT("Yayıncı"));
	booklistcolumns->Add(wxT("subject"));booklistcolumndesc->Add(wxT("Konu"));
	booklistcolumns->Add(wxT("refid"));booklistcolumndesc->Add(wxT("Ref."));
	booklist = new wxListView(middlesub1,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	for(int i=0;i<8;i++)
	{
		wxListItem booklistcol;
		booklistcol.SetId(i);
		booklistcol.SetText(booklistcolumndesc->Item(i));
		booklist->InsertColumn(i,booklistcol);
		booklist->SetColumnWidth(i,booklistcolumnwidths[i]);
	}
	KaynakcaYonetimi::KitaplariYukle(wxT(""));
	bookhbox->Add(booklist,1,wxALIGN_CENTER|wxEXPAND);
	middlesub1->SetSizer(bookhbox);

	wxPanel *middlesub2 = new wxPanel(middlenb,-1);
	wxBoxSizer *paperhbox = new wxBoxSizer(wxHORIZONTAL);
	paperlistcolumns = new wxArrayString();
	paperlistcolumndesc = new wxArrayString();
	int paperlistcolumnwidths[] = {100,55,20,200,120,120,60,40,40,40,40,120,120,120};
	paperlistcolumns->Add(wxT("doi"));paperlistcolumndesc->Add(wxT("DOI Numarası"));
	paperlistcolumns->Add(wxT("star"));paperlistcolumndesc->Add(wxT("Beğeni"));
	paperlistcolumns->Add(wxT(""));paperlistcolumndesc->Add(wxT(""));
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
	for(int i=0;i<14;i++)
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
	wxBoxSizer *documenthbox = new wxBoxSizer(wxHORIZONTAL);
	documentlistcolumns = new wxArrayString();
	documentlistcolumndesc = new wxArrayString();
	int documentlistcolumnwidths[] = {0,55,20,200,240};
	documentlistcolumns->Add(wxT("id"));documentlistcolumndesc->Add(wxT("Id"));
	documentlistcolumns->Add(wxT("star"));documentlistcolumndesc->Add(wxT("Beğeni"));
	documentlistcolumns->Add(wxT(""));documentlistcolumndesc->Add(wxT(""));
	documentlistcolumns->Add(wxT("name"));documentlistcolumndesc->Add(wxT("Doküman Adı"));
	documentlistcolumns->Add(wxT("desc"));documentlistcolumndesc->Add(wxT("Doküman Açıklaması"));
	documentlist = new wxListView(middlesub3,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	for(int i=0;i<5;i++)
	{
		wxListItem documentlistcol;
		documentlistcol.SetId(i);
		documentlistcol.SetText(documentlistcolumndesc->Item(i));
		documentlist->InsertColumn(i,documentlistcol);
		documentlist->SetColumnWidth(i,documentlistcolumnwidths[i]);
	}
	KaynakcaYonetimi::DokumanlariYukle(wxT(""));
	documenthbox->Add(documentlist,1,wxALIGN_CENTER|wxEXPAND);
	middlesub3->SetSizer(documenthbox);
	
	wxPanel *middlesub4 = new wxPanel(middlenb,-1);
	wxBoxSizer *filehbox = new wxBoxSizer(wxHORIZONTAL);
	filelistcolumns = new wxArrayString();
	filelistcolumndesc = new wxArrayString();
	int filelistcolumnwidths[] = {0,55,20,200,240};
	filelistcolumns->Add(wxT("id"));filelistcolumndesc->Add(wxT("Id"));
	filelistcolumns->Add(wxT("star"));filelistcolumndesc->Add(wxT("Beğeni"));
	filelistcolumns->Add(wxT(""));filelistcolumndesc->Add(wxT(""));
	filelistcolumns->Add(wxT("name"));filelistcolumndesc->Add(wxT("Dosya Adı"));
	filelistcolumns->Add(wxT("desc"));filelistcolumndesc->Add(wxT("Dosya Açıklaması"));
	filelist = new wxListView(middlesub4,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	for(int i=0;i<5;i++)
	{
		wxListItem filelistcol;
		filelistcol.SetId(i);
		filelistcol.SetText(filelistcolumndesc->Item(i));
		filelist->InsertColumn(i,filelistcol);
		filelist->SetColumnWidth(i,filelistcolumnwidths[i]);
	}
	KaynakcaYonetimi::DosyalariYukle(wxT(""));
	filehbox->Add(filelist,1,wxALIGN_CENTER|wxEXPAND);
	middlesub4->SetSizer(filehbox);

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

	middlenb->AddPage(middlesub1,wxT("Kitaplar"),false);
	middlenb->AddPage(middlesub2,wxT("Makaleler"),true);
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
	dropperlogo2->DragAcceptFiles(true);
	dropperhbox1->Add(dropperlogo2,0,wxALIGN_LEFT);
	dropperhbox1->Add(new wxStaticText(dropperhpanel1,-1,wxT("")),1,wxEXPAND);
	dropperhpanel1->SetSizer(dropperhbox1);
	droppervbox->Add(dropperhpanel1,0,wxALIGN_CENTER|wxEXPAND);
	droppervbox->Add(new wxStaticLine(droppervpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	wxPanel *dropperhpanel2 = new wxPanel(droppervpanel,-1);
	wxBoxSizer *dropperhbox2 = new wxBoxSizer(wxHORIZONTAL);
	dropperhbox2->Add(new wxStaticText(dropperhpanel2,-1,wxT("")),1,wxEXPAND);
	wxStaticBitmap *dropperlogo3 = new wxStaticBitmap(dropperhpanel2,-1,iconDocument);
	dropperlogo3->DragAcceptFiles(true);
	dropperhbox2->Add(dropperlogo3,0,wxALIGN_RIGHT);
	dropperhbox2->Add(new wxStaticLine(dropperhpanel2,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL),0,wxEXPAND);
	wxStaticBitmap *dropperlogo4 = new wxStaticBitmap(dropperhpanel2,-1,iconFile);
	dropperlogo4->DragAcceptFiles(true);
	dropperhbox2->Add(dropperlogo4,0,wxALIGN_LEFT);
	dropperhbox2->Add(new wxStaticText(dropperhpanel2,-1,wxT("")),1,wxEXPAND);
	dropperhpanel2->SetSizer(dropperhbox2);
	droppervbox->Add(dropperhpanel2,0,wxALIGN_CENTER|wxEXPAND);
	droppervbox->Add(-1,5);
	droppervpanel->SetSizer(droppervbox);
	rightvbox->Add(droppervpanel,0,wxALIGN_CENTER|wxALIGN_BOTTOM|wxEXPAND);

	rightpanel->SetSizer(rightvbox);
	middlehbox->Add(rightpanel,0,wxALIGN_RIGHT|wxEXPAND);

	middlepanel->SetSizer(middlehbox);
	
	mainvbox->Add(middlepanel,1,wxEXPAND);
	
	mainpanel->SetSizer(mainvbox);
	
	Connect(wxID_FILE1,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::DosyaEkleKitapDialog));
	Connect(wxID_FILE2,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::DosyaEkleMakaleDialog));
	Connect(wxID_FILE3,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::DosyaEkleDokumanDialog));
	Connect(wxID_FILE4,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::DosyaEkleDosyaDialog));
	Connect(ID_ADDMENU_BOOK,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleKitapDialog));
	Connect(ID_ADDMENU_ARTICLE,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleMakaleDialog));
	Connect(ID_ADDMENU_DOCUMENT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleDokumanDialog));
	Connect(ID_ADDMENU_FILE,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleDosyaDialog));
	Connect(ID_ADDMENU_LIST,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleListeDialog));
	Connect(ID_TOOLBAR_ADDBOOK,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleKitapDialog));
	Connect(ID_TOOLBAR_ADDARTICLE,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleMakaleDialog));
	Connect(ID_TOOLBAR_ADDDOCUMENT,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleDokumanDialog));
	Connect(ID_TOOLBAR_ADDFILE,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleDosyaDialog));
	Connect(ID_TOOLBAR_ADDLIST,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleListeDialog));
	Connect(ID_TOOLMENU_FINDISBN,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::BulISBNDialog));
	Connect(ID_TOOLMENU_FINDDOI,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::BulDOIDialog));
	Connect(ID_TOOLMENU_SEARCH,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::AramaKutusuDialog));
	Connect(ID_TOOLBAR_FINDISBN,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::BulISBNDialog));
	Connect(ID_TOOLBAR_FINDDOI,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::BulDOIDialog));
	Connect(ID_TOOLBAR_SEARCH,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::AramaKutusuDialog));
	Connect(wxID_ABOUT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::Hakkinda));
	Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::Kapat));
	Connect(booklist->GetId(),wxEVT_COMMAND_LIST_COL_CLICK,wxListEventHandler(KaynakcaYonetimi::KitapSirala));
	Connect(booklist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::KitapSagTik));
	Connect(booklist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(KaynakcaYonetimi::KitapCiftTik));
	Connect(paperlist->GetId(),wxEVT_COMMAND_LIST_COL_CLICK,wxListEventHandler(KaynakcaYonetimi::MakaleSirala));
	Connect(paperlist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::MakaleSagTik));
	Connect(paperlist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(KaynakcaYonetimi::MakaleCiftTik));
	Connect(documentlist->GetId(),wxEVT_COMMAND_LIST_COL_CLICK,wxListEventHandler(KaynakcaYonetimi::DokumanSirala));
	Connect(documentlist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::DokumanSagTik));
	Connect(documentlist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(KaynakcaYonetimi::DokumanCiftTik));
	Connect(filelist->GetId(),wxEVT_COMMAND_LIST_COL_CLICK,wxListEventHandler(KaynakcaYonetimi::DosyaSirala));
	Connect(filelist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::DosyaSagTik));
	Connect(filelist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(KaynakcaYonetimi::DosyaCiftTik));
	Connect(listlist->GetId(),wxEVT_COMMAND_LIST_COL_CLICK,wxListEventHandler(KaynakcaYonetimi::ListeSirala));
	Connect(listlist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::ListeSagTik));
	Connect(listlist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(KaynakcaYonetimi::GosterListeDialog));
	Connect(todolist->GetId(),wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,wxListEventHandler(KaynakcaYonetimi::AjandaSagTik));
	Connect(todolist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(KaynakcaYonetimi::EkleAjandaDialog));
	Connect(todocal->GetId(),wxEVT_CALENDAR_SEL_CHANGED,(wxObjectEventFunction)&KaynakcaYonetimi::AjandayiYenile, NULL, this);
	dropperlogo1->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(KaynakcaYonetimi::KitapBirak), NULL, this);
	dropperlogo2->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(KaynakcaYonetimi::MakaleBirak), NULL, this);
	dropperlogo3->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(KaynakcaYonetimi::DokumanBirak), NULL, this);
	dropperlogo4->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(KaynakcaYonetimi::DosyaBirak), NULL, this);
	//Connect(toolbarSearchBox->GetId(),wxEVT_COMMAND_TEXT_ENTER,wxCommandEventHandler(KaynakcaYonetimi::Arama));
	
	SetIcon(wxIcon(appLocation+wxT("resource/icons/kaynakcayonetimi.xpm")));
	Centre();

	// Bu kismi bir fonksiyona cevirip onresize ile de tekrar tetiklemeliyim
	int frameSize = mainSize.GetWidth();
	int blockSize = rightSize.GetWidth()+20;
	listlist->SetColumnWidth(1,150);
	listlist->SetColumnWidth(2,300);
	listlist->SetColumnWidth(3,frameSize-blockSize-450);
	//wxString sizerstring;
	//sizerstring << frameSize << wxT(" ") << frameSize-blockSize << wxT(" ") << blockSize;
	//wxMessageDialog sizerdial(this,sizerstring,wxT("Boyutlar"),wxOK);
	//sizerdial.ShowModal();
}

/////////////////////////////////////////////////
// Genel ////////////////////////////////////////
/////////////////////////////////////////////////
void KaynakcaYonetimi::Hakkinda(wxCommandEvent& WXUNUSED(event))
{
	wxAboutDialogInfo info;
	info.SetName(wxT("Kaynakça Yönetimi"));
	info.SetVersion(wxT("0.0.1"));
	info.SetDescription(wxT("Kaynakça öğelerini barındıran bir veritabanını yönetecek ve tez veya makalelerde kullanılmak üzere seçilen öğeleri barındıran kaynakça listelerini istenilen biçimde otomatik oluşturan bir program."));
	info.SetCopyright(wxT("Pardus Yazılım Kampı 2013 (C) Bora CANBULA <bora.canbula@cbu.edu.tr>"));
	wxAboutBox(info);
}
void KaynakcaYonetimi::Kapat(wxCommandEvent& WXUNUSED(event)) {Close(true);}
void KaynakcaYonetimi::Arama(wxCommandEvent& WXUNUSED(event))
{
	//KaynakcaYonetimi::MakaleleriYukle(wxT(""));
}
/////////////////////////////////////////////////
// Kitap ////////////////////////////////////////
/////////////////////////////////////////////////
void KaynakcaYonetimi::DosyaEkleKitapDialog(wxCommandEvent& event)
{
	wxFileDialog *newfileforbook = new wxFileDialog(this,wxT("Kitap olarak yüklemek istediğiniz dosyayı seçiniz.."),wxT(""),wxT(""),wxT("*.pdf;*.djvu"));
	if(newfileforbook->ShowModal() == wxID_OK)
	{
		KaynakcaYonetimi::KitapYeniDosya(newfileforbook->GetPath());
	}
}
void KaynakcaYonetimi::EkleKitapDialog(wxCommandEvent& event)
{
	EkleKitap eklekitap(wxT("Yeni Kitap Ekle"),wxT(""));
	if(eklekitap.ShowModal() == wxID_OK) {
		eklekitap.SaveBook();
		KaynakcaYonetimi::KitaplariYukle(wxT(""));
		eklekitap.Destroy();
	}
}
void KaynakcaYonetimi::BulISBNDialog(wxCommandEvent& event)
{
	BulISBN bulisbn(wxT("ISBN Numarası Bulma Aracı"),wxT(""));
	if(bulisbn.ShowModal() == wxID_OK) {
		EkleKitap eklekitap(wxT("Yeni Kitap Ekle"),bulisbn.GetISBN());
		if(eklekitap.ShowModal() == wxID_OK) {
			eklekitap.SaveBook();
			KaynakcaYonetimi::KitaplariYukle(wxT(""));
			eklekitap.Destroy();
		}
		bulisbn.Destroy();
	}
}
void KaynakcaYonetimi::KitaplariYukle(const wxString& sorter,const wxString& query)
{
	booklist->DeleteAllItems();
	wxString booklistsql;
	booklistsql << wxT("SELECT * FROM books");
	if(query != wxT(""))
	{
		wxStringTokenizer searchtkz(query,wxT(" "));
		int i = 0;
		while(searchtkz.HasMoreTokens())
		{
			wxString srcquery = searchtkz.GetNextToken();
			if(i==0)
			{
				booklistsql << wxT(" WHERE (isbn LIKE '\%") << srcquery << wxT("\%' OR title LIKE '\%") << srcquery << wxT("\%' OR authors LIKE '\%") << srcquery << wxT("\%' OR publisher LIKE '\%") << srcquery << wxT("\%' OR subject LIKE '\%") << srcquery << wxT("\%' OR refid LIKE '\%") << srcquery << wxT("\%')");
			}
			else
			{
				booklistsql << wxT(" OR (isbn LIKE '\%") << srcquery << wxT("\%' OR title LIKE '\%") << srcquery << wxT("\%' OR authors LIKE '\%") << srcquery << wxT("\%' OR publisher LIKE '\%") << srcquery << wxT("\%' OR subject LIKE '\%") << srcquery << wxT("\%' OR refid LIKE '\%") << srcquery << wxT("\%')");
			}
			i++;
		}
	}
	if(sorter != wxT("")) booklistsql << wxT(" ORDER BY ") << sorter << wxT(" DESC ");
	vtcevap booklistcevap;
	booklistcevap = Vt(booklistsql);
	wxImage::AddHandler(new wxPNGHandler);
	wxImageList *bookimagelist = new wxImageList();
	bookimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/book_0_star.png"),wxBITMAP_TYPE_PNG));
	bookimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/book_1_star.png"),wxBITMAP_TYPE_PNG));
	bookimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/book_2_star.png"),wxBITMAP_TYPE_PNG));
	bookimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/book_3_star.png"),wxBITMAP_TYPE_PNG));
	bookimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/book_4_star.png"),wxBITMAP_TYPE_PNG));
	bookimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/book_5_star.png"),wxBITMAP_TYPE_PNG));
	bookimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/book_0_file.png"),wxBITMAP_TYPE_PNG));
	bookimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/book_1_file.png"),wxBITMAP_TYPE_PNG));
	wxImage::AddHandler(new wxJPEGHandler);
	for(int i=0;i<booklistcevap.satir;i++)
		bookimagelist->Add(wxBitmap(appLocation+wxT("resource/bookcovers/")+booklistcevap.sonuc.Item(i*booklistcevap.sutun+0)+wxT(".jpeg"),wxBITMAP_TYPE_JPEG));
	booklist->SetImageList(bookimagelist,wxIMAGE_LIST_SMALL);
	for(int i=0;i<booklistcevap.satir;i++)
	{
		wxListItem item;
		item.SetId(0);
		if(i%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		int textcolorfromstar;
		textcolorfromstar = 150-wxAtoi(booklistcevap.sonuc.Item(i*booklistcevap.sutun+6))*30;
		item.SetTextColour(wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
		booklist->InsertItem(item);
		booklist->SetItemImage(item,i+8);
		booklist->SetItem(0,0,booklistcevap.sonuc.Item(i*booklistcevap.sutun+0));
		booklist->SetItem(0,1,wxT(""));
		booklist->SetItemColumnImage(item,1,wxAtoi(booklistcevap.sonuc.Item(i*booklistcevap.sutun+6)));
		wxString dosyakontrolcommand;
		dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name ") << booklistcevap.sonuc.Item(i*booklistcevap.sutun+0) << wxT(".*");
		wxArrayString output;
		wxArrayString errors;
		wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
		if(output.GetCount() > 0)
		{
			if(wxFileExists(output.Item(0)))
			{
				booklist->SetItem(0,2,wxT(""));
				booklist->SetItemColumnImage(item,2,7);
			}
			else
			{
				booklist->SetItem(0,2,wxT(""));
				booklist->SetItemColumnImage(item,2,6);
			}
		}
		booklist->SetItem(0,3,booklistcevap.sonuc.Item(i*booklistcevap.sutun+1));
		booklist->SetItem(0,4,booklistcevap.sonuc.Item(i*booklistcevap.sutun+2));
		booklist->SetItem(0,5,booklistcevap.sonuc.Item(i*booklistcevap.sutun+3));
		booklist->SetItem(0,6,booklistcevap.sonuc.Item(i*booklistcevap.sutun+4));
		booklist->SetItem(0,7,booklistcevap.sonuc.Item(i*booklistcevap.sutun+5));
	}
	if(booklist->GetItemCount() > 0)
		booklist->RefreshItems(0,booklist->GetItemCount()-1);
	middlenb->SetSelection(0);
}
void KaynakcaYonetimi::KitapSirala(wxListEvent& event) {KaynakcaYonetimi::KitaplariYukle(booklistcolumns->Item(event.GetColumn()));}
void KaynakcaYonetimi::KitapSagTikList(wxCommandEvent &event)
{
	void *data=static_cast<wxMenu *>(event.GetEventObject())->GetClientData();
	wxListItem item;
	item.SetId(booklist->GetFocusedItem());
	item.SetColumn(0);
	booklist->GetItem(item);
	if(event.GetId() < 7200)
	{
		wxArrayString starupdate;
		wxString starstring;
		starstring << event.GetId()-7190;
		starupdate.Add(starstring);
		starupdate.Add(booklist->GetItemText(item));
		VtEkleSilGuncelle(wxT("UPDATE books SET star=? WHERE isbn=?"),starupdate);
		int textcolorfromstar;
		textcolorfromstar = 150-wxAtoi(starstring)*30;
		booklist->SetItemColumnImage(item,1,wxAtoi(starstring));
		//booklist->SetItem(booklist->GetFocusedItem(),1,starstring);
		booklist->SetItemTextColour(item,wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
	}
	else
	{
		if(event.GetId() > 8200)
		{
			wxArrayString listrefremove;
			wxString idstring;
			idstring << event.GetId()-8200;
			listrefremove.Add(idstring);
			listrefremove.Add(booklist->GetItemText(item));
			VtEkleSilGuncelle(wxT("DELETE FROM listrefs WHERE listid==? AND isbndoi==?"),listrefremove);
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
			listrefsave.Add(wxT("book"));
			listrefsave.Add(booklist->GetItemText(item));
			VtEkleSilGuncelle(wxT("INSERT INTO listrefs VALUES (?,?,?,?);"),listrefsave);
		}
	}
}
void KaynakcaYonetimi::KitapSagTikTik(wxCommandEvent &event)
{
	void *data=static_cast<wxMenu *>(event.GetEventObject())->GetClientData();
	wxListItem item;
	item.SetId(booklist->GetFocusedItem());
	item.SetColumn(0);
	booklist->GetItem(item);
	switch(event.GetId())
	{
		case ID_BOOKRCMENU_EDIT:
		{
			EkleKitap eklekitap(wxT("Kitap Düzenle"),booklist->GetItemText(item));
			if(eklekitap.ShowModal() == wxID_OK) {
				eklekitap.SaveBook();
				KaynakcaYonetimi::KitaplariYukle(wxT(""));
				eklekitap.Destroy();
			}
		}
		break;
		case ID_BOOKRCMENU_DELETE:
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Bu kitabı silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
			if(dial->ShowModal() == wxID_YES) {
				wxArrayString bookremove;
				bookremove.Add(booklist->GetItemText(item));
				VtEkleSilGuncelle(wxT("DELETE FROM books WHERE isbn==?"),bookremove);
				VtEkleSilGuncelle(wxT("DELETE FROM listrefs WHERE isbndoi==?"),bookremove);
				KaynakcaYonetimi::KitaplariYukle(wxT(""));
			}
		}
		break;
		case ID_BOOKRCMENU_UPLOAD:
		{
			wxFileDialog *uploadfileforbook = new wxFileDialog(this,wxT("Bu kitap ile ilişkilendirmek için bir dosya seçiniz.."),wxT(""),wxT(""),wxT("*.pdf;*.djvu"));
			if(uploadfileforbook->ShowModal() == wxID_OK)
			{
				wxString uploadedfileforbook = uploadfileforbook->GetPath();
				wxString uploadedfileisbn = booklist->GetItemText(item);
				wxString uploadedfilepath;
				uploadedfilepath << appLocation << wxT("files/") << uploadedfileisbn;
				wxCopyFile(uploadedfileforbook,uploadedfilepath);
			}
		}
		break;
		case ID_BOOKRCMENU_WWW:
		{
			wxString wwwbookcommand;
			wwwbookcommand << wxT("xdg-open http://www.amazon.com/dp/") << booklist->GetItemText(item);
			wxExecute(wwwbookcommand);
		}
		break;
	}
}
void KaynakcaYonetimi::KitapSagTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(booklist->GetFocusedItem());
	item.SetColumn(0);
	booklist->GetItem(item);
	
	wxString kitapsagtiksql;
	kitapsagtiksql << wxT("SELECT * FROM books WHERE isbn == '") << booklist->GetItemText(item) << wxT("';");
	vtcevap kitapsagtikcevap;
	kitapsagtikcevap = Vt(kitapsagtiksql);
	int kitapsagtikstarid = 7190 + wxAtoi(kitapsagtikcevap.sonuc.Item(6));
	wxMenu kitapsagtikmenu;
	kitapsagtikmenu.SetClientData(data);
	kitapsagtikmenu.Append(ID_BOOKRCMENU_EDIT,wxT("Düzenle"));
	kitapsagtikmenu.Append(ID_BOOKRCMENU_DELETE,wxT("Sil"));
	kitapsagtikmenu.AppendSeparator();
	kitapsagtikmenu.Append(ID_BOOKRCMENU_UPLOAD,wxT("Dosya Yükle"));
	kitapsagtikmenu.AppendSeparator();
	kitapsagtikmenu.Append(ID_BOOKRCMENU_WWW,wxT("Web'de Görüntüle"));
	kitapsagtikmenu.AppendSeparator();
	wxMenu *kitapsagtiksubmenu1 = new wxMenu;
	vtcevap kitapsagtiklistcevap;
	kitapsagtiklistcevap = Vt(wxT("SELECT * FROM lists ORDER BY id DESC"));
	for(int i=0;i<kitapsagtiklistcevap.satir;i++)
	{
		wxString kitapsagtiklistrefsql;
		kitapsagtiklistrefsql << wxT("SELECT * FROM listrefs WHERE listid == '") << kitapsagtiklistcevap.sonuc.Item(i*kitapsagtiklistcevap.sutun+0) << wxT("' AND isbndoi=='") << booklist->GetItemText(item) << wxT("';");
		vtcevap kitapsagtiklistref;
		kitapsagtiklistref = Vt(kitapsagtiklistrefsql);
		int kitapsagtiklistrefid = 7200;
		if(kitapsagtiklistref.satir>0)
		{
			if(kitapsagtiklistcevap.sonuc.Item(i*kitapsagtiklistcevap.sutun+0)==kitapsagtiklistref.sonuc.Item(0))
				kitapsagtiklistrefid = 8200;
		}
		int kitapsagtiklistid = kitapsagtiklistrefid + wxAtoi(kitapsagtiklistcevap.sonuc.Item(i*kitapsagtiklistcevap.sutun+0));
		kitapsagtiksubmenu1->AppendCheckItem(kitapsagtiklistid,kitapsagtiklistcevap.sonuc.Item(i*kitapsagtiklistcevap.sutun+1));
		if(kitapsagtiklistid > 8200)
			kitapsagtiksubmenu1->Check(kitapsagtiklistid,TRUE);
		Connect(kitapsagtiklistid, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::KitapSagTikList, NULL, this);
	}
	kitapsagtikmenu.Append(-1,wxT("Listeler"), kitapsagtiksubmenu1);
	kitapsagtikmenu.AppendSeparator();
	wxMenu *kitapsagtiksubmenu2 = new wxMenu;
	kitapsagtiksubmenu2->AppendCheckItem(7190,wxT("0"));
	kitapsagtiksubmenu2->AppendCheckItem(7191,wxT("1"));
	kitapsagtiksubmenu2->AppendCheckItem(7192,wxT("2"));
	kitapsagtiksubmenu2->AppendCheckItem(7193,wxT("3"));
	kitapsagtiksubmenu2->AppendCheckItem(7194,wxT("4"));
	kitapsagtiksubmenu2->AppendCheckItem(7195,wxT("5"));
	kitapsagtiksubmenu2->Check(kitapsagtikstarid,TRUE);
	Connect(7190, 7195, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::KitapSagTikList, NULL, this);
	kitapsagtikmenu.Append(-1,wxT("Beğeni"), kitapsagtiksubmenu2);
	kitapsagtikmenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::KitapSagTikTik, NULL, this);
	PopupMenu(&kitapsagtikmenu);
}
void KaynakcaYonetimi::KitapCiftTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(booklist->GetFocusedItem());
	item.SetColumn(0);
	booklist->GetItem(item);
	wxString kitapdosyaisbn = booklist->GetItemText(item);
	wxString dosyakontrolcommand;
	dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name ") << kitapdosyaisbn << wxT(".*");
	wxArrayString output;
	wxArrayString errors;
	wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
	if(output.GetCount() > 0)
	{
		if(wxFileExists(output.Item(0)))
		{
			wxString openfilecommand;
			openfilecommand << wxT("xdg-open '") << output.Item(0) << wxT("'");
			wxExecute(openfilecommand);
		}
		else
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu kitap ile ilişkili bir dosya bulunmuyor.\nYeni dosya yüklemek için sağ tıklayın."),wxT("Dosya Bulunamadı"),wxOK);
			dial->ShowModal();
		}
	}
	else
	{
		wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu kitap ile ilişkili bir dosya bulunmuyor.\nYeni dosya yüklemek için sağ tıklayın."),wxT("Dosya Bulunamadı"),wxOK);
		dial->ShowModal();
	}
}
void KaynakcaYonetimi::KitapYeniDosya(const wxString& yenidosya)
{
	wxFileName* gelendosyaadi = new wxFileName(yenidosya);
	wxString gelendosyaisbn = gelendosyaadi->GetName();

	wxRegEx* reISBN = new wxRegEx(wxT("((\\d{9}|\\d{12})[\\d|X])"),1);
	if ( reISBN->Matches(gelendosyaisbn) )
	{
		wxString bulunanisbn = reISBN->GetMatch(gelendosyaisbn);
		EkleKitap eklekitap(wxT("Yeni Kitap Ekle"),bulunanisbn);
		if(eklekitap.ShowModal() == wxID_OK) {
			eklekitap.SaveBook();
			KaynakcaYonetimi::KitaplariYukle(wxT(""));
			eklekitap.Destroy();
			wxString yenidosyayolu;
			yenidosyayolu << appLocation << wxT("files/") << bulunanisbn;
			wxCopyFile(yenidosya,yenidosyayolu);
		}
	}
	else
	{
		BulISBN bulisbn(wxT("ISBN Numarası Bulma Aracı"),yenidosya);
		if(bulisbn.ShowModal() == wxID_OK) {
			EkleKitap eklekitap(wxT("Yeni Kitap Ekle"),bulisbn.GetISBN());
			if(eklekitap.ShowModal() == wxID_OK) {
				eklekitap.SaveBook();
				KaynakcaYonetimi::KitaplariYukle(wxT(""));
				eklekitap.Destroy();
				wxString bulunanisbn = bulisbn.GetISBN();
				wxString yenidosyayolu;
				yenidosyayolu << appLocation << wxT("files/") << bulunanisbn;
				wxCopyFile(yenidosya,yenidosyayolu);
			}
			bulisbn.Destroy();
		}
	}
}
void KaynakcaYonetimi::KitapBirak(wxDropFilesEvent& event)
{
	if(event.GetNumberOfFiles() > 0)
	{
		wxString* gelendosyalar = event.GetFiles();
		wxASSERT(gelendosyalar);

		for(int i=0; i < event.GetNumberOfFiles(); i++)
		{
			if(wxFileExists(gelendosyalar[i]))
			{
				KaynakcaYonetimi::KitapYeniDosya(gelendosyalar[i]);
			}
			else if(wxDirExists(gelendosyalar[i]))
			{
				wxArrayString klasordekidosyalar;
				wxDir::GetAllFiles(gelendosyalar[i],&klasordekidosyalar);
				for(int i=0;klasordekidosyalar.GetCount()-1;i++)
				{
					KaynakcaYonetimi::KitapYeniDosya(klasordekidosyalar.Item(i));
				}
			}
		}
	}
}
/////////////////////////////////////////////////
// Makale ///////////////////////////////////////
/////////////////////////////////////////////////
void KaynakcaYonetimi::DosyaEkleMakaleDialog(wxCommandEvent& event)
{
	wxFileDialog *newfileforpaper = new wxFileDialog(this,wxT("Makale olarak yüklemek istediğiniz dosyayı seçiniz.."),wxT(""),wxT(""),wxT("*.pdf"));
	if(newfileforpaper->ShowModal() == wxID_OK)
	{
		KaynakcaYonetimi::MakaleYeniDosya(newfileforpaper->GetPath());
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
void KaynakcaYonetimi::BulDOIDialog(wxCommandEvent& event)
{
	BulDOI buldoi(wxT("DOI Numarası Bulma Aracı"),wxT(""));
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
void KaynakcaYonetimi::MakaleleriYukle(const wxString& sorter,const wxString& query)
{
	paperlist->DeleteAllItems();
	wxString paperlistsql;
	paperlistsql << wxT("SELECT * FROM papers");
	if(query != wxT(""))
	{
		wxStringTokenizer searchtkz(query,wxT(" "));
		int i = 0;
		while(searchtkz.HasMoreTokens())
		{
			wxString srcquery = searchtkz.GetNextToken();
			if(i==0)
			{
				paperlistsql << wxT(" WHERE (doi LIKE '\%") << srcquery << wxT("\%' OR title LIKE '\%") << srcquery << wxT("\%' OR authors LIKE '\%") << srcquery << wxT("\%' OR journal LIKE '\%") << srcquery << wxT("\%' OR published LIKE '\%") << srcquery << wxT("\%' OR subject LIKE '\%") << srcquery << wxT("\%' OR refid LIKE '\%") << srcquery << wxT("\%')");
			}
			else
			{
				paperlistsql << wxT(" OR (doi LIKE '\%") << srcquery << wxT("\%' OR title LIKE '\%") << srcquery << wxT("\%' OR authors LIKE '\%") << srcquery << wxT("\%' OR journal LIKE '\%") << srcquery << wxT("\%' OR published LIKE '\%") << srcquery << wxT("\%' OR subject LIKE '\%") << srcquery << wxT("\%' OR refid LIKE '\%") << srcquery << wxT("\%')");
			}
			i++;
		}
	}
	if(sorter != wxT("")) paperlistsql << wxT(" ORDER BY ") << sorter << wxT(" DESC ");
	vtcevap paperlistcevap;
	paperlistcevap = Vt(paperlistsql);
	wxImage::AddHandler(new wxPNGHandler);
	wxImageList *paperimagelist = new wxImageList();
	paperimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/0_star.png"),wxBITMAP_TYPE_PNG));
	paperimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/1_star.png"),wxBITMAP_TYPE_PNG));
	paperimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/2_star.png"),wxBITMAP_TYPE_PNG));
	paperimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/3_star.png"),wxBITMAP_TYPE_PNG));
	paperimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/4_star.png"),wxBITMAP_TYPE_PNG));
	paperimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/5_star.png"),wxBITMAP_TYPE_PNG));
	paperimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/0_file.png"),wxBITMAP_TYPE_PNG));
	paperimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/1_file.png"),wxBITMAP_TYPE_PNG));
	paperlist->SetImageList(paperimagelist,wxIMAGE_LIST_SMALL);
	for(int i=0;i<paperlistcevap.satir;i++)
	{
		wxListItem item;
		item.SetId(0);
		if(i%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		int textcolorfromstar;
		textcolorfromstar = 150-wxAtoi(paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+12))*30;
		item.SetTextColour(wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
		paperlist->InsertItem(item);
		paperlist->SetItem(0,0,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+0));
		paperlist->SetItem(0,1,wxT(""));
		paperlist->SetItemColumnImage(item,1,wxAtoi(paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+12)));
		wxString makaledosyadoi = paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+0);
		makaledosyadoi.Replace(wxT("/"),wxT("|"));
		wxString dosyakontrolcommand;
		dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name ") << makaledosyadoi << wxT(".*");
		wxArrayString output;
		wxArrayString errors;
		wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
		if(output.GetCount() > 0)
		{
			if(wxFileExists(output.Item(0)))
			{
				paperlist->SetItem(0,2,wxT(""));
				paperlist->SetItemColumnImage(item,2,7);
			}
			else
			{
				paperlist->SetItem(0,2,wxT(""));
				paperlist->SetItemColumnImage(item,2,6);
			}
		}
		paperlist->SetItem(0,3,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+1));
		paperlist->SetItem(0,4,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+2));
		paperlist->SetItem(0,5,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+3));
		paperlist->SetItem(0,6,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+4));
		paperlist->SetItem(0,7,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+5));
		paperlist->SetItem(0,8,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+6));
		paperlist->SetItem(0,9,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+7));
		paperlist->SetItem(0,10,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+8));
		paperlist->SetItem(0,11,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+9));
		paperlist->SetItem(0,12,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+10));
		paperlist->SetItem(0,13,paperlistcevap.sonuc.Item(i*paperlistcevap.sutun+11));
	}
	if(paperlist->GetItemCount() > 0)
		paperlist->RefreshItems(0,paperlist->GetItemCount()-1);
	middlenb->SetSelection(1);
}
void KaynakcaYonetimi::MakaleSirala(wxListEvent& event) {KaynakcaYonetimi::MakaleleriYukle(paperlistcolumns->Item(event.GetColumn()));}
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
			EkleMakale eklemakale(wxT("Makale Düzenle"),paperlist->GetItemText(item));
			if(eklemakale.ShowModal() == wxID_OK) {
				eklemakale.SavePaper();
				KaynakcaYonetimi::MakaleleriYukle(wxT(""));
				eklemakale.Destroy();
			}
		}
		break;
		case ID_PAPERRCMENU_DELETE:
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Bu makaleyi silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
			if(dial->ShowModal() == wxID_YES) {
				wxArrayString paperremove;
				paperremove.Add(paperlist->GetItemText(item));
				VtEkleSilGuncelle(wxT("DELETE FROM papers WHERE doi==?"),paperremove);
				VtEkleSilGuncelle(wxT("DELETE FROM listrefs WHERE isbndoi==?"),paperremove);
				KaynakcaYonetimi::MakaleleriYukle(wxT(""));
			}
		}
		break;
		case ID_PAPERRCMENU_UPLOAD:
		{
			wxFileDialog *uploadfileforpaper = new wxFileDialog(this,wxT("Bu makale ile ilişkilendirmek için bir dosya seçiniz.."),wxT(""),wxT(""),wxT("*.pdf"));
			if(uploadfileforpaper->ShowModal() == wxID_OK)
			{
				wxString uploadedfileforpaper = uploadfileforpaper->GetPath();
				wxString uploadedfiledoi = paperlist->GetItemText(item);
				uploadedfiledoi.Replace(wxT("/"),wxT("|"));
				wxString uploadedfilepath;
				uploadedfilepath << appLocation << wxT("files/") << uploadedfiledoi;
				wxCopyFile(uploadedfileforpaper,uploadedfilepath);
			}
		}
		break;
		case ID_PAPERRCMENU_WWW:
		{
			wxString wwwpapercommand;
			wwwpapercommand << wxT("xdg-open http://dx.doi.org/") << paperlist->GetItemText(item);
			wxExecute(wwwpapercommand);
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
	makalesagtikmenu.Append(ID_PAPERRCMENU_UPLOAD,wxT("Dosya Yükle"));
	makalesagtikmenu.AppendSeparator();
	makalesagtikmenu.Append(ID_PAPERRCMENU_WWW,wxT("Web'de Görüntüle"));
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
void KaynakcaYonetimi::MakaleCiftTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(paperlist->GetFocusedItem());
	item.SetColumn(0);
	paperlist->GetItem(item);
	wxString makaledosyadoi = paperlist->GetItemText(item);
	makaledosyadoi.Replace(wxT("/"),wxT("|"));
	wxString dosyakontrolcommand;
	dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name ") << makaledosyadoi << wxT(".*");
	wxArrayString output;
	wxArrayString errors;
	wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
	if(output.GetCount() > 0)
	{
		if(wxFileExists(output.Item(0)))
		{
			wxString openfilecommand;
			openfilecommand << wxT("xdg-open '") << output.Item(0) << wxT("'");
			wxExecute(openfilecommand);
		}
		else
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu makale ile ilişkili bir dosya bulunmuyor.\nYeni dosya yüklemek için sağ tıklayın."),wxT("Dosya Bulunamadı"),wxOK);
			dial->ShowModal();
		}
	}
	else
	{
		wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu makale ile ilişkili bir dosya bulunmuyor.\nYeni dosya yüklemek için sağ tıklayın."),wxT("Dosya Bulunamadı"),wxOK);
		dial->ShowModal();
	}
}
void KaynakcaYonetimi::MakaleYeniDosya(const wxString& yenidosya)
{
	wxFileName* gelendosyaadi = new wxFileName(yenidosya);
	wxString gelendosyauzanti = gelendosyaadi->GetExt();
	wxString gelendosyadoi = gelendosyaadi->GetName();
	gelendosyadoi.Replace(wxT("|"),wxT("/"));

	wxRegEx* reDOI = new wxRegEx(wxT("(10[.][0-9]{4,}(?:[.][0-9]+)*/(?:(?![\"&'<>])\\S)+)"),1);
	//wxRegEx* reDOI = new wxRegEx(wxT("\\b(10[.][0-9]{4,}(?:[.][0-9]+)*/(?:(?![\"&'<>])\\S)+)\\b"),1);
	if ( reDOI->Matches(gelendosyadoi) )
	{
		wxString bulunandoi = reDOI->GetMatch(gelendosyadoi);
		EkleMakale eklemakale(wxT("Yeni Makale Ekle"),bulunandoi);
		if(eklemakale.ShowModal() == wxID_OK) {
			eklemakale.SavePaper();
			KaynakcaYonetimi::MakaleleriYukle(wxT(""));
			eklemakale.Destroy();
			bulunandoi.Replace(wxT("/"),wxT("|"));
			wxString yenidosyayolu;
			yenidosyayolu << appLocation << wxT("files/") << bulunandoi << wxT(".") << gelendosyauzanti;
			wxCopyFile(yenidosya,yenidosyayolu);
		}
	}
	else
	{
		wxString opendoicommand;
		opendoicommand << wxT("xdg-open '") << yenidosya << wxT("'");
		//wxExecute(opendoicommand);
		BulDOI buldoi(wxT("DOI Numarası Bulma Aracı"),yenidosya);
		if(buldoi.ShowModal() == wxID_OK) {
			EkleMakale eklemakale(wxT("Yeni Makale Ekle"),buldoi.GetDOI());
			if(eklemakale.ShowModal() == wxID_OK) {
				eklemakale.SavePaper();
				KaynakcaYonetimi::MakaleleriYukle(wxT(""));
				eklemakale.Destroy();
				wxString bulunandoi = buldoi.GetDOI();
				bulunandoi.Replace(wxT("/"),wxT("|"));
				wxString yenidosyayolu;
				yenidosyayolu << appLocation << wxT("files/") << bulunandoi << wxT(".") << gelendosyauzanti;
				wxCopyFile(yenidosya,yenidosyayolu);
			}
			buldoi.Destroy();
		}
	}
}
void KaynakcaYonetimi::MakaleBirak(wxDropFilesEvent& event)
{
	if(event.GetNumberOfFiles() > 0)
	{
		wxString* gelendosyalar = event.GetFiles();
		wxASSERT(gelendosyalar);

		for(int i=0; i < event.GetNumberOfFiles(); i++)
		{
			if(wxFileExists(gelendosyalar[i]))
			{
				KaynakcaYonetimi::MakaleYeniDosya(gelendosyalar[i]);
			}
			else if(wxDirExists(gelendosyalar[i]))
			{
				wxArrayString klasordekidosyalar;
				wxDir::GetAllFiles(gelendosyalar[i],&klasordekidosyalar);
				for(int i=0;klasordekidosyalar.GetCount()-1;i++)
				{
					KaynakcaYonetimi::MakaleYeniDosya(klasordekidosyalar.Item(i));
				}
			}
		}
	}
}
/////////////////////////////////////////////////
// Doküman //////////////////////////////////////
/////////////////////////////////////////////////
void KaynakcaYonetimi::DosyaEkleDokumanDialog(wxCommandEvent& event)
{
	wxFileDialog *newfilefordocument = new wxFileDialog(this,wxT("Yüklemek istediğiniz dosyayı seçiniz.."));
	if(newfilefordocument->ShowModal() == wxID_OK)
	{
		KaynakcaYonetimi::DokumanYeniDosya(newfilefordocument->GetPath());
	}
}
void KaynakcaYonetimi::EkleDokumanDialog(wxCommandEvent& event)
{
	EkleDokuman ekledokuman(wxT("Yeni Doküman Ekle"),wxT(""));
	if(ekledokuman.ShowModal() == wxID_OK) {
		ekledokuman.SaveDocument();
		KaynakcaYonetimi::DokumanlariYukle(wxT(""));
		ekledokuman.Destroy();
	}
}
void KaynakcaYonetimi::DokumanlariYukle(const wxString& sorter,const wxString& query)
{
	documentlist->DeleteAllItems();
	wxString documentlistsql;
	documentlistsql << wxT("SELECT * FROM documents");
	if(query != wxT(""))
	{
		wxStringTokenizer searchtkz(query,wxT(" "));
		int i = 0;
		while(searchtkz.HasMoreTokens())
		{
			wxString srcquery = searchtkz.GetNextToken();
			if(i==0)
			{
				documentlistsql << wxT(" WHERE (name LIKE '\%") << srcquery << wxT("\%' OR desc LIKE '\%") << srcquery << wxT("\%')");
			}
			else
			{
				documentlistsql << wxT(" OR (name LIKE '\%") << srcquery << wxT("\%' OR desc LIKE '\%") << srcquery << wxT("\%')");
			}
			i++;
		}
	}
	if(sorter != wxT("")) documentlistsql << wxT(" ORDER BY ") << sorter << wxT(" DESC ");
	vtcevap documentlistcevap;
	documentlistcevap = Vt(documentlistsql);
	wxImage::AddHandler(new wxPNGHandler);
	wxImageList *documentimagelist = new wxImageList();
	documentimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/0_star.png"),wxBITMAP_TYPE_PNG));
	documentimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/1_star.png"),wxBITMAP_TYPE_PNG));
	documentimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/2_star.png"),wxBITMAP_TYPE_PNG));
	documentimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/3_star.png"),wxBITMAP_TYPE_PNG));
	documentimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/4_star.png"),wxBITMAP_TYPE_PNG));
	documentimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/5_star.png"),wxBITMAP_TYPE_PNG));
	documentimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/0_file.png"),wxBITMAP_TYPE_PNG));
	documentimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/1_file.png"),wxBITMAP_TYPE_PNG));
	documentlist->SetImageList(documentimagelist,wxIMAGE_LIST_SMALL);
	for(int i=0;i<documentlistcevap.satir;i++)
	{
		wxListItem item;
		item.SetId(0);
		if(i%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		int textcolorfromstar;
		textcolorfromstar = 150-wxAtoi(documentlistcevap.sonuc.Item(i*documentlistcevap.sutun+3))*30;
		item.SetTextColour(wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
		documentlist->InsertItem(item);
		documentlist->SetItem(0,0,documentlistcevap.sonuc.Item(i*documentlistcevap.sutun+0));
		documentlist->SetItem(0,1,wxT(""));
		documentlist->SetItemColumnImage(item,1,wxAtoi(documentlistcevap.sonuc.Item(i*documentlistcevap.sutun+3)));
		wxString dosyakontrolcommand;
		dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name doc.") << documentlistcevap.sonuc.Item(i*documentlistcevap.sutun+0) << wxT(".*");
		wxArrayString output;
		wxArrayString errors;
		wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
		if(output.GetCount() > 0)
		{
			if(wxFileExists(output.Item(0)))
			{
				documentlist->SetItem(0,2,wxT(""));
				documentlist->SetItemColumnImage(item,2,7);
			}
			else
			{
				documentlist->SetItem(0,2,wxT(""));
				documentlist->SetItemColumnImage(item,2,6);
			}
		}
		documentlist->SetItem(0,3,documentlistcevap.sonuc.Item(i*documentlistcevap.sutun+1));
		documentlist->SetItem(0,4,documentlistcevap.sonuc.Item(i*documentlistcevap.sutun+2));
	}
	if(documentlist->GetItemCount() > 0)
		documentlist->RefreshItems(0,documentlist->GetItemCount()-1);
	middlenb->SetSelection(2);
}
void KaynakcaYonetimi::DokumanSirala(wxListEvent& event) { KaynakcaYonetimi::DokumanlariYukle(documentlistcolumns->Item(event.GetColumn())); }
void KaynakcaYonetimi::DokumanSagTikTik(wxCommandEvent &event)
{
	void *data=static_cast<wxMenu *>(event.GetEventObject())->GetClientData();
	wxListItem item;
	item.SetId(documentlist->GetFocusedItem());
	item.SetColumn(0);
	documentlist->GetItem(item);
	switch(event.GetId())
	{
		case ID_DOCUMENTRCMENU_EDIT:
		{
			EkleDokuman ekledokuman(wxT("Doküman Düzenle"),documentlist->GetItemText(item));
			if(ekledokuman.ShowModal() == wxID_OK) {
				ekledokuman.UpdateDocument(documentlist->GetItemText(item));
				KaynakcaYonetimi::DokumanlariYukle(wxT(""));
				ekledokuman.Destroy();
			}
		}
		break;
		case ID_DOCUMENTRCMENU_DELETE:
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Bu dokümanı silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
			if(dial->ShowModal() == wxID_YES) {
				wxArrayString documentremove;
				documentremove.Add(documentlist->GetItemText(item));
				VtEkleSilGuncelle(wxT("DELETE FROM documents WHERE id==?"),documentremove);
				KaynakcaYonetimi::DokumanlariYukle(wxT(""));
			}
		}
		break;
		case ID_DOCUMENTRCMENU_UPLOAD:
		{
			wxFileDialog *uploadfilefordocument = new wxFileDialog(this,wxT("Bir dosya seçiniz.."));
			if(uploadfilefordocument->ShowModal() == wxID_OK)
			{
				wxString uploadedfilefordocument = uploadfilefordocument->GetPath();
				wxFileName* uploadedfilename = new wxFileName(uploadedfilefordocument);
				wxString uploadedfileext = uploadedfilename->GetExt();
				wxString uploadedfileid = documentlist->GetItemText(item);
				wxString uploadedfilepath;
				uploadedfilepath << appLocation << wxT("files/doc.") << uploadedfileid << wxT(".") << uploadedfileext;
				wxCopyFile(uploadedfilefordocument,uploadedfilepath);
			}
		}
		break;
		default:
		{
			wxArrayString starupdate;
			wxString starstring;
			starstring << event.GetId()-7190;
			starupdate.Add(starstring);
			starupdate.Add(documentlist->GetItemText(item));
			VtEkleSilGuncelle(wxT("UPDATE documents SET star=? WHERE id=?"),starupdate);
			int textcolorfromstar;
			textcolorfromstar = 150-wxAtoi(starstring)*30;
			documentlist->SetItemColumnImage(item,1,wxAtoi(starstring));
			//filelist->SetItem(booklist->GetFocusedItem(),1,starstring);
			documentlist->SetItemTextColour(item,wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
		}
		break;
	}
}
void KaynakcaYonetimi::DokumanSagTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(documentlist->GetFocusedItem());
	item.SetColumn(0);
	documentlist->GetItem(item);
	
	wxString dokumansagtiksql;
	dokumansagtiksql << wxT("SELECT * FROM documents WHERE id == '") << documentlist->GetItemText(item) << wxT("';");
	vtcevap dokumansagtikcevap;
	dokumansagtikcevap = Vt(dokumansagtiksql);
	int dokumansagtikstarid = 7190 + wxAtoi(dokumansagtikcevap.sonuc.Item(3));
	wxMenu dokumansagtikmenu;
	dokumansagtikmenu.SetClientData(data);
	dokumansagtikmenu.Append(ID_DOCUMENTRCMENU_EDIT,wxT("Düzenle"));
	dokumansagtikmenu.Append(ID_DOCUMENTRCMENU_DELETE,wxT("Sil"));
	dokumansagtikmenu.AppendSeparator();
	dokumansagtikmenu.Append(ID_DOCUMENTRCMENU_UPLOAD,wxT("Dosya Yükle"));
	dokumansagtikmenu.AppendSeparator();
	wxMenu *dokumansagtiksubmenu2 = new wxMenu;
	dokumansagtiksubmenu2->AppendCheckItem(7190,wxT("0"));
	dokumansagtiksubmenu2->AppendCheckItem(7191,wxT("1"));
	dokumansagtiksubmenu2->AppendCheckItem(7192,wxT("2"));
	dokumansagtiksubmenu2->AppendCheckItem(7193,wxT("3"));
	dokumansagtiksubmenu2->AppendCheckItem(7194,wxT("4"));
	dokumansagtiksubmenu2->AppendCheckItem(7195,wxT("5"));
	dokumansagtiksubmenu2->Check(dokumansagtikstarid,TRUE);
	dokumansagtikmenu.Append(-1,wxT("Beğeni"), dokumansagtiksubmenu2);
	dokumansagtikmenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::DokumanSagTikTik, NULL, this);
	PopupMenu(&dokumansagtikmenu);
}
void KaynakcaYonetimi::DokumanCiftTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(documentlist->GetFocusedItem());
	item.SetColumn(0);
	documentlist->GetItem(item);
	wxString dokumandosyaid = documentlist->GetItemText(item);
	wxString dosyakontrolcommand;
	dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name doc.") << dokumandosyaid << wxT(".*");
	wxArrayString output;
	wxArrayString errors;
	wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
	if(output.GetCount() > 0)
	{
		if(wxFileExists(output.Item(0)))
		{
			wxString openfilecommand;
			openfilecommand << wxT("xdg-open '") << output.Item(0) << wxT("'");
			wxExecute(openfilecommand);
		}
		else
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu öğe ile ilişkili bir dosya bulunmuyor.\nYeni dosya yüklemek için sağ tıklayın."),wxT("Dosya Bulunamadı"),wxOK);
			dial->ShowModal();
		}
	}
	else
	{
		wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu öğe ile ilişkili bir dosya bulunmuyor.\nYeni dosya yüklemek için sağ tıklayın."),wxT("Dosya Bulunamadı"),wxOK);
		dial->ShowModal();
	}
}
void KaynakcaYonetimi::DokumanYeniDosya(const wxString& yenidosya)
{
	wxFileName* gelendosyaadi = new wxFileName(yenidosya);
	wxString gelendosyauzanti = gelendosyaadi->GetExt();
	EkleDokuman ekledokuman(wxT("Yeni Dosya Ekle"),wxT(""));
	if(ekledokuman.ShowModal() == wxID_OK) {
		ekledokuman.SaveDocument();
		KaynakcaYonetimi::DokumanlariYukle(wxT(""));
		wxString eklenenid = ekledokuman.GetID();
		wxString yenidosyayolu;
		yenidosyayolu << appLocation << wxT("files/doc.") << eklenenid << wxT(".") << gelendosyauzanti;
		wxCopyFile(yenidosya,yenidosyayolu);
		ekledokuman.Destroy();
	}
}
void KaynakcaYonetimi::DokumanBirak(wxDropFilesEvent& event)
{
	if(event.GetNumberOfFiles() > 0)
	{
		wxString* gelendosyalar = event.GetFiles();
		wxASSERT(gelendosyalar);

		for(int i=0; i < event.GetNumberOfFiles(); i++)
		{
			if(wxFileExists(gelendosyalar[i]))
			{
				KaynakcaYonetimi::DokumanYeniDosya(gelendosyalar[i]);
			}
			else if(wxDirExists(gelendosyalar[i]))
			{
				wxArrayString klasordekidosyalar;
				wxDir::GetAllFiles(gelendosyalar[i],&klasordekidosyalar);
				for(int i=0;klasordekidosyalar.GetCount()-1;i++)
				{
					KaynakcaYonetimi::DokumanYeniDosya(klasordekidosyalar.Item(i));
				}
			}
		}
	}
}
/////////////////////////////////////////////////
// Dosya ////////////////////////////////////////
/////////////////////////////////////////////////
void KaynakcaYonetimi::DosyaEkleDosyaDialog(wxCommandEvent& event)
{
	wxFileDialog *newfileforfile = new wxFileDialog(this,wxT("Yüklemek istediğiniz dosyayı seçiniz.."));
	if(newfileforfile->ShowModal() == wxID_OK)
	{
		KaynakcaYonetimi::DosyaYeniDosya(newfileforfile->GetPath());
	}
}
void KaynakcaYonetimi::EkleDosyaDialog(wxCommandEvent& event)
{
	EkleDosya ekledosya(wxT("Yeni Dosya Ekle"),wxT(""));
	if(ekledosya.ShowModal() == wxID_OK) {
		ekledosya.SaveFile();
		KaynakcaYonetimi::DosyalariYukle(wxT(""));
		ekledosya.Destroy();
	}
}
void KaynakcaYonetimi::DosyalariYukle(const wxString& sorter,const wxString& query)
{
	filelist->DeleteAllItems();
	wxString filelistsql;
	filelistsql << wxT("SELECT * FROM files");
	if(query != wxT(""))
	{
		wxStringTokenizer searchtkz(query,wxT(" "));
		int i = 0;
		while(searchtkz.HasMoreTokens())
		{
			wxString srcquery = searchtkz.GetNextToken();
			if(i==0)
			{
				filelistsql << wxT(" WHERE (name LIKE '\%") << srcquery << wxT("\%' OR desc LIKE '\%") << srcquery << wxT("\%')");
			}
			else
			{
				filelistsql << wxT(" OR (name LIKE '\%") << srcquery << wxT("\%' OR desc LIKE '\%") << srcquery << wxT("\%')");
			}
			i++;
		}
	}
	if(sorter != wxT("")) filelistsql << wxT(" ORDER BY ") << sorter << wxT(" DESC ");
	vtcevap filelistcevap;
	filelistcevap = Vt(filelistsql);
	wxImage::AddHandler(new wxPNGHandler);
	wxImageList *fileimagelist = new wxImageList();
	fileimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/0_star.png"),wxBITMAP_TYPE_PNG));
	fileimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/1_star.png"),wxBITMAP_TYPE_PNG));
	fileimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/2_star.png"),wxBITMAP_TYPE_PNG));
	fileimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/3_star.png"),wxBITMAP_TYPE_PNG));
	fileimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/4_star.png"),wxBITMAP_TYPE_PNG));
	fileimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/5_star.png"),wxBITMAP_TYPE_PNG));
	fileimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/0_file.png"),wxBITMAP_TYPE_PNG));
	fileimagelist->Add(wxBitmap(appLocation+wxT("resource/toolbar/1_file.png"),wxBITMAP_TYPE_PNG));
	filelist->SetImageList(fileimagelist,wxIMAGE_LIST_SMALL);
	for(int i=0;i<filelistcevap.satir;i++)
	{
		wxListItem item;
		item.SetId(0);
		if(i%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		int textcolorfromstar;
		textcolorfromstar = 150-wxAtoi(filelistcevap.sonuc.Item(i*filelistcevap.sutun+3))*30;
		item.SetTextColour(wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
		filelist->InsertItem(item);
		filelist->SetItem(0,0,filelistcevap.sonuc.Item(i*filelistcevap.sutun+0));
		filelist->SetItem(0,1,wxT(""));
		filelist->SetItemColumnImage(item,1,wxAtoi(filelistcevap.sonuc.Item(i*filelistcevap.sutun+3)));
		wxString dosyakontrolcommand;
		dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name file.") << filelistcevap.sonuc.Item(i*filelistcevap.sutun+0) << wxT(".*");
		wxArrayString output;
		wxArrayString errors;
		wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
		if(output.GetCount() > 0)
		{
			if(wxFileExists(output.Item(0)))
			{
				filelist->SetItem(0,2,wxT(""));
				filelist->SetItemColumnImage(item,2,7);
			}
			else
			{
				filelist->SetItem(0,2,wxT(""));
				filelist->SetItemColumnImage(item,2,6);
			}
		}
		filelist->SetItem(0,3,filelistcevap.sonuc.Item(i*filelistcevap.sutun+1));
		filelist->SetItem(0,4,filelistcevap.sonuc.Item(i*filelistcevap.sutun+2));
	}
	if(filelist->GetItemCount() > 0)
		filelist->RefreshItems(0,filelist->GetItemCount()-1);
	middlenb->SetSelection(3);
}
void KaynakcaYonetimi::DosyaSirala(wxListEvent& event) { KaynakcaYonetimi::DosyalariYukle(filelistcolumns->Item(event.GetColumn())); }
void KaynakcaYonetimi::DosyaSagTikTik(wxCommandEvent &event)
{
	void *data=static_cast<wxMenu *>(event.GetEventObject())->GetClientData();
	wxListItem item;
	item.SetId(filelist->GetFocusedItem());
	item.SetColumn(0);
	filelist->GetItem(item);
	switch(event.GetId())
	{
		case ID_FILERCMENU_EDIT:
		{
			EkleDosya ekledosya(wxT("Dosya Düzenle"),filelist->GetItemText(item));
			if(ekledosya.ShowModal() == wxID_OK) {
				ekledosya.UpdateFile(filelist->GetItemText(item));
				KaynakcaYonetimi::DosyalariYukle(wxT(""));
				ekledosya.Destroy();
			}
		}
		break;
		case ID_FILERCMENU_DELETE:
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Bu dosyayı silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
			if(dial->ShowModal() == wxID_YES) {
				wxArrayString fileremove;
				fileremove.Add(filelist->GetItemText(item));
				VtEkleSilGuncelle(wxT("DELETE FROM files WHERE id==?"),fileremove);
				KaynakcaYonetimi::DosyalariYukle(wxT(""));
			}
		}
		break;
		case ID_FILERCMENU_UPLOAD:
		{
			wxFileDialog *uploadfileforfile = new wxFileDialog(this,wxT("Bir dosya seçiniz.."));
			if(uploadfileforfile->ShowModal() == wxID_OK)
			{
				wxString uploadedfileforfile = uploadfileforfile->GetPath();
				wxFileName* uploadedfilename = new wxFileName(uploadedfileforfile);
				wxString uploadedfileext = uploadedfilename->GetExt();
				wxString uploadedfileid = filelist->GetItemText(item);
				wxString uploadedfilepath;
				uploadedfilepath << appLocation << wxT("files/") << uploadedfileid << wxT(".") << uploadedfileext;
				wxCopyFile(uploadedfileforfile,uploadedfilepath);
			}
		}
		break;
		default:
		{
			wxArrayString starupdate;
			wxString starstring;
			starstring << event.GetId()-7190;
			starupdate.Add(starstring);
			starupdate.Add(filelist->GetItemText(item));
			VtEkleSilGuncelle(wxT("UPDATE files SET star=? WHERE id=?"),starupdate);
			int textcolorfromstar;
			textcolorfromstar = 150-wxAtoi(starstring)*30;
			filelist->SetItemColumnImage(item,1,wxAtoi(starstring));
			//filelist->SetItem(booklist->GetFocusedItem(),1,starstring);
			filelist->SetItemTextColour(item,wxColour(textcolorfromstar,textcolorfromstar,textcolorfromstar));
		}
		break;
	}
}
void KaynakcaYonetimi::DosyaSagTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(filelist->GetFocusedItem());
	item.SetColumn(0);
	filelist->GetItem(item);
	
	wxString dosyasagtiksql;
	dosyasagtiksql << wxT("SELECT * FROM files WHERE id == '") << filelist->GetItemText(item) << wxT("';");
	vtcevap dosyasagtikcevap;
	dosyasagtikcevap = Vt(dosyasagtiksql);
	int dosyasagtikstarid = 7190 + wxAtoi(dosyasagtikcevap.sonuc.Item(3));
	wxMenu dosyasagtikmenu;
	dosyasagtikmenu.SetClientData(data);
	dosyasagtikmenu.Append(ID_FILERCMENU_EDIT,wxT("Düzenle"));
	dosyasagtikmenu.Append(ID_FILERCMENU_DELETE,wxT("Sil"));
	dosyasagtikmenu.AppendSeparator();
	dosyasagtikmenu.Append(ID_FILERCMENU_UPLOAD,wxT("Dosya Yükle"));
	dosyasagtikmenu.AppendSeparator();
	wxMenu *dosyasagtiksubmenu2 = new wxMenu;
	dosyasagtiksubmenu2->AppendCheckItem(7190,wxT("0"));
	dosyasagtiksubmenu2->AppendCheckItem(7191,wxT("1"));
	dosyasagtiksubmenu2->AppendCheckItem(7192,wxT("2"));
	dosyasagtiksubmenu2->AppendCheckItem(7193,wxT("3"));
	dosyasagtiksubmenu2->AppendCheckItem(7194,wxT("4"));
	dosyasagtiksubmenu2->AppendCheckItem(7195,wxT("5"));
	dosyasagtiksubmenu2->Check(dosyasagtikstarid,TRUE);
	dosyasagtikmenu.Append(-1,wxT("Beğeni"), dosyasagtiksubmenu2);
	dosyasagtikmenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&KaynakcaYonetimi::DosyaSagTikTik, NULL, this);
	PopupMenu(&dosyasagtikmenu);
}
void KaynakcaYonetimi::DosyaCiftTik(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(filelist->GetFocusedItem());
	item.SetColumn(0);
	filelist->GetItem(item);
	wxString dosyadosyaid = filelist->GetItemText(item);
	wxString dosyakontrolcommand;
	dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name file.") << dosyadosyaid << wxT(".*");
	wxArrayString output;
	wxArrayString errors;
	wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
	if(output.GetCount() > 0)
	{
		if(wxFileExists(output.Item(0)))
		{
			wxString openfilecommand;
			openfilecommand << wxT("xdg-open '") << output.Item(0) << wxT("'");
			wxExecute(openfilecommand);
		}
		else
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu öğe ile ilişkili bir dosya bulunmuyor.\nYeni dosya yüklemek için sağ tıklayın."),wxT("Dosya Bulunamadı"),wxOK);
			dial->ShowModal();
		}
	}
	else
	{
		wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu öğe ile ilişkili bir dosya bulunmuyor.\nYeni dosya yüklemek için sağ tıklayın."),wxT("Dosya Bulunamadı"),wxOK);
		dial->ShowModal();
	}
}
void KaynakcaYonetimi::DosyaYeniDosya(const wxString& yenidosya)
{
	wxFileName* gelendosyaadi = new wxFileName(yenidosya);
	wxString gelendosyauzanti = gelendosyaadi->GetExt();
	EkleDosya ekledosya(wxT("Yeni Dosya Ekle"),wxT(""));
	if(ekledosya.ShowModal() == wxID_OK) {
		ekledosya.SaveFile();
		KaynakcaYonetimi::DosyalariYukle(wxT(""));
		wxString eklenenid = ekledosya.GetID();
		wxString yenidosyayolu;
		yenidosyayolu << appLocation << wxT("files/file.") << eklenenid << wxT(".") << gelendosyauzanti;
		wxCopyFile(yenidosya,yenidosyayolu);
		ekledosya.Destroy();
	}
}
void KaynakcaYonetimi::DosyaBirak(wxDropFilesEvent& event)
{
	if(event.GetNumberOfFiles() > 0)
	{
		wxString* gelendosyalar = event.GetFiles();
		wxASSERT(gelendosyalar);

		for(int i=0; i < event.GetNumberOfFiles(); i++)
		{
			if(wxFileExists(gelendosyalar[i]))
			{
				KaynakcaYonetimi::DosyaYeniDosya(gelendosyalar[i]);
			}
			else if(wxDirExists(gelendosyalar[i]))
			{
				wxArrayString klasordekidosyalar;
				wxDir::GetAllFiles(gelendosyalar[i],&klasordekidosyalar);
				for(int i=0;klasordekidosyalar.GetCount()-1;i++)
				{
					KaynakcaYonetimi::DosyaYeniDosya(klasordekidosyalar.Item(i));
				}
			}
		}
	}
}
/////////////////////////////////////////////////
// Liste ////////////////////////////////////////
/////////////////////////////////////////////////
void KaynakcaYonetimi::EkleListeDialog(wxCommandEvent& event)
{
	EkleListe ekleliste(wxT("Yeni Liste Ekle"),wxT(""));
	if(ekleliste.ShowModal() == wxID_OK) {
		ekleliste.SaveList();
		KaynakcaYonetimi::ListeleriYukle(wxT(""));
		ekleliste.Destroy();
	}
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
void KaynakcaYonetimi::ListeSirala(wxListEvent& event) {KaynakcaYonetimi::ListeleriYukle(listlistcolumns->Item(event.GetColumn()));}
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
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Bu listeyi silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
			if(dial->ShowModal() == wxID_YES) {
				wxArrayString listremove;
				listremove.Add(listlist->GetItemText(item));
				VtEkleSilGuncelle(wxT("DELETE FROM lists WHERE id==?"),listremove);
				VtEkleSilGuncelle(wxT("DELETE FROM listrefs WHERE listid==?"),listremove);
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
/////////////////////////////////////////////////
// Ajanda ///////////////////////////////////////
/////////////////////////////////////////////////
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
void KaynakcaYonetimi::AjandayiYenile(wxCommandEvent& event) {KaynakcaYonetimi::AjandayiYukle();}
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
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Bu ajanda notunu silmek istediğinize emin misiniz?"),wxT("Onay"),wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION);
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
/////////////////////////////////////////////////
// Arama ////////////////////////////////////////
/////////////////////////////////////////////////
void KaynakcaYonetimi::AramaKutusuDialog(wxCommandEvent& event)
{
	AramaKutusu aramakutusu(wxT("Arama Yap"));
	if(aramakutusu.ShowModal() == wxID_OK) {
		wxString squery = aramakutusu.GetQuery();
		wxString stype = aramakutusu.GetType();
		if(stype == wxT("Kitap Ara")) KaynakcaYonetimi::KitaplariYukle(wxT(""),squery);
		if(stype == wxT("Makale Ara")) KaynakcaYonetimi::MakaleleriYukle(wxT(""),squery);
		if(stype == wxT("Doküman Ara")) KaynakcaYonetimi::DokumanlariYukle(wxT(""),squery);
		if(stype == wxT("Dosya Ara")) KaynakcaYonetimi::DosyalariYukle(wxT(""),squery);
		aramakutusu.Destroy();
	}
}
