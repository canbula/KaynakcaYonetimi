#include "wxlibs.h"

class GosterListe : public wxDialog
{
public:
	GosterListe(const wxString& title,wxString id);

	enum
	{
		ID_SHOWLIST_UP = wxID_HIGHEST + 1,
		ID_SHOWLIST_DOWN,
		ID_SHOWLIST_SORT,
		ID_SHOWLIST_REMOVE
	};

	void UsteCikar(wxCommandEvent& event);
	void AltaIndir(wxCommandEvent& event);
	void OtoSirala(wxCommandEvent& event);
	void RefKaldir(wxCommandEvent& event);
	void SayfayiHazirla();
	void ListeyiYukle();
	void SirayiYenile();

	wxString* listid;
	wxListView* showlist;
	wxArrayString* showlistcolumns;
	wxArrayString* showlistcolumndesc;
	wxStaticText *listname;
	wxChoice *displaymode;
};
