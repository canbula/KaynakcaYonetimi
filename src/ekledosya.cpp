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

#include "ekledosya.h"

EkleDosya::EkleDosya(const wxString& title,const wxString& id)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,300))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(srcLocation+wxT("resource/toolbar/file.png"),wxBITMAP_TYPE_PNG);
	wxBitmap okButton(srcLocation+wxT("resource/toolbar/checkmark.png"),wxBITMAP_TYPE_PNG);
	wxBitmap cancelButton(srcLocation+wxT("resource/toolbar/cross.png"),wxBITMAP_TYPE_PNG);
	
	wxPanel *panel = new wxPanel(this,-1);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText *mainleft = new wxStaticText(panel,-1,wxT(" "));
	hbox->Add(mainleft,0,wxEXPAND);
	
	wxPanel *subpanel = new wxPanel(panel,-1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	
	vbox->Add(-1,10);
	
	wxPanel *toppanel = new wxPanel(subpanel,-1);
	wxBoxSizer *tophbox = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *dialogtitle = new wxStaticText(toppanel, -1, wxT("Dosya Ekle/Düzenle"));
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
	mid1hbox->Add(new wxStaticText(mid1panel,-1,wxT("Dosya Adı")),1,wxEXPAND);
	filename = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid1hbox->Add(filename,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	vbox->Add(mid1panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid2panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Dosya Açıklaması")),1,wxEXPAND);
	filedesc = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,100),wxTE_MULTILINE);
	mid2hbox->Add(filedesc,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	vbox->Add(mid2panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	
	vbox->Add(new wxStaticText(subpanel,-1,wxT("")),1,wxEXPAND);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	
	wxPanel *bottompanel = new wxPanel(subpanel,-1);
	wxBoxSizer *bottomhbox = new wxBoxSizer(wxHORIZONTAL);
	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT(" ")),0,wxEXPAND);
	wxArrayString filestars;
	filestars.Add(wxT("Beğeni"));
	filestars.Add(wxT("0"));
	filestars.Add(wxT("1"));
	filestars.Add(wxT("2"));
	filestars.Add(wxT("3"));
	filestars.Add(wxT("4"));
	filestars.Add(wxT("5"));
	filestar = new wxChoice(bottompanel,-1,wxPoint(-1,-1),wxSize(150,-1),filestars);
	bottomhbox->Add(filestar,0,wxEXPAND);
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
		EkleDosya::PrepareUpdate(id); 
}

void EkleDosya::PrepareUpdate(const wxString& id)
{
	wxString preparesql;
	preparesql << wxT("SELECT * FROM files WHERE id == '") << id << wxT("';");
	vtcevap preparecevap;
	preparecevap = Vt(preparesql);
	filename->SetValue(preparecevap.sonuc.Item(1));
	filedesc->SetValue(preparecevap.sonuc.Item(2));
	filestar->SetStringSelection(preparecevap.sonuc.Item(3));
}

void EkleDosya::UpdateFile(const wxString& id)
{
	wxArrayString fileupdate;
	fileupdate.Add(id);
	fileupdate.Add(filename->GetValue());
	fileupdate.Add(filedesc->GetValue());
	if(filestar->GetSelection() == 0)
	{
		fileupdate.Add(wxT("0"));
	}
	else
	{
		fileupdate.Add(filestar->GetString(filestar->GetSelection()));
	}
	VtEkleSilGuncelle(wxT("INSERT OR REPLACE INTO files VALUES (?,?,?,?);"),fileupdate);
}

void EkleDosya::SaveFile()
{
	wxArrayString filesave;
	filesave.Add(filename->GetValue());
	filesave.Add(filedesc->GetValue());
	if(filestar->GetSelection() == 0)
	{
		filesave.Add(wxT("0"));
	}
	else
	{
		filesave.Add(filestar->GetString(filestar->GetSelection()));
	}
	VtEkleSilGuncelle(wxT("INSERT INTO files VALUES (NULL,?,?,?);"),filesave);
}

wxString EkleDosya::GetID()
{
	wxString idsql;
	idsql << wxT("SELECT * FROM files WHERE name == '") << filename->GetValue() << wxT("' AND  desc  == '") << filedesc->GetValue() << wxT("';");
	vtcevap idcevap;
	idcevap = Vt(idsql);
	return idcevap.sonuc.Item(0);
}
