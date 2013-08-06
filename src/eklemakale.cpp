#include "eklemakale.h"

EkleMakale::EkleMakale(const wxString& title,const wxString& doi)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,500))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(appLocation+wxT("resource/toolbar/Article.png"),wxBITMAP_TYPE_PNG);
	
	wxPanel *panel = new wxPanel(this,-1);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText *mainleft = new wxStaticText(panel,-1,wxT(" "));
	hbox->Add(mainleft,0,wxEXPAND);
	
	wxPanel *subpanel = new wxPanel(panel,-1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	
	vbox->Add(-1,10);
	
	wxPanel *toppanel = new wxPanel(subpanel,-1);
	wxBoxSizer *tophbox = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *dialogtitle = new wxStaticText(toppanel, -1, wxT("Yeni Makale Ekle"));
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
	mid1hbox->Add(new wxStaticText(mid1panel,-1,wxT("DOI Numarası")),1,wxEXPAND);
	paperdoi = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	paperdoi->SetValue(doi);
	mid1hbox->Add(paperdoi,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	vbox->Add(mid1panel,0,wxEXPAND);

	vbox->Add(-1,10);
	vbox->Add(new wxButton(subpanel,ADDPAPER_DIALOG_RETRIEVE,wxT("Detayları Getir")),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	vbox->Add(-1,10);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid2panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Başlık")),1,wxEXPAND);
	papertitle = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid2hbox->Add(papertitle,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	vbox->Add(mid2panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid3panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid3hbox = new wxBoxSizer(wxHORIZONTAL);
	mid3hbox->Add(new wxStaticText(mid3panel,-1,wxT("Yazarlar")),1,wxEXPAND);
	paperauthors = new wxTextCtrl(mid3panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid3hbox->Add(paperauthors,0,wxALIGN_RIGHT);
	mid3panel->SetSizer(mid3hbox);
	vbox->Add(mid3panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid4panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid4hbox = new wxBoxSizer(wxHORIZONTAL);
	mid4hbox->Add(new wxStaticText(mid4panel,-1,wxT("Dergi")),1,wxEXPAND);
	paperjournal = new wxTextCtrl(mid4panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid4hbox->Add(paperjournal,0,wxALIGN_RIGHT);
	mid4panel->SetSizer(mid4hbox);
	vbox->Add(mid4panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid5panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid5hbox = new wxBoxSizer(wxHORIZONTAL);
	mid5hbox->Add(new wxStaticText(mid5panel,-1,wxT("Cilt")),1,wxEXPAND);
	papervolume = new wxTextCtrl(mid5panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid5hbox->Add(papervolume,0,wxALIGN_RIGHT);
	mid5panel->SetSizer(mid5hbox);
	vbox->Add(mid5panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid6panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid6hbox = new wxBoxSizer(wxHORIZONTAL);
	mid6hbox->Add(new wxStaticText(mid6panel,-1,wxT("Sayı")),1,wxEXPAND);
	paperissue = new wxTextCtrl(mid6panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid6hbox->Add(paperissue,0,wxALIGN_RIGHT);
	mid6panel->SetSizer(mid6hbox);
	vbox->Add(mid6panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid7panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid7hbox = new wxBoxSizer(wxHORIZONTAL);
	mid7hbox->Add(new wxStaticText(mid7panel,-1,wxT("İlk Sayfa")),1,wxEXPAND);
	paperfirstpage = new wxTextCtrl(mid7panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid7hbox->Add(paperfirstpage,0,wxALIGN_RIGHT);
	mid7panel->SetSizer(mid7hbox);
	vbox->Add(mid7panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid8panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid8hbox = new wxBoxSizer(wxHORIZONTAL);
	mid8hbox->Add(new wxStaticText(mid8panel,-1,wxT("Son Sayfa / Nesne Numarası")),1,wxEXPAND);
	paperlastpage = new wxTextCtrl(mid8panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid8hbox->Add(paperlastpage,0,wxALIGN_RIGHT);
	mid8panel->SetSizer(mid8hbox);
	vbox->Add(mid8panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid9panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid9hbox = new wxBoxSizer(wxHORIZONTAL);
	mid9hbox->Add(new wxStaticText(mid9panel,-1,wxT("Yayın Tarihi")),1,wxEXPAND);
	paperpublished = new wxTextCtrl(mid9panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid9hbox->Add(paperpublished,0,wxALIGN_RIGHT);
	mid9panel->SetSizer(mid9hbox);
	vbox->Add(mid9panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid10panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid10hbox = new wxBoxSizer(wxHORIZONTAL);
	mid10hbox->Add(new wxStaticText(mid10panel,-1,wxT("Yayıncı Linki")),1,wxEXPAND);
	paperlink = new wxTextCtrl(mid10panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid10hbox->Add(paperlink,0,wxALIGN_RIGHT);
	mid10panel->SetSizer(mid10hbox);
	vbox->Add(mid10panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid11panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid11hbox = new wxBoxSizer(wxHORIZONTAL);
	mid11hbox->Add(new wxStaticText(mid11panel,-1,wxT("Konu / Anahtar Kelimeler")),1,wxEXPAND);
	papersubject = new wxTextCtrl(mid11panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid11hbox->Add(papersubject,0,wxALIGN_RIGHT);
	mid11panel->SetSizer(mid11hbox);
	vbox->Add(mid11panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	
	vbox->Add(new wxStaticText(subpanel,-1,wxT("")),1,wxEXPAND);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	vbox->Add(new wxButton(subpanel,wxID_OK,wxT("Kaydet")),0,wxALIGN_BOTTOM|wxALIGN_RIGHT);
	vbox->Add(-1,10);
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);
	
	Connect(ADDPAPER_DIALOG_RETRIEVE,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(EkleMakale::DOIRetrieve));
	
	Centre();
}

void EkleMakale::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void EkleMakale::DOIRetrieve(wxCommandEvent& WXUNUSED(event))
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
	doiretrieveSet.Finalize();
	doiretriever->Close();
	delete doiretriever;
}

void EkleMakale::SavePaper()
{
	paperdoi->GetValue();
	papertitle->GetValue();
	paperauthors->GetValue();
	paperjournal->GetValue();
	papervolume->GetValue();
	paperissue->GetValue();
	paperfirstpage->GetValue();
	paperlastpage->GetValue();
	paperpublished->GetValue();
	paperlink->GetValue();
	papersubject->GetValue();
}
