#include "bulisbn.h"
#include "md5.h"

BulISBN::BulISBN(const wxString& title)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,500))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(appLocation+wxT("resource/toolbar/barcode.png"),wxBITMAP_TYPE_PNG);
	
	wxPanel *panel = new wxPanel(this,-1);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText *mainleft = new wxStaticText(panel,-1,wxT(" "));
	hbox->Add(mainleft,0,wxEXPAND);
	
	wxPanel *subpanel = new wxPanel(panel,-1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	
	vbox->Add(-1,10);
	
	wxPanel *toppanel = new wxPanel(subpanel,-1);
	wxBoxSizer *tophbox = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *dialogtitle = new wxStaticText(toppanel, -1, wxT("ISBN Numarası Bulma Aracı"));
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
	srcauthor = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid1hbox->Add(srcauthor,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	vbox->Add(mid1panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid2panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Kitabın Adı")),1,wxEXPAND);
	srctitle = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(300,-1));
	mid2hbox->Add(srctitle,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	vbox->Add(mid2panel,0,wxEXPAND);

	vbox->Add(-1,10);
	vbox->Add(new wxButton(subpanel,FINDISBN_DIALOG_RETRIEVE,wxT("ISBN Numarasını Bul")),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	vbox->Add(-1,10);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	findisbnresults = new wxHtmlWindow(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1));
	vbox->Add(findisbnresults,1,wxEXPAND);
	
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	
	wxPanel *bottompanel = new wxPanel(subpanel,-1);
	wxBoxSizer *bottomhbox = new wxBoxSizer(wxHORIZONTAL);
	wxArrayString isbnnumbers;
	isbnnumbers.Add(wxT("Bir ISBN numarası seçebilirsiniz"));
	isbnnumber = new wxChoice(bottompanel,-1,wxPoint(-1,-1),wxSize(280,-1),isbnnumbers);
	bottomhbox->Add(isbnnumber,1,wxEXPAND);
	bottomhbox->Add(new wxButton(bottompanel,wxID_CANCEL,wxT("Vazgeç")),0,wxALIGN_BOTTOM|wxALIGN_RIGHT);
	bottomhbox->Add(new wxButton(bottompanel,wxID_OK,wxT("Ekle")),0,wxALIGN_BOTTOM|wxALIGN_RIGHT);
	bottompanel->SetSizer(bottomhbox);
	vbox->Add(bottompanel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);
	
	Connect(FINDISBN_DIALOG_RETRIEVE,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(BulISBN::FindISBNRetrieve));
	
	Centre();
}

void BulISBN::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void BulISBN::FindISBNRetrieve(wxCommandEvent& WXUNUSED(event))
{
	wxString authortitle;
	authortitle << srcauthor->GetValue() << srctitle->GetValue();
	authortitle = MD5wxString(authortitle);
	wxString findisbncommand;
	findisbncommand << wxT("php ") << appLocation << wxT("src/bulisbn.php '") << srcauthor->GetValue() << wxT("' '") << srctitle->GetValue() << wxT("'");
	wxWindowDisabler disableAll;
	wxBusyInfo info(wxT("Kitap çevrimiçi veritabanında aranıyor!"), this);
	wxExecute(findisbncommand,wxEXEC_SYNC);
	wxSQLite3Database *findisbnretriever = new wxSQLite3Database();
	findisbnretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString findisbnretrievesql;
	findisbnretrievesql << wxT("SELECT * FROM findisbn WHERE authortitle = '") << authortitle << wxT("';");
	wxSQLite3ResultSet findisbnretrieveSet = findisbnretriever->ExecuteQuery(findisbnretrievesql);
	findisbnresults->SetPage(findisbnretrieveSet.GetAsString(wxT("result")));
	isbnnumber->Clear();
	wxStringTokenizer isbntkz(findisbnretrieveSet.GetAsString(wxT("isbnnumbers")),wxT(";"));
	while(isbntkz.HasMoreTokens()) {
		wxString isbntoken = isbntkz.GetNextToken();
		isbnnumber->Append(isbntoken);
	}
	isbnnumber->SetSelection(0);
	findisbnretrieveSet.Finalize();
	findisbnretriever->Close();
	delete findisbnretriever;
}

wxString BulISBN::GetISBN()
{
	wxString isbnstring;
	isbnstring << isbnnumber->GetString(isbnnumber->GetSelection());
	return isbnstring;
}
