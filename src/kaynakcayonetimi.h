#include "wxlibs.h"

class KaynakcaYonetimi : public wxFrame
{
public:
	KaynakcaYonetimi(const wxString& title);
	
	void EkleKitapDialog(wxCommandEvent& event);
	void EkleMakaleDialog(wxCommandEvent& event);
	void BulDOIDialog(wxCommandEvent& event);
	void BulISBNDialog(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	
	//wxMenuBar *menubar;
	//wxMenu *file;
	//wxMenu *add;
	//wxMenu *tool;
	//wxMenu *help;
	//wxStatusBar *statusbar;
};

/*
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

const int ID_TOOLMENU_FINDISBN = 801;
const int ID_TOOLMENU_FINDDOI = 802;

const int ID_HELPMENU_ABOUT = 901;
*/

const int ID_TOOLBAR_ADDBOOK = 501;
const int ID_TOOLBAR_ADDARTICLE = 502;
const int ID_TOOLBAR_ADDDOCUMENT = 503;
const int ID_TOOLBAR_ADDFILE = 504;
const int ID_TOOLBAR_ADDLIST = 505;
const int ID_TOOLBAR_FINDISBN = 506;
const int ID_TOOLBAR_FINDDOI = 507;
const int ID_TOOLBAR_HELP = 508;
const int ID_TOOLBAR_ABOUT = 509;
