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
#include <wx/choice.h>
#include <wx/colour.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/filename.h>
#include <wx/gdicmn.h>
#include <wx/grid.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/splitter.h>
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

#endif
