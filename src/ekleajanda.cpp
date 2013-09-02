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

#include "ekleajanda.h"

EkleAjanda::EkleAjanda(const wxString& title,const wxString& id,const wxString& date)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,320))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(appLocation+wxT("resource/toolbar/calendar_month.png"),wxBITMAP_TYPE_PNG);
	wxBitmap okButton(appLocation+wxT("resource/toolbar/checkmark.png"),wxBITMAP_TYPE_PNG);
	wxBitmap cancelButton(appLocation+wxT("resource/toolbar/cross.png"),wxBITMAP_TYPE_PNG);
	
	wxPanel *panel = new wxPanel(this,-1);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText *mainleft = new wxStaticText(panel,-1,wxT(" "));
	hbox->Add(mainleft,0,wxEXPAND);
	
	wxPanel *subpanel = new wxPanel(panel,-1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	
	vbox->Add(-1,10);
	
	wxPanel *toppanel = new wxPanel(subpanel,-1);
	wxBoxSizer *tophbox = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *dialogtitle = new wxStaticText(toppanel, -1, wxT("Yeni Ajanda Notu Ekle"));
	wxFont font = dialogtitle->GetFont();
	font.SetPointSize(18);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	dialogtitle->SetFont(font);
	tophbox->Add(dialogtitle,1,wxALIGN_BOTTOM|wxEXPAND);
	wxStaticBitmap *dialoglogo = new wxStaticBitmap(toppanel,-1,dialogLogo);
	tophbox->Add(dialoglogo,0,wxALIGN_RIGHT);
	toppanel->SetSizer(tophbox);
	vbox->Add(toppanel,0,wxEXPAND);

	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid1panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid1hbox = new wxBoxSizer(wxHORIZONTAL);
	mid1hbox->Add(new wxStaticText(mid1panel,-1,wxT("Not Tarihi")),1,wxEXPAND);
	tododate = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	tododate->SetValue(date);
	mid1hbox->Add(tododate,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	vbox->Add(mid1panel,0,wxEXPAND);

	vbox->Add(-1,10);
	wxPanel *mid2panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Not Başlığı")),1,wxEXPAND);
	todotitle = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid2hbox->Add(todotitle,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	vbox->Add(mid2panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid3panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid3hbox = new wxBoxSizer(wxHORIZONTAL);
	mid3hbox->Add(new wxStaticText(mid3panel,-1,wxT("Not İçeriği")),1,wxEXPAND);
	tododetails = new wxTextCtrl(mid3panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,100),wxTE_MULTILINE);
	mid3hbox->Add(tododetails,0,wxALIGN_RIGHT);
	mid3panel->SetSizer(mid3hbox);
	vbox->Add(mid3panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	
	vbox->Add(new wxStaticText(subpanel,-1,wxT("")),1,wxEXPAND);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	
	wxPanel *bottompanel = new wxPanel(subpanel,-1);
	wxBoxSizer *bottomhbox = new wxBoxSizer(wxHORIZONTAL);
	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT("")),1,wxEXPAND);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_CANCEL,cancelButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_OK,okButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	bottompanel->SetSizer(bottomhbox);
	vbox->Add(bottompanel,0,wxEXPAND);
	
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);
	
	//Centre();

	if(id != wxT(""))
		EkleAjanda::PrepareUpdate(id); 
}

void EkleAjanda::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void EkleAjanda::PrepareUpdate(const wxString& id)
{
	wxSQLite3Database *prepareretriever = new wxSQLite3Database();
	prepareretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString prepareretrievesql;
	prepareretrievesql << wxT("SELECT * FROM todos WHERE id == '") << id << wxT("';");
	wxSQLite3ResultSet prepareretrieveSet = prepareretriever->ExecuteQuery(prepareretrievesql);
	tododate->SetValue(prepareretrieveSet.GetAsString(wxT("date")));
	todotitle->SetValue(prepareretrieveSet.GetAsString(wxT("title")));
	tododetails->SetValue(prepareretrieveSet.GetAsString(wxT("details")));
	prepareretrieveSet.Finalize();
	prepareretriever->Close();
	delete prepareretriever;
}

void EkleAjanda::UpdateTodo(const wxString& id)
{
	wxSQLite3Database *todosaver = new wxSQLite3Database();
	todosaver->Open(appLocation+wxT("db/Kaynakca.db"));
	wxSQLite3Statement todosaversql = todosaver->PrepareStatement(wxT("INSERT OR REPLACE INTO todos VALUES (?,?,?,?);"));
	todosaversql.Bind(1,id);
	todosaversql.Bind(2,tododate->GetValue());
	todosaversql.Bind(3,todotitle->GetValue());
	todosaversql.Bind(4,tododetails->GetValue());
	todosaversql.ExecuteUpdate();
	todosaversql.ClearBindings();
	todosaversql.Reset();
	todosaver->Close();
	delete todosaver;
}

void EkleAjanda::SaveTodo()
{
	wxSQLite3Database *todosaver = new wxSQLite3Database();
	todosaver->Open(appLocation+wxT("db/Kaynakca.db"));
	wxSQLite3Statement todosaversql = todosaver->PrepareStatement(wxT("INSERT OR REPLACE INTO todos VALUES (NULL,?,?,?);"));
	todosaversql.Bind(1,tododate->GetValue());
	todosaversql.Bind(2,todotitle->GetValue());
	todosaversql.Bind(3,tododetails->GetValue());
	todosaversql.ExecuteUpdate();
	todosaversql.ClearBindings();
	todosaversql.Reset();
	todosaver->Close();
	delete todosaver;
}
