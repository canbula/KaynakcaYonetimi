#include "wxlibs.h"

class EkleMakale : public wxDialog
{
public:
	EkleMakale(const wxString& title,const wxString& doi);
	void OnQuit(wxCommandEvent& event);
	void DOIRetrieveTrigger(wxCommandEvent& event);
	void DOIRetrieve();
	void SavePaper();
	wxString GetNewPaperDOI();
	
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
	wxTextCtrl *paperrefid;
	wxChoice *paperstar;
};

const int ADDPAPER_DIALOG_RETRIEVE = 2201;
