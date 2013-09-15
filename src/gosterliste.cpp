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
	displaymodes.Add(wxT("BibTeX"));
	displaymodes.Add(wxT("XML (MODS)"));
	displaymodes.Add(wxT("XML (MS Word/OpenOffice)"));
	displaymodes.Add(wxT("RIS"));
	displaymodes.Add(wxT("EndNote"));
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

void GosterListe::CiktiVer()
{
	if(displaymode->GetSelection() > 0 and displaymode->GetSelection() < 5)
	{
		wxString listsql;
		listsql << wxT("SELECT * FROM lists WHERE id=='") << *listid << wxT("'");
		vtcevap listcevap;
		listcevap = Vt(listsql);
		wxString listeciktidosyasi = appLocation+wxT("files/list.")+*listid+wxT(".");
		if(displaymode->GetSelection() == 1) listeciktidosyasi << wxT("txt");
		if(displaymode->GetSelection() == 2) listeciktidosyasi << wxT("tex");
		if(displaymode->GetSelection() > 2) listeciktidosyasi << wxT("bib");
		wxTextFile listeciktisi(listeciktidosyasi);
		if(listeciktisi.Exists())
		{
			listeciktisi.Open();
		}
		else
		{
			listeciktisi.Create();
		}
		listeciktisi.Clear();
		wxString listoutputsql;
		listoutputsql << wxT("SELECT * FROM listrefs WHERE listid=='") << *listid << wxT("' ORDER BY number ASC");
		vtcevap listoutputcevap;
		listoutputcevap = Vt(listoutputsql);
		wxString firstline;
		if(displaymode->GetSelection() == 2) firstline << wxT("\\begin{thebibliography}{") << listoutputcevap.satir << wxT("}");
		if(displaymode->GetSelection() == 2) listeciktisi.AddLine(firstline);
		wxString ciktisatiri;
		for(int i=0;i<listoutputcevap.satir;i++)
		{
			ciktisatiri = listcevap.sonuc.Item(3);
			wxString listoutputitemsql;
			vtcevap listoutputitemcevap;
			wxString refidstring;
			if(listoutputcevap.sonuc.Item(i*listoutputcevap.sutun+2) == wxT("book"))
			{
				listoutputitemsql << wxT("SELECT * FROM books WHERE isbn=='") << listoutputcevap.sonuc.Item(i*listoutputcevap.sutun+3) << wxT("'");
				listoutputitemcevap = Vt(listoutputitemsql);
				ciktisatiri.Replace(wxT("{cilt}"),wxT(""));
				ciktisatiri.Replace(wxT("({sayı})"),wxT(""));
				ciktisatiri.Replace(wxT("{sayı}"),wxT(""));
				ciktisatiri.Replace(wxT("{ilksayfa-sonsayfa}"),wxT(""));
				ciktisatiri.Replace(wxT("{ilksayfa}"),wxT(""));
				ciktisatiri.Replace(wxT("{sonsayfa}"),wxT(""));
				ciktisatiri.Replace(wxT("({yıl})"),wxT(""));
				ciktisatiri.Replace(wxT("{yıl}"),wxT(""));
				refidstring << wxT("\\bibitem{") << listoutputitemcevap.sonuc.Item(5) << wxT("}");
				if(displaymode->GetSelection() > 2)
				{
					listeciktisi.AddLine(wxT("@Book{")+listoutputitemcevap.sonuc.Item(5)+wxT(","));
					listeciktisi.AddLine(wxT("author    = {")+listoutputitemcevap.sonuc.Item(2)+wxT("},"));
					listeciktisi.AddLine(wxT("title     = {")+listoutputitemcevap.sonuc.Item(1)+wxT("},"));
					listeciktisi.AddLine(wxT("publisher = {")+listoutputitemcevap.sonuc.Item(3)+wxT("},"));
					listeciktisi.AddLine(wxT("year      = {},"));
					listeciktisi.AddLine(wxT("}"));
				}
			}
			if(listoutputcevap.sonuc.Item(i*listoutputcevap.sutun+2) == wxT("paper"))
			{
				listoutputitemsql << wxT("SELECT * FROM papers WHERE doi=='") << listoutputcevap.sonuc.Item(i*listoutputcevap.sutun+3) << wxT("'");
				listoutputitemcevap = Vt(listoutputitemsql);
				ciktisatiri.Replace(wxT("{cilt}"),listoutputitemcevap.sonuc.Item(4));
				if(listoutputitemcevap.sonuc.Item(5) == wxT(""))
				{
					ciktisatiri.Replace(wxT("({sayı})"),wxT(""));
				}
				else
				{
					ciktisatiri.Replace(wxT("{sayı}"),listoutputitemcevap.sonuc.Item(5));
				}
				ciktisatiri.Replace(wxT("{ilksayfa}"),listoutputitemcevap.sonuc.Item(6));
				ciktisatiri.Replace(wxT("{ilksayfa"),listoutputitemcevap.sonuc.Item(6));
				ciktisatiri.Replace(wxT("{sonsayfa}"),listoutputitemcevap.sonuc.Item(7));
				wxString ilksonsayfa;
				if(listoutputitemcevap.sonuc.Item(7) == wxT(""))
				{
					ilksonsayfa << listoutputitemcevap.sonuc.Item(6);
					ciktisatiri.Replace(wxT("-sonsayfa}"),wxT(""));
				}
				else
				{
					ilksonsayfa << listoutputitemcevap.sonuc.Item(6) << wxT("-") << listoutputitemcevap.sonuc.Item(7);
					ciktisatiri.Replace(wxT("sonsayfa}"),listoutputitemcevap.sonuc.Item(7));
				}
				ciktisatiri.Replace(wxT("{yıl}"),listoutputitemcevap.sonuc.Item(8).Mid(0,4));
				refidstring << wxT("\\bibitem{") << listoutputitemcevap.sonuc.Item(11) << wxT("}");
				if(displaymode->GetSelection() > 2)
				{
					listeciktisi.AddLine(wxT("@Article{")+listoutputitemcevap.sonuc.Item(11)+wxT(","));
					listeciktisi.AddLine(wxT("author    = {")+listoutputitemcevap.sonuc.Item(2)+wxT("},"));
					listeciktisi.AddLine(wxT("title     = {")+listoutputitemcevap.sonuc.Item(1)+wxT("},"));
					listeciktisi.AddLine(wxT("journal   = {")+listoutputitemcevap.sonuc.Item(3)+wxT("},"));
					listeciktisi.AddLine(wxT("year      = {")+listoutputitemcevap.sonuc.Item(8).Mid(0,4)+wxT("},"));
					listeciktisi.AddLine(wxT("volume    = {")+listoutputitemcevap.sonuc.Item(4)+wxT("},"));
					listeciktisi.AddLine(wxT("number    = {")+listoutputitemcevap.sonuc.Item(5)+wxT("},"));
					listeciktisi.AddLine(wxT("pages     = {")+ilksonsayfa+wxT("},"));
					listeciktisi.AddLine(wxT("month     = {")+listoutputitemcevap.sonuc.Item(8).Mid(5,2)+wxT("},"));
					listeciktisi.AddLine(wxT("url       = {")+listoutputitemcevap.sonuc.Item(9)+wxT("},"));
					listeciktisi.AddLine(wxT("}"));
				}
			}
			ciktisatiri.Replace(wxT("{başlık}"),listoutputitemcevap.sonuc.Item(1));
			ciktisatiri.Replace(wxT("{yazarlar}"),listoutputitemcevap.sonuc.Item(2));
			ciktisatiri.Replace(wxT("{yayıncı}"),listoutputitemcevap.sonuc.Item(3));
			ciktisatiri.Replace(wxT(" {yenisatır} "),wxT("\n"));
			if(displaymode->GetSelection() == 2) listeciktisi.AddLine(refidstring);
			if(displaymode->GetSelection() == 1 or displaymode->GetSelection() == 2) listeciktisi.AddLine(ciktisatiri);
		}
		if(displaymode->GetSelection() == 2) listeciktisi.AddLine(wxT("\\end{thebibliography}"));
		listeciktisi.Write();
		listeciktisi.Close();
		if(displaymode->GetSelection() < 4)
		{
			wxFileDialog *filesaveas = new wxFileDialog(this,wxT("Çıktı dosyasını kaydedin.."),wxT(""),wxT(""),wxT("*.txt;*.tex;*.bib"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
			filesaveas->SetPath(listeciktidosyasi);
			if(filesaveas->ShowModal() == wxID_OK)
			{
				wxCopyFile(listeciktidosyasi,filesaveas->GetPath());
			}
			/*
			wxString showoutputcommand;
			if(platform==wxT("linux"))
				showoutputcommand << wxT("xdg-open '") << listeciktidosyasi << wxT("'");
			if(platform==wxT("apple"))
			{
				showoutputcommand << wxT("open '") << listeciktidosyasi << wxT("'");
				showoutputcommand.Replace(wxT("//"),wxT("/"));
			}
			wxExecute(showoutputcommand);
			*/
		}
	}
	if(displaymode->GetSelection() == 4)
	{
		wxString listeciktidosyasi = appLocation+wxT("files/list.")+*listid+wxT(".bib");
		wxString listeciktidosyasi2 = appLocation+wxT("files/list.")+*listid+wxT(".mods.xml");
		wxString convertcommand = wxT("sh -c \"bib2xml '")+listeciktidosyasi+wxT("' > '")+listeciktidosyasi2+wxT("'\"");
		wxExecute(convertcommand,wxEXEC_SYNC);
		wxFileDialog *filesaveas = new wxFileDialog(this,wxT("Çıktı dosyasını kaydedin.."),wxT(""),wxT(""),wxT("*.xml"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
		filesaveas->SetPath(listeciktidosyasi2);
		if(filesaveas->ShowModal() == wxID_OK)
		{
			wxCopyFile(listeciktidosyasi2,filesaveas->GetPath());
		}
		/*
		wxString showoutputcommand;
		if(platform==wxT("linux"))
			showoutputcommand << wxT("xdg-open '") << listeciktidosyasi2 << wxT("'");
		if(platform==wxT("apple"))
		{
			showoutputcommand << wxT("open '") << listeciktidosyasi2 << wxT("'");
			showoutputcommand.Replace(wxT("//"),wxT("/"));
		}
		wxExecute(showoutputcommand);
		*/
	}
	if(displaymode->GetSelection() == 5)
	{
		wxString listeciktidosyasi = appLocation+wxT("files/list.")+*listid+wxT(".bib");
		wxString listeciktidosyasi2 = appLocation+wxT("files/list.")+*listid+wxT(".mods.xml");
		wxString listeciktidosyasi3 = appLocation+wxT("files/list.")+*listid+wxT(".xml");
		wxString convertcommand = wxT("sh -c \"bib2xml '")+listeciktidosyasi+wxT("' > '")+listeciktidosyasi2+wxT("'\"");
		wxExecute(convertcommand,wxEXEC_SYNC);
		convertcommand = wxT("sh -c \"xml2wordbib '")+listeciktidosyasi2+wxT("' > '")+listeciktidosyasi3+wxT("'\"");
		wxExecute(convertcommand,wxEXEC_SYNC);
		wxFileDialog *filesaveas = new wxFileDialog(this,wxT("Çıktı dosyasını kaydedin.."),wxT(""),wxT(""),wxT("*.xml"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
		filesaveas->SetPath(listeciktidosyasi3);
		if(filesaveas->ShowModal() == wxID_OK)
		{
			wxCopyFile(listeciktidosyasi3,filesaveas->GetPath());
		}
		/*
		wxString showoutputcommand;
		if(platform==wxT("linux"))
			showoutputcommand << wxT("xdg-open '") << listeciktidosyasi3 << wxT("'");
		if(platform==wxT("apple"))
		{
			showoutputcommand << wxT("open '") << listeciktidosyasi3 << wxT("'");
			showoutputcommand.Replace(wxT("//"),wxT("/"));
		}
		wxExecute(showoutputcommand);
		*/
	}
	if(displaymode->GetSelection() == 6)
	{
		wxString listeciktidosyasi = appLocation+wxT("files/list.")+*listid+wxT(".bib");
		wxString listeciktidosyasi2 = appLocation+wxT("files/list.")+*listid+wxT(".mods.xml");
		wxString listeciktidosyasi3 = appLocation+wxT("files/list.")+*listid+wxT(".ris");
		wxString convertcommand = wxT("sh -c \"bib2xml '")+listeciktidosyasi+wxT("' > '")+listeciktidosyasi2+wxT("'\"");
		wxExecute(convertcommand,wxEXEC_SYNC);
		convertcommand = wxT("sh -c \"xml2ris '")+listeciktidosyasi2+wxT("' > '")+listeciktidosyasi3+wxT("'\"");
		wxExecute(convertcommand,wxEXEC_SYNC);
		wxFileDialog *filesaveas = new wxFileDialog(this,wxT("Çıktı dosyasını kaydedin.."),wxT(""),wxT(""),wxT("*.ris"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
		filesaveas->SetPath(listeciktidosyasi3);
		if(filesaveas->ShowModal() == wxID_OK)
		{
			wxCopyFile(listeciktidosyasi3,filesaveas->GetPath());
		}
		/*
		wxString showoutputcommand;
		if(platform==wxT("linux"))
			showoutputcommand << wxT("xdg-open '") << listeciktidosyasi3 << wxT("'");
		if(platform==wxT("apple"))
		{
			showoutputcommand << wxT("open '") << listeciktidosyasi3 << wxT("'");
			showoutputcommand.Replace(wxT("//"),wxT("/"));
		}
		wxExecute(showoutputcommand);
		*/
	}
	if(displaymode->GetSelection() == 7)
	{
		wxString listeciktidosyasi = appLocation+wxT("files/list.")+*listid+wxT(".bib");
		wxString listeciktidosyasi2 = appLocation+wxT("files/list.")+*listid+wxT(".mods.xml");
		wxString listeciktidosyasi3 = appLocation+wxT("files/list.")+*listid+wxT(".enl");
		wxString convertcommand = wxT("sh -c \"bib2xml '")+listeciktidosyasi+wxT("' > '")+listeciktidosyasi2+wxT("'\"");
		wxExecute(convertcommand,wxEXEC_SYNC);
		convertcommand = wxT("sh -c \"xml2end '")+listeciktidosyasi2+wxT("' > '")+listeciktidosyasi3+wxT("'\"");
		wxExecute(convertcommand,wxEXEC_SYNC);
		wxFileDialog *filesaveas = new wxFileDialog(this,wxT("Çıktı dosyasını kaydedin.."),wxT(""),wxT(""),wxT("*.enl"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
		filesaveas->SetPath(listeciktidosyasi3);
		if(filesaveas->ShowModal() == wxID_OK)
		{
			wxCopyFile(listeciktidosyasi3,filesaveas->GetPath());
		}
		/*
		wxString showoutputcommand;
		if(platform==wxT("linux"))
			showoutputcommand << wxT("xdg-open '") << listeciktidosyasi3 << wxT("'");
		if(platform==wxT("apple"))
		{
			showoutputcommand << wxT("open '") << listeciktidosyasi3 << wxT("'");
			showoutputcommand.Replace(wxT("//"),wxT("/"));
		}
		wxExecute(showoutputcommand);
		*/
	}
	if(displaymode->GetSelection() == 8)
	{
		wxString listeciktidosyasi = appLocation+wxT("files/list.")+*listid+wxT(".tar");
		wxString createtarcommand = wxT("tar -cf ");
		createtarcommand << wxT("'") << listeciktidosyasi << wxT("' --directory=") << appLocation << wxT("files");
		wxString createtarsql;
		createtarsql << wxT("SELECT * FROM listrefs WHERE listid=='") << *listid << wxT("' ORDER BY number ASC");
		vtcevap createtarcevap;
		createtarcevap = Vt(createtarsql);
		for(int i=0;i<createtarcevap.satir;i++)
		{
			wxString dosyaid = createtarcevap.sonuc.Item(i*createtarcevap.sutun+3);
			dosyaid.Replace(wxT("/"),wxT("|"));
			wxString dosyakontrolcommand;
			if(platform==wxT("linux"))
				dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name ") << dosyaid << wxT(".*");
			if(platform==wxT("apple"))
				dosyakontrolcommand << wxT("find ") << appLocation << wxT("files/ -name '") << dosyaid << wxT(".*'");
			wxArrayString output;
			wxArrayString errors;
			wxExecute(dosyakontrolcommand,output,errors,wxEXEC_SYNC);
			if(output.GetCount() > 0)
			{
				if(wxFileExists(output.Item(0)))
				{
					wxFileName refdosya(output.Item(0));
					createtarcommand << wxT(" '") << refdosya.GetFullName() << wxT("'");
				}
			}
		}
		wxExecute(createtarcommand,wxEXEC_SYNC);
		wxFileDialog *filesaveas = new wxFileDialog(this,wxT("Çıktı dosyasını kaydedin.."),wxT(""),wxT(""),wxT("*.tar"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
		filesaveas->SetPath(listeciktidosyasi);
		if(filesaveas->ShowModal() == wxID_OK)
		{
			wxCopyFile(listeciktidosyasi,filesaveas->GetPath());
		}
		/*
		wxString showoutputcommand;
		if(platform==wxT("linux"))
			showoutputcommand << wxT("xdg-open '") << listeciktidosyasi << wxT("'");
		if(platform==wxT("apple"))
		{
			showoutputcommand << wxT("open '") << listeciktidosyasi << wxT("'");
			showoutputcommand.Replace(wxT("//"),wxT("/"));
		}
		wxExecute(showoutputcommand);
		*/
	}
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
