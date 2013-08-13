#include "wxlibs.h"

class BulISBN : public wxDialog
{
public:
	BulISBN(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void FindISBNRetrieve(wxCommandEvent& event);
	wxString GetISBN();
	
	wxTextCtrl *srcauthor;
	wxTextCtrl *srctitle;
	wxHtmlWindow *findisbnresults;
	wxChoice *isbnnumber;
};

const int FINDISBN_DIALOG_RETRIEVE = 4201;
