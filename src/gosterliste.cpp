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

#include "gosterliste.h"

GosterListe::GosterListe(const wxString& title,wxString id)
	: wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,500))
{
	listid = &id;
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap dialogLogo(appLocation+wxT("resource/toolbar/list2.png"),wxBITMAP_TYPE_PNG);
	wxBitmap upButton(appLocation+wxT("resource/toolbar/arrow_up.png"),wxBITMAP_TYPE_PNG);
	wxBitmap downButton(appLocation+wxT("resource/toolbar/arrow_down.png"),wxBITMAP_TYPE_PNG);
	wxBitmap sortButton(appLocation+wxT("resource/toolbar/arrow_bidirectional.png"),wxBITMAP_TYPE_PNG);
	wxBitmap removeButton(appLocation+wxT("resource/toolbar/cancel.png"),wxBITMAP_TYPE_PNG);
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
	listname = new wxStaticText(toppanel, -1, wxT(""));
	wxFont font = listname->GetFont();
	font.SetPointSize(18);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	listname->SetFont(font);
	tophbox->Add(listname,1,wxALIGN_BOTTOM|wxEXPAND);
	wxStaticBitmap *dialoglogo = new wxStaticBitmap(toppanel,-1,dialogLogo);
	tophbox->Add(dialoglogo,0,wxALIGN_RIGHT);
	toppanel->SetSizer(tophbox);
	vbox->Add(toppanel,0,wxEXPAND);

	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	vbox->Add(-1,10);
	wxPanel *mid0panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid0hbox = new wxBoxSizer(wxHORIZONTAL);
	mid0hbox->Add(new wxBitmapButton(mid0panel,ID_SHOWLIST_UP,upButton),0,wxALIGN_LEFT);
	mid0hbox->Add(new wxBitmapButton(mid0panel,ID_SHOWLIST_DOWN,downButton),0,wxALIGN_LEFT);
	mid0hbox->Add(new wxBitmapButton(mid0panel,ID_SHOWLIST_SORT,sortButton),0,wxALIGN_LEFT);
	mid0hbox->Add(new wxStaticText(mid0panel,-1,wxT("")),1,wxEXPAND);
	mid0hbox->Add(new wxBitmapButton(mid0panel,ID_SHOWLIST_REMOVE,removeButton),0,wxALIGN_RIGHT);
	mid0panel->SetSizer(mid0hbox);
	vbox->Add(mid0panel,0,wxEXPAND);

	wxPanel *mid1panel = new wxPanel(subpanel,-1);
	wxBoxSizer *mid1hbox = new wxBoxSizer(wxHORIZONTAL);
	
	showlistcolumns = new wxArrayString();
	showlistcolumndesc = new wxArrayString();
	int showlistcolumnwidths[] = {0,40,80,240,120};
	showlistcolumns->Add(wxT("id"));showlistcolumndesc->Add(wxT("Id"));
	showlistcolumns->Add(wxT("order"));showlistcolumndesc->Add(wxT("Sıra"));
	showlistcolumns->Add(wxT("isbndoi"));showlistcolumndesc->Add(wxT("ISBN/DOI"));
	showlistcolumns->Add(wxT("title"));showlistcolumndesc->Add(wxT("Başlık"));
	showlistcolumns->Add(wxT("authors"));showlistcolumndesc->Add(wxT("Yazar"));
	showlist = new wxListView(mid1panel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLC_REPORT|wxLC_HRULES|wxLC_SINGLE_SEL);
	for(int i=0;i<5;i++)
	{
		wxListItem showlistcol;
		showlistcol.SetId(i);
		showlistcol.SetText(showlistcolumndesc->Item(i));
		showlist->InsertColumn(i,showlistcol);
		showlist->SetColumnWidth(i,showlistcolumnwidths[i]);
	}
	GosterListe::ListeyiYukle();
	mid1hbox->Add(showlist,1,wxALIGN_CENTER|wxEXPAND);

	mid1panel->SetSizer(mid1hbox);
	vbox->Add(mid1panel,1,wxEXPAND);
	
	vbox->Add(-1,10);
	
	vbox->Add(new wxStaticLine(subpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	vbox->Add(-1,10);
	
	wxPanel *bottompanel = new wxPanel(subpanel,-1);
	wxBoxSizer *bottomhbox = new wxBoxSizer(wxHORIZONTAL);

	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT(" ")),0,wxEXPAND);
	wxArrayString displaymodes;
	displaymodes.Add(wxT("Gösterim Modu"));
	displaymodes.Add(wxT("Düz Metin"));
	displaymodes.Add(wxT("LaTeX"));
	displaymodes.Add(wxT("OpenOffice"));
	displaymodes.Add(wxT("Dosya Paketi"));
	displaymode = new wxChoice(bottompanel,-1,wxPoint(-1,-1),wxSize(150,-1),displaymodes);
	bottomhbox->Add(displaymode,0,wxEXPAND);

	bottomhbox->Add(new wxStaticText(bottompanel,-1,wxT("")),1,wxEXPAND);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_CANCEL,cancelButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	bottomhbox->Add(new wxBitmapButton(bottompanel,wxID_OK,okButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	bottompanel->SetSizer(bottomhbox);
	vbox->Add(bottompanel,0,wxEXPAND);
	
	subpanel->SetSizer(vbox);
	hbox->Add(subpanel,1,wxEXPAND);
	hbox->Add(new wxStaticText(panel,-1,wxT(" ")),0,wxEXPAND);
	panel->SetSizer(hbox);

	Connect(ID_SHOWLIST_UP,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(GosterListe::UsteCikar));
	Connect(ID_SHOWLIST_DOWN,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(GosterListe::AltaIndir));
	Connect(ID_SHOWLIST_SORT,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(GosterListe::OtoSirala));
	Connect(ID_SHOWLIST_REMOVE,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(GosterListe::RefKaldir));
	Connect(showlist->GetId(),wxEVT_COMMAND_LIST_ITEM_ACTIVATED,wxListEventHandler(GosterListe::OgeyeGozAt));
	
	//Centre();

	if(id != wxT(""))
		GosterListe::SayfayiHazirla();
}

void GosterListe::ListeyiYukle()
{
	showlist->DeleteAllItems();
	wxString showlistsql;
	showlistsql << wxT("SELECT * FROM listrefs WHERE listid=='") << *listid << wxT("' ORDER BY number ASC");
	vtcevap showlistcevap;
	showlistcevap = Vt(showlistsql);
	for(int i=0;i<showlistcevap.satir;i++)
	{
		wxListItem item;
		item.SetId(i);
		if(i%2==1) item.SetBackgroundColour(wxColour(245,245,255));
		showlist->InsertItem(item);
		showlist->SetItem(i,0,showlistcevap.sonuc.Item(i*showlistcevap.sutun+3));
		showlist->SetItem(i,1,showlistcevap.sonuc.Item(i*showlistcevap.sutun+1));
		showlist->SetItem(i,2,showlistcevap.sonuc.Item(i*showlistcevap.sutun+3));
		if(showlistcevap.sonuc.Item(i*showlistcevap.sutun+2) == wxT("book"))
		{
			wxString showlistitemsql;
			showlistitemsql << wxT("SELECT * FROM books WHERE isbn=='") << showlistcevap.sonuc.Item(i*showlistcevap.sutun+3) << wxT("'");
			vtcevap showlistitemcevap;
			showlistitemcevap = Vt(showlistitemsql);
			showlist->SetItem(i,3,showlistitemcevap.sonuc.Item(1));
			showlist->SetItem(i,4,showlistitemcevap.sonuc.Item(2));
			if(showlistitemcevap.sonuc.Item(7)==wxT("Sarı")) showlist->SetItemBackgroundColour(item,wxColour(255,255,200));
			if(showlistitemcevap.sonuc.Item(7)==wxT("Kırmızı")) showlist->SetItemBackgroundColour(item,wxColour(255,200,200));
			if(showlistitemcevap.sonuc.Item(7)==wxT("Yeşil")) showlist->SetItemBackgroundColour(item,wxColour(200,255,200));
			if(showlistitemcevap.sonuc.Item(7)==wxT("Mavi")) showlist->SetItemBackgroundColour(item,wxColour(200,200,255));
		}
		if(showlistcevap.sonuc.Item(i*showlistcevap.sutun+2) == wxT("paper"))
		{
			wxString showlistitemsql;
			showlistitemsql << wxT("SELECT * FROM papers WHERE doi=='") << showlistcevap.sonuc.Item(i*showlistcevap.sutun+3) << wxT("'");
			vtcevap showlistitemcevap;
			showlistitemcevap = Vt(showlistitemsql);
			showlist->SetItem(i,3,showlistitemcevap.sonuc.Item(1));
			showlist->SetItem(i,4,showlistitemcevap.sonuc.Item(2));
			if(showlistitemcevap.sonuc.Item(13)==wxT("Sarı")) showlist->SetItemBackgroundColour(item,wxColour(255,255,200));
			if(showlistitemcevap.sonuc.Item(13)==wxT("Kırmızı")) showlist->SetItemBackgroundColour(item,wxColour(255,200,200));
			if(showlistitemcevap.sonuc.Item(13)==wxT("Yeşil")) showlist->SetItemBackgroundColour(item,wxColour(200,255,200));
			if(showlistitemcevap.sonuc.Item(13)==wxT("Mavi")) showlist->SetItemBackgroundColour(item,wxColour(200,200,255));
		}
	}
	if(showlist->GetItemCount() > 0)
		showlist->RefreshItems(0,showlist->GetItemCount()-1);
}

void GosterListe::SayfayiHazirla()
{
	wxString preparesql;
	preparesql << wxT("SELECT * FROM lists WHERE id == '") << *listid << wxT("';");
	vtcevap preparecevap;
	preparecevap = Vt(preparesql);
	listname->SetLabel(preparecevap.sonuc.Item(1));
}

void GosterListe::SirayiYenile()
{
	wxString numberupdatesql;
	numberupdatesql << wxT("SELECT * FROM listrefs WHERE listid=='") << *listid << wxT("' ORDER BY number ASC");
	vtcevap numberupdatecevap;
	numberupdatecevap = Vt(numberupdatesql);
	for(int i=0;i<numberupdatecevap.satir;i++)
	{
		wxArrayString numberupdate;
		numberupdate.Add(wxString::Format(wxT("%03d"),i+1));
		numberupdate.Add(*listid);
		numberupdate.Add(numberupdatecevap.sonuc.Item(i*numberupdatecevap.sutun+3));
		VtEkleSilGuncelle(wxT("UPDATE listrefs SET number=? WHERE listid==? AND isbndoi==?"),numberupdate);
	}
	GosterListe::ListeyiYukle();
}

void GosterListe::OgeyeGozAt(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxListItem item;
	item.SetId(showlist->GetFocusedItem());
	item.SetColumn(0);
	showlist->GetItem(item);
	wxString dosyaisbndoi = showlist->GetItemText(item);
	dosyaisbndoi.Replace(wxT("/"),wxT("|"));
	wxString dosyakontrolcommand;
	if(platform==wxT("linux"))
		dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name ") << dosyaisbndoi << wxT(".*");
	if(platform==wxT("apple"))
		dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name '") << dosyaisbndoi << wxT(".*'");
	wxArrayString output;
	wxArrayString errors;
	wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
	if(output.GetCount() > 0)
	{
		if(wxFileExists(output.Item(0)))
		{
			wxString openfilecommand;
			if(platform==wxT("linux"))
				openfilecommand << wxT("xdg-open '") << output.Item(0) << wxT("'");
			if(platform==wxT("apple"))
			{
				openfilecommand << wxT("open '") << output.Item(0) << wxT("'");
				openfilecommand.Replace(wxT("//"),wxT("/"));
			}
			wxExecute(openfilecommand);
		}
		else
		{
			wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu öğe ile ilişkili bir dosya bulunmuyor."),wxT("Dosya Bulunamadı"),wxOK);
			dial->ShowModal();
		}
	}
	else
	{
		wxMessageDialog *dial = new wxMessageDialog(this,wxT("Sistemde bu öğe ile ilişkili bir dosya bulunmuyor."),wxT("Dosya Bulunamadı"),wxOK);
		dial->ShowModal();
	}
}

void GosterListe::UsteCikar(wxCommandEvent& event)
{
	wxListItem item;
	item.SetId(showlist->GetFocusedItem());
	item.SetColumn(0);
	showlist->GetItem(item);
	wxString numberupdatesql;
	numberupdatesql << wxT("SELECT * FROM listrefs WHERE listid=='") << *listid << wxT("' ORDER BY number DESC");
	vtcevap numberupdatecevap;
	numberupdatecevap = Vt(numberupdatesql);
	int j=0;
	int k=0;
	for(int i=0;i<numberupdatecevap.satir;i++)
	{
		k = numberupdatecevap.satir - i;
		if(j==1)
		{
			wxArrayString numberupdate;
			numberupdate.Add(wxString::Format(wxT("%03d"),k+1));
			numberupdate.Add(*listid);
			numberupdate.Add(numberupdatecevap.sonuc.Item(i*numberupdatecevap.sutun+3));
			VtEkleSilGuncelle(wxT("UPDATE listrefs SET number=? WHERE listid==? AND isbndoi==?"),numberupdate);
			j=0;
		}
		if(numberupdatecevap.sonuc.Item(i*numberupdatecevap.sutun+3) == showlist->GetItemText(item) && k != 1)
		{
			wxArrayString numberupdate;
			numberupdate.Add(wxString::Format(wxT("%03d"),k-1));
			numberupdate.Add(*listid);
			numberupdate.Add(numberupdatecevap.sonuc.Item(i*numberupdatecevap.sutun+3));
			VtEkleSilGuncelle(wxT("UPDATE listrefs SET number=? WHERE listid==? AND isbndoi==?"),numberupdate);
			j=1;
		}
	}
	GosterListe::ListeyiYukle();
}

void GosterListe::AltaIndir(wxCommandEvent& event)
{
	wxListItem item;
	item.SetId(showlist->GetFocusedItem());
	item.SetColumn(0);
	showlist->GetItem(item);
	wxString numberupdatesql;
	numberupdatesql << wxT("SELECT * FROM listrefs WHERE listid=='") << *listid << wxT("' ORDER BY number ASC");
	vtcevap numberupdatecevap;
	numberupdatecevap = Vt(numberupdatesql);
	int j=0;
	for(int i=0;i<numberupdatecevap.satir;i++)
	{
		if(j==1)
		{
			wxArrayString numberupdate;
			numberupdate.Add(wxString::Format(wxT("%03d"),i));
			numberupdate.Add(*listid);
			numberupdate.Add(numberupdatecevap.sonuc.Item(i*numberupdatecevap.sutun+3));
			VtEkleSilGuncelle(wxT("UPDATE listrefs SET number=? WHERE listid==? AND isbndoi==?"),numberupdate);
			j=0;
		}
		if(numberupdatecevap.sonuc.Item(i*numberupdatecevap.sutun+3) == showlist->GetItemText(item) && i != (numberupdatecevap.satir-1))
		{
			wxArrayString numberupdate;
			numberupdate.Add(wxString::Format(wxT("%03d"),i+2));
			numberupdate.Add(*listid);
			numberupdate.Add(numberupdatecevap.sonuc.Item(i*numberupdatecevap.sutun+3));
			VtEkleSilGuncelle(wxT("UPDATE listrefs SET number=? WHERE listid==? AND isbndoi==?"),numberupdate);
			j=1;
		}
	}
	GosterListe::ListeyiYukle();
}

void GosterListe::OtoSirala(wxCommandEvent& event)
{
	GosterListe::SirayiYenile();
}

void GosterListe::RefKaldir(wxCommandEvent& event)
{
	wxListItem item;
	item.SetId(showlist->GetFocusedItem());
	item.SetColumn(0);
	showlist->GetItem(item);
	wxArrayString listrefremove;
	listrefremove.Add(*listid);
	listrefremove.Add(showlist->GetItemText(item));
	VtEkleSilGuncelle(wxT("DELETE FROM listrefs WHERE listid==? AND isbndoi==?"),listrefremove);
	GosterListe::SirayiYenile();
}
