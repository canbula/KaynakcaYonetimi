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
		ID_BOOKRCMENU_EDIT,
		ID_BOOKRCMENU_DELETE,
		ID_BOOKRCMENU_UPLOAD,
		ID_BOOKRCMENU_WWW,
		ID_PAPERRCMENU_EDIT,
		ID_PAPERRCMENU_DELETE,
		ID_PAPERRCMENU_UPLOAD,
		ID_PAPERRCMENU_WWW,
		ID_DOCUMENTRCMENU_EDIT,
		ID_DOCUMENTRCMENU_DELETE,
		ID_DOCUMENTRCMENU_UPLOAD,
		ID_FILERCMENU_EDIT,
		ID_FILERCMENU_DELETE,
		ID_FILERCMENU_UPLOAD,
		ID_LISTRCMENU_EDIT,
		ID_LISTRCMENU_DELETE,
		ID_TODORCMENU_EDIT,
		ID_TODORCMENU_DELETE
	};

	// Genel
	void Kapat(wxCommandEvent& event);
	void Hakkinda(wxCommandEvent& event);
	void Arama(wxCommandEvent& event);
	wxNotebook* middlenb;
	
	// Kitap
	void DosyaEkleKitapDialog(wxCommandEvent& event);
	void EkleKitapDialog(wxCommandEvent& event);
	void BulISBNDialog(wxCommandEvent& event);
	void KitaplariYukle(const wxString& sorter);
	void KitapSirala(wxListEvent& event);
	void KitapSagTikList(wxCommandEvent &event);
	void KitapSagTikTik(wxCommandEvent &event);
	void KitapSagTik(wxListEvent &event);
	void KitapCiftTik(wxListEvent &event);
	void KitapYeniDosya(const wxString& yenidosya);
	void KitapBirak(wxDropFilesEvent& event);
	wxListView* booklist;
	wxArrayString* booklistcolumns;
	wxArrayString* booklistcolumndesc;

	// Makale
	void DosyaEkleMakaleDialog(wxCommandEvent& event);
	void EkleMakaleDialog(wxCommandEvent& event);
	void BulDOIDialog(wxCommandEvent& event);
	void MakaleleriYukle(const wxString& sorter);
	void MakaleSirala(wxListEvent& event);
	void MakaleSagTikList(wxCommandEvent &event);
	void MakaleSagTikTik(wxCommandEvent &event);
	void MakaleSagTik(wxListEvent &event);
	void MakaleCiftTik(wxListEvent &event);
	void MakaleYeniDosya(const wxString& yenidosya);
	void MakaleBirak(wxDropFilesEvent& event);
	wxListView* paperlist;
	wxArrayString* paperlistcolumns;
	wxArrayString* paperlistcolumndesc;

	// Doküman
	void DosyaEkleDokumanDialog(wxCommandEvent& event);
	void EkleDokumanDialog(wxCommandEvent& event);
	void DokumanlariYukle(const wxString& sorter);
	void DokumanSirala(wxListEvent& event);
	void DokumanSagTikTik(wxCommandEvent &event);
	void DokumanSagTik(wxListEvent &event);
	void DokumanCiftTik(wxListEvent &event);
	void DokumanYeniDosya(const wxString& yenidosya);
	void DokumanBirak(wxDropFilesEvent& event);
	wxListView* documentlist;
	wxArrayString* documentlistcolumns;
	wxArrayString* documentlistcolumndesc;

	// Dosya
	void DosyaEkleDosyaDialog(wxCommandEvent& event);
	void EkleDosyaDialog(wxCommandEvent& event);
	void DosyalariYukle(const wxString& sorter);
	void DosyaSirala(wxListEvent& event);
	void DosyaSagTikTik(wxCommandEvent &event);
	void DosyaSagTik(wxListEvent &event);
	void DosyaCiftTik(wxListEvent &event);
	void DosyaYeniDosya(const wxString& yenidosya);
	void DosyaBirak(wxDropFilesEvent& event);
	wxListView* filelist;
	wxArrayString* filelistcolumns;
	wxArrayString* filelistcolumndesc;

	// Liste
	void EkleListeDialog(wxCommandEvent& event);
	void ListeleriYukle(const wxString& sorter);
	void ListeSirala(wxListEvent& event);
	void ListeSagTikTik(wxCommandEvent &event);
	void ListeSagTik(wxListEvent &event);
	void GosterListeDialog(wxListEvent &event);
	wxListView* listlist;
	wxArrayString* listlistcolumns;
	wxArrayString* listlistcolumndesc;

	// Ajanda
	void EkleAjandaDialog(wxListEvent &event);
	void AjandayiYukle();
	void AjandayiYenile(wxCommandEvent& event);
	void AjandaSagTikTik(wxCommandEvent &event);
	void AjandaSagTik(wxListEvent &event);
	wxCalendarCtrl* todocal;
	wxListView* todolist;
};
