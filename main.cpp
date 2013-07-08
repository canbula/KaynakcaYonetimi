#include "main.h"
#include "kaynakcayonetimi.h"

IMPLEMENT_APP(KaynakcaYonetimiApp)

bool KaynakcaYonetimiApp::OnInit()
{
	KaynakcaYonetimi *kaynakcayonetimi = new KaynakcaYonetimi(wxT("Kaynakça Yönetimi"));
	kaynakcayonetimi->Show(true);
	
	return true;
}
