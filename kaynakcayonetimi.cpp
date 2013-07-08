#include "kaynakcayonetimi.h"

KaynakcaYonetimi::KaynakcaYonetimi(const wxString& title)
	: wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(800,600))
{
	SetIcon(wxIcon(wxT("kaynakcayonetimi.xpm")));
	Centre();
}
