#include "wxlibs.h"

class EkleKitap : public wxDialog
{
public:
	EkleKitap(const wxString& title,const wxString& isbn);
	void OnQuit(wxCommandEvent& event);
	void ISBNRetrieve(wxCommandEvent& event);
	void SetISBNCover1(wxCommandEvent& event);
	void SetISBNCover2(wxCommandEvent& event);
	void SetISBNCover3(wxCommandEvent& event);
	void SetISBNCover4(wxCommandEvent& event);
	wxString GetNewBookISBN();
	wxString GetNewBookTitle();
	void SaveBook();
	
	wxTextCtrl *bookisbn;
	wxTextCtrl *booktitle;
	wxTextCtrl *bookauthors;
	wxTextCtrl *bookpublisher;
	wxTextCtrl *booksubject;
	wxSlider *bookcover;
	wxBitmapButton *isbnCover_1;
	wxBitmapButton *isbnCover_2;
	wxBitmapButton *isbnCover_3;
	wxBitmapButton *isbnCover_4;
};

const int ADDBOOK_DIALOG_RETRIEVE = 1201;
const int ADDBOOK_DIALOG_COVER_1 = 1301;
const int ADDBOOK_DIALOG_COVER_2 = 1302;
const int ADDBOOK_DIALOG_COVER_3 = 1303;
const int ADDBOOK_DIALOG_COVER_4 = 1304;
