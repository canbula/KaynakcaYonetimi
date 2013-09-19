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

#include "bulisbn.h"
#include "md5.h"

BulISBN::BulISBN(const wxString& title,const wxString& pdfFile)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,500))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(srcLocation+wxT("resource/toolbar/barcode.png"),wxBITMAP_TYPE_PNG);
	wxBitmap searchButton(srcLocation+wxT("resource/toolbar/zoom.png"),wxBITMAP_TYPE_PNG);
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
	
	wxPanel *midhpanel = new wxPanel(subpanel,-1);
	wxBoxSizer *midhbox = new wxBoxSizer(wxHORIZONTAL);
	
	wxPanel *midvpanel = new wxPanel(midhpanel,-1);
	wxBoxSizer *midvbox = new wxBoxSizer(wxVERTICAL);
	
	wxPanel *mid1panel = new wxPanel(midvpanel,-1);
	wxBoxSizer *mid1hbox = new wxBoxSizer(wxHORIZONTAL);
	mid1hbox->Add(new wxStaticText(mid1panel,-1,wxT("Başlıca Yazarın Soyadı ")),1,wxEXPAND);
	srcauthor = new wxTextCtrl(mid1panel,-1,wxT(""),wxPoint(-1,-1),wxSize(260,-1));
	mid1hbox->Add(srcauthor,0,wxALIGN_RIGHT);
	mid1panel->SetSizer(mid1hbox);
	midvbox->Add(mid1panel,0,wxEXPAND);
	midvbox->Add(-1,10);
	wxPanel *mid2panel = new wxPanel(midvpanel,-1);
	wxBoxSizer *mid2hbox = new wxBoxSizer(wxHORIZONTAL);
	mid2hbox->Add(new wxStaticText(mid2panel,-1,wxT("Kitabın Adı ")),1,wxEXPAND);
	srctitle = new wxTextCtrl(mid2panel,-1,wxT(""),wxPoint(-1,-1),wxSize(260,-1));
	mid2hbox->Add(srctitle,0,wxALIGN_RIGHT);
	mid2panel->SetSizer(mid2hbox);
	midvbox->Add(mid2panel,0,wxEXPAND);
	
	midvpanel->SetSizer(midvbox);
	
	midhbox->Add(midvpanel,0,wxEXPAND);
	midhbox->Add(new wxStaticText(midhpanel,-1,wxT("")),1,wxEXPAND);
	midhbox->Add(new wxBitmapButton(midhpanel,FINDISBN_DIALOG_RETRIEVE,searchButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	
	midhpanel->SetSizer(midhbox);
	
	vbox->Add(midhpanel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	findisbnnb = new wxNotebook(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1));
	wxPanel *imgpanel = new wxPanel(findisbnnb,-1);
	wxBoxSizer *imghbox = new wxBoxSizer(wxHORIZONTAL);
	wxString isbnfrompdf = wxT("");
	wxString rawfrompdf = wxT("");
	if(pdfFile != wxT(""))
	{
		wxString convertimgcom;
		convertimgcom << wxT("convert -density 300x300 '") << pdfFile << wxT("[0]' -resize 480x '") << appLocation << wxT("files/newbook.png'");
		wxWindowDisabler disableAll;
		wxBusyInfo info(wxT("Kitap yükleniyor!"), this);
		wxExecute(convertimgcom,wxEXEC_SYNC);
		wxArrayString output;
		wxArrayString errors;
		wxString outputtype;
		wxString findisbnpdfcommand;
		findisbnpdfcommand << wxT("python ") << appLocation << wxT("src/bulisbnpdf.py '") << pdfFile << wxT("'");
		wxExecute(findisbnpdfcommand,output,errors,wxEXEC_SYNC);
		if(output.GetCount() > 0)
		{
			wxStringTokenizer outputtkz(output.Item(0),wxT(":"));
			int i=0;
			while(outputtkz.HasMoreTokens())
			{
				wxString outputtoken = outputtkz.GetNextToken();
				if(i==0) outputtype = outputtoken;
				if(i==1)
				{
					if(outputtype == wxT("meta"))
					{
						wxStringTokenizer isbnpdftkz(outputtoken,wxT(";"));
						int j=0;
						while(isbnpdftkz.HasMoreTokens())
						{
							wxString isbnpdftoken = isbnpdftkz.GetNextToken();
							if(j==0) srcauthor->SetValue(isbnpdftoken);
							if(j==1) srctitle->SetValue(isbnpdftoken);
							j=1;
						}
					}
					if(outputtype == wxT("isbn"))
					{
						isbnfrompdf = outputtoken;
					}
					if(outputtype == wxT("raw"))
					{
						rawfrompdf = outputtoken;
					}
				}
				i=1;
			}
		}
		tekerlipencere = new wxScrolledWindow(imgpanel,-1);
		wxBitmap imgofPdf(appLocation+wxT("files/newbook.png"),wxBITMAP_TYPE_PNG);
		wxStaticBitmap *tekericiresim = new wxStaticBitmap(tekerlipencere, -1, imgofPdf);
		int nWidth = imgofPdf.GetWidth();
		int nHeight = imgofPdf.GetHeight();
  		tekerlipencere->SetScrollbars(0, 10, 0, nHeight/10);
		tekerlipencere->SetBackgroundColour(wxColour(255,255,255));
		imghbox->Add(tekerlipencere,1,wxEXPAND);
	}
	imgpanel->SetSizer(imghbox);

	wxPanel *filpanel = new wxPanel(findisbnnb,-1);
	wxBoxSizer *filhbox = new wxBoxSizer(wxHORIZONTAL);
	findisbnlistcolumns = new wxArrayString();
	findisbnlistcolumndesc = new wxArrayString();
	int findisbnlistcolumnwidths[] = {100,100,80,210};
	findisbnlistcolumns->Add(wxT("isbn"));findisbnlistcolumndesc->Add(wxT("ISBN"));
	findisbnlistcolumns->Add(wxT("authors"));findisbnlistcolumndesc->Add(wxT("Yazarlar"));
	findisbnlistcolumns->Add(wxT("publisher"));findisbnlistcolumndesc->Add(wxT("Yayıncı"));
	findisbnlistcolumns->Add(wxT("title"));findisbnlistcolumndesc->Add(wxT("Kitap İsmi"));
	findisbnlist = new wxListView(filpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	for(int i=0;i<4;i++)
	{
		wxListItem findisbnlistcol;
		findisbnlistcol.SetId(i);
		findisbnlistcol.SetText(findisbnlistcolumndesc->Item(i));
		findisbnlist->InsertColumn(i,findisbnlistcol);
		findisbnlist->SetColumnWidth(i,findisbnlistcolumnwidths[i]);
	}
	if(isbnfrompdf != wxT(""))
	{
		wxListItem item;
		item.SetId(0);
		item.SetBackgroundColour(wxColour(255,205,205));
		findisbnlist->InsertItem(item);
		findisbnlist->SetItem(0,0,isbnfrompdf);
		findisbnlist->SetItem(0,1,wxT("-"));
		findisbnlist->SetItem(0,2,wxT("-"));
		findisbnlist->SetItem(0,3,wxT("PDF dosyasının içinde bulundu."));
	}
	filhbox->Add(findisbnlist,1,wxALIGN_CENTER|wxEXPAND);
	filpanel->SetSizer(filhbox);

	findisbnnb->AddPage(imgpanel,wxT("Kitap Önizleme"),true);
	findisbnnb->AddPage(filpanel,wxT("Arama Sonuçları"),false);
	if(rawfrompdf != wxT(""))
	{
		wxPanel *rawpanel = new wxPanel(findisbnnb,-1);
		wxBoxSizer *rawhbox = new wxBoxSizer(wxHORIZONTAL);
		rawfrompdf.Replace(wxT(";"),wxT("\n"));
		wxTextCtrl *rawtextctrl = new wxTextCtrl(rawpanel,-1,rawfrompdf,wxPoint(-1,-1),wxSize(-1,-1),wxTE_MULTILINE);
		rawhbox->Add(rawtextctrl,1,wxALIGN_CENTER|wxEXPAND);
		rawpanel->SetSizer(rawhbox);
		findisbnnb->AddPage(rawpanel,wxT("PDF Taraması"));
	}
	
	if(isbnfrompdf != wxT("") or pdfFile == wxT("")) findisbnnb->SetSelection(1);
	if(rawfrompdf != wxT("")) findisbnnb->SetSelection(2);
	vbox->Add(findisbnnb,1,wxEXPAND);

	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	
	wxPanel *bottompanel = new wxPanel(subpanel,-1);
	wxBoxSizer *bottomhbox = new wxBoxSizer(wxHORIZONTAL);
	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT("")),1,wxEXPAND);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_CANCEL,cancelButton),0,wxALIGN_BOTTOM|wxALIGN_RIGHT);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_OK,okButton),0,wxALIGN_BOTTOM|wxALIGN_RIGHT);
	bottompanel->SetSizer(bottomhbox);
	vbox->Add(bottompanel,0,wxEXPAND);
	
	vbox->Add(-1,10);
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);
	
	Connect(FINDISBN_DIALOG_RETRIEVE,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(BulISBN::FindISBNRetrieve));
	
	//Centre();
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

	findisbnlist->DeleteAllItems();
	wxString findisbnlistsql;
	findisbnlistsql << wxT("SELECT * FROM findisbn WHERE authortitle=='") << authortitle << wxT("';");
	vtcevap findisbnlistcevap;
	findisbnlistcevap = Vt(findisbnlistsql);
	for(int i=0;i<findisbnlistcevap.satir;i++)
	{
		wxListItem item;
		item.SetId(i);
		if(i%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		findisbnlist->InsertItem(item);
		findisbnlist->SetItem(i,0,findisbnlistcevap.sonuc.Item(i*findisbnlistcevap.sutun+1));
		findisbnlist->SetItem(i,1,findisbnlistcevap.sonuc.Item(i*findisbnlistcevap.sutun+2));
		findisbnlist->SetItem(i,2,findisbnlistcevap.sonuc.Item(i*findisbnlistcevap.sutun+3));
		findisbnlist->SetItem(i,3,findisbnlistcevap.sonuc.Item(i*findisbnlistcevap.sutun+4));
	}
	if(findisbnlist->GetItemCount() > 0)
		findisbnlist->RefreshItems(0,findisbnlist->GetItemCount()-1);
	findisbnnb->SetSelection(1);
}

wxString BulISBN::GetISBN()
{
	wxListItem item;
	item.SetId(findisbnlist->GetFocusedItem());
	item.SetColumn(0);
	findisbnlist->GetItem(item);
	return findisbnlist->GetItemText(item);
}
