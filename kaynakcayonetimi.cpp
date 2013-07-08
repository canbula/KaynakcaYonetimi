#include "kaynakcayonetimi.h"

KaynakcaYonetimi::KaynakcaYonetimi(const wxString& title)
	: wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(800,600))
{
	menubar = new wxMenuBar;
	file = new wxMenu;
	file->Append(wxID_EXIT,wxT("&Kapat"));
	menubar->Append(file,wxT("&Dosya"));
	SetMenuBar(menubar);
	
	statusbar = new wxStatusBar(this,wxID_ANY,wxST_SIZEGRIP);
	this->SetStatusBar(statusbar);
	statusbar->SetStatusText(wxT("Kaynakça Yönetimi - Pardus Yazılım Kampı 2013"));
	
	Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(KaynakcaYonetimi::OnQuit));
	
	SetIcon(wxIcon(wxT("kaynakcayonetimi.xpm")));
	Centre();
}

void KaynakcaYonetimi::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}
