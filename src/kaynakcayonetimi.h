#include "wxlibs.h"

class KaynakcaYonetimi : public wxFrame
{
public:
	KaynakcaYonetimi(const wxString& title);
	
	void EkleKitapDialog(wxCommandEvent& event);
	void EkleMakaleDialog(wxCommandEvent& event);
	void BulDOIDialog(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	
	wxMenuBar *menubar;
	wxMenu *file;
	wxMenu *add;
	wxMenu *tool;
	wxStatusBar *statusbar;
};

const int ID_ADDMENU_BOOK = 502;
const int ID_ADDMENU_ARTICLE = 503;
const int ID_ADDMENU_DOCUMENT = 504;
const int ID_ADDMENU_FILE = 505;
const int ID_ADDMENU_LIST = 506;

const int ID_TOOLBAR_LIBRARY = 701;
const int ID_TOOLBAR_BOOK = 702;
const int ID_TOOLBAR_ARTICLE = 703;
const int ID_TOOLBAR_DOCUMENT = 704;
const int ID_TOOLBAR_FILE = 705;
const int ID_TOOLBAR_LIST = 706;

const int ID_TOOLMENU_FINDDOI = 801;
