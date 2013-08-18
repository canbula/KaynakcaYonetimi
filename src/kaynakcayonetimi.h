#include "wxlibs.h"

class KaynakcaYonetimi : public wxFrame
{
public:
	KaynakcaYonetimi(const wxString& title);
	
	enum
	{
		ID_TOOLBAR_ADDBOOK = wxID_HIGHEST + 1,
		ID_TOOLBAR_ADDARTICLE,
		ID_TOOLBAR_ADDDOCUMENT,
		ID_TOOLBAR_ADDFILE,
		ID_TOOLBAR_ADDLIST,
		ID_TOOLBAR_FINDISBN,
		ID_TOOLBAR_FINDDOI,
		ID_TOOLBAR_HELP,
		ID_TOOLBAR_ABOUT
	};
	
	void EkleKitapDialog(wxCommandEvent& event);
	void EkleMakaleDialog(wxCommandEvent& event);
	void BulDOIDialog(wxCommandEvent& event);
	void BulISBNDialog(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};
