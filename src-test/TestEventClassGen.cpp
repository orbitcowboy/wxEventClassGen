///
/// A demo application for testing the results of wxEventClassGen
///
/// @author Dr. Martin Ettl
/// @date 2012-07-30


#include <wx/wx.h>
#include <wx/aboutdlg.h>

#include "wxTestEvent.hpp"

// Declare a wxTestEventCommandEvent
const wxEventType wxTestCommandEvent = wxNewEventType();

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class MyFrame: public wxFrame
{
        enum wxIDs
        {
            ID_ABOUT = wxID_HIGHEST
                       , ID_QUIT
            , ID_TEST
            , ID_FIRE_EVENT
        };

    public:

        MyFrame(wxFrame *frame, const wxString& title);
        ~MyFrame();


    protected:

        // event handler
        // -------------
        void OnQuit(wxCommandEvent &);
        void OnAbout(wxCommandEvent &);
        void vOnButton(wxCommandEvent &);
        void vOnTestEvent(wxTest &);

        // helper functions:
        // -----------------
        void vSetUpMenuBar(void);
        void vSetUpStatusBar(void);

        wxButton *m_pFireEventBtn;

        // menu bar stuff
        wxMenuBar   *m_pMenubar ;
        wxMenu      *m_pFileMenu;
        wxMenu      *m_pHelpMenu;

        DECLARE_EVENT_TABLE()
};


// create the app
IMPLEMENT_APP(MyApp)

// initialize the frame
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame(0L, _("wxWidgets::wxTestEventClassGen"));
    frame->Show();
    return true;
}

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

// wxEvent Table
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_QUIT            , MyFrame::OnQuit)
    EVT_MENU(ID_ABOUT           , MyFrame::OnAbout)
    EVT_TEST(ID_TEST            , MyFrame::vOnTestEvent)
    EVT_BUTTON(ID_FIRE_EVENT    , MyFrame::vOnButton)
END_EVENT_TABLE()

MyFrame::MyFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
    , m_pFireEventBtn(NULL)
    , m_pMenubar(NULL)
    , m_pFileMenu(NULL)
    , m_pHelpMenu(NULL)
{
    // set up the menu bar
    vSetUpMenuBar();

    // set up the status bar
    vSetUpStatusBar();

    m_pFireEventBtn = new wxButton(this, ID_FIRE_EVENT, wxT("Fire Event"));

}

MyFrame::~MyFrame()
{
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void MyFrame::vOnTestEvent(wxTest& event)
{
    switch(event.GetId())
    {
        case ID_TEST:
        {
            wxMessageBox( wxT("Catched custom event") );
            break;
        }
        default:
            std::cerr << "### internal error in  MyFrame::vOnTestEvent() , please report\n";
    }
}

void MyFrame::vOnButton(wxCommandEvent& event)
{
    switch(event.GetId())
    {
        case ID_FIRE_EVENT:
        {
            wxTest TestEvent;
            TestEvent.SetId(ID_TEST);
            wxPostEvent(this, TestEvent);
            break;
        }
        default:
            std::cerr << "### internal error in  MyFrame::vOnButton() , please report\n";
    }
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo AboutDialogInfo;
    AboutDialogInfo.AddDeveloper(wxT("Ettl Martin Dipl. Inf (FH)\nTechnical University of Munich\nResearch Department Satellite Geodesy\n-Fundamentalstation Wettzell -\nSackenrieder Str.25\nD-93444 Bad Koetzting\nEmail:ettl@fs.wettzell.de\n "));
    AboutDialogInfo.SetDescription(wxT("wxTestEventClassGen Demo\nby\nEttl Martin"));
    AboutDialogInfo.SetName(wxT("wxTestEventClassGen"));
    AboutDialogInfo.SetVersion(wxT(__DATE__));

    wxAboutBox(AboutDialogInfo);
}


void MyFrame::vSetUpMenuBar(void)
{
#if wxUSE_MENUS

    m_pMenubar = new wxMenuBar();

    // set up the file menu
    m_pFileMenu = new wxMenu(_T(""));
    m_pFileMenu->Append(ID_QUIT, _("&Quit\tAlt-F4"), _("Quit the application"));
    m_pMenubar->Append(m_pFileMenu, _("&File"));

    // set up the help menu
    m_pHelpMenu = new wxMenu(_T(""));
    m_pHelpMenu->Append(ID_ABOUT, _("&About\tF1"), _("Show info about this application"));
    m_pMenubar->Append(m_pHelpMenu, _("&Help"));

    // realize the menu( send it to the window)
    SetMenuBar(m_pMenubar);

#endif // wxUSE_MENUS
}

void MyFrame::vSetUpStatusBar(void)
{
#if wxUSE_STATUSBAR

    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello wxWidgets user !"), 0);
    SetStatusText(wxbuildinfo(short_f), 1);

#endif // wxUSE_STATUSBAR   
}

