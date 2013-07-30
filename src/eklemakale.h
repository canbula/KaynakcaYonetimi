#include "wxlibs.h"

class EkleMakale : public wxDialog
{
public:
	EkleMakale(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void DOIRetrieve(wxCommandEvent& event);
	void SavePaper();
	
	wxTextCtrl *paperdoi;
	wxTextCtrl *papertitle;
	wxTextCtrl *paperauthors;
	wxTextCtrl *paperjournal;
	wxTextCtrl *papervolume;
	wxTextCtrl *paperissue;
	wxTextCtrl *paperfirstpage;
	wxTextCtrl *paperlastpage;
	wxTextCtrl *paperpublished;
	wxTextCtrl *paperlink;
	wxTextCtrl *papersubject;
};

const int ADDPAPER_DIALOG_RETRIEVE = 2201;
