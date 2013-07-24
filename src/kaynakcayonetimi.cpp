#include "kaynakcayonetimi.h"
#include "eklekitap.h"

KaynakcaYonetimi::KaynakcaYonetimi(const wxString& title)
	: wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(800,600))
{
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap toolbarLibrary(appLocation+wxT("resource/toolbar/Library.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarBook(appLocation+wxT("resource/toolbar/Book.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarArticle(appLocation+wxT("resource/toolbar/Article.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarDocument(appLocation+wxT("resource/toolbar/Document.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarFile(appLocation+wxT("resource/toolbar/File.png"),wxBITMAP_TYPE_PNG);
	wxBitmap toolbarList(appLocation+wxT("resource/toolbar/List.png"),wxBITMAP_TYPE_PNG);
	
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
	SetMenuBar(menubar);
	
	wxToolBar *toolbar = CreateToolBar();
	toolbar->AddTool(ID_TOOLBAR_LIBRARY,wxT("Kaynaklar"),toolbarLibrary);
	toolbar->AddTool(ID_TOOLBAR_BOOK,wxT("Kitap"),toolbarBook);
	toolbar->AddTool(ID_TOOLBAR_ARTICLE,wxT("Makale"),toolbarArticle);
	toolbar->AddTool(ID_TOOLBAR_DOCUMENT,wxT("Doküman"),toolbarDocument);
	toolbar->AddTool(ID_TOOLBAR_FILE,wxT("Dosya"),toolbarFile);
	toolbar->AddTool(ID_TOOLBAR_LIST,wxT("Liste"),toolbarList);
	toolbar->Realize();
	
	statusbar = new wxStatusBar(this,wxID_ANY,wxST_SIZEGRIP);
	this->SetStatusBar(statusbar);
	statusbar->SetStatusText(wxT("Kaynakça Yönetimi - Pardus Yazılım Kampı 2013"));
	
	Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::OnQuit));
	Connect(ID_TOOLBAR_BOOK,wxEVT_COMMAND_TOOL_CLICKED,wxCommandEventHandler(KaynakcaYonetimi::EkleKitapDialog));
	Connect(ID_ADDMENU_BOOK,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::EkleKitapDialog));
	
	SetIcon(wxIcon(appLocation+wxT("resource/icons/kaynakcayonetimi.xpm")));
	Centre();
}

void KaynakcaYonetimi::EkleKitapDialog(wxCommandEvent& event)
{
	EkleKitap eklekitap(wxT("Yeni Kitap Ekle"));
	if(eklekitap.ShowModal() == wxID_OK) {
		eklekitap.Destroy();
	}
}

void KaynakcaYonetimi::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}
