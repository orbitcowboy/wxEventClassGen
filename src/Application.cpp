// --------------------------
/// @author ettl martin
/// @date   2012-01-24
// --------------------------

#include "Application.hpp"
#include "wxEventClassGen.hpp"

// create the app
IMPLEMENT_APP(MyApp)

// initialize the frame
bool MyApp::OnInit()
{

    wxEventClassGen* pFrame = new wxEventClassGen(0L, wxID_ANY, _("A tool to generate wxEvent classes"));

    pFrame->Show();
    return true;
}
