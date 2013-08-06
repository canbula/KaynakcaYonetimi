#include "wxlibs.h"

class BulDOI : public wxDialog
{
public:
	BulDOI(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void FindDOIRetrieve(wxCommandEvent& event);
	wxString GetDOI();
	
	wxTextCtrl *srcauthor;
	wxTextCtrl *srctitle;
	wxHtmlWindow *finddoiresults;
	wxChoice *doinumber;
};

const int FINDDOI_DIALOG_RETRIEVE = 3201;
