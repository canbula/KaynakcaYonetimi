#ifndef _WXLIBS_H
#define _WXLIBS_H

//#include "<wx/wxprec.h>"
//#ifndef WX_PRECOMP
//	#include "<wx/wx.h>"
//#endif

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/arrstr.h>
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/busyinfo.h>
#include <wx/calctrl.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/colour.h>
#include <wx/datectrl.h>
#include <wx/datetime.h>
#include <wx/dialog.h>
#include <wx/dnd.h>
#include <wx/event.h>
#include <wx/filename.h>
#include <wx/gdicmn.h>
#include <wx/grid.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/mimetype.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>
#include <wx/statbmp.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/tokenzr.h>
#include <wx/toolbar.h>
#include <wx/utils.h>
#include <wx/wxhtml.h>
#include <wx/wxsqlite3.h>

const wxStandardPaths stdPath;

#ifdef __APPLE__
const wxString appLocation = wxT("");
#endif

#ifdef __LINUX__
const wxString appLocation = wxFileName(stdPath.GetExecutablePath()).GetPath()+wxT("/");
#endif

struct vtcevap
{
	int sutun;
	int satir;
	wxArrayString sonuc;
};

inline vtcevap Vt(const wxString& sqlstring)
{
	vtcevap vtsonuc;
	wxSQLite3Database *vtsonucretriever = new wxSQLite3Database();
	vtsonucretriever->Open(appLocation+wxT("db/Kaynakca.db"));
	wxSQLite3ResultSet vtsonucretrieveSet = vtsonucretriever->ExecuteQuery(sqlstring);
	vtsonuc.sutun = vtsonucretrieveSet.GetColumnCount();
	int j=0;
	while(vtsonucretrieveSet.NextRow())
	{
		for(int i=0;i<vtsonucretrieveSet.GetColumnCount();i++)
		{
			vtsonuc.sonuc.Add(vtsonucretrieveSet.GetAsString(i));
		}
		j++;
	}
	vtsonucretrieveSet.Finalize();
	vtsonucretriever->Close();
	vtsonuc.satir = j;
	delete vtsonucretriever;
	return vtsonuc;
}

inline void VtEkleSilGuncelle(const wxString& sqlstring,const wxArrayString& bindvalues)
{
	wxSQLite3Database *vtguncelleyici = new wxSQLite3Database();
	vtguncelleyici->Open(appLocation+wxT("db/Kaynakca.db"));
	wxSQLite3Statement vtguncelleyicisql = vtguncelleyici->PrepareStatement(sqlstring);
	for(int i=1;i<=bindvalues.GetCount();i++)
	{
		vtguncelleyicisql.Bind(i,bindvalues.Item(i-1));
	}
	vtguncelleyicisql.ExecuteUpdate();
	vtguncelleyicisql.ClearBindings();
	vtguncelleyicisql.Reset();
	vtguncelleyici->Close();
	delete vtguncelleyici;
}

#endif
