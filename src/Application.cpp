/// @author Dr. Martin Ettl
/// @date   2015-10-20

#include "Application.hpp"
#include "wxEventClassGen.hpp"

// create the app
IMPLEMENT_APP(MyApp)

// initialize the frame
bool MyApp::OnInit()
{
    wxEventClassGen* pFrame = new wxEventClassGen(0L, wxID_ANY, _("A tool to generate a customized wxWidgets (wxEvent) class."));

    pFrame->Show();
    return true;
}
