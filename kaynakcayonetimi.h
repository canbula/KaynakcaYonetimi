#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/artprov.h>
#include <wx/toolbar.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/statbmp.h>
#include <wx/textctrl.h>
#include <wx/string.h>
#include <wx/dialog.h>
#include <wx/aboutdlg.h>

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
