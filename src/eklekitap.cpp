#include "eklekitap.h"

EkleKitap::EkleKitap(const wxString& title,const wxString& isbn)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,500))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(appLocation+wxT("resource/toolbar/Book.png"),wxBITMAP_TYPE_PNG);
	
	wxPanel *panel = new wxPanel(this,-1);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText *mainleft = new wxStaticText(panel,-1,wxT(" "));
	hbox->Add(mainleft,0,wxEXPAND);
	
	wxPanel *subpanel = new wxPanel(panel,-1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	
	vbox->Add(-1,10);
	
	wxPanel *toppanel = new wxPanel(subpanel,-1);
	wxBoxSizer *tophbox = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *dialogtitle = new wxStaticText(toppanel, -1, wxT("Yeni Kitap Ekle"));
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
	mid1hbox->Add(new wxStaticText(mid1panel,-1,wxT("ISBN Numarası")),1,wxEXPAND);
	bookisbn = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	bookisbn->SetValue(isbn);
	mid1hbox->Add(bookisbn,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	vbox->Add(mid1panel,0,wxEXPAND);

	vbox->Add(-1,10);
	vbox->Add(new wxButton(subpanel,ADDBOOK_DIALOG_RETRIEVE,wxT("Detayları Getir")),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	vbox->Add(-1,10);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid2panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Başlık")),1,wxEXPAND);
	booktitle = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid2hbox->Add(booktitle,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	vbox->Add(mid2panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid3panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid3hbox = new wxBoxSizer(wxHORIZONTAL);
	mid3hbox->Add(new wxStaticText(mid3panel,-1,wxT("Yazarlar")),1,wxEXPAND);
	bookauthors = new wxTextCtrl(mid3panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid3hbox->Add(bookauthors,0,wxALIGN_RIGHT);
	mid3panel->SetSizer(mid3hbox);
	vbox->Add(mid3panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid4panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid4hbox = new wxBoxSizer(wxHORIZONTAL);
	mid4hbox->Add(new wxStaticText(mid4panel,-1,wxT("Yayıncı")),1,wxEXPAND);
	bookpublisher = new wxTextCtrl(mid4panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid4hbox->Add(bookpublisher,0,wxALIGN_RIGHT);
	mid4panel->SetSizer(mid4hbox);
	vbox->Add(mid4panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid5panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid5hbox = new wxBoxSizer(wxHORIZONTAL);
	mid5hbox->Add(new wxStaticText(mid5panel,-1,wxT("Konu")),1,wxEXPAND);
	booksubject = new wxTextCtrl(mid5panel,-1,wxT(""),wxPoint(-1,-1),wxSize(360,-1));
	mid5hbox->Add(booksubject,0,wxALIGN_RIGHT);
	mid5panel->SetSizer(mid5hbox);
	vbox->Add(mid5panel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	
	wxPanel *mid6panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid6hbox = new wxBoxSizer(wxHORIZONTAL);
	mid6hbox->Add(new wxStaticText(mid6panel,-1,wxT(" ")),1,wxEXPAND);
	mid6hbox->Add(new wxStaticText(mid6panel,-1,wxT("Kitap için bir kapak seçin")),0,wxALIGN_CENTER|wxEXPAND);
	mid6hbox->Add(new wxStaticText(mid6panel,-1,wxT(" ")),1,wxEXPAND);
	mid6panel->SetSizer(mid6hbox);
	vbox->Add(mid6panel,1,wxALIGN_CENTER|wxEXPAND);
	
	vbox->Add(-1,10);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	wxImage::AddHandler(new wxJPEGHandler);
	wxBitmap genericCover_1(appLocation+wxT("resource/bookcovers/0.1.jpeg"),wxBITMAP_TYPE_JPEG);
	wxBitmap genericCover_2(appLocation+wxT("resource/bookcovers/0.2.jpeg"),wxBITMAP_TYPE_JPEG);
	wxBitmap genericCover_3(appLocation+wxT("resource/bookcovers/0.3.jpeg"),wxBITMAP_TYPE_JPEG);
	wxBitmap genericCover_4(appLocation+wxT("resource/bookcovers/0.4.jpeg"),wxBITMAP_TYPE_JPEG);
	wxBitmap genericCover_5(appLocation+wxT("resource/bookcovers/0.5.jpeg"),wxBITMAP_TYPE_JPEG);
	wxBitmap genericCover_6(appLocation+wxT("resource/bookcovers/0.6.jpeg"),wxBITMAP_TYPE_JPEG);
	
	vbox->Add(-1,10);
	wxPanel *mid7panel = new wxPanel(subpanel,-1,wxPoint(-1,-1),wxSize(420,100));
	wxBoxSizer *mid7hbox = new wxBoxSizer(wxHORIZONTAL);
	isbnCover_1 = new wxBitmapButton(mid7panel,ADDBOOK_DIALOG_COVER_1,genericCover_1,wxPoint(-1,-1),wxSize(80,100));
	mid7hbox->Add(isbnCover_1,1,wxEXPAND);
	mid7hbox->Add(new wxStaticText(mid7panel,-1,wxT(" ")),0,wxEXPAND);
	isbnCover_2 = new wxBitmapButton(mid7panel,ADDBOOK_DIALOG_COVER_2,genericCover_2,wxPoint(-1,-1),wxSize(80,100));
	mid7hbox->Add(isbnCover_2,1,wxEXPAND);
	mid7hbox->Add(new wxStaticText(mid7panel,-1,wxT(" ")),0,wxEXPAND);
	isbnCover_3 = new wxBitmapButton(mid7panel,ADDBOOK_DIALOG_COVER_3,genericCover_4,wxPoint(-1,-1),wxSize(80,100));
	mid7hbox->Add(isbnCover_3,1,wxEXPAND);
	mid7hbox->Add(new wxStaticText(mid7panel,-1,wxT(" ")),0,wxEXPAND);
	isbnCover_4 = new wxBitmapButton(mid7panel,ADDBOOK_DIALOG_COVER_4,genericCover_5,wxPoint(-1,-1),wxSize(80,100));
	mid7hbox->Add(isbnCover_4,1,wxEXPAND);
	mid7panel->SetSizer(mid7hbox);
	vbox->Add(mid7panel,0,wxALIGN_CENTER|wxEXPAND);
	
	vbox->Add(-1,5);
	
	wxPanel *mid8panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid8hbox = new wxBoxSizer(wxHORIZONTAL);
	mid8hbox->Add(new wxStaticText(mid8panel,-1,wxT("         ")),0,wxEXPAND);
	bookcover = new wxSlider(mid8panel,-1,1,1,4,wxPoint(-1,-1),wxSize(-1,-1),wxSL_AUTOTICKS|wxSL_TOP);
	mid8hbox->Add(bookcover,1,wxALIGN_CENTER|wxEXPAND);
	mid8hbox->Add(new wxStaticText(mid8panel,-1,wxT("         ")),0,wxEXPAND);
	mid8panel->SetSizer(mid8hbox);
	vbox->Add(mid8panel,1,wxALIGN_CENTER|wxEXPAND);
	
	vbox->Add(new wxStaticText(subpanel,-1,wxT("")),1,wxEXPAND);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	vbox->Add(new wxButton(subpanel,wxID_OK,wxT("Kaydet")),0,wxALIGN_BOTTOM|wxALIGN_RIGHT);
	vbox->Add(-1,10);
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);
	
	Connect(ADDBOOK_DIALOG_RETRIEVE,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(EkleKitap::ISBNRetrieve));
	Connect(ADDBOOK_DIALOG_COVER_1,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(EkleKitap::SetISBNCover1));
	Connect(ADDBOOK_DIALOG_COVER_2,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(EkleKitap::SetISBNCover2));
	Connect(ADDBOOK_DIALOG_COVER_3,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(EkleKitap::SetISBNCover3));
	Connect(ADDBOOK_DIALOG_COVER_4,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(EkleKitap::SetISBNCover4));
	
	Centre();
	
}

void EkleKitap::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void EkleKitap::ISBNRetrieve(wxCommandEvent& WXUNUSED(event))
{
	wxString isbncommand;
	isbncommand << wxT("php ") << appLocation << wxT("src/eklekitap.php '") << bookisbn->GetValue() << wxT("'");
	wxWindowDisabler disableAll;
	wxBusyInfo info(wxT("Detaylar çevrimiçi veritabanından getiriliyor!"), this);
	wxExecute(isbncommand,wxEXEC_SYNC);
	wxSQLite3Database *isbnretriever = new wxSQLite3Database();
	isbnretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxString isbnretrievesql;
	isbnretrievesql << wxT("SELECT * FROM book_retrieve WHERE isbn = '") << bookisbn->GetValue() << wxT("';");
	wxSQLite3ResultSet isbnretrieveSet = isbnretriever->ExecuteQuery(isbnretrievesql);
	booktitle->SetValue(isbnretrieveSet.GetAsString(wxT("title")));
	bookauthors->SetValue(isbnretrieveSet.GetAsString(wxT("authors")));
	bookpublisher->SetValue(isbnretrieveSet.GetAsString(wxT("publisher")));
	booksubject->SetValue(isbnretrieveSet.GetAsString(wxT("subject")));
	wxString cover1url;
	cover1url << appLocation << wxT("resource/bookcovers/") << bookisbn->GetValue() << wxT(".1.jpeg");
	wxBitmap cover1image(cover1url,wxBITMAP_TYPE_JPEG);
	isbnCover_1->SetBitmapLabel(cover1image);
	wxString cover2url;
	cover2url << appLocation << wxT("resource/bookcovers/") << bookisbn->GetValue() << wxT(".2.jpeg");
	wxBitmap cover2image(cover2url,wxBITMAP_TYPE_JPEG);
	isbnCover_2->SetBitmapLabel(cover2image);
	wxString cover3url;
	cover3url << appLocation << wxT("resource/bookcovers/") << bookisbn->GetValue() << wxT(".4.jpeg");
	wxBitmap cover3image(cover3url,wxBITMAP_TYPE_JPEG);
	isbnCover_3->SetBitmapLabel(cover3image);
	wxString cover4url;
	cover4url << appLocation << wxT("resource/bookcovers/") << bookisbn->GetValue() << wxT(".5.jpeg");
	wxBitmap cover4image(cover4url,wxBITMAP_TYPE_JPEG);
	isbnCover_4->SetBitmapLabel(cover4image);
	isbnretrieveSet.Finalize();
	isbnretriever->Close();
	delete isbnretriever;
}

void EkleKitap::SetISBNCover1(wxCommandEvent& WXUNUSED(event))
{
	bookcover->SetValue(1);
}

void EkleKitap::SetISBNCover2(wxCommandEvent& WXUNUSED(event))
{
	bookcover->SetValue(2);
}

void EkleKitap::SetISBNCover3(wxCommandEvent& WXUNUSED(event))
{
	bookcover->SetValue(3);
}

void EkleKitap::SetISBNCover4(wxCommandEvent& WXUNUSED(event))
{
	bookcover->SetValue(4);
}

wxString EkleKitap::GetNewBookISBN()
{
	return bookisbn->GetValue();
}

wxString EkleKitap::GetNewBookTitle()
{
	return booktitle->GetValue();
}

void EkleKitap::SaveBook()
{
	bookisbn->GetValue();
	booktitle->GetValue();
	bookauthors->GetValue();
	bookpublisher->GetValue();
	booksubject->GetValue();
	bookcover->GetValue();
}
