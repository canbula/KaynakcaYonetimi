#include "wxlibs.h"

class KaynakcaYonetimi : public wxFrame
{
public:
	KaynakcaYonetimi(const wxString& title);
	
	void OnQuit(wxCommandEvent& event);
	
	wxMenuBar *menubar;
	wxMenu *file;
	wxStatusBar *statusbar;
};

const int ID_TOOLBAR_LIBRARY = 701;
const int ID_TOOLBAR_BOOK = 702;
const int ID_TOOLBAR_ARTICLE = 703;
const int ID_TOOLBAR_DOCUMENT = 704;
const int ID_TOOLBAR_FILE = 705;
const int ID_TOOLBAR_LIST = 706;
