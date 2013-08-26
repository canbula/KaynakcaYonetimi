#include "wxlibs.h"

class KaynakcaYonetimi : public wxFrame
{
public:
	KaynakcaYonetimi(const wxString& title);
	
	enum
	{
		ID_ADDMENU_BOOK = wxID_HIGHEST + 1,
		ID_ADDMENU_ARTICLE,
		ID_ADDMENU_DOCUMENT,
		ID_ADDMENU_FILE,
		ID_ADDMENU_LIST,
		ID_TOOLMENU_FINDISBN,
		ID_TOOLMENU_FINDDOI,
		ID_TOOLBAR_ADDBOOK,
		ID_TOOLBAR_ADDARTICLE,
		ID_TOOLBAR_ADDDOCUMENT,
		ID_TOOLBAR_ADDFILE,
		ID_TOOLBAR_ADDLIST,
		ID_TOOLBAR_FINDISBN,
		ID_TOOLBAR_FINDDOI,
		ID_TOOLBAR_HELP,
		ID_TOOLBAR_ABOUT,
		ID_PAPERRCMENU_EDIT,
		ID_PAPERRCMENU_DELETE,
		ID_LISTRCMENU_EDIT,
		ID_LISTRCMENU_DELETE,
		ID_TODORCMENU_EDIT,
		ID_TODORCMENU_DELETE
	};
	
	void EkleKitapDialog(wxCommandEvent& event);
	void EkleMakaleDialog(wxCommandEvent& event);
	void BulDOIDialog(wxCommandEvent& event);
	void BulISBNDialog(wxCommandEvent& event);
	
	void Kapat(wxCommandEvent& event);
	void Hakkinda(wxCommandEvent& event);
	void AramaKurtarma(wxCommandEvent& event);

	void MakaleleriYukle(const wxString& sorter);
	void MakaleSirala(wxListEvent& event);
	void MakaleSagTikList(wxCommandEvent &event);
	void MakaleSagTikTik(wxCommandEvent &event);
	void MakaleSagTik(wxListEvent &event);

	void EkleListeDialog(wxCommandEvent& event);
	void ListeleriYukle(const wxString& sorter);
	void ListeSirala(wxListEvent& event);
	void ListeSagTikTik(wxCommandEvent &event);
	void ListeSagTik(wxListEvent &event);
	void GosterListeDialog(wxListEvent &event);

	void EkleAjandaDialog(wxListEvent &event);
	void AjandayiYukle();
	void AjandayiYenile(wxCommandEvent& event);
	void AjandaSagTikTik(wxCommandEvent &event);
	void AjandaSagTik(wxListEvent &event);

	void NaberBora(wxCommandEvent& event);
	void OnDropFiles(wxDropFilesEvent& event);

	wxListView* paperlist;
	wxArrayString* paperlistcolumns;
	wxArrayString* paperlistcolumndesc;

	wxListView* listlist;
	wxArrayString* listlistcolumns;
	wxArrayString* listlistcolumndesc;

	wxCalendarCtrl* todocal;
	wxListView* todolist;
};
