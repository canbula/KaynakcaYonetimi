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

#include "eklemakale.h"

EkleMakale::EkleMakale(const wxString& title,const wxString& doi)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,550))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(appLocation+wxT("resource/toolbar/contract2.png"),wxBITMAP_TYPE_PNG);
	wxBitmap searchButton(appLocation+wxT("resource/toolbar/zoom.png"),wxBITMAP_TYPE_PNG);
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
	wxStaticText *dialogtitle = new wxStaticText(toppanel, -1, wxT("Makale Ekle / Düzenle"));
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
	
	wxPanel *midhpanel = new wxPanel(subpanel,-1);
	wxBoxSizer *midhbox = new wxBoxSizer(wxHORIZONTAL);
	
	wxPanel *midvpanel = new wxPanel(midhpanel,-1);
	wxBoxSizer *midvbox = new wxBoxSizer(wxVERTICAL);
	
	midvbox->Add(-1,10);
	wxPanel *mid1panel = new wxPanel(midvpanel,-1);
	wxBoxSizer *mid1hbox = new wxBoxSizer(wxHORIZONTAL);
	mid1hbox->Add(new wxStaticText(mid1panel,-1,wxT("DOI Numarası ")),1,wxEXPAND);
	paperdoi = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	paperdoi->SetValue(doi);
	mid1hbox->Add(paperdoi,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	midvbox->Add(mid1panel,0,wxEXPAND);
	midvbox->Add(-1,10);
	midvpanel->SetSizer(midvbox);
	
	midhbox->Add(midvpanel,0,wxALIGN_CENTER_VERTICAL|wxEXPAND);
	midhbox->Add(new wxStaticText(midhpanel,-1,wxT("")),1,wxEXPAND);
	midhbox->Add(new wxBitmapButton(midhpanel,ADDPAPER_DIALOG_RETRIEVE,searchButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	
	midhpanel->SetSizer(midhbox);
	
	vbox->Add(midhpanel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid2panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Makale Başlığı")),1,wxEXPAND);
	papertitle = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid2hbox->Add(papertitle,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	vbox->Add(mid2panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid3panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid3hbox = new wxBoxSizer(wxHORIZONTAL);
	mid3hbox->Add(new wxStaticText(mid3panel,-1,wxT("Yazarlar")),1,wxEXPAND);
	paperauthors = new wxTextCtrl(mid3panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid3hbox->Add(paperauthors,0,wxALIGN_RIGHT);
	mid3panel->SetSizer(mid3hbox);
	vbox->Add(mid3panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid4panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid4hbox = new wxBoxSizer(wxHORIZONTAL);
	mid4hbox->Add(new wxStaticText(mid4panel,-1,wxT("Dergi")),1,wxEXPAND);
	paperjournal = new wxTextCtrl(mid4panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid4hbox->Add(paperjournal,0,wxALIGN_RIGHT);
	mid4panel->SetSizer(mid4hbox);
	vbox->Add(mid4panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid5panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid5hbox = new wxBoxSizer(wxHORIZONTAL);
	mid5hbox->Add(new wxStaticText(mid5panel,-1,wxT("Cilt")),1,wxEXPAND);
	papervolume = new wxTextCtrl(mid5panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid5hbox->Add(papervolume,0,wxALIGN_RIGHT);
	mid5panel->SetSizer(mid5hbox);
	vbox->Add(mid5panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid6panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid6hbox = new wxBoxSizer(wxHORIZONTAL);
	mid6hbox->Add(new wxStaticText(mid6panel,-1,wxT("Sayı")),1,wxEXPAND);
	paperissue = new wxTextCtrl(mid6panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid6hbox->Add(paperissue,0,wxALIGN_RIGHT);
	mid6panel->SetSizer(mid6hbox);
	vbox->Add(mid6panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid7panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid7hbox = new wxBoxSizer(wxHORIZONTAL);
	mid7hbox->Add(new wxStaticText(mid7panel,-1,wxT("İlk Sayfa / Numara")),1,wxEXPAND);
	paperfirstpage = new wxTextCtrl(mid7panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid7hbox->Add(paperfirstpage,0,wxALIGN_RIGHT);
	mid7panel->SetSizer(mid7hbox);
	vbox->Add(mid7panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid8panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid8hbox = new wxBoxSizer(wxHORIZONTAL);
	mid8hbox->Add(new wxStaticText(mid8panel,-1,wxT("Son Sayfa")),1,wxEXPAND);
	paperlastpage = new wxTextCtrl(mid8panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid8hbox->Add(paperlastpage,0,wxALIGN_RIGHT);
	mid8panel->SetSizer(mid8hbox);
	vbox->Add(mid8panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid9panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid9hbox = new wxBoxSizer(wxHORIZONTAL);
	mid9hbox->Add(new wxStaticText(mid9panel,-1,wxT("Yayın Tarihi")),1,wxEXPAND);
	paperpublished = new wxTextCtrl(mid9panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid9hbox->Add(paperpublished,0,wxALIGN_RIGHT);
	mid9panel->SetSizer(mid9hbox);
	vbox->Add(mid9panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid10panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid10hbox = new wxBoxSizer(wxHORIZONTAL);
	mid10hbox->Add(new wxStaticText(mid10panel,-1,wxT("Yayıncı Linki")),1,wxEXPAND);
	paperlink = new wxTextCtrl(mid10panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid10hbox->Add(paperlink,0,wxALIGN_RIGHT);
	mid10panel->SetSizer(mid10hbox);
	vbox->Add(mid10panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid11panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid11hbox = new wxBoxSizer(wxHORIZONTAL);
	mid11hbox->Add(new wxStaticText(mid11panel,-1,wxT("Konu / Anahtar Kelimeler")),1,wxEXPAND);
	papersubject = new wxTextCtrl(mid11panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid11hbox->Add(papersubject,0,wxALIGN_RIGHT);
	mid11panel->SetSizer(mid11hbox);
	vbox->Add(mid11panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid12panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid12hbox = new wxBoxSizer(wxHORIZONTAL);
	mid12hbox->Add(new wxStaticText(mid12panel,-1,wxT("Referans Kimliği")),1,wxEXPAND);
	paperrefid = new wxTextCtrl(mid12panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid12hbox->Add(paperrefid,0,wxALIGN_RIGHT);
	mid12panel->SetSizer(mid12hbox);
	vbox->Add(mid12panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	
	vbox->Add(new wxStaticText(subpanel,-1,wxT("")),1,wxEXPAND);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	
	wxPanel *bottompanel = new wxPanel(subpanel,-1);
	wxBoxSizer *bottomhbox = new wxBoxSizer(wxHORIZONTAL);
	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT(" ")),0,wxEXPAND);
	wxArrayString paperstars;
	paperstars.Add(wxT("Beğeni"));
	paperstars.Add(wxT("0"));
	paperstars.Add(wxT("1"));
	paperstars.Add(wxT("2"));
	paperstars.Add(wxT("3"));
	paperstars.Add(wxT("4"));
	paperstars.Add(wxT("5"));
	paperstar = new wxChoice(bottompanel,-1,wxPoint(-1,-1),wxSize(150,-1),paperstars);
	bottomhbox->Add(paperstar,0,wxEXPAND);
	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT("")),1,wxEXPAND);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_CANCEL,cancelButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_OK,okButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	bottompanel->SetSizer(bottomhbox);
	vbox->Add(bottompanel,0,wxEXPAND);
	
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);
	
	Connect(ADDPAPER_DIALOG_RETRIEVE,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(EkleMakale::DOIRetrieveTrigger));
	
	//Centre();

	if(doi != wxT(""))
	{
		wxString doichecksql;
		doichecksql << wxT("SELECT * FROM papers WHERE doi=='") << doi << wxT("'");
		vtcevap doicheck;
		doicheck = Vt(doichecksql);
		if(doicheck.satir>0)
		{
			papertitle->SetValue(doicheck.sonuc.Item(1));
			paperauthors->SetValue(doicheck.sonuc.Item(2));
			paperjournal->SetValue(doicheck.sonuc.Item(3));
			papervolume->SetValue(doicheck.sonuc.Item(4));
			paperissue->SetValue(doicheck.sonuc.Item(5));
			paperfirstpage->SetValue(doicheck.sonuc.Item(6));
			paperlastpage->SetValue(doicheck.sonuc.Item(7));
			paperpublished->SetValue(doicheck.sonuc.Item(8));
			paperlink->SetValue(doicheck.sonuc.Item(9));
			papersubject->SetValue(doicheck.sonuc.Item(10));
			paperrefid->SetValue(doicheck.sonuc.Item(11));
			paperstar->SetStringSelection(doicheck.sonuc.Item(12));
		}
		else
		{
			EkleMakale::DOIRetrieve();
		}
	}
}

void EkleMakale::DOIRetrieveTrigger(wxCommandEvent& WXUNUSED(event))
{
	EkleMakale::DOIRetrieve();
}

void EkleMakale::DOIRetrieve()
{
	wxString doicommand;
	doicommand << wxT("python ") << appLocation << wxT("src/eklemakale.py '") << paperdoi->GetValue() << wxT("'");
	wxWindowDisabler disableAll;
	wxBusyInfo info(wxT("Detaylar çevrimiçi veritabanından getiriliyor!"), this);
	wxExecute(doicommand,wxEXEC_SYNC);
	wxSQLite3Database *doiretriever = new wxSQLite3Database();
	doiretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString doiretrievesql;
	doiretrievesql << wxT("SELECT * FROM paper_retrieve WHERE doi = '") << paperdoi->GetValue() << wxT("';");
	wxSQLite3ResultSet doiretrieveSet = doiretriever->ExecuteQuery(doiretrievesql);
	papertitle->SetValue(doiretrieveSet.GetAsString(wxT("title")));
	paperauthors->SetValue(doiretrieveSet.GetAsString(wxT("authors")));
	paperjournal->SetValue(doiretrieveSet.GetAsString(wxT("journal")));
	papervolume->SetValue(doiretrieveSet.GetAsString(wxT("volume")));
	paperissue->SetValue(doiretrieveSet.GetAsString(wxT("issue")));
	paperfirstpage->SetValue(doiretrieveSet.GetAsString(wxT("firstpage")));
	paperlastpage->SetValue(doiretrieveSet.GetAsString(wxT("lastpage")));
	paperpublished->SetValue(doiretrieveSet.GetAsString(wxT("published")));
	paperlink->SetValue(doiretrieveSet.GetAsString(wxT("link")));
	papersubject->SetValue(doiretrieveSet.GetAsString(wxT("subject")));
	paperrefid->SetValue(doiretrieveSet.GetAsString(wxT("refid")));
	doiretrieveSet.Finalize();
	doiretriever->Close();
	delete doiretriever;
}

void EkleMakale::SavePaper()
{
	wxSQLite3Database *papersaver = new wxSQLite3Database();
	papersaver->Open(appLocation+wxT("db/Kaynakca.db"));
	wxSQLite3Statement papersaversql = papersaver->PrepareStatement(wxT("INSERT OR REPLACE INTO papers VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?);"));
	papersaversql.Bind(1,paperdoi->GetValue());
	papersaversql.Bind(2,papertitle->GetValue());
	papersaversql.Bind(3,paperauthors->GetValue());
	papersaversql.Bind(4,paperjournal->GetValue());
	papersaversql.Bind(5,papervolume->GetValue());
	papersaversql.Bind(6,paperissue->GetValue());
	papersaversql.Bind(7,paperfirstpage->GetValue());
	papersaversql.Bind(8,paperlastpage->GetValue());
	papersaversql.Bind(9,paperpublished->GetValue());
	papersaversql.Bind(10,paperlink->GetValue());
	papersaversql.Bind(11,papersubject->GetValue());
	papersaversql.Bind(12,paperrefid->GetValue());
	if(paperstar->GetSelection() == 0)
	{
		papersaversql.Bind(13,wxT("0"));
	}
	else
	{
		papersaversql.Bind(13,paperstar->GetString(paperstar->GetSelection()));
	}
	// edit kismini kodlarken paperstar->SetStringSelection(wxT("0")); yaparsin
	papersaversql.ExecuteUpdate();
	papersaversql.ClearBindings();
	papersaversql.Reset();
	papersaver->Close();
	delete papersaver;
}

wxString EkleMakale::GetNewPaperDOI()
{
	return paperdoi->GetValue();
}
