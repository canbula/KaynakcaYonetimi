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
