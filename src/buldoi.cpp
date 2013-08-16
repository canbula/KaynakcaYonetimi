#include "buldoi.h"
#include "md5.h"

BulDOI::BulDOI(const wxString& title)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,500))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(appLocation+wxT("resource/toolbar/serial-number.png"),wxBITMAP_TYPE_PNG);
	
	wxPanel *panel = new wxPanel(this,-1);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText *mainleft = new wxStaticText(panel,-1,wxT(" "));
	hbox->Add(mainleft,0,wxEXPAND);
	
	wxPanel *subpanel = new wxPanel(panel,-1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	
	vbox->Add(-1,10);
	
	wxPanel *toppanel = new wxPanel(subpanel,-1);
	wxBoxSizer *tophbox = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *dialogtitle = new wxStaticText(toppanel, -1, wxT("DOI Numarası Bulma Aracı"));
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
	mid1hbox->Add(new wxStaticText(mid1panel,-1,wxT("Başlıca Yazarın Soyadı")),1,wxEXPAND);
	srcauthor = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid1hbox->Add(srcauthor,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	vbox->Add(mid1panel,0,wxEXPAND);
	
	wxPanel *mid2panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Makalenin Başlığı")),1,wxEXPAND);
	srctitle = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid2hbox->Add(srctitle,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	vbox->Add(mid2panel,0,wxEXPAND);

	vbox->Add(-1,10);
	vbox->Add(new wxButton(subpanel,FINDDOI_DIALOG_RETRIEVE,wxT("DOI Numarasını Bul")),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	vbox->Add(-1,10);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	finddoiresults = new wxHtmlWindow(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1));
	vbox->Add(finddoiresults,1,wxEXPAND);
	
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	
	wxPanel *bottompanel = new wxPanel(subpanel,-1);
	wxBoxSizer *bottomhbox = new wxBoxSizer(wxHORIZONTAL);
	wxArrayString doinumbers;
	doinumbers.Add(wxT("Eklemek için bir DOI numarası seçebilirsiniz"));
	doinumber = new wxChoice(bottompanel,-1,wxPoint(-1,-1),wxSize(280,-1),doinumbers);
	bottomhbox->Add(doinumber,1,wxEXPAND);
	bottomhbox->Add(new wxButton(bottompanel,wxID_OK,wxT("Ekle")),0,wxALIGN_BOTTOM|wxALIGN_RIGHT);
	bottompanel->SetSizer(bottomhbox);
	vbox->Add(bottompanel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);
	
	Connect(FINDDOI_DIALOG_RETRIEVE,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(BulDOI::FindDOIRetrieve));
	
	Centre();
}

void BulDOI::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void BulDOI::FindDOIRetrieve(wxCommandEvent& WXUNUSED(event))
{
	wxString authortitle;
	authortitle << srcauthor->GetValue() << srctitle->GetValue();
	authortitle = MD5wxString(authortitle);
	wxString finddoicommand;
	finddoicommand << wxT("python ") << appLocation << wxT("src/buldoi.py '") << srcauthor->GetValue() << wxT("' '") << srctitle->GetValue() << wxT("'");
	wxWindowDisabler disableAll;
	wxBusyInfo info(wxT("Makale çevrimiçi veritabanında aranıyor!"), this);
	wxExecute(finddoicommand,wxEXEC_SYNC);
	wxSQLite3Database *finddoiretriever = new wxSQLite3Database();
	finddoiretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString finddoiretrievesql;
	finddoiretrievesql << wxT("SELECT * FROM finddoi WHERE authortitle = '") << authortitle << wxT("';");
	wxSQLite3ResultSet finddoiretrieveSet = finddoiretriever->ExecuteQuery(finddoiretrievesql);
	finddoiresults->SetPage(finddoiretrieveSet.GetAsString(wxT("result")));
	wxStringTokenizer doitkz(finddoiretrieveSet.GetAsString(wxT("doinumbers")),wxT(";"));
	while(doitkz.HasMoreTokens()) {
		wxString doitoken = doitkz.GetNextToken();
		doinumber->Append(doitoken);
	}
	finddoiretrieveSet.Finalize();
	finddoiretriever->Close();
	delete finddoiretriever;
}

wxString BulDOI::GetDOI()
{
	wxString doistring;
	doistring << doinumber->GetString(doinumber->GetSelection());
	return doistring;
}
