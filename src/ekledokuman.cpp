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

#include "ekledokuman.h"

EkleDokuman::EkleDokuman(const wxString& title,const wxString& id)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,300))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(appLocation+wxT("resource/toolbar/document1.png"),wxBITMAP_TYPE_PNG);
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
	wxStaticText *dialogtitle = new wxStaticText(toppanel, -1, wxT("Doküman Ekle/Düzenle"));
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
	mid1hbox->Add(new wxStaticText(mid1panel,-1,wxT("Doküman Adı")),1,wxEXPAND);
	documentname = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid1hbox->Add(documentname,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	vbox->Add(mid1panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid2panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Doküman Açıklaması")),1,wxEXPAND);
	documentdesc = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,100),wxTE_MULTILINE);
	mid2hbox->Add(documentdesc,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	vbox->Add(mid2panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	
	vbox->Add(new wxStaticText(subpanel,-1,wxT("")),1,wxEXPAND);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	
	wxPanel *bottompanel = new wxPanel(subpanel,-1);
	wxBoxSizer *bottomhbox = new wxBoxSizer(wxHORIZONTAL);
	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT(" ")),0,wxEXPAND);
	wxArrayString documentstars;
	documentstars.Add(wxT("Beğeni"));
	documentstars.Add(wxT("0"));
	documentstars.Add(wxT("1"));
	documentstars.Add(wxT("2"));
	documentstars.Add(wxT("3"));
	documentstars.Add(wxT("4"));
	documentstars.Add(wxT("5"));
	documentstar = new wxChoice(bottompanel,-1,wxPoint(-1,-1),wxSize(150,-1),documentstars);
	bottomhbox->Add(documentstar,0,wxEXPAND);
	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT("")),1,wxEXPAND);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_CANCEL,cancelButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_OK,okButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	bottompanel->SetSizer(bottomhbox);
	vbox->Add(bottompanel,0,wxEXPAND);
	
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);

	if(id != wxT(""))
		EkleDokuman::PrepareUpdate(id); 
}

void EkleDokuman::PrepareUpdate(const wxString& id)
{
	wxString preparesql;
	preparesql << wxT("SELECT * FROM documents WHERE id == '") << id << wxT("';");
	vtcevap preparecevap;
	preparecevap = Vt(preparesql);
	documentname->SetValue(preparecevap.sonuc.Item(1));
	documentdesc->SetValue(preparecevap.sonuc.Item(2));
	documentstar->SetStringSelection(preparecevap.sonuc.Item(3));
}

void EkleDokuman::UpdateDocument(const wxString& id)
{
	wxArrayString documentupdate;
	documentupdate.Add(id);
	documentupdate.Add(documentname->GetValue());
	documentupdate.Add(documentdesc->GetValue());
	if(documentstar->GetSelection() == 0)
	{
		documentupdate.Add(wxT("0"));
	}
	else
	{
		documentupdate.Add(documentstar->GetString(documentstar->GetSelection()));
	}
	VtEkleSilGuncelle(wxT("INSERT OR REPLACE INTO documents VALUES (?,?,?,?);"),documentupdate);
}

void EkleDokuman::SaveDocument()
{
	wxArrayString documentsave;
	documentsave.Add(documentname->GetValue());
	documentsave.Add(documentdesc->GetValue());
	if(documentstar->GetSelection() == 0)
	{
		documentsave.Add(wxT("0"));
	}
	else
	{
		documentsave.Add(documentstar->GetString(documentstar->GetSelection()));
	}
	VtEkleSilGuncelle(wxT("INSERT INTO documents VALUES (NULL,?,?,?);"),documentsave);
}

wxString EkleDokuman::GetID()
{
	wxString idsql;
	idsql << wxT("SELECT * FROM documents WHERE name == '") << documentname->GetValue() << wxT("' AND  desc  == '") << documentdesc->GetValue() << wxT("';");
	vtcevap idcevap;
	idcevap = Vt(idsql);
	return idcevap.sonuc.Item(0);
}
