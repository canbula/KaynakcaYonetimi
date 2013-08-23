#include "wxlibs.h"

class EkleAjanda : public wxDialog
{
public:
	EkleAjanda(const wxString& title,const wxString& id,const wxString& date);

	void OnQuit(wxCommandEvent& event);
	void PrepareUpdate(const wxString& id);
	void UpdateTodo(const wxString& id);
	void SaveTodo();
	
	wxTextCtrl *tododate;
	wxTextCtrl *todotitle;
	wxTextCtrl *tododetails;
};
