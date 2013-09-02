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
	void OgeyeGozAt(wxListEvent &event);
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
