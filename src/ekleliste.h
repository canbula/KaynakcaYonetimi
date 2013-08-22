#include "wxlibs.h"

class EkleListe : public wxDialog
{
public:
	EkleListe(const wxString& title,const wxString& id);

	void OnQuit(wxCommandEvent& event);
	void SetStyleFromHelper(wxCommandEvent& event);
	void PrepareUpdate(const wxString& id);
	void UpdateList(const wxString& id);
	void SaveList();
	
	wxTextCtrl *listname;
	wxTextCtrl *listdesc;
	wxTextCtrl *liststyle;
	wxChoice *liststylehelper;
};
