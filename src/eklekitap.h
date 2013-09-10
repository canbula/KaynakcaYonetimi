/*
    This file is part of KaynakcaYonetimi.

    KaynakcaYonetimi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    KaynakcaYonetimi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with KaynakcaYonetimi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "wxlibs.h"

class EkleKitap : public wxDialog
{
public:
	EkleKitap(const wxString& title,const wxString& isbn);
	void ISBNRetrieveTrigger(wxCommandEvent& event);
	void ISBNRetrieve(const wxString& retrievemode);
	void SetISBNCover1(wxCommandEvent& event);
	void SetISBNCover2(wxCommandEvent& event);
	void SetISBNCover3(wxCommandEvent& event);
	void SetISBNCover4(wxCommandEvent& event);
	void SaveBook();
	wxString GetNewBookISBN();
	
	wxTextCtrl *bookisbn;
	wxTextCtrl *booktitle;
	wxTextCtrl *bookauthors;
	wxTextCtrl *bookpublisher;
	wxTextCtrl *booksubject;
	wxTextCtrl *bookrefid;
	wxCheckBox *bookcov;
	wxChoice *bookstar;
	wxChoice *bookcolor;
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
